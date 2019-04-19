/* AST Header File */

#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sym_tab.h"

enum ast_types {AST_ASSIGN = 1, AST_UNOP, AST_BINOP, AST_NUMBER, AST_IDENT, AST_CHARLIT, AST_STRING, AST_FNCALL, AST_SIZEOF, AST_COMP_SELECT, AST_EXPR_LIST, AST_TOP_EXPR, AST_TERNARY, AST_STORAGE, AST_POINTER, AST_SCALAR, AST_FN, AST_STRUCT, AST_MEMB, AST_ARRAY, AST_IF_ST, AST_IF_ELSE_ST, AST_WHILE_ST, AST_DO_WHILE_ST, AST_FOR_ST, AST_SWITCH_ST, AST_RETURN_ST, AST_COMPOUND_ST, AST_LABELED_ST, AST_CASE_LABEL, AST_DEF_LABEL, AST_BREAK_ST, AST_CONT_ST, AST_GOTO_ST, AST_NAMED_LABEL, AST_TEMP};
enum num_signs {UNSIGNED_T = 0, SIGNED_T = 1, VOID_SIGN};
enum num_types {INT_T = 1, LONG_T, LONGLONG_T, DOUBLE_T, LONGDOUBLE_T, FLOAT_T, CHAR_T};
enum storage_classes {AUTO_T = 1, EXTERN_T, STATIC_T};
enum direction {PREV = 0, NEXT = 1};

struct astnode_assign {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;	/* LHS */ 
	union astnode *right;	/* RHS */
};

struct astnode_unop {
	int node_type;
	union astnode *prev;
	union astnode *next;
	int operator;
	union astnode *left;	/* Operator applied to this */
};

struct astnode_binop {
	int node_type;
	union astnode *prev;
	union astnode *next;
	int operator;
	union astnode *left;	/* LHS */ 
	union astnode *right;	/* RHS */
};

struct astnode_number {
	int node_type;
	union astnode *prev;
	union astnode *next;
	unsigned long long int_value;
	long double float_value;
	int sign;
	int type;
};

struct astnode_ident {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char *name;
};

struct astnode_charlit {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char c;
};

struct astnode_string {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char word[4096];
	int length;
};

struct astnode_fncall {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;	/* Function name */ 
	union astnode *right;	/* Function arguments */
};

struct astnode_sizeof {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;	/* Take sizeof this */
};

struct astnode_comp_select {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;	/* Name of struct/union */ 
	union astnode *right;	/* Member */
};

struct astnode_expr_list {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;	/* Original list member */
	union astnode *right;	/* New list member */
};

struct astnode_top_expr {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;
};

struct astnode_ternary {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond;		/* Condition */
	union astnode *if_true;		/* True */
	union astnode *if_false;	/* False */
};

struct astnode_storage {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left;
	int storage_class; 		/* AUTO, EXTERN, or STATIC */
};

struct astnode_if_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond; 		/* Check condition */
	union astnode *if_true; 	/* If true, execute this */
};

struct astnode_if_else_st {
	int node_type;
	union astnode *prev;
	union astnode *next; 		/* If false, execute this */
	union astnode *cond; 		/* Check condition */
	union astnode *if_true; 	/* If true, execute this */
};

struct astnode_while_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond; 	/* Check condition */
	union astnode *body; 	/* Body of loop */
};

struct astnode_do_while_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond; 	/* Check condition */
	union astnode *body; 	/* Body of loop */
};

struct astnode_for_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond; 	/* Check condition */
	union astnode *left; 	/* Initial Clause */
	union astnode *body; 	/* Body of loop */
	union astnode *right; 	/* Update */
};

struct astnode_switch_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *cond; 	/* Check condition */
	union astnode *body; 	/* Body of statement */
};

struct astnode_return_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *ret; 	/* Return value */
};

struct astnode_compound_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *body; 	/* Body of statement */
};

struct astnode_labeled_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *label; 	/* Holds the diff type of labels (i.e. case, default, named) */
	union astnode *body; 	/* Statement following the label */
};

struct astnode_case_label {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *expr; 	/* The actual label */
};

struct astnode_def_label {
	int node_type;
	union astnode *prev;
	union astnode *next;
};

struct astnode_break_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
};

struct astnode_cont_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
};

struct astnode_goto_st {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *label; 	/* Which label to go to */
};

struct astnode_named_label {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char *name; 			/* Holds name of label */
	int defined; 			/* Holds whether or not label has been defined */
	int call;				/* Holds whether the label is being called (i.e. from a goto) */
};


/* Symbol Table Nodes Below */

struct astnode_pointer {
	int node_type;
	union astnode *prev;
	union astnode *next;
	union astnode *left; 	/* Pointer points to this */
};

struct astnode_scalar {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char *filename;
	int lineno;
	char *name;
	union astnode *node; 	/* comparable to ret_value in astnode_fn */
	int type;		/* Type of scalar */
	int sign;
};

struct astnode_fn {
	int node_type;
	union astnode *prev;
	union astnode *next;
	char *filename;
	int lineno;
	char *name;
	union astnode *ret_value;	/* Return Value of function */
	struct symbol_table *mini; 	/* Mini symbol table for function (proto scope) */
	union astnode *body;
};

struct astnode_struct {
	int node_type;
	union astnode *prev;
	union astnode *next;
	int complete;				/* Flag for complete definition, 1 if complete, 0 if not */
	char *name; 			/* check to make sure the name is added to the struct node */
	union astnode *node;
	char *filename;
	int lineno;
	struct symbol_table *mini;	/* Mini symbol table for the struct/union */
};

struct astnode_array {
	int node_type;
	union astnode *prev;
	union astnode *next;
	int size;				/* Number of elements in array */
	union astnode *type; 	/* Type of values stored in array */ 
	//union astnode *left;
};

/* Quad stuff */
struct astnode_temp {
	int node_type;
	union astnode *prev;
	union astnode *next;
};


union astnode {
	struct astnode_gen {
		int node_type;
		union astnode *prev;
		union astnode *next;
	} gen; 										/* Defines stuff for entire union */
	struct astnode_assign assign; 				/* Assignment */
	struct astnode_unop unop;					/* Unary Operator */
	struct astnode_binop binop;					/* Binary Operator */
	struct astnode_number num;					/* Number (Constant) */
	struct astnode_ident ident; 				/* Identifier */
	struct astnode_charlit charlit; 			/* Character Literal */
	struct astnode_string string; 				/* String */
	struct astnode_fncall fncall; 				/* Function Call */
	struct astnode_sizeof size_of; 				/* Sizeof */
	struct astnode_comp_select comp_select; 	/* Component Selection */
	struct astnode_expr_list expr_list; 		/* List of Expressions */ 
	struct astnode_top_expr top_expr; 			/* Top Level Expression -- Might not need*/
	struct astnode_ternary ternary; 			/* Ternary Expression */
	struct astnode_storage storage;				/* Storage Class */
	struct astnode_if_st if_st; 				/* IF Statement */
	struct astnode_if_else_st if_else_st;		/* IF-ELSE Statement */
	struct astnode_while_st while_st; 			/* WHILE Statement */
	struct astnode_do_while_st do_while_st;		/* DO-WHILE Statement */
	struct astnode_for_st for_st; 				/* FOR Statement */
	struct astnode_switch_st switch_st;			/* SWITCH Statement */
	struct astnode_return_st return_st;			/* RETURN Statement */
	struct astnode_compound_st compound_st; 	/* Compound Statement */
	struct astnode_labeled_st labeled_st; 		/* Labeled Statement */
	struct astnode_case_label case_label;		/* CASE Label */
	struct astnode_def_label def_label;			/* DEAFULT Label */
	struct astnode_break_st break_st;			/* BREAK Statement */
	struct astnode_cont_st cont_st; 			/* CONTINUE Statement */
	struct astnode_goto_st goto_st;				/* GOTO Statement */
	struct astnode_named_label named_label; 	/* Named label */


	/* Symbol Table Nodes Below */ 
	struct astnode_pointer pointer;				/* Pointer */
	struct astnode_scalar scalar;				/* Scalars */
	struct astnode_fn fn;						/* Function */
	struct astnode_struct struct_n;				/* Struct/Union */
	struct astnode_array array;					/* Array */

	/* Used in quads */
	struct astnode_temp temp;					/* Temporary node */
};

/* Allocate a new AST node */
union astnode * astnode_alloc(int node_type);

/* Append node into AST (useful for lists) */
union astnode * astnode_append(union astnode *root, union astnode *new, int direction);

/* Reverse order of nodes in AST */
union astnode * astnode_reverse(union astnode *root, int direction);

/* Print out the AST */
void print_ast(struct symbol_table *t, union astnode *root, int level);

/* Dump the AST for a function/struct */
//void ast_dump(union astnode *root, char *name);
void ast_dump(struct symbol_table *t, union astnode *root, char *name);

/* Find return value of function */
union astnode * find_ret_value(union astnode *root);

/* Print out keyword associated with token -- Defined in lexer.l */
char* print_kw(int token);

/* Print out char in string -- Defined in lexer.l */
void print_char(char c);








#endif 