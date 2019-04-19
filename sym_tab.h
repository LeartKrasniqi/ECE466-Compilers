/* Symbol Table */

#ifndef __SYM_TABLE_H
#define __SYM_TABLE_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

enum scopes {GLOBAL_SCOPE = 1, FUNCTION_SCOPE, BLOCK_SCOPE, PROTO_SCOPE, MINI}; 	/* MINI just used for minisymbol table */
enum namespaces {TAG_NS = 1, LABEL_NS, MEMBER_NS, OTHER_NS};
enum symbol_types {VOID_T = 0, VAR_T, FN_T, STRUCT_T, MEMB_T, S_TAG_T};

struct symbol {
		char *name;					/* Name of entry */
		int lineno; 				/* Line Number */
		char *filename; 			/* File Name */
		int name_space;				/* Namespace - Tags, Labels, Members, Other */
		int storage_class; 			/* Storage Class */
		int type;					/* VOID, SCALAR (VAR), FN, STRUCT, MEMB (struct member) S_TAG_T (struct tag) */
		union astnode *ast_node; 	/* AST node for symbol */
		int complete;				/* Used for struct/union tags -> 1 if complete, 0 if not */
		struct symbol *next;		/* Link to next symbol */
		int scope_type;
		int redeclaration; 			/* Flag for redeclaration */
		struct symbol *list;		/* Used for a list of symbols, i.e. int a,b,c; */
};
	
struct symbol_table {
	int scope_type;				/* Type of scope */
	int lineno;					/* Line Number */
	char *filename;				/* File Name */
	struct symbol *head;		/* First entry */
	struct symbol *tail;		/* Last entry */
	struct symbol_table *prev;	/* Maintain stack of symbol tables of different scopes */
};

/* Allocate a new symbol table and add current table to stack */
struct symbol_table * symbol_table_alloc(int scope_type, int l, char *f, struct symbol_table *prev);

/* Allocate a new symbol */
struct symbol * symbol_alloc(char *key);

/* Insert symbol into table (1 if success, 0 if not) */
//int symbol_table_insert(struct symbol_table *t, char *key, int l, char *f, int name_space, union astnode *n);

/* Insert symol into table (return symbol if success, NULL if not) */
struct symbol * symbol_table_insert(struct symbol_table *t, char *key, int l, char *f, int name_space, union astnode *n, struct symbol *curr_symbol);

/* Search for particular key and name space, return pointer if found, NULL if not */
void * symbol_table_search(struct symbol_table *t, char *key, int name_space);

/* Search for particular key attributes */
struct symbol * symbol_table_get_info(struct symbol_table *t, char *key, int name_space);

/* Pop and destroy symbol table off stack to return to outer scope table */
struct symbol_table * symbol_table_pop(struct symbol_table *t);

/* Destroy table when leaving scope */
void symbol_table_free(struct symbol_table *t);

/* Print out the symbol table */
void print_sym_tab(struct symbol_table *t);

/* Get name of scope */
char * get_scope_name(int scope_type);

char * find_sym_type(struct symbol *symbol);
char * find_sym_class(struct symbol *symbol);
int sym_class_fn(struct symbol *symbol);
char * find_sym_use(struct symbol *symbol);

int is_valid_redeclaration(struct symbol_table *t, struct symbol *s, int name_space);

void update_symbol(struct symbol_table *t, union astnode *n, int name_space, int symbol_exists, int l, char *f);






#endif
