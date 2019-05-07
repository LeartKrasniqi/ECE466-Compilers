/* quads.c */

#include "quads.h"

extern int lineno;
extern char file[256];
struct basic_block *curr_bb;
struct basic_block_list *curr_bb_list;
struct loop *curr_loop;
int fn_number = 1;
int bb_number = 1;
int temp_number = 0;
int string_number;
char string_buffer[4096];

/* Flag for weird if-else duplication thingy */
int if_else_flag = 0;

/* Symbol Table for Symbol references */
struct symbol_table *symbol_table;

/* Output file for the target code */
FILE *outfile;

/* Amount of stack space for local and temp variables */
int stack_space = 0;

/* Creates a new quad and appends to list of current quads */
struct quad * quad_emit(int opcode, union astnode *src1, union astnode *src2, union astnode *result)
{
	struct quad *q = malloc(sizeof(struct quad));
	if (q == NULL)
	{
		fprintf(stderr, "Error allocating new quad: %s\n", strerror(errno));
		return NULL;
	}

	q->opcode = opcode;
	q->src1 = src1;
	q->src2 = src2;
	q->result = result;

	/* Append to list of quads in current basic block */
	curr_bb->q_list = quad_list_append(q, curr_bb->q_list);

	return q;
}

/* Creates a new quad list */
struct quad_list * quad_new_list(void)
{
	struct quad_list *list = malloc(sizeof(struct quad_list));
	if (list == NULL)
	{
		fprintf(stderr, "Error allocating new quad list: %s\n", strerror(errno));
		return NULL;
	}

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

/* Append quad to list of quads in current basic block */
struct quad_list * quad_list_append(struct quad *q, struct quad_list *list)
{
	struct quad_list *l = list;
	if (l->size == 0)
	{
		l->head = q;
		l->tail = q;
	}
	else
	{
		l->tail->next = q;
		l->tail = q;
	}

	l->size++;

	return l;
}

/* Creates a temporary node */
union astnode * quad_new_temp(void)
{
	union astnode *n = astnode_alloc(AST_TEMP);
	temp_number += 1;
	n->temp.number = temp_number;

	return n;
}

/* Generates lvalue */
union astnode * quad_gen_lvalue(union astnode *node, int *mode)
{

	switch (node->gen.node_type)
	{
		case AST_NUMBER: 	/* Let the fall-through do its magic */
		case AST_CHARLIT:
		case AST_STRING: 	return NULL;

		case AST_IDENT: 	*mode = DIRECT_M;
							return node;

		case AST_UNOP: 
							/* Check for deref */
							if (node->unop.operator == '*')
							{
								*mode = INDIRECT_M;
								return quad_gen_rvalue(node->unop.left, NULL);
							}
							else 
								break; 
	}

	return NULL;
}

/* Generates rvalue, if target is NULL, we are expected to create a temporary */
union astnode * quad_gen_rvalue(union astnode *node, union astnode *target)
{
	union astnode *temp, *left, *right;
	union astnode *addr;

	struct symbol *s;
	union astnode *n;
	switch (node->gen.node_type)
	{
		case AST_IDENT: 	/* might be bypassing the array by going straight here... double check this -- check symbol table to see if it is array*/
							s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
							n = s->ast_node->scalar.node;
							while(n != NULL)
							{
								if(n->gen.node_type == AST_ARRAY)
								{
									temp = quad_new_temp();
									quad_emit(Q_LEA, n, NULL, temp);
									return temp;
								}

								n = n->gen.prev;
							}
							return node;

		case AST_NUMBER: 	/* Let the fall-through do its magic, again */ 
		case AST_CHARLIT: 	return node;

		case AST_STRING: 	/* Do some extra stuff for the target gen later */
							node->string.number = string_number;
							string_number++;
							sprintf(string_buffer + strlen(string_buffer), "\t.section .rodata\n");
							sprintf(string_buffer + strlen(string_buffer), ".string_ro_%d:\n", node->string.number);
							sprintf(string_buffer + strlen(string_buffer), "\t.string \"");
							for(int i = 0; i < node->string.length; i++)
							{
								char c = node->string.word[i];
								switch(c)
								{
									case '\0':	sprintf(string_buffer + strlen(string_buffer), "\\0"); break;
									case '\a': 	sprintf(string_buffer + strlen(string_buffer), "\\a"); break; 
									case '\b': 	sprintf(string_buffer + strlen(string_buffer), "\\b"); break;
									case '\f': 	sprintf(string_buffer + strlen(string_buffer), "\\f"); break;
									case '\n': 	sprintf(string_buffer + strlen(string_buffer), "\\n"); break;
									case '\r': 	sprintf(string_buffer + strlen(string_buffer), "\\r"); break;
									case '\t': 	sprintf(string_buffer + strlen(string_buffer), "\\t"); break;
									case '\v': 	sprintf(string_buffer + strlen(string_buffer), "\\v"); break;
									case '\'': 	sprintf(string_buffer + strlen(string_buffer), "\\\'"); break;
									case '\"': 	sprintf(string_buffer + strlen(string_buffer), "\\\""); break;
									case '\\': 	sprintf(string_buffer + strlen(string_buffer), "\\\\"); break;
									default:	if (c > 127 || c < 32)
													sprintf(string_buffer + strlen(string_buffer), "\\%03o", (unsigned char)c);
												else
													sprintf(string_buffer + strlen(string_buffer), "%c", c);
												break;
								}
							}
							sprintf(string_buffer + strlen(string_buffer), "\"\n");
							sprintf(string_buffer + strlen(string_buffer), "\t.data\n");
							sprintf(string_buffer + strlen(string_buffer), "\t.align 4\n");
							sprintf(string_buffer + strlen(string_buffer), ".string_%d:\n", node->string.number);
							sprintf(string_buffer + strlen(string_buffer), "\t.long .string_ro_%d\n", node->string.number);
													
							return node;

		case AST_UNOP: 	
							/* Check for deref */
							if (node->unop.operator == '*')
							{
								if (node->unop.left->gen.node_type == AST_ARRAY)
									return quad_gen_rvalue(node->unop.left, target);

								addr = quad_gen_rvalue(node->unop.left, NULL);
								if (target == NULL)
									target = quad_new_temp();
								quad_emit(Q_LOAD, addr, NULL, target);
								return target;
							}

							/* All other unops */
							if (target == NULL)
									target = quad_new_temp();
							union astnode *unop_expr = quad_gen_rvalue(node->unop.left, target);
							if (node->unop.operator == '&')
								quad_emit(Q_LEA, unop_expr, NULL, target);
							else if (node->unop.operator == PLUSPLUS)
							{
								/* First put the contents of variable in target */
								quad_emit(Q_MOV, unop_expr, NULL, target);

								/* Then increment the variable */
								union astnode *number = astnode_alloc(AST_NUMBER);
								number->num.int_value = 1;
								quad_emit('+', unop_expr, number, unop_expr);
							}
							else if (node->unop.operator == MINUSMINUS)
							{
								/* First put the contents of variable in target */
								quad_emit(Q_MOV, unop_expr, NULL, target);

								/* Then increment the variable */
								union astnode *number = astnode_alloc(AST_NUMBER);
								number->num.int_value = 1;
								quad_emit('-', unop_expr, number, unop_expr);
							} 

							//quad_emit(node->unop.operator, unop_expr, NULL, target);
							return target;

		case AST_BINOP: 	/* Binary Operator Case */	
							left = quad_gen_rvalue(node->binop.left, NULL);
							right = quad_gen_rvalue(node->binop.right, NULL);
							if (target == NULL)
								target = quad_new_temp();

							#if 1
							/* Pointer Arithmetic */
							if (node->binop.operator == '+' || node->binop.operator == '-')
							{
								union astnode *number = astnode_alloc(AST_NUMBER);
								//number->num.int_value = 8; 	/* Size of pointer */
								struct symbol *sl = NULL;
								struct symbol *sr = NULL;

								if (node->binop.left->gen.node_type == AST_IDENT)
									sl = symbol_table_get_info(symbol_table, node->binop.left->ident.name, OTHER_NS);
								if (node->binop.right->gen.node_type == AST_IDENT)
									sr = symbol_table_get_info(symbol_table, node->binop.right->ident.name, OTHER_NS);

								/* First check if adding pointer/array to non-pointer */
								if (sl && (sl->ast_node->scalar.node->gen.prev->gen.node_type == AST_POINTER || sl->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY) && ( (node->binop.right->gen.node_type == AST_NUMBER) ||  (node->binop.right->gen.node_type == AST_IDENT) ) )
								{
									union astnode *temp = quad_new_temp();
									if (sl->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY)
										number->num.int_value = quad_get_sizeof(sl->ast_node->scalar.node->gen.prev->array.type);
									else
										number->num.int_value = 8;
									quad_emit('*', right, number, temp);
									right = temp;
								}
								/* Unfortunately, addition is commutative so we check non-pointer added to pointer/array */
								else if (sr && (sr->ast_node->scalar.node->gen.prev->gen.node_type == AST_POINTER || sr->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY) && ( (node->binop.left->gen.node_type == AST_NUMBER) ||  (node->binop.left->gen.node_type == AST_NUMBER)) )
								{
									union astnode *temp = quad_new_temp();
									if (sr->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY)
										number->num.int_value = quad_get_sizeof(sl->ast_node->scalar.node->gen.prev->array.type);
									else
										number->num.int_value = 8;
									quad_emit('*', left, number, temp);
									left = temp;
								}
								/* Check if pointer/array + pointer/array */
								else if (sl && sr && (sl->ast_node->scalar.node->gen.prev->gen.node_type == AST_POINTER || sl->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY) && (sr->ast_node->scalar.node->gen.prev->gen.node_type == AST_POINTER || sr->ast_node->scalar.node->gen.prev->gen.node_type == AST_ARRAY) )
								{
									/* Should only be able to do pointer subtraction */
									if (node->binop.operator == '+')
									{
										fprintf(stderr, "ERROR: Pointer Addition not allowed!\n");
										exit(-1);
									}

									/* Check to make sure the pointers are the same type */
									union astnode *ptrl = sl->ast_node->scalar.node->gen.prev;
									union astnode *ptrr = sr->ast_node->scalar.node->gen.prev;

									if (ptrl->gen.node_type != ptrr->gen.node_type)
									{
										fprintf(stderr, "ERROR: Conflicting pointer types!\n");
										exit(-1);
									}

									while (ptrl->gen.node_type == ptrr->gen.node_type)
									{
										if (ptrl->gen.node_type == AST_SCALAR)
										{
											if (ptrl->scalar.type == ptrr->scalar.type)
												break;
											else
											{
												fprintf(stderr, "ERROR: Conflicting pointer types!\n");
												exit(-1);
											}
										}
										ptrl = ptrl->gen.prev;
										ptrr = ptrr->gen.prev;

										if (ptrl->gen.node_type != ptrr->gen.node_type)
										{	
											fprintf(stderr, "ERROR: Conflicting pointer types!\n");
											exit(-1);
										}

									}

									/* If we get here, then the types matched.  Now to do the actual computations... */
									union astnode *temp = quad_new_temp();

									/* Do the subtraction */
									quad_emit(node->binop.operator, left, right, temp);

									/* Then divide by the sizeof the scalar */
									union astnode *size = astnode_alloc(AST_NUMBER);
									size->num.int_value = quad_get_sizeof(ptrl);
									quad_emit('/', temp, size, target);
									return target;

								}


							}
							#endif
							
							/* Conditionals in rvalue context -- treat similar to IF statement */
							int b_op = node->binop.operator;
							if ( (b_op == '<') || (b_op == LTEQ) || (b_op == '>') || (b_op == GTEQ) || (b_op == EQEQ) || (b_op == NOTEQ) )
							{
								struct basic_block *Bt = quad_new_bb(); 	/* TRUE Arm */
								struct basic_block *Bf = quad_new_bb(); 	/* FALSE Arm */
								struct basic_block *Bn = quad_new_bb(); 	/* Statement that follows */

								/* Create branches to Bt and Bf */
								quad_gen_cond_expr(node, Bt, Bf);

								curr_bb = Bt;

								/* If true, MOV 1 into target */
								union astnode *tr = astnode_alloc(AST_NUMBER);
								tr->num.int_value = 1;
								quad_emit(Q_MOV, tr, NULL, target);

								quad_link_bb(curr_bb, ALWAYS, Bn, NULL);

								/* If false, MOV 0 into target */
								curr_bb = Bf;
								union astnode *fa = astnode_alloc(AST_NUMBER);
								fa->num.int_value = 0;
								quad_emit(Q_MOV, fa, NULL, target);
								quad_link_bb(curr_bb, ALWAYS, Bn, NULL);
								

								curr_bb = Bn;

								return target;	
							}
	

							quad_emit(node->binop.operator, left, right, target);
							return target;

		case AST_ARRAY: 	/* Array variable -- might need to add symbol table stuff to get name of array */
							temp = quad_new_temp();
							quad_emit(Q_LEA, node, NULL, temp);
							return temp;

		case AST_SIZEOF: 	/* SIZEOF */
							if (target == NULL)
								target = quad_new_temp();
							union astnode *sizeof_expr = astnode_alloc(AST_NUMBER);
							sizeof_expr->num.int_value = quad_get_sizeof(node->size_of.left);
							quad_emit(Q_MOV, sizeof_expr, NULL, target);
							return target;

		case AST_FNCALL: 	/* Function call as an r-value */
							if (target == NULL)
								target = quad_new_temp();
							quad_gen_fncall(node, target);
							return target;


	}

	fprintf(stderr, "ERROR: No proper rvalue %s:%d\n", file, lineno);
	exit(-1);
}

/* Gets size of a node */
int quad_get_sizeof(union astnode *node)
{
	struct symbol *s;
	union astnode *n;
	//int pointer_multiplier = 0;
	switch(node->gen.node_type)
	{
		case AST_CHARLIT: 	return 1;
		case AST_NUMBER: 	return 4;
		case AST_POINTER: 	return 8;

		case AST_UNOP:		if (node->unop.operator == '&')
								return 8;
							break;

		case AST_SCALAR: 	if (node->scalar.type == CHAR_T)
								return 1;
							else
								return 4;

		case AST_IDENT: 	s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
							n = s->ast_node->scalar.node;
							while(n != NULL)
							{
								// if (n->gen.node_type == AST_POINTER)
								// 	pointer_multiplier = 1;

								// if (n->gen.node_type == AST_SCALAR)
								// {
								// 	if(pointer_multiplier)
								// 		return (quad_get_sizeof(n) * 8);
								// 	else
								// 		return quad_get_sizeof(n);
								// }

								if (n->gen.node_type == AST_POINTER)
									return 8;

								if (n->gen.node_type == AST_SCALAR)
									return quad_get_sizeof(n);

								if(n->gen.node_type == AST_ARRAY)
									return (quad_get_sizeof(n->array.type) * n->array.size);

	
								n = n->gen.prev;
							}

	}

	return 256; 	/* DEBUG PURPOSES */
}


/* Parse node and determine which quad must be generated for the statement */
void * quad_gen_stmt(union astnode *node)
{
	/* List to hold the quads */
	//struct quad_list *l = quad_new_list();
	if(if_else_flag)
	{
		if_else_flag = 0;
		return NULL;
	}
	
	switch (node->gen.node_type)
	{
		case AST_COMPOUND_ST: 	/* Just do each statement */
								quad_gen_stmt(node->compound_st.body);
								node = node->compound_st.body;
								while(node->gen.next != NULL)
								{
									quad_gen_stmt(node->gen.next);
									node = node->gen.next;
								}
								break;

		case AST_ASSIGN: 		/* Assignment */
								quad_gen_assign(node);
								break;

		case AST_IF_ST: 		/* IF Statement -- Fall through to IF-ELSE as well */

		case AST_IF_ELSE_ST: 	/* IF-ELSE Statement */
								quad_gen_if(node);
								break;

		case AST_WHILE_ST: 		/* WHILE Statement */
								quad_gen_while(node);
								break;

		case AST_DO_WHILE_ST: 	/* DO-WHILE Statement */
								quad_gen_do_while(node);
								break;

		case AST_FOR_ST: 		/* FOR Statement */
								quad_gen_for(node);
								break;

		case AST_RETURN_ST: 	/* RETURN Statement */
								quad_gen_return(node);
								break;

		case AST_BREAK_ST: 		/* BREAK Statement */
								quad_gen_break(node);
								break;

		case AST_CONT_ST: 		/* CONTINUE Statement */
								quad_gen_continue(node);
								break;

		case AST_UNOP: 			/* Should only work for a++ or a-- */
								if ( (node->unop.operator == PLUSPLUS) || (node->unop.operator == MINUSMINUS) )
									quad_gen_unop(node);
								break;

		case AST_FNCALL: 		/* Function Call */
								quad_gen_fncall(node, NULL);
								break;
	}

	return NULL;
}



/* Generate assignment quad */
union astnode * quad_gen_assign(union astnode *node)
{
	union astnode *dest;	/* Destination node */ 
	union astnode *t1;		/* Temporary node */ 
	int dest_mode; 			/* Will be set by quad_gen_lvalue() */

	dest = quad_gen_lvalue(node->assign.left, &dest_mode);

	if (dest == NULL)
		fprintf(stderr, "ERROR: Invalid LHS of assignment\n");
	if (dest_mode == DIRECT_M)
	{
		t1 = quad_gen_rvalue(node->assign.right, dest);
		//if (t1->gen.node_type == AST_NUMBER)
			quad_emit(Q_MOV, t1, NULL, dest);
	}
	else
	{
		t1 = quad_gen_rvalue(node->assign.right, NULL);
		quad_emit(Q_STORE, t1, dest, NULL);
	}

	return dest;

}

/* Generate IF quad */
union astnode * quad_gen_if(union astnode *node)
{
	struct basic_block *Bt = quad_new_bb(); 	/* TRUE Arm */
	struct basic_block *Bf = quad_new_bb(); 	/* FALSE Arm */
	struct basic_block *Bn; 					/* Statement that follows the IF Statement */

	/* Determine what follows the IF part */
	if ( (node->gen.node_type == AST_IF_ELSE_ST) && (node->if_else_st.next != NULL) )
		Bn = quad_new_bb();
	else
		Bn = Bf;

	/* Create branches to Bt and Bf */
	quad_gen_cond_expr(node->if_st.cond, Bt, Bf);

	curr_bb = Bt;

	/* Make use of the fact that unions are laid out consistently ... hopefully */
	quad_gen_stmt(node->if_st.if_true);

	quad_link_bb(curr_bb, ALWAYS, Bn, NULL);

	if( (node->gen.node_type == AST_IF_ELSE_ST) && (node->if_else_st.next != NULL) )
	{
		curr_bb = Bf;

		quad_gen_stmt(node->if_else_st.next);
		if_else_flag = 1;
		quad_link_bb(curr_bb, ALWAYS, Bn, NULL);
	}

	curr_bb = Bn;

	return NULL;	
}

/* Generate a conditional expression (used in quad_gen_if) */
union astnode * quad_gen_cond_expr(union astnode *node, struct basic_block *Bt, struct basic_block *Bf)
{
	/* Format: left COND_OPERATOR right */
	union astnode *left, *right;
	switch (node->gen.node_type)
	{
		case AST_ASSIGN: 	/* Assignment */
							left = quad_gen_assign(node);
							right = astnode_alloc(AST_NUMBER);
							right->num.int_value = 0;
							quad_emit(Q_COMP, left, right, NULL);
							quad_link_bb(curr_bb, COND_NEQ, Bt, Bf);
							break;

		case AST_UNOP: 		/* Unary Operation */
							left = quad_gen_rvalue(node, NULL);
							right = astnode_alloc(AST_NUMBER);
							right->num.int_value = 0;
							quad_emit(Q_COMP, left, right, NULL);
							quad_link_bb(curr_bb, COND_NEQ, Bt, Bf);

		case AST_BINOP: 	/* Binary Operation */
							left = quad_gen_rvalue(node->binop.left, NULL);
							right = quad_gen_rvalue(node->binop.right, NULL);
							quad_emit(Q_COMP, left, right, NULL);
							switch (node->binop.operator)
							{
								case '<': 		quad_link_bb(curr_bb, COND_LT, Bt, Bf); 	break;
								case LTEQ: 		quad_link_bb(curr_bb, COND_LTEQ, Bt, Bf); 	break;
								case '>': 		quad_link_bb(curr_bb, COND_GT, Bt, Bf); 	break;
								case GTEQ: 		quad_link_bb(curr_bb, COND_GTEQ, Bt, Bf); 	break;
								case EQEQ: 		quad_link_bb(curr_bb, COND_EQ, Bt, Bf); 	break;
								case NOTEQ: 	quad_link_bb(curr_bb, COND_NEQ, Bt, Bf); 	break;
								default: 		printf("error(binop in gen_cond_expr)\n");
							}
							break;

		case AST_NUMBER: 	/* Number */
		case AST_CHARLIT: 	/* Character Literal */

		case AST_IDENT: 	/* Identifier */
							left = quad_gen_rvalue(node, NULL);
							right = astnode_alloc(AST_NUMBER);
							right->num.int_value = 0;
							quad_emit(Q_COMP, left, right, NULL);
							quad_link_bb(curr_bb, COND_NEQ, Bt, Bf);
							break;

	}

	return NULL;
}



/******************************************************
					LOOP STUFF 
******************************************************/

/* Create a new loop */
struct loop * quad_new_loop(void)
{
	struct loop *l = malloc(sizeof(struct loop));
	if (l == NULL)
	{
		fprintf(stderr, "Error allocating new loop: %s\n", strerror(errno));
		return NULL;
	}

	l->prev = curr_loop;

	return l;
}


void * quad_gen_while(union astnode *node)
{
	struct basic_block *bb_cond = quad_new_bb(); 	/* Condition */
	struct basic_block *bb_body = quad_new_bb(); 	/* Body */
	struct basic_block *bb_next = quad_new_bb(); 	/* Next bb after loop */

	curr_loop = quad_new_loop();
	curr_loop->bb_continue = bb_cond;
	curr_loop->bb_break = bb_next;

	/* Link current bb to beginning of WHILE loop and set the new bb to the condition check in the WHILE loop */
	quad_link_bb(curr_bb, ALWAYS, bb_cond, NULL);
	curr_bb = bb_cond;

	/* Check the conditional expression, if true, branch to body, if false, branch to next */
	quad_gen_cond_expr(node->while_st.cond, bb_body, bb_next);

	/* Now, deal with the body */
	curr_bb = bb_body;
	quad_gen_stmt(node->while_st.body);

	/* Link back to the condition */
	quad_link_bb(curr_bb, ALWAYS, bb_cond, NULL);

	/* Once loop is finished, move onto the next bb and remove loop from list of loops */
	curr_bb = bb_next;
	curr_loop = curr_loop->prev;

	return NULL;

}

void * quad_gen_do_while(union astnode *node)
{
	struct basic_block *bb_cond = quad_new_bb(); 	/* Condition */
	struct basic_block *bb_body = quad_new_bb(); 	/* Body */
	struct basic_block *bb_next = quad_new_bb(); 	/* Next bb after loop */

	curr_loop = quad_new_loop();
	curr_loop->bb_continue = bb_cond;
	curr_loop->bb_break = bb_next;

	/* Link current bb to beginning of DO-WHILE loop and set the new bb to the body in the DO-WHILE loop */
	quad_link_bb(curr_bb, ALWAYS, bb_body, NULL);
	curr_bb = bb_body;

	quad_gen_stmt(node->do_while_st.body);

	/* Link to condition */
	quad_link_bb(curr_bb, ALWAYS, bb_cond, NULL);
	curr_bb = bb_cond;

	/* Check the conditional expression, if true, branch to body, if false, branch to next */
	quad_gen_cond_expr(node->do_while_st.cond, bb_body, bb_next);

	/* Once loop is finished, move onto the next bb and remove loop from list of loops */
	curr_bb = bb_next;
	curr_loop = curr_loop->prev;

	return NULL;

}

/* Using alternative form, faster when there are more loop iterations */
void * quad_gen_for(union astnode *node)
{
	struct basic_block *bb_cond = quad_new_bb(); 	/* Condition */
	struct basic_block *bb_body = quad_new_bb(); 	/* Body */
	struct basic_block *bb_incr = quad_new_bb(); 	/* Increment */
	struct basic_block *bb_next = quad_new_bb(); 	/* Next bb after loop */

	curr_loop = quad_new_loop();
	curr_loop->bb_continue = bb_incr;
	curr_loop->bb_break = bb_next;

	/* The initial clause of the loop */
	quad_gen_assign(node->for_st.left);

	/* Link to condition check */
	quad_link_bb(curr_bb, ALWAYS, bb_cond, NULL);
	curr_bb = bb_cond;

	/* If true, go back to body, if false go to next bb after the loop */
	quad_gen_cond_expr(node->for_st.cond, bb_body, bb_next);

	/* Now, deal with the body */
	curr_bb = bb_body;
	quad_gen_stmt(node->for_st.body);
	quad_link_bb(curr_bb, ALWAYS, bb_incr, NULL);

	/* Now, deal with the increment */
	curr_bb = bb_incr;
	quad_gen_stmt(node->for_st.right);
	quad_link_bb(curr_bb, ALWAYS, bb_cond, NULL);

	/* Once loop is finished, move onto the next bb and remove loop from list of loops */
	curr_bb = bb_next;
	curr_loop = curr_loop->prev;

	return NULL;
	
}

void * quad_gen_break(union astnode *node)
{
	/* Should just go to break point of loop */
	quad_link_bb(curr_bb, ALWAYS, curr_loop->bb_break, NULL);
	return NULL;
}

void * quad_gen_continue(union astnode *node)
{
	/* Should just go to continue point of loop */
	quad_link_bb(curr_bb, ALWAYS, curr_loop->bb_continue, NULL);
	return NULL;
}

void * quad_gen_return(union astnode *node)
{
	union astnode *ret_val = NULL;
	/* Should just go to exit node of function */
	if (node->return_st.ret != NULL)
		ret_val = quad_gen_rvalue(node->return_st.ret, NULL);

	quad_emit(Q_RETURN, ret_val, NULL, NULL);
	return NULL;
}

void * quad_gen_unop(union astnode *node)
{
	union astnode *number = astnode_alloc(AST_NUMBER);
	number->num.int_value = 1;

	if (node->unop.operator == PLUSPLUS)
		quad_emit('+', node->unop.left, number, node->unop.left);
	else if (node->unop.operator == MINUSMINUS)
		quad_emit('-', node->unop.left, number, node->unop.left);
	
	return NULL; 
}

void * quad_gen_fncall(union astnode *node, union astnode *target)
{
	union astnode *n = malloc(sizeof(union astnode));
	union astnode *n2 = node;
	union astnode *arg;
	int n_arg = 1;
	int total_arg = 0;

	n2 = n2->fncall.right;
	total_arg++;
	while (n2->gen.next != NULL)
	{
		total_arg++;
		n2 = n2->gen.next;
	}

	/* Buffer to store the contents of node */
	if (memcpy(n, node, total_arg * sizeof(union astnode)) == NULL)
		fprintf(stderr, "Error allocating memory for function arguments in quad_gen_fncall: %s\n", strerror(errno));

	/* Reverse the order for the pushl opcode */
	n = astnode_reverse(n->fncall.right, NEXT);
	
	/* Dealing with arguments (in reversed order) */
	while(n != NULL)
	{
		union astnode *number = astnode_alloc(AST_NUMBER);
		number->num.int_value = total_arg - n_arg;
		if (n->gen.node_type == AST_BINOP || n->gen.node_type == AST_UNOP)
			arg = quad_gen_rvalue(n, NULL);
		else
			arg = n;
		quad_emit(Q_ARG, number, arg, NULL);
		n_arg++;
		n = n->gen.next;
	}

	/* Now the function itself */
	union astnode *num_arg = astnode_alloc(AST_NUMBER);
	num_arg->num.int_value = total_arg;
	quad_emit(Q_CALL, node->fncall.left, num_arg, target);

	// /* Dealing with arguments -- kept in same order in case I want to use movl instead of pushl */
	// union astnode *number = astnode_alloc(AST_NUMBER);
	// if(n->fncall.right->gen.node_type == AST_BINOP || n->fncall.right->gen.node_type == AST_UNOP)
	// 	arg = quad_gen_rvalue(n->fncall.right, NULL);
	// else
	// 	arg = n->fncall.right;
	// quad_emit(Q_ARG, number, arg, NULL);
	// n_arg++;
	// n = n->fncall.right;
	// while (n->gen.next != NULL)
	// {
	// 	union astnode *number = astnode_alloc(AST_NUMBER);
	// 	number->num.int_value = n_arg;
	// 	if (n->gen.next->gen.node_type == AST_BINOP || n->gen.next->gen.node_type == AST_UNOP)
	// 		arg = quad_gen_rvalue(n->gen.next, NULL);
	// 	else
	// 		arg = n->gen.next;
	// 	quad_emit(Q_ARG, number, arg, NULL);
	// 	n_arg++;
	// 	n = n->gen.next;
	// }

	/* Now the function itself */
	// n2 = n2->fncall.right;
	// n_arg2++;
	// while (n2->gen.next != NULL)
	// {
	// 	n_arg2++;
	// 	n2 = n2->gen.next;
	// }

	return NULL;
}






/* Print out the quads */
void print_quads(struct quad *q)
{
	if (q == NULL)
		return;

	printf("\t");
	/* The lvalue is either a temp or an ident */
	if (q->result != NULL)
	{
		if (q->result->gen.node_type == AST_IDENT)
		{
			/* Get info from symbol table */
			struct symbol *s = symbol_table_get_info(symbol_table, q->result->ident.name, OTHER_NS);
			printf("%s", s->name);
			if(s->storage_class == AUTO_T)
				printf("{local} = ");
			else
				printf("{globl} = ");
		}
		else if (q->result->gen.node_type == AST_TEMP)
			printf("%%T%05d = ", q->result->temp.number);
	}


	/* Check opcode and print out the proper stuff */
	switch(q->opcode)
	{
		case '+': 	/* ADD */
					printf("ADD ");
					print_rval(q->src1);
					printf(", ");
					print_rval(q->src2);
					printf("\n");
					break;

		case '-': 	/* SUB */
					printf("SUB ");
					print_rval(q->src1);
					printf(", ");
					print_rval(q->src2);
					printf("\n");
					break;

		case '*': 	/* MUL */
					printf("MUL ");
					print_rval(q->src1);
					printf(", ");
					print_rval(q->src2);
					printf("\n");
					break;

		case '/': 	/* DIV */
					printf("DIV ");
					print_rval(q->src1);
					printf(", ");
					print_rval(q->src2);
					printf("\n");
					break;

		case Q_LOAD: 	/* LOAD Operation */
						printf("LOAD ");
						if (q->src1->gen.node_type == AST_TEMP)
							printf(" [%%T%05d]", q->src1->temp.number);
						else
							print_rval(q->src1);
						printf("\n");
						break;

		case '&':
		case Q_LEA: 	/* LEA Operation */
						printf("LEA ");
						print_rval(q->src1);
						printf("\n");
						break;

		case Q_MOV: 	/* MOV Operation */
						printf("MOV ");
						print_rval(q->src1);
						printf("\n");
						break;

		case Q_STORE: 	/* STORE Operation */
						printf("STORE ");
						print_rval(q->src1);
						printf(", ");
						print_rval(q->src2);
						printf("\n");
						break;

		case Q_COMP: 	/* COMP Operation */
						printf("COMP ");
						print_rval(q->src1);
						printf(", ");
						print_rval(q->src2);
						printf("\n");
						break;

		case Q_ARG: 	/* Function Call Arguments */
						printf("ARG ");
						print_rval(q->src1); 	/* Should just be the index of the current argument */
						printf(", ");
						print_rval(q->src2);
						printf("\n");
						break;

		case Q_CALL: 	/* Function Call itself */
						printf("CALL ");
						print_rval(q->src1); 	/* Should be address of function */
						printf(", ");
						print_rval(q->src2); 	/* Should be number of arguments */
						printf("\n");
						break;

		case Q_RETURN: 	/* Return Statement */
						printf("RETURN ");
						print_rval(q->src1);
						printf("\n");
						break;
	}					

}

/* Helper function to print out rvalue in print_quads */
void print_rval(union astnode *node)
{
	if (node == NULL)
		return;

	if (node->gen.node_type == AST_IDENT)
	{
		struct symbol *s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
		printf("%s", node->ident.name);
		if(s->storage_class == AUTO_T)
			printf("{local}");
		else
			printf("{globl}");
	}
	
	if (node->gen.node_type == AST_TEMP)
		printf("%%T%05d", node->temp.number);
	
	if (node->gen.node_type == AST_NUMBER)
		printf("%llu", node->num.int_value);

	if (node->gen.node_type == AST_CHARLIT)
		printf("%c", (unsigned char)node->charlit.c);

	if (node->gen.node_type == AST_ARRAY)
	{
		struct symbol *s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
		printf("%s", node->array.name);
		if(s->storage_class == AUTO_T)
			printf("{local}");
		else
			printf("{globl}");
	}

	if (node->gen.node_type == AST_STRING)
	{
		for(int i = 0; i < node->string.length; i++)
			print_char(node->string.word[i]);

		/* Do this for the target code gen later */
		quad_gen_rvalue(node, NULL);
	}

}




/******************************************************
				 BASIC BLOCK STUFF
******************************************************/

/* Create a new basic block */
struct basic_block * quad_new_bb(void)
{

	struct basic_block *bb = malloc(sizeof(struct basic_block));
	if (bb == NULL)
	{
		fprintf(stderr, "Error allocating new basic block: %s\n", strerror(errno));
		return NULL;
	}

	char temp[256] = {0};
	sprintf(temp, ".BB.%d.%d", fn_number, bb_number);
	bb_number++;

	bb->label = strdup(temp);
	bb->q_list = quad_new_list();

	/* Append basic block to current list of basic blocks */
	curr_bb_list = quad_bb_list_append(bb, curr_bb_list);

	return bb;
}

/* Create a new list of basic blocks */
struct basic_block_list * quad_new_bb_list(void)
{
	struct basic_block_list *list = malloc(sizeof(struct basic_block_list));
	if (list == NULL)
	{
		fprintf(stderr, "Error allocating new bb list: %s\n", strerror(errno));
		return NULL;
	}

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

/* Append basic block to current list of basic blocks */
struct basic_block_list * quad_bb_list_append(struct basic_block *bb, struct basic_block_list *list)
{
	struct basic_block_list *l = list;

	/* This should only happen in the first run when first allocating the curr_list */
	if (l == NULL)
		l = quad_new_bb_list();

	if (l->size == 0)
	{
		l->head = bb;
		l->tail = bb;
	}
	else
	{
		l->tail->next = bb;
		l->tail = bb;
	}

	l->size++;

	return l;
}

/* Link basic blocks together */
struct basic_block * quad_link_bb(struct basic_block *bb, int branch, struct basic_block *left, struct basic_block *right)
{
	bb->branch = branch;
	bb->left = left;
	bb->right = right;

	return bb;
}

/* Print out the bb */
void print_bb(struct basic_block *block)
{
	if (block != NULL)
	{
		struct basic_block *bb = block;
		struct quad *q = bb->q_list->head;
		printf("%s:\n", bb->label);

		/* Print quads in the bb */
		while (q != NULL)
		{
			print_quads(q);
			q = q->next;
		}

		printf("\t");
		/* Print the branch onto the next bb */
		switch (bb->branch)
		{
			case NEVER: 		break;
			case ALWAYS:		printf("BR %s\n", bb->left->label); break;
			case COND_LT:		printf("BRLT %s %s\n", bb->left->label, bb->right->label); break;
			case COND_GT:		printf("BRGT %s %s\n", bb->left->label, bb->right->label); break;
			case COND_LTEQ: 	printf("BRLE %s %s\n", bb->left->label, bb->right->label); break;
			case COND_GTEQ: 	printf("BRGE %s %s\n", bb->left->label, bb->right->label); break;
			case COND_EQ: 		printf("BREQ %s %s\n", bb->left->label, bb->right->label); break;
			case COND_NEQ: 		printf("BRNE %s %s\n", bb->left->label, bb->right->label); break;
		}

		/* Move onto the next bb in the list of bbs */
		print_bb(bb->next);
	}
}



/******************************************
	THIS IS WHAT ULTIMATELY GETS CALLED
******************************************/

/* Puts everything together and generates quads for a function */
void * gen_fn_quads(union astnode *function, union astnode *stmt, struct symbol_table *sym_tab, FILE *f)
{
	/* Useful for getting info about idents */
	symbol_table = sym_tab;

	curr_bb_list = quad_new_bb_list();
	curr_bb = quad_new_bb();
	curr_bb->q_list = quad_new_list();


	printf("\n\n---------- QUADS BEGIN ----------\n");

	printf("%s:\n", function->ident.name);

	union astnode *n = stmt;
	while (n != NULL)
	{
		/* Skip printing of ident declarations */
		if (n->gen.node_type == AST_IDENT)
			n = n->gen.next;

		quad_gen_stmt(n);
		n = n->gen.next;
	}

	print_bb(curr_bb_list->head);
	printf("\n---------- QUADS END ----------\n\n");

	/* Generate the target code */
	outfile = f;
	global_setup();
	fn_prologue(function);
	target_print_bb(curr_bb_list->head);


	/* Increase the function number and reset the bb_number for the next function */
	fn_number++;
	bb_number = 1;
	temp_number = 0; 	/* Can reset this because the temp registers are just like local vars in the function (i.e. can be reassigned) */
	memset(string_buffer, 0, 4096);

	return NULL;
}



/******************************************
	Target Gen Stuff
******************************************/

void global_setup()
{
	/* Set up the global stuff only for the first function */
	if (fn_number != 1)
		return;

	/* Get first symbol in the GLOBAL symbol table */
	struct symbol *s = symbol_table->prev->head;
	
	/* Print stuff for each global symbol */
	while (s != NULL)
	{
		if (s->ast_node->gen.node_type == AST_SCALAR)
		{
			int size = quad_get_sizeof(s->ast_node->scalar.node);
			fprintf(outfile, "\t.comm %s, %d, %d\n", s->name, size, (size == 1 || size == 2)?size:4);
		}
		else if (s->ast_node->gen.node_type == AST_FN)
		{
			fprintf(outfile, "\t.globl %s\n", s->name);
			fprintf(outfile, "\t.type %s, @function\n", s->name);
		}

		s = s->next;
	}

	fprintf(outfile, "%s", string_buffer);

}


void fn_prologue(union astnode *function)
{
	/* Get stack space for local variables, as well as declare variables in the other storage classes */
	struct symbol *s = symbol_table->head;
	while (s != NULL)
	{
		if (s->ast_node->gen.node_type == AST_SCALAR)
		{
			if (s->storage_class == EXTERN_T)
			{
				int size = quad_get_sizeof(s->ast_node->scalar.node);
				fprintf(outfile, "\t.comm %s, %d, %d\n", s->name, size, (size == 1 || size == 2)?size:4);
			}
			else if (s->storage_class == STATIC_T)
			{
				int size = quad_get_sizeof(s->ast_node->scalar.node);
				fprintf(outfile, "\t.local%s.%d\n", s->name, fn_number);
				fprintf(outfile, "\t.comm %s.%d, %d, %d\n", s->name, fn_number, size, (size == 1 || size == 2)?size:4);
			}
			else
				stack_space = s->frame_offset;
		}

		s = s->next;
	}

	/* Allign to 4-byte boundary */
	while ( (stack_space % 4) != 0 )
		stack_space++;

	/* Add the temporary variables to the stack frame offset (each is 4 bytes which ensures 4-byte allignment after above code) */
	stack_space += (temp_number * 4);

	fprintf(outfile, "\t.text\n");
	fprintf(outfile, "%s:\n", function->ident.name);
	fprintf(outfile, "\tpushl %%ebp\n");
	fprintf(outfile, "\tmovl %%esp, %%ebp\n");
	fprintf(outfile, "\tsubl $%d, %%esp\n", stack_space);

}
#if 1
/* Print out the target bb */
void target_print_bb(struct basic_block *block)
{
	if (block != NULL)
	{
		struct basic_block *bb = block;
		struct quad *q = bb->q_list->head;
		fprintf(outfile, "%s:\n", bb->label);

		/* Print quads in the bb */
		while (q != NULL)
		{
			translate_quads(q);
			q = q->next;
		}

		fprintf(outfile, "\t");
		/* Print the branch onto the next bb */
		switch (bb->branch)
		{
			case NEVER: 		break;

			case ALWAYS:		fprintf(outfile, "jmp %s\n", bb->left->label); 
								break;

			case COND_LT:		fprintf(outfile, "jl %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;

			case COND_GT:		fprintf(outfile, "jg %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;

			case COND_LTEQ: 	fprintf(outfile, "jle %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;

			case COND_GTEQ: 	fprintf(outfile, "jge %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;

			case COND_EQ: 		fprintf(outfile, "je %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;

			case COND_NEQ: 		fprintf(outfile, "jne %s\n", bb->left->label);
								fprintf(outfile, "\tjmp %s\n", bb->right->label);
								break;
		}

		/* Move onto the next bb in the list of bbs */
		target_print_bb(bb->next);
	}
}

/* Translate the quads to X86-32 Assembly */
void translate_quads(struct quad *q)
{
	if (q == NULL)
		return;

	fprintf(outfile, "\t");

	/* Check opcode and print out the proper stuff */
	switch(q->opcode)
	{
		case '+': 	/* ADD */
					fprintf(outfile, "movl ");
					target_print(q->src1);
					fprintf(outfile, ", %%ecx\t#add\n");

					fprintf(outfile, "\taddl ");
					target_print(q->src2);
					fprintf(outfile, ", %%ecx\n");

					fprintf(outfile, "\tmovl %%ecx, ");
					target_print(q->result);
					fprintf(outfile, "\n");

					break;

		case '-': 	/* SUB */
					fprintf(outfile, "movl ");
					target_print(q->src1);
					fprintf(outfile, ", %%ecx\t#sub\n");

					fprintf(outfile, "\tsubl ");
					target_print(q->src2);
					fprintf(outfile, ", %%ecx\n");

					fprintf(outfile, "\tmovl %%ecx, ");
					target_print(q->result);
					fprintf(outfile, "\n");

					break;

		case '*': 	/* MUL -- this is slighlty special, need to use eax and edx combo */
					fprintf(outfile, "movl ");
					target_print(q->src1);
					fprintf(outfile, ", %%eax\t#mul\n");

					/* Clear contents of edx */
					fprintf(outfile, "\txor %%edx, %%edx\n");

					fprintf(outfile, "\tmovl ");
					target_print(q->src2);
					fprintf(outfile, ", %%ebx\n");

					fprintf(outfile, "\tmul %%ebx\n");
					fprintf(outfile, "\tmovl %%eax, ");
					target_print(q->result);
					fprintf(outfile, "\n");

					break;

		case '/': 	/* DIV -- this is slighlty special, need to use eax and edx combo */
					/* Dividend */
					fprintf(outfile, "movl ");
					target_print(q->src1);
					fprintf(outfile, ", %%eax\t#div\n");

					/* Clear contents of edx */
					fprintf(outfile, "\txor %%edx, %%edx");

					/* Divisor -- has to be a register */
					fprintf(outfile, "\tmovl ");
					target_print(q->src2);
					fprintf(outfile, ", %%ebx\n");

					/* Do the division (result is in eax) */
					fprintf(outfile, "\tdiv %%ebx\n");
					fprintf(outfile, "\tmovl %%eax, ");
					target_print(q->result);
					fprintf(outfile, "\n");

					break;

		case Q_LOAD: 	/* LOAD Operation */
						//fprintf(outfile, "lea ");
						// target_print(q->src1);
						// fprintf(outfile, ", %%ecx\n");

						fprintf(outfile, "movl ");
						target_print(q->src1);
						fprintf(outfile, ", %%ecx\t#load\n");

						fprintf(outfile, "\tmovl (%%ecx), %%ebx\n");

						fprintf(outfile, "\tmovl %%ebx, ");
						target_print(q->result);
						fprintf(outfile, "\n");
						
						break;						
						
		case '&':
		case Q_LEA: 	/* LEA Operation */
						fprintf(outfile, "lea ");
						//fprintf(outfile, "movl ");
						target_print(q->src1);
						fprintf(outfile, ", %%ecx\t#lea\n");

						fprintf(outfile, "\tmovl %%ecx, ");
						target_print(q->result);
						fprintf(outfile, "\n");

						break;

		case Q_MOV: 	/* MOV Operation */
						fprintf(outfile, "movl ");
						target_print(q->src1);
						fprintf(outfile, ", %%ecx\t#mov\n");

						fprintf(outfile, "\tmovl %%ecx, ");
						target_print(q->result);
						fprintf(outfile, "\n");

						break;

		case Q_STORE: 	/* STORE Operation */
						//fprintf(outfile, "lea ");
						fprintf(outfile, "movl ");
						target_print(q->src1);
						fprintf(outfile, ", %%ecx\t#store\n");

						fprintf(outfile, "\tmovl ");
						target_print(q->src2);
						fprintf(outfile, ", %%ebx\n");

						fprintf(outfile, "\tmovl %%ecx, (%%ebx)\n");

						break;

		case Q_COMP: 	/* COMP Operation */
						fprintf(outfile, "movl ");
						target_print(q->src1);
						fprintf(outfile, ", %%ecx\t#comp\n");

						fprintf(outfile, "\tmovl ");
						target_print(q->src2);
						fprintf(outfile, ", %%ebx\n");

						fprintf(outfile, "\tcmp %%ebx, %%ecx\n");

						break;

		case Q_ARG: 	/* Function Call Arguments */
						/* Put arguments into ecx and then push them onto the stack one by one */
						fprintf(outfile, "movl ");
						target_print(q->src2);
						fprintf(outfile, ", %%ecx\t#arg\n");

						fprintf(outfile, "\tpushl %%ecx\n");

						break;

		case Q_CALL: 	/* Function Call itself */
						fprintf(outfile, "call ");
						target_print(q->src1);
						fprintf(outfile, "\t#call\n");

						/* Time to re-adjust esp */
						union astnode *n = astnode_alloc(AST_NUMBER);
						n->num.int_value = q->src2->num.int_value * 4;
						fprintf(outfile, "\taddl ");
						target_print(n);
						fprintf(outfile, ", %%esp\n"); 

						/* If destination is not null, put result (i.e. eax) into destination */
						if(q->result != NULL)
						{
							fprintf(outfile, "\tmovl %%eax, ");
							target_print(q->result);
							fprintf(outfile, "\n");
						}

						break;

		case Q_RETURN: 	/* Return Statement */
						/* Put return value into eax */					
						if (q->src1 != NULL)
						{
							fprintf(outfile, "movl ");
							target_print(q->src1);
							fprintf(outfile, ", %%eax\t#return\n");
							fprintf(outfile, "\t");
						}

						fprintf(outfile, "leave\n");
						fprintf(outfile, "\tret\n");

						break;
	}					

}

/* Helper function to print out addressing mode in print_quads */
void target_print(union astnode *node)
{
	if (node == NULL)
		return;

	if (node->gen.node_type == AST_IDENT)
	{
		struct symbol *s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
		if (s->storage_class == AUTO_T)
			fprintf(outfile, "-%d(%%ebp)", s->frame_offset);
		else if (s->storage_class == STATIC_T)
			fprintf(outfile, "%s.%d", s->name, fn_number);
		else
		{
			fprintf(outfile, "%s", s->name);
			// if (s->ast_node->gen.node_type == AST_FN)
			// 	fprintf(outfile, "%s", s->name);
			// else
			// 	fprintf(outfile, "$%s", s->name);
		}
	}
	
	if (node->gen.node_type == AST_TEMP)
	{
		int temp_offset = (stack_space - (4 * temp_number)) + (4 * node->temp.number);
		fprintf(outfile, "-%d(%%ebp)", temp_offset);
	}
	
	if (node->gen.node_type == AST_NUMBER)
		fprintf(outfile, "$%llu", node->num.int_value);

	if (node->gen.node_type == AST_CHARLIT)
		printf("$%d", (unsigned char)node->charlit.c);

	if (node->gen.node_type == AST_ARRAY)
	{
		struct symbol *s = symbol_table_get_info(symbol_table, node->ident.name, OTHER_NS);
		if (s->storage_class == AUTO_T)
			fprintf(outfile, "-%d(%%ebp)", s->frame_offset);
		else if (s->storage_class == STATIC_T)
			fprintf(outfile, "%s.%d", s->name, fn_number);
		else
			fprintf(outfile, "%s", s->name);
	}

	if (node->gen.node_type == AST_STRING)
		fprintf(outfile, ".string_%d", node->string.number);

}	

#endif















