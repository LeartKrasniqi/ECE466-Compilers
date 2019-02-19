/* AST Header File */

#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum ast_types {AST_ASSIGN = 1, AST_UNOP, AST_BINOP, AST_NUMBER, AST_IDENT, AST_CHARLIT, AST_STRING, AST_FNCALL, AST_SIZEOF, AST_COMP_SELECT, AST_EXPR_LIST, AST_TOP_EXPR, AST_IF_ELSE};
enum num_signs {UNSIGNED_T = 0, SIGNED_T = 1};
enum num_types {INT_T = 0, LONG_T, LONGLONG_T, DOUBLE_T, LONGDOUBLE_T, FLOAT_T};

struct astnode_assign {
	struct astnode *left;	/* LHS */ 
	struct astnode *right;	/* RHS */
};

struct astnode_unop {
	int operator;
	struct astnode *left;	/* Operator applied to this */
};

struct astnode_binop {
	int operator;
	struct astnode *left;	/* LHS */ 
	struct astnode *right;	/* RHS */
};

struct astnode_number {
	unsigned long long int_value;
	long double float_value;
	int sign;
	int type;
};

struct astnode_ident {
	char *name;
};

struct astnode_charlit {
	char c;
};

struct astnode_string {
	char word[4096];
	int length;
};

struct astnode_fncall {
	struct astnode *left;	/* Function name */ 
	struct astnode *right;	/* Function arguments */
};

struct astnode_sizeof {
	struct astnode *left;	/* Take sizeof this */
};

struct astnode_comp_select {
	struct astnode *left;	/* Name of struct/union */ 
	struct astnode *right;	/* Member */
};

struct astnode_expr_list {
	struct astnode *left;	/* Original list member */
	struct astnode *right;	/* New list member */
};

struct astnode_expr_list_mem {
	struct astnode *left;
};

struct astnode_top_expr {
	struct astnode *left;
};

struct astnode_if_else {
	struct astnode *cond;		/* Condition */
	struct astnode *if_true;	/* True */
	struct astnode *if_false;	/* False */
};

struct astnode {
	int node_type; 
	union {
		struct astnode_assign assign; 
		struct astnode_unop unop;
		struct astnode_binop binop;
		struct astnode_number num;
		struct astnode_ident ident;
		struct astnode_charlit charlit;
		struct astnode_string string;
		struct astnode_fncall fncall;
		struct astnode_sizeof size_of;
		struct astnode_comp_select comp_select;
		struct astnode_expr_list expr_list;
		struct astnode_expr_list_mem expr_mem;
		struct astnode_top_expr top_expr;
		struct astnode_if_else if_else;
		/* add more */	
	} u;	
};

/* Allocate a new AST node */
struct astnode * astnode_alloc(int node_type);

/* Print out the AST */
void print_ast(struct astnode *root, int level);

char* print_kw(int token);

#endif 
