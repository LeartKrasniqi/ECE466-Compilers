/* ast.c */
#include "ast.h"

/* Allocates new AST node */
struct astnode * astnode_alloc(int node_type)
{
	struct astnode *n = malloc(sizeof(struct astnode));
	if (n == NULL)
	{
		fprintf(stderr, "Error allocating new AST node: %s\n", strerror(errno));
		return NULL;
	}

	n->node_type = node_type;;

	return n;
}

/* Prints out AST */
void print_ast(struct astnode *root, int level)
{	
	/* Avoid additional spacing for the expression lists */
	if(root->node_type != AST_EXPR_LIST)
	{
		for (int i = 0; i < level; i++)
			fprintf(stdout, "  ");
	}

	if (root == NULL)
	{
		fprintf(stdout, "NULL\n");
		return;
	}

	switch (root->node_type)
	{
		case AST_ASSIGN:	fprintf(stdout, "ASSIGNMENT\n");
							print_ast(root->u.assign.left, level + 1);
							print_ast(root->u.assign.right, level + 1);
							break;

		case AST_UNOP:		fprintf(stdout, "UNARY OP %d", root->u.unop.operator);
							if(root->u.unop.operator < 255)
								fprintf(stdout, " (%c)\n",  (unsigned char)root->u.unop.operator);
							else
								fprintf(stdout, " (%s)\n",  print_kw(root->u.unop.operator));
							print_ast(root->u.unop.left, level + 1);
							break;

		case AST_BINOP:		fprintf(stdout, "BINARY OP %d", root->u.binop.operator);
							if(root->u.binop.operator < 255)
								fprintf(stdout, " (%c)\n", (unsigned char)root->u.binop.operator);
							else
								fprintf(stdout, " (%s)\n", print_kw(root->u.binop.operator));
							print_ast(root->u.binop.left, level + 1);
							print_ast(root->u.binop.right, level + 1);
							break;

		case AST_IDENT:		fprintf(stdout, "IDENT %s\n", root->u.ident.name);
							break;

		case AST_NUMBER:	fprintf(stdout, "NUMBER: (numtype = ");
							switch(root->u.num.type)
							{
								case INT_T:			fprintf(stdout, "int) %lld\n", root->u.num.int_value); 				break;
								case LONG_T:		fprintf(stdout, "long) %lld\n", root->u.num.int_value); 			break;
								case LONGLONG_T:	fprintf(stdout, "long long) %lld\n", root->u.num.int_value); 		break;
								case DOUBLE_T: 		fprintf(stdout, "double) %Lf\n", root->u.num.float_value); 			break;
								case LONGDOUBLE_T:	fprintf(stdout, "long double) %Lf\n", root->u.num.float_value); 	break;
								case FLOAT_T:		fprintf(stdout, "float) %Lg\n", root->u.num.float_value); 			break;
								default:			fprintf(stdout, "unknown) \n"); 									break;
							}
							break;

		case AST_CHARLIT:	fprintf(stdout, "CHARLIT %c\n", root->u.charlit.c);
							break;

		case AST_STRING:	fprintf(stdout, "STRING %s\n", root->u.string.word);
							break;

		case AST_FNCALL:	fprintf(stdout, "FUNCTION CALL\n");
							print_ast(root->u.fncall.left, level + 1);
							print_ast(root->u.fncall.right, level + 2);
							break;

		case AST_SIZEOF:	fprintf(stdout, "SIZEOF\n");
							print_ast(root->u.size_of.left, level + 1);
							break;

		case AST_COMP_SELECT:	fprintf(stdout, "COMPONENT SELECTION\n"); 
								print_ast(root->u.comp_select.left, level + 1);
								print_ast(root->u.comp_select.right, level + 1);
								break;

		case AST_EXPR_LIST:	print_ast(root->u.expr_list.left, level);
							print_ast(root->u.expr_list.right, level);
							break;

		case AST_TOP_EXPR: print_ast(root->u.top_expr.left, level); break;

		case AST_IF_ELSE:	fprintf(stdout, "IF CONDITION\n");
							print_ast(root->u.if_else.cond, level + 1);
							fprintf(stdout, "TRUE CLAUSE\n");
							print_ast(root->u.if_else.if_true, level + 1);
							fprintf(stdout, "FALSE CLAUSE\n");
							print_ast(root->u.if_else.if_false, level + 1);
							break;

	}

}
