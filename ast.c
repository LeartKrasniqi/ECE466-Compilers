/* ast.c */
#include "ast.h"

/* Allocates new AST node */
union astnode * astnode_alloc(int node_type)
{
	union astnode *n = malloc(sizeof(union astnode));
	if (n == NULL)
	{
		fprintf(stderr, "Error allocating new AST node: %s\n", strerror(errno));
		return NULL;
	}

	n->gen.node_type = node_type;
	n->gen.prev = NULL;
	n->gen.next = NULL;

	return n;
}

union astnode * astnode_append(union astnode *root, union astnode *new, int direction)
{
	if (root == NULL)
		return new;

	if (direction == PREV)
	{
		union astnode *temp = root;
		while(root->gen.prev != NULL)
			root = root->gen.prev;
		root->gen.prev = new;
		return temp;
	}
	else if (direction == NEXT)
	{
		union astnode *temp = root;
		while (root->gen.next != NULL)
			root = root->gen.next;
		root->gen.next = new;
		return temp;
	}
	else
		return NULL;
}

union astnode * astnode_reverse(union astnode *root, int direction)
{
	union astnode *new_root = NULL;
	while (root != NULL)
	{
		union astnode *temp;
		if (direction == PREV)
		{
			temp = root->gen.prev;
			root->gen.prev = new_root;
		}
		else if (direction == NEXT)
		{
			temp = root->gen.next;
			root->gen.next = new_root;
		}

		new_root = root;
		root = temp;
	}

	return new_root;
}

/* Find return value of a function or array */
union astnode * find_ret_value(union astnode *root)
{
	union astnode *n = root;
	while (n != NULL)
	{
		if (n->gen.node_type == AST_SCALAR) //|| (n->gen.node_type == AST_POINTER) )
		{
			//printf("scalar\n");
			return n;
		}
		else if (n->gen.node_type == AST_POINTER)
		{
			//printf("pointer\n");
			return n;
		}
		n = n->gen.prev;
	}
	//printf("nothing\n");
	return NULL;
}

/* Prints out AST */
#if 0
void print_ast(union astnode *root, int level)
{	
	/* Avoid additional spacing for the expression lists */
	if(root->gen.node_type != AST_EXPR_LIST)
	{
		for (int i = 0; i < level; i++)
			fprintf(stdout, "  ");
	}

	if (root == NULL)
	{
		fprintf(stdout, "NULL\n");
		return;
	}

	switch (root->gen.node_type)
	{
		case AST_ASSIGN:	fprintf(stdout, "ASSIGNMENT\n");
							print_ast(root->assign.left, level + 1);
							print_ast(root->assign.right, level + 1);
							break;

		case AST_UNOP:		fprintf(stdout, "UNARY OP %d", root->unop.operator);
							if(root->unop.operator < 255)
								fprintf(stdout, " (%c)\n",  (unsigned char)root->unop.operator);
							else
								fprintf(stdout, " (%s)\n",  print_kw(root->unop.operator));
							print_ast(root->unop.left, level + 1);
							break;

		case AST_BINOP:		fprintf(stdout, "BINARY OP %d", root->binop.operator);
							if(root->binop.operator < 255)
								fprintf(stdout, " (%c)\n", (unsigned char)root->binop.operator);
							else
								fprintf(stdout, " (%s)\n", print_kw(root->binop.operator));
							print_ast(root->binop.left, level + 1);
							print_ast(root->binop.right, level + 1);
							break;

		case AST_IDENT:		fprintf(stdout, "IDENT %s\n", root->ident.name); //This was good

		case AST_NUMBER:	fprintf(stdout, "NUMBER: (numtype = ");
							switch(root->num.type)
							{
								case INT_T:			fprintf(stdout, "int) %lld\n", root->num.int_value); 			break;
								case LONG_T:		fprintf(stdout, "long) %lld\n", root->num.int_value); 			break;
								case LONGLONG_T:	fprintf(stdout, "long long) %lld\n", root->num.int_value); 		break;
								case DOUBLE_T: 		fprintf(stdout, "double) %Lf\n", root->num.float_value); 		break;
								case LONGDOUBLE_T:	fprintf(stdout, "long double) %Lf\n", root->num.float_value); 	break;
								case FLOAT_T:		fprintf(stdout, "float) %Lg\n", root->num.float_value); 		break;
								default:			fprintf(stdout, "unknown) \n"); 								break;
							}
							break;

		case AST_CHARLIT:	fprintf(stdout, "CHARLIT %c\n", root->charlit.c);
							break;

		case AST_STRING:	fprintf(stdout, "STRING %s\n", root->string.word);
							break;

		case AST_FNCALL:	fprintf(stdout, "FUNCTION CALL\n");
							print_ast(root->fncall.left, level + 1);
							print_ast(root->fncall.right, level + 2);
							break;

		case AST_SIZEOF:	fprintf(stdout, "SIZEOF\n");
							print_ast(root->size_of.left, level + 1);
							break;

		case AST_COMP_SELECT:	fprintf(stdout, "COMPONENT SELECTION\n"); 
								print_ast(root->comp_select.left, level + 1);
								print_ast(root->comp_select.right, level + 1);
								break;

		case AST_EXPR_LIST:	//print_ast(root->expr_list.left, level);
							//print_ast(root->expr_list.right, level);
							print_ast(root->expr_list.right, level);
							break;

		case AST_TOP_EXPR: print_ast(root->top_expr.left, level); break;

		case AST_TERNARY:	fprintf(stdout, "TERNARY OP\n");
							fprintf(stdout, "IF CONDITION\n");
							print_ast(root->ternary.cond, level + 1);
							fprintf(stdout, "TRUE CLAUSE\n");
							print_ast(root->ternary.if_true, level + 1);
							fprintf(stdout, "FALSE CLAUSE\n");
							print_ast(root->ternary.if_false, level + 1);
							break;

		case AST_STORAGE: 

		case AST_POINTER: 	fprintf(stdout, "pointer to\n"); 
							print_ast(root->pointer.prev, level + 1);
							break;

		case AST_SCALAR: 	switch(root->scalar.sign)
							{
								case UNSIGNED_T: fprintf(stdout, "Unsigned "); break;
								case SIGNED_T: fprintf(stdout, "Signed "); break;
								default: fprintf(stdout, "idk\n");
							}

							switch(root->scalar.type)
							{
								case INT_T: fprintf(stdout, "INT\n"); break;
								case LONG_T: fprintf(stdout, "LONG\n"); break;
								case LONGLONG_T: fprintf(stdout, "LONGLONG\n"); break;
								case DOUBLE_T: fprintf(stdout, "DOUBLE\n"); break;
								case LONGDOUBLE_T: fprintf(stdout, "LONGDOUBLE\n"); break;
								case FLOAT_T: fprintf(stdout, "FLOAT\n"); break;
								case CHAR_T: fprintf(stdout, "CHAR\n"); break;
								default: fprintf(stdout, "idk\n"); 
							}
							break;

		case AST_FN:

		case AST_STRUCT: 	fprintf(stdout, "struct %s ", root->struct_n.name);
							if (root->struct_n.complete)
								fprintf(stdout, "(defined at %s:%d)\n", root->struct_n.filename, root->struct_n.lineno);
							else
								fprintf(stdout, "(incomplete)\n");
							break;

		case AST_MEMB:

		case AST_ARRAY: 	fprintf(stdout, "Array of %d elements of type:\n", root->array.size);
							print_ast(root->array.type, level + 1);
							break;

		case AST_IF_ST: 		fprintf(stdout , "IF STATEMENT: \n");
								fprintf(stdout, "IF CONDITION\n");
								print_ast(root->if_st.cond, level + 1);
								fprintf(stdout, "TRUE CLAUSE\n");
								print_ast(root->if_st.if_true, level + 1);
								break;

		case AST_IF_ELSE_ST: 	fprintf(stdout , "IF-ELSE STATEMENT: \n");
								fprintf(stdout, "IF CONDITION\n");
								print_ast(root->if_else_st.cond, level + 1);
								fprintf(stdout, "TRUE CLAUSE\n");
								print_ast(root->if_else_st.if_true, level + 1);
								fprintf(stdout, "FALSE CLAUSE\n");
								print_ast(root->if_else_st.next, level + 1);
								break;

		case AST_WHILE_ST: 		fprintf(stdout, "WHILE STATEMENT\n");
								fprintf(stdout, "CONDITION\n");
								print_ast(root->while_st.cond, level + 1);
								fprintf(stdout, "BODY\n");
								print_ast(root->while_st.body, level + 1);
								break;

		case AST_DO_WHILE_ST: 	fprintf(stdout, "DO-WHILE STATEMENT\n");
								fprintf(stdout, "BODY\n");
								print_ast(root->do_while_st.body, level + 1);
								fprintf(stdout, "CONDITION\n");
								print_ast(root->do_while_st.cond, level + 1);
								break;

		case AST_FOR_ST: 		fprintf(stdout, "FOR STATEMENT\n");
								fprintf(stdout, "INIT\n");
								print_ast(root->for_st.left, level + 1);
								fprintf(stdout, "CONDITION\n");
								print_ast(root->for_st.cond, level + 1);
								fprintf(stdout, "BODY\n");
								print_ast(root->for_st.body, level + 1);
								fprintf(stdout, "INCREMENT\n");
								print_ast(root->for_st.right, level + 1);
								break;

		case AST_SWITCH_ST: break;

		case AST_RETURN_ST: fprintf(stdout, "RETURN\n");
							print_ast(root->return_st.ret, level + 1);
							break;

	}

}
#endif

/* Dump AST for function/struct */
/*
void ast_dump(union astnode *root, char *name)
{
	if (name != NULL)
		printf("\n---------- AST DUMP FOR %s BEGIN ----------\n", name);
	else
		printf("\n---------- AST DUMP BEGIN ----------\n");

	union astnode *n = root;
	while (n != NULL)
	{
		print_ast(n, 0);
		n = n->gen.next;
	}

	printf("\n---------- AST DUMP END ----------\n");

}*/

void ast_dump(struct symbol_table *t, union astnode *root, char *name)
{
	if (name != NULL)
		printf("\n---------- AST DUMP FOR %s BEGIN ----------\n", name);
	else
		printf("\n---------- AST DUMP BEGIN ----------\n");

	union astnode *n = root;
	while (n != NULL)
	{
		print_ast(t, n, 0);

		/* Avoids the repetition in the ELSE part */
		if(n->gen.node_type == AST_IF_ELSE_ST)
			n = n->gen.next->gen.next;
		else
			n = n->gen.next;
	}

	printf("\n---------- AST DUMP END ----------\n");

}

void print_ast(struct symbol_table *t, union astnode *root, int level)
{	
	/* Avoid additional spacing for the expression lists */
	/*
	if(root->gen.node_type != AST_EXPR_LIST)
	{
		for (int i = 0; i < level; i++)
			fprintf(stdout, "  ");
	}*/

	for (int i = 0; i < level; i++)
			fprintf(stdout, "  ");

	if (root == NULL)
	{
		fprintf(stdout, "NULL\n");
		return;
	}

	struct symbol *s = malloc(sizeof(struct symbol));
	switch (root->gen.node_type)
	{
		case AST_ASSIGN:	fprintf(stdout, "ASSIGNMENT\n");
							print_ast(t, root->assign.left, level + 1);
							print_ast(t, root->assign.right, level + 1);
							break;

		case AST_UNOP:		fprintf(stdout, "UNARY OP %d", root->unop.operator);
							if(root->unop.operator < 255)
								fprintf(stdout, " (%c)\n",  (unsigned char)root->unop.operator);
							else
								fprintf(stdout, " (%s)\n",  print_kw(root->unop.operator));
							print_ast(t, root->unop.left, level + 1);
							break;

		case AST_BINOP:		fprintf(stdout, "BINARY OP %d", root->binop.operator);
							if(root->binop.operator < 255)
								fprintf(stdout, " (%c)\n", (unsigned char)root->binop.operator);
							else
								fprintf(stdout, " (%s)\n", print_kw(root->binop.operator));
							print_ast(t, root->binop.left, level + 1);
							print_ast(t, root->binop.right, level + 1);
							break;

		case AST_IDENT:		s = symbol_table_get_info(t, root->ident.name, OTHER_NS);
							if (s == NULL)
							{
								fprintf(stdout, "ERROR: %s was not defined\n", root->ident.name);
								break;
							}
							if (s->ast_node->gen.node_type == AST_SCALAR)
								fprintf(stdout, "stab_var ");
							else if (s->ast_node->gen.node_type == AST_FN)
								fprintf(stdout, "stab_fn ");
							fprintf(stdout, "name = %s defined at %s:%d\n", s->name, s->filename, s->lineno);
							break;

		case AST_NUMBER:	fprintf(stdout, "NUMBER: (numtype = ");
							switch(root->num.type)
							{
								case INT_T:			fprintf(stdout, "int) %lld\n", root->num.int_value); 			break;
								case LONG_T:		fprintf(stdout, "long) %lld\n", root->num.int_value); 			break;
								case LONGLONG_T:	fprintf(stdout, "long long) %lld\n", root->num.int_value); 		break;
								case DOUBLE_T: 		fprintf(stdout, "double) %Lf\n", root->num.float_value); 		break;
								case LONGDOUBLE_T:	fprintf(stdout, "long double) %Lf\n", root->num.float_value); 	break;
								case FLOAT_T:		fprintf(stdout, "float) %Lg\n", root->num.float_value); 		break;
								default:			fprintf(stdout, "unknown) \n"); 								break;
							}
							break;

		case AST_CHARLIT:	fprintf(stdout, "CHARLIT %c\n", root->charlit.c);
							break;

		case AST_STRING:	//fprintf(stdout, "STRING %s\n", root->string.word);
							fprintf(stdout, "STRING ");
							for(int i = 0; i < root->string.length; i++)
									print_char(root->string.word[i]);
							fprintf(stdout, "\n");
							break;

		case AST_FNCALL:	fprintf(stdout, "FUNCTION CALL\n");
							print_ast(t, root->fncall.left, level + 1);
							for (int i = 0; i < level; i++)
								fprintf(stdout, "  ");
							fprintf(stdout, "ARGUMENTS\n");
							print_ast(t, root->fncall.right, level + 1);
							root = root->fncall.right;
							while (root->gen.next != NULL)
							{
								print_ast(t, root->gen.next, level + 1);
								root = root->gen.next;
							}
							break;

		case AST_SIZEOF:	fprintf(stdout, "SIZEOF\n");
							print_ast(t, root->size_of.left, level + 1);
							break;

		case AST_COMP_SELECT:	fprintf(stdout, "COMPONENT SELECTION\n"); 
								print_ast(t, root->comp_select.left, level + 1);
								print_ast(t, root->comp_select.right, level + 1);
								break;

		case AST_EXPR_LIST:	//print_ast(t, root->expr_list.left, level);
							//print_ast(t, root->expr_list.right, level);
							//print_ast(t, root->expr_list.next, level);
							break;

		case AST_TOP_EXPR: print_ast(t, root->top_expr.left, level); break;

		case AST_TERNARY:	fprintf(stdout, "TERNARY OP\n");
							fprintf(stdout, "IF CONDITION\n");
							print_ast(t, root->ternary.cond, level + 1);
							fprintf(stdout, "TRUE CLAUSE\n");
							print_ast(t, root->ternary.if_true, level + 1);
							fprintf(stdout, "FALSE CLAUSE\n");
							print_ast(t, root->ternary.if_false, level + 1);
							break;

		case AST_STORAGE: 

		case AST_POINTER: 	fprintf(stdout, "pointer to\n"); 
							print_ast(t, root->pointer.prev, level + 1);
							break;

		case AST_SCALAR: 	switch(root->scalar.sign)
							{
								case UNSIGNED_T: fprintf(stdout, "Unsigned "); break;
								case SIGNED_T: fprintf(stdout, "Signed "); break;
								case VOID_SIGN: break;
								default: fprintf(stdout, "idk\n");
							}

							switch(root->scalar.type)
							{
								case INT_T: fprintf(stdout, "INT\n"); break;
								case LONG_T: fprintf(stdout, "LONG\n"); break;
								case LONGLONG_T: fprintf(stdout, "LONGLONG\n"); break;
								case DOUBLE_T: fprintf(stdout, "DOUBLE\n"); break;
								case LONGDOUBLE_T: fprintf(stdout, "LONGDOUBLE\n"); break;
								case FLOAT_T: fprintf(stdout, "FLOAT\n"); break;
								case CHAR_T: fprintf(stdout, "CHAR\n"); break;
								case VOID_T: fprintf(stdout, "VOID\n"); break;
								default: fprintf(stdout, "idk\n"); 
							}
							break;

		case AST_FN:

		case AST_STRUCT: 	fprintf(stdout, "struct %s ", root->struct_n.name);
							if (root->struct_n.complete)
								fprintf(stdout, "(defined at %s:%d)\n", root->struct_n.filename, root->struct_n.lineno);
							else
								fprintf(stdout, "(incomplete)\n");
							break;

		case AST_MEMB:

		case AST_ARRAY: 	fprintf(stdout, "Array of %d elements of type:\n", root->array.size);
							print_ast(t, root->array.type, level + 1);
							break;

		case AST_IF_ST: 		fprintf(stdout , "IF STATEMENT: \n");
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "IF CONDITION\n");
								print_ast(t, root->if_st.cond, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "TRUE CLAUSE (NO ELSE)\n");
								print_ast(t, root->if_st.if_true, level + 1);
								break;

		case AST_IF_ELSE_ST: 	fprintf(stdout , "IF-ELSE STATEMENT: \n");
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "IF CONDITION\n");
								print_ast(t, root->if_else_st.cond, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "TRUE CLAUSE\n");
								print_ast(t, root->if_else_st.if_true, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "FALSE CLAUSE\n");
								print_ast(t, root->if_else_st.next, level + 1);
								break;

		case AST_WHILE_ST: 		fprintf(stdout, "WHILE STATEMENT\n");
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "CONDITION\n");
								print_ast(t, root->while_st.cond, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "BODY\n");
								print_ast(t, root->while_st.body, level + 1);
								break;

		case AST_DO_WHILE_ST: 	fprintf(stdout, "DO-WHILE STATEMENT\n");
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "BODY\n");
								print_ast(t, root->do_while_st.body, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "CONDITION\n");
								print_ast(t, root->do_while_st.cond, level + 1);
								break;

		case AST_FOR_ST: 		fprintf(stdout, "FOR STATEMENT\n");
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "INIT\n");
								print_ast(t, root->for_st.left, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "CONDITION\n");
								print_ast(t, root->for_st.cond, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "BODY\n");
								print_ast(t, root->for_st.body, level + 1);
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "INCREMENT\n");
								print_ast(t, root->for_st.right, level + 1);
								break;

		case AST_SWITCH_ST: 	fprintf(stdout, "SWITCH, EXPR:\n");
								print_ast(t, root->switch_st.cond, level + 1);
								/* Line up the spacing a bit better */
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "BODY\n");
								print_ast(t, root->switch_st.body, level + 1);
								break;

		case AST_RETURN_ST: 	fprintf(stdout, "RETURN\n");
								print_ast(t, root->return_st.ret, level + 1);
								break;

		case AST_COMPOUND_ST:   fprintf(stdout, "COMPOUND STMT {\n");
								print_ast(t, root->compound_st.body, level+1);
								root = root->compound_st.body;
								while(root->gen.next != NULL)
								{
									print_ast(t, root->gen.next, level+1);
									root = root->gen.next;
								}
								/* Line up the spacing a bit better */
								for (int i = 0; i < level; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "}\n");
								break;

		case AST_LABELED_ST: 	print_ast(t, root->labeled_st.label, level);
								print_ast(t, root->labeled_st.body, level+2);
								break;

		case AST_CASE_LABEL:	fprintf(stdout, "CASE, EXPR:\n");
								print_ast(t, root->case_label.expr, level + 2);
								/* Line up the spacing a bit better */
								for (int i = 0; i < level+1; i++)
									fprintf(stdout, "  ");
								fprintf(stdout, "BODY\n");
								break;

		case AST_DEF_LABEL: 	fprintf(stdout, "DEFAULT\n");
								break;

		case AST_BREAK_ST: 		fprintf(stdout, "BREAK\n");
								break;

		case AST_CONT_ST:		fprintf(stdout, "CONTINUE\n");
								break;

		case AST_GOTO_ST: 		fprintf(stdout, "GOTO %s ", root->goto_st.label->named_label.name);
								s = symbol_table_get_info(t, root->goto_st.label->named_label.name, LABEL_NS);
								/*
								if (root->goto_st.label->named_label.defined)
									fprintf(stdout, "(defined)\n");
								else
									fprintf(stdout, "(undefined)\n");
								*/
								if (s != NULL)
									fprintf(stdout, "(defined)\n");
								else
									fprintf(stdout, "(undefined)\n");
								break;

		case AST_NAMED_LABEL: 	fprintf(stdout, "LABEL (%s)\n", root->named_label.name);
								break;


	}

}






