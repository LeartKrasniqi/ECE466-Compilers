/* quads.c */

#include "quads.h"

struct basic_block *curr_bb;

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
	quad_list_append(q, curr_bb->q_list);

	return q;
}

/* Creates a temporary node */
union astnode * quad_new_temp(void)
{
	union astnode *n = astnode_alloc(AST_TEMP);

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
}

/* Generates rvalue, if target is NULL, we are expected to create a temporary */
union astnode * quad_gen_rvalue(union astnode *node, union astnode *target)
{
	union astnode *temp, *left, *right;
	union astnode *addr;

	switch (node->gen.node_type)
	{
		case AST_NUMBER: 	/* Let the fall-through do its magic, again */ 
		case AST_IDENT:
		case AST_CHARLIT:
		case AST_STRING: 	return node;

		case AST_UNOP: 		
							/* Check for deref */
							if (node->unop.operator == '*')
							{
								if (node->unop.left->gen.node_type == AST_ARRAY)
									return quad_gen_rvalue(node->gen.left, target);

								addr = quad_gen_rvalue(node->unop.left, NULL);
								if (target == NULL)
									target = quad_new_temp();
								quad_emit(Q_LOAD, addr, NULL, target);
								
							}

		case AST_BINOP: 	/* Binary Operator Case */	
							left = quad_gen_rvalue(node->binop.left, NULL);
							right = quad_gen_rvalue(node->binop.right, NULL);
							if (target == NULL)
								target = quad_new_temp();
							quad_emit(node->binop.operator, left, right, target);
							return target;

		case AST_ARRAY: 	/* Array variable */
							temp = quad_new_temp();
							quad_emit(Q_LEA, node, NULL, temp);
							return temp;




	}
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
		quad_gen_rvalue(node->assign.right, dest);
	else
	{
		t1 = quad_gen_rvalue(node->assign.right, NULL);
		quad_emit(Q_STORE, t1, dst, NULL);
	}

}



/* Append quad to list of quads in current basic block */
struct quad_list * quad_list_append(struct quad *q, struct quad_list *l)
{
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



