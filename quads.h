/* quads.h */

#ifndef __QUADS_H
#define __QUADS_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

enum quad_opcodes {};
enum addr_modes {DIRECT_M = 0, INDIRECT_M = 1};

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
	struct quad_list *q_list; 	/* Hold list of quads in this basic block */
	struct basic_block *left; 	/* Left branch */
	struct basic_block *right; 	/* Right branch */
	struct basic_block *next; 	/* Maintain a linked list of basic blocks */
};

struct basic_block_list {
	int size;
	struct basic_block *head;
	struct basic_block *tail;
}


/* Creates a new quad and appends to list of current quads */
struct quad * quad_emit(int opcode, union astnode *src1, union astnode *src2, union astnode *result);

/* Creates a temporary node */
union astnode * quad_new_temp(void);

/* Generates lvalue */
union astnode * quad_gen_lvalue(union astnode *node, int *mode);

/* Generates rvalue, if target is NULL, we are expected to create a temporary */
union astnode * quad_gen_rvalue(union astnode *node, union astnode *target);

/* Generate assignment quad */
union astnode * quad_gen_assign(union astnode *node);

/* Generate IF statement quad */
union astnode * quad_gen_if(union astnode *node);

/* Generate WHILE loop quad */
union astnode * quad_gen_while(union astnode *node);



/* Append quad to list of quads in current basic block */
struct quad_list * quad_list_append(struct quad *q, struct quad_list *l);







#endif