/* Symbol Table */

#include "sym_tab.h"

struct symbol_table * symbol_table_alloc(int scope_type, int l, char *f, struct symbol_table *prev)
{
	struct symbol_table *t = malloc(sizeof(struct symbol_table));
	if (t == NULL)
	{
		fprintf(stderr, "Error allocating new symbol table: %s\n", strerror(errno));
		return NULL;
	}

	t->scope_type = scope_type;
	t->lineno = l;
	t->filename = strdup(f);
	t->head = NULL;
	t->tail = NULL;
	t->prev = prev;

	return t;
}

struct symbol * symbol_alloc(char *key)
{
	struct symbol *s = malloc(sizeof(struct symbol));
	if (s == NULL)
	{
		fprintf(stderr, "Error allocating new symbol: %s\n", strerror(errno));
		return NULL;
	}

	s->name = strdup(key);

	return s;
}

//int symbol_table_insert(struct symbol_table *t, char *key, int name_space, int type)
#if 0
int symbol_table_insert(struct symbol_table *t, char *key, int l, char *f, int name_space, union astnode *n)
{
	struct symbol *symbol_in_table = symbol_table_search(t, key, name_space);
	if ( symbol_in_table == NULL )
	{
		struct symbol *s = symbol_alloc(key);
		s->lineno = l;
		s->filename = strdup(f);
		s->scope_type = t->scope_type;
		//s->type = type;
		s->name_space = name_space;
		s->ast_node = n;
		s->next = NULL;
		if(t->head == NULL)
		{
			t->head = s;
			t->tail = s;
		}
		else
		{
			t->tail->next = s;
			t->tail = s;
		}
		return 1;
	}
	/*
	else if ( is_valid_redeclaration(t, key, name_space, n, symbol_in_table) )
	{
		printf("VALID REDECLARATION at %s:%d\n", f, l);
		symbol_in_table->lineno = l;
		symbol_in_table->ast_node = n;
	}*/
	else	
		return 0;
}
#endif

struct symbol * symbol_table_insert(struct symbol_table *t, char *key, int l, char *f, int name_space, union astnode *n, struct symbol *curr_symbol)
{
	struct symbol *symbol_in_table = symbol_table_search(t, key, name_space);
	struct symbol *s = symbol_alloc(key);
	s->lineno = l;
	s->filename = strdup(f);
	s->scope_type = t->scope_type;
	s->name_space = name_space;
	s->ast_node = n;
	s->list = curr_symbol;
	s->next = NULL;
	if(t->head == NULL)
	{
		t->head = s;
		t->tail = s;
	}
	else
	{
		t->tail->next = s;
		t->tail = s;
	}
	if ( symbol_in_table == NULL )
	{	
		s->redeclaration = 0;
		/*
		struct symbol *s = symbol_alloc(key);
		s->lineno = l;
		s->filename = strdup(f);
		s->scope_type = t->scope_type;
		//s->type = type;
		s->name_space = name_space;
		s->ast_node = n;
		s->list = curr_symbol;
		s->next = NULL;
		s->redeclaration = 0;
		if(t->head == NULL)
		{
			t->head = s;
			t->tail = s;
		}
		else
		{
			t->tail->next = s;
			t->tail = s;
		}
		return s;
		*/
	}
	/*
	else if ( is_valid_redeclaration(t, key, name_space, n, symbol_in_table) )
	{
		printf("VALID REDECLARATION at %s:%d\n", f, l);
		symbol_in_table->lineno = l;
		symbol_in_table->ast_node = n;
	}*/
	else
	{
		s->redeclaration = 1;
		//return NULL;
	}

	return s;	
		
}

void * symbol_table_search(struct symbol_table *t, char *key, int name_space)
{
	struct symbol_table *table = t;
	/* Iterate through all the enclosing scopes */
	while (table != NULL)
	{
		struct symbol *node = table->head;

		/* Iterate through symbols in the table */
		while(node != NULL)
		{
			if( (strcmp(key, node->name) == 0) && (node->name_space == name_space) && (node->redeclaration == 0) )
				return node;

			node = node->next;
		}

		table = table->prev;

	}

	return NULL;
}

struct symbol * symbol_table_get_info(struct symbol_table *t, char *key, int name_space)
{
	struct symbol *s = symbol_table_search(t, key, name_space);
	return s;

	/*
	if (s != NULL)
		return s;
	else
		fprintf(stderr, "Error obtaining information about specified symbol: %s\n", strerror(errno));

	return NULL;
	*/

}

struct symbol_table * symbol_table_pop(struct symbol_table *t)
{
	struct symbol_table *temp = t;
	free(t);
	return temp->prev;
}


/* Checks if declaration is valid (Three Cases)
	1) Functions (must match) -- recursively check if types match
	2) extern int i; int i;
	3) int i; int i; (In global scope)
*/
int is_valid_redeclaration(struct symbol_table *t, struct symbol *s, int name_space)
{
	/* If the symbol does not currently exist in the table, the declaration should be valid */
	if (s->redeclaration == 0)
		return 1;

	struct symbol *existing = symbol_table_get_info(t, s->name, name_space);

	/* Case 1 */
	if( (strcmp(find_sym_use(s) , "function") == 0) && (strcmp(find_sym_use(existing) , "function") == 0) )
	{	
		union astnode *temp = existing->ast_node->scalar.node;
		union astnode *temp2 = s->ast_node->scalar.node;

		/* Walk along the AST node trail to see if types match */
		while (temp->gen.node_type == temp2->gen.node_type)
		{
			if (temp->gen.node_type == AST_SCALAR)
			{
				/* Should be scalar nodes here, which are the last nodes in the trail */
				if (temp->scalar.type == temp2->scalar.type)
					return 1;
				else
					return 0;
			}

			/* Should be pointers here */
			temp = temp->gen.prev;
			temp2 = temp2->gen.prev;
		}
	}

	/* Case 2 */
	//if(strcmp(find_sym_class(existing), "EXTERN") == 0)
	if(existing->storage_class == EXTERN_T)
	{
		union astnode *temp = existing->ast_node->scalar.node;
		union astnode *temp2 = s->ast_node->scalar.node;

		/* Walk along the AST node trail to see if types match */
		while (temp->gen.node_type == temp2->gen.node_type)
		{
			if (temp->gen.node_type == AST_SCALAR)
			{
				/* Should be scalar nodes here, which are the last nodes in the trail */
				if (temp->scalar.type == temp2->scalar.type)
					return 1;
				else
					return 0;
			}

			temp = temp->gen.prev;
			/* Skip the EXTERN node */
			if (temp->gen.node_type == AST_STORAGE)
				temp = temp->gen.prev;

			temp2 = temp2->gen.prev;
		}
	}

	/* Case 3 */
	if(t->scope_type == GLOBAL_SCOPE)
	{
		union astnode *temp = existing->ast_node->scalar.node;
		union astnode *temp2 = s->ast_node->scalar.node;

		/* Walk along the AST node trail to see if types match */
		while (temp->gen.node_type == temp2->gen.node_type)
		{
			if (temp->gen.node_type == AST_SCALAR)
			{
				/* Should be scalar nodes here, which are the last nodes in the trail */
				if (temp->scalar.type == temp2->scalar.type)
					return 1;
				else
					return 0;
			}

			temp = temp->gen.prev;
			temp2 = temp2->gen.prev;
		}
	}

	/* If neither of these cases is reached, the redeclaration is invalid */
	return 0;

}


/* If symbol_exists == 1, rewrite over the contents of symbol, if not, just add details to the symbol */
void update_symbol(struct symbol_table *t, union astnode *n, int name_space, int symbol_exists, int l, char *f)
{
	struct symbol *s = symbol_table_get_info(t, n->ident.name, name_space);
	if (symbol_exists)
	{
		//printf("Redeclaring %s at %s:%d\n", s->name, f, l);
		s->lineno = l;
		s->filename = strdup(f);
		s->ast_node = n;
	}
	else
	{
		//printf("Updating info for %s at %s:%d\n", s->name, f, l);
		s->ast_node = n;
	}
}


/*
void symbol_table_free(struct symbol_table *t)
{
	free(t);
}
*/
/*
void print_sym_tab(struct symbol *s)
{
	if(s == NULL)
		return ;

	fprintf(stdout, "Name of entry: %s\n", s->name);
	fprintf(stdout, "%s:%d\n", s->filename, s->lineno);
	fprintf(stdout, "Type: %d\n", s->type);
	fprintf(stdout, "Namespace: %d\n", s->ns_type);
	fprintf(stdout, "Storage Class: %d\n", s->storage_class);
	print_sym_tab(s->next);

}
*/
/*
void print_sym_tab(struct symbol_table *t)
{
	struct symbol *s = t->head;
	printf("Printing table:\n");
	while (s != NULL)
	{
		printf("%s defined at %s:%d with Namespace %d and scope %d\n", s->name, s->filename, s->lineno, s->name_space, t->scope_type);
		s = s->next;
	}

}
*/

void print_sym_tab(struct symbol_table *t)
{
	struct symbol *s = t->head;
	while (s != NULL)
	{
		char *use = find_sym_use(s);
		if(strcmp(use, "function") == 0)
		{
			union astnode *n = s->ast_node->fn.ret_value; /* Do this in order to get to AST_IDENT node, not just the AST_FN one */
			while (n->gen.node_type != AST_FN)
				n = n->gen.prev;
			n = n->fn.ret_value;
			if (n == NULL)
				printf("NULL\n");
			printf("%s is defined at  %s:%d [in %s scope starting at %s:%d] as a function with stgclass %s returning type: \n", s->name, s->filename, s->lineno, get_scope_name(t->scope_type), t->filename, t->lineno, find_sym_class(s));
			print_ast(t, n, 1);
		}
		else if(strcmp(use, "variable") == 0)
		{
			printf("%s is defined at  %s:%d [in %s scope starting at %s:%d] as a %s with stgclass %s of type: \n", s->name, s->filename, s->lineno, get_scope_name(t->scope_type), t->filename, t->lineno, use, find_sym_class(s));
			union astnode *n = s->ast_node->scalar.node; /* In order to get to AST_IDENT node, not just the AST_SCALAR one */ 

			/* Walk along node trail until we find the right node */
			while ( (n->gen.node_type != AST_ARRAY) && (n->gen.node_type != AST_POINTER) && (n->gen.node_type != AST_SCALAR))
					n = n->gen.prev;

			switch(n->gen.node_type)
			{
				case AST_ARRAY: 	print_ast(t, n, 1); break;
				case AST_POINTER: 	print_ast(t, n, 1); break;
				case AST_SCALAR:	print_ast(t, n, 1); break;
				default: printf("NULL\n");
			}
		}
		else if(strcmp(use, "struct") == 0)
		{
			printf("struct %s definition at %s:%d{\n", s->name, s->filename, s->lineno);
			
			union astnode *p = s->ast_node;
			/*while ( p->gen.node_type != AST_STRUCT )
				p = p->gen.prev;*/

			struct symbol * struct_s = p->struct_n.mini->head;
			while (struct_s != NULL)
			{
				printf("%s is defined at  %s:%d [in STRUCT/UNION scope starting at %s:%d] as a field of struct %s of type: \n", struct_s->name, struct_s->filename, struct_s->lineno, p->struct_n.filename, p->struct_n.lineno, p->struct_n.name);
				//union astnode *n = s->ast_node;
				union astnode *n = struct_s->ast_node->scalar.node;

				/* Walk along node trail until we find the right node */
				while ( (n->gen.node_type != AST_ARRAY) && (n->gen.node_type != AST_POINTER) && (n->gen.node_type != AST_SCALAR))
					n = n->gen.prev;

				switch(n->gen.node_type)
				{
					case AST_ARRAY: 	print_ast(t, n, 1); break;
					case AST_POINTER: 	print_ast(t, n, 1); break;
					case AST_SCALAR:	print_ast(t, n, 1); break;
					case AST_STRUCT: 	print_ast(t, n, 1); break;
					default: printf("NULL\n");
				}

				struct_s = struct_s->next;

			}
			//printf("} (size = %d)\n", s->size);
			printf("}");
		}
		else if (strcmp(use, "label") == 0)
		{
			if(s->ast_node->named_label.defined)
				printf("%s is defined at  %s:%d [in %s scope starting at %s:%d] as a label", s->name, s->filename, s->lineno, get_scope_name(t->scope_type), t->filename, t->lineno);
			else
				printf("%s is defined at  %s:%d [in %s scope starting at %s:%d] as a label", s->name, s->filename, s->lineno, get_scope_name(t->scope_type), t->filename, t->lineno);
		}
		s = s->next;
	}
} 

/* Get name of scope */
char * get_scope_name(int scope_type)
{
	switch(scope_type)
	{
		case GLOBAL_SCOPE: return "GLOBAL";
		case FUNCTION_SCOPE: return "FUNCTION";
		case BLOCK_SCOPE: return "BLOCK";
		case PROTO_SCOPE: return "PROTO";
		case MINI: return "STRUCT/UNION";
	}

	return NULL;
}

/* Find use of symbol (i.e. var, fn, typedef) */
char * find_sym_use(struct symbol *symbol)
{
	union astnode *n = symbol->ast_node;
	while (n != NULL)
	{
		switch (n->gen.node_type)
		{
			case AST_SCALAR: return "variable"; 	 
			case AST_FN: return "function";
			case AST_STRUCT: return "struct";
			case AST_NAMED_LABEL: return "label";
		}

		n = n->gen.prev;
	}

	return NULL;
}

char * find_sym_type(struct symbol *symbol)
{
	union astnode *n = symbol->ast_node;

	while (n != NULL)
	{
		switch (n->gen.node_type)
		{
			case AST_POINTER: return "pointer";
			case AST_SCALAR: return "scalar"; 	 
			case AST_FN: return "function";
			case AST_ARRAY: return "array";
		}

		n = n->gen.prev;

	}

	return NULL;
}

char * find_sym_class(struct symbol *symbol)
{
	union astnode *n = symbol->ast_node;
	while (n != NULL)
	{
		if (n->gen.node_type == AST_STORAGE)
		{
			switch (n->storage.storage_class)
			{
				case AUTO_T: return "AUTO";
				case EXTERN_T: return "EXTERN";
				case STATIC_T: return "STATIC";
			}
		}

		n = n->gen.prev;
	}

	switch (symbol->scope_type)
	{
		case FUNCTION_SCOPE: return "AUTO";
		default: return "EXTERN";
	}
}

/* Better version of the find_sym_class function */
int sym_class_fn(struct symbol *symbol)
{
	union astnode *n = symbol->ast_node->scalar.node;
	while (n != NULL)
	{
		if (n->gen.node_type == AST_STORAGE)
			return n->storage.storage_class;

		n = n->gen.prev;
	}

	switch (symbol->scope_type)
	{
		case FUNCTION_SCOPE: return AUTO_T;
		default: return EXTERN_T;
	}
}






