/* quads.h */

#ifndef __QUADS_H
#define __QUADS_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

enum quad_opcodes {Q_LOAD = 300, Q_LEA, Q_MOV, Q_STORE, Q_COMP, Q_ARG, Q_CALL, Q_RETURN};
enum addr_modes {DIRECT_M = 0, INDIRECT_M = 1};
enum bb_branches {NEVER = 0, ALWAYS, COND_LT, COND_GT, COND_LTEQ, COND_GTEQ, COND_EQ, COND_NEQ};

/* Syntax will be result = OP src1, src2 */
struct quad {
	int opcode;					
	union astnode *result; 		/* lvalue */	
	union astnode *src1; 		/* rvalue */
	union astnode *src2;		/* rvalue */
	struct quad *next; 			/* Maintain a linked list of quads */
};

struct quad_list {
	int size;
	struct quad *head;
	struct quad *tail;
};

struct basic_block {
	char *label;				/* Label associated with this basic block.  Format: .BB.F.N */
	int branch; 				/* ALWAYS, */
	struct quad_list *q_list; 	/* Hold list of quads in this basic block */
	struct basic_block *left; 	/* Left branch */
	struct basic_block *right; 	/* Right branch */
	struct basic_block *next; 	/* Maintain a linked list of basic blocks */
};

struct basic_block_list {
	int size;
	struct basic_block *head;
	struct basic_block *tail;
};

struct loop {
	struct basic_block *bb_continue; 	/* The "CONTINUE" point of the loop */
	struct basic_block *bb_break; 		/* The "BREAK" point of the loop */
	struct loop *prev; 					/* Allows to have loops within loops */
};


/* Creates a new quad and appends to list of current quads */
struct quad * quad_emit(int opcode, union astnode *src1, union astnode *src2, union astnode *result);

/* Creates a new quad list */
struct quad_list * quad_new_list(void);

struct quad_list * quad_list_append(struct quad *q, struct quad_list *l);

/* Creates a temporary node */
union astnode * quad_new_temp(void);

/* Generates lvalue */
union astnode * quad_gen_lvalue(union astnode *node, int *mode);

/* Generates rvalue, if target is NULL, we are expected to create a temporary */
union astnode * quad_gen_rvalue(union astnode *node, union astnode *target);

int quad_get_sizeof(union astnode *node);

void * quad_gen_stmt(union astnode *node);

/* Generate assignment quad */
union astnode * quad_gen_assign(union astnode *node);

/* Generate IF statement quad */
union astnode * quad_gen_if(union astnode *node);

union astnode * quad_gen_cond_expr(union astnode *node, struct basic_block *Bt, struct basic_block *Bf);

struct loop * quad_new_loop(void);
void * quad_gen_while(union astnode *node);
void * quad_gen_do_while(union astnode *node);
void * quad_gen_for(union astnode *node);
void * quad_gen_break(union astnode *node);
void * quad_gen_continue(union astnode *node);
void * quad_gen_return(union astnode *node);
void * quad_gen_unop(union astnode *node);
void * quad_gen_fncall(union astnode *node, union astnode *target);

void print_quads(struct quad *q);
void print_rval(union astnode *node);




/* Basic Block */
/* Create a new basic block */
struct basic_block * quad_new_bb(void);
struct basic_block_list * quad_new_bb_list(void);
struct basic_block_list * quad_bb_list_append(struct basic_block *bb, struct basic_block_list *l);
struct basic_block * quad_link_bb(struct basic_block *bb, int branch, struct basic_block *left, struct basic_block *right);
void print_bb(struct basic_block *block);


void * gen_fn_quads(union astnode *function, union astnode *stmt, struct symbol_table *t, FILE *f);


void global_setup();
void fn_prologue(union astnode *function);
void target_print_bb(struct basic_block *block);
void translate_quads(struct quad *q);
void target_print(union astnode *node);






#endif