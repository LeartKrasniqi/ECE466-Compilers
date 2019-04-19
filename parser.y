%debug
%{	/* Parser */
#include "ast.h"
#include "sym_tab.h"
#include <stdio.h>
#include <stdlib.h>

int yylex();
extern int lineno;
extern char file[256];
void yyerror(const char* msg) {fprintf(stderr, "%s:%d: %s\n", file, lineno, msg);}
char* print_kw(int token);
struct symbol_table *curr_scope;
struct symbol *curr_symbol;
int symbol_exists;

%}
%error-verbose
%union{ /* Definition of yylval union */
		
		struct identifier {
			char *name;
		} ident;

		struct string_literal {
			char word[4096];
			int length;
		} string;

		struct number {
			unsigned long long int_value;
			long double float_value;
			int sign;
			int type;
		} num;

		char char_lit;

		union astnode *astnode_p;
		struct symbol *temp;

}
/* Tokens */
%token <num.int_value> IDENT CHARLIT STRING NUMBER INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR ELLIPSIS
%token <num.int_value> TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ ANDEQ OREQ XOREQ AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO
%token <num.int_value> DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC
%token <num.int_value> STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

/* Declarations */
%type <astnode_p> declaration initialized_declarator_list storage_class_specifier type_specifier 
%type <astnode_p> /*function_specifier*/ initialized_declarator declarator initializer enum_type_specifier floating_point_type_specifier
%type <astnode_p> integer_type_specifier structure_type_specifier /*typedef_name*/ union_type_specifier void_type_specifier pointer_declarator
%type <astnode_p> direct_declarator simple_declarator function_declarator array_declarator pointer type_qualifier_list /*constant_expression*/
%type <astnode_p> parameter_type_list parameter_list parameter_declaration identifier_list initializer_list designation designator_list
%type <astnode_p> designator type_qualifier
/*%type <num.int_value> type_qualifier*/
%type <astnode_p> declaration_specifiers  

/* Types */
%type <astnode_p> bool_type_specifier  
%type <astnode_p> complex_type_specifier enum_type_definition enum_type_reference enum_tag enum_definition_list enum_constant_definition
%type <astnode_p> enum_constant structure_type_definition structure_type_reference structure_tag field_list component_declaration
%type <astnode_p> component_declarator_list component_declarator simple_component bit_field width union_type_definition 
%type <astnode_p> union_type_reference union_tag type_name abstract_declarator direct_abstract_declarator
%type <num.int_value> signed_type_specifier unsigned_type_specifier character_type_specifier

/* Expressions */
%type <astnode_p> primary_expression constant parenthesized_expression postfix_expression subscript_expression
%type <astnode_p> component_selection_expression function_call expression_list postincrement_expression postdecrement_expression 
%type <astnode_p> compound_literal cast_expression unary_expression sizeof_expression unary_minus_expression unary_plus_expression 
%type <astnode_p> logical_negation_expression bitwise_negation_expression address_expression 
%type <astnode_p> indirection_expression preincrement_expression predecrement_expression multiplicative_expression additive_expression 
%type <astnode_p> shift_expression relational_expression equality_expression bitwise_or_expression bitwise_xor_expression 
%type <astnode_p> bitwise_and_expression logical_or_expression logical_and_expression conditional_expression assignment_expression expression
%type <num.int_value> assignment_op

/* Statements */
%type <astnode_p> statement conditional_statement iterative_statement expression_statement labeled_statement label compound_statement
%type <astnode_p> declaration_or_statement_list declaration_or_statement if_statement if_else_statement while_statement do_statement
%type <astnode_p> for_statement for_expressions initial_clause switch_statement case_label default_label break_statement continue_statement
%type <astnode_p> goto_statement named_label null_statement return_statement 

/* Functions */
%type <astnode_p> translation_unit top_level_declaration function_definition function_def_specifier declaration_list


%start translation_unit

%%
/* TODO - 	fix indentation in print_ast, 			- Done i think
			figuring out if a label is defined, 
			cleaning up print_sym code, 
			fix list of expressions 				- Done i think 
*/

 /* Grammars */

/* duplicate definition for assignment 2, might have to remove */
/*
expression_statement : expression ';' 						{
																$$ = astnode_alloc(AST_TOP_EXPR);
															 	$$->top_expr.left = $1;
															 	fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
															 	print_ast($$, 0);
															 	fprintf(stdout, "\n---------- END LINE %d ----------\n", lineno);
															}
					 | expression_statement expression ';' 	{ *//* More than one expression */	
/*
					 											$$ = astnode_alloc(AST_TOP_EXPR);
												 				$$->top_expr.left = $2;
												 				fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
																print_ast($$, 0);
																fprintf(stdout, "---------- END LINE %d ----------\n", lineno);
															}
					 ;*/

/* Declarations */
declaration : declaration_specifiers initialized_declarator_list ';' 		{ 
																				union astnode *top = $2;
																				
																				/* Get proper order of symbols by reversing their order */		
																				struct symbol *new_symbol_list = NULL;
																				while (curr_symbol != NULL)
																				{
																					struct symbol *temp = curr_symbol->list;
																					curr_symbol->list = new_symbol_list;
																					new_symbol_list = curr_symbol;
																					curr_symbol = temp;
																				}
																				curr_symbol = new_symbol_list;

																				while ($2 != NULL)
																				{
																					union astnode *n = $1;

																					/* Walk along node trail */
																					while ( (n != NULL) && (n->gen.node_type == AST_STORAGE) )
																						n = n->gen.prev;

																					/* Append the list */
																					n = astnode_append(n, $2, PREV);
																					/*
																					union astnode *k = n;
				  																	int o = 0;
					  																while (k != NULL)
												  									{
												  										o++;
												  										printf("Node %d with type %d\n", o, k->gen.node_type);
												  										k = k->gen.prev;
												  									}*/																				

																					$$ = astnode_reverse(n, PREV);
																					//union astnode *temp = $$;
																					#if 0
																					printf("Now reverse\n");
																					union astnode *l = $$;
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}
												  									#endif

																					if ($1->gen.node_type == AST_STORAGE)
																					{
																						union astnode *t1 = $$->gen.prev;
																						union astnode *t2 = $1;

																						/* Walk along node trail again */
																						while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																							t2 = t2->gen.prev;

																						t2->gen.prev = t1;
																						$$->gen.prev = $1;
																					}
																					

																					$2 = $2->gen.next;


																					union astnode *temp = $$;
																					union astnode *temp1 = $$;
																					int type_flag = AST_SCALAR;
												  									while (temp != NULL)
												  									{
												  										if(temp->gen.node_type == AST_FN)
												  										{
												  											type_flag = AST_FN;
												  											temp->fn.ret_value = find_ret_value(temp);
												  											break;
												  										}
												  										else if (temp->gen.node_type == AST_ARRAY)
												  										{
												  											temp->array.type = find_ret_value(temp);
												  										}
												  										//else if (temp->gen.node_type == )
												  											
												  										temp = temp->gen.prev;
												  									}


											  										$$ = temp1;

											  										
											  										union astnode *symbol_node = $$;
											  										union astnode *hak = astnode_alloc(type_flag);

														  							/* Since the union is laid out consistently, scalar.filename should work for fn.filename -- if not, use switch case*/
														  							hak->scalar.filename = strdup(file);
														  							hak->scalar.lineno = lineno;
														  							hak->scalar.name = strdup(curr_symbol->name);
														  							hak->scalar.node = $$;
														  							
														  							curr_symbol->ast_node = hak;

														  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

														  							/*
														  							printf("SYMBOL NODE\n");
																					union astnode *l = curr_symbol->ast_node->scalar.node;
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}*/

														  							/* Check for valid redeclaration here */
														  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
														  								/* Do Nothing */;
														  							else
														  							{
														  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
														  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
														  								exit(-1);
														  							}



																					curr_symbol = curr_symbol->list;


																				}
																				curr_symbol = NULL;

																				//$$ = top;
																				/*
																				union astnode *q = $$;
																				printf("end\n");
				  																int o = 0;
				  																while (q != NULL)
											  									{
											  										o++;
											  										printf("Node %d with type %d\n", o, q->gen.node_type);
											  										q = q->gen.prev;
											  									}*/
																				/*
											  									union astnode *temp = $$;
											  									while (temp != NULL)
											  									{
											  										if(temp->gen.node_type == AST_FN)
											  										{
											  											temp->fn.ret_value = find_ret_value(temp);
											  											break;
											  										}
											  										else if (temp->gen.node_type == AST_ARRAY)
											  										{
											  											temp->array.type = find_ret_value(temp);
											  										}
											  										temp = temp->gen.prev;
											  									}

											  									$$ = temp;*/
											  									/*
																				if ($$->gen.node_type == AST_FN)
																				{
																					printf("here\n");
																					$$->fn.ret_value = find_ret_value($$);
																				}*/



																			}
			;

declaration_specifiers : storage_class_specifier  							
																				
					   | storage_class_specifier declaration_specifiers 	{ /* Append to list */
																				$$ = astnode_append($1, $2, PREV);
																			}
					   | type_specifier 									
					   | type_specifier declaration_specifiers 				{ /* Append to list */
					   															$$ = astnode_append($1, $2, PREV);
					   														}
					   | type_qualifier  									{ /* Ignore for now */ }
					   | type_qualifier declaration_specifiers 				{ $$ = $2;}
					   /*| function_specifier
					   | function_specifier declaration_specifiers*/
					   ;

initialized_declarator_list : initialized_declarator
							| initialized_declarator_list ',' initialized_declarator 	{ /* Append to list */
																							$$ = astnode_append($1, $3, NEXT)
																						}
							;

initialized_declarator : declarator 
					   | declarator '=' initializer 	{$$ = $1;}
					   ;

storage_class_specifier : AUTO 		{ /* AUTO storage class */
										$$ = astnode_alloc(AST_STORAGE);
										$$->storage.storage_class = AUTO_T;
									}
						| EXTERN 	{ /* EXTERN storage class */
										$$ = astnode_alloc(AST_STORAGE);
										$$->storage.storage_class = EXTERN_T;
									}
						| STATIC 	{ /* STATIC storage class */
										$$ = astnode_alloc(AST_STORAGE);
										$$->storage.storage_class = STATIC_T;
									}
						;

type_specifier : enum_type_specifier 				{ /* Ignore for now */}
			   | floating_point_type_specifier 	
			   | integer_type_specifier 			
			   | structure_type_specifier 			
			   /*| typedef_name */						{ /* Ignore for now */}
			   | union_type_specifier 				
			   | void_type_specifier 				
			   ;

type_qualifier : CONST 		
			   | VOLATILE 	
			   | RESTRICT 	
			   ;

declarator : pointer_declarator
		   | direct_declarator
		   ;

direct_declarator : simple_declarator
				  | '(' declarator ')' 		{$$ = $2;}
				  | function_declarator
				  | array_declarator
				  ;

simple_declarator : IDENT 		{ /* Declaring an identifier */
				  					/*
				  					$$ = astnode_alloc(AST_IDENT);
				  					$$->ident.name = yylval.ident.name;
				  					if (symbol_table_insert(curr_scope, $$->ident.name, lineno, file, OTHER_NS, $$) == 0)
				  						//fprintf(stderr, "Redeclaration of ident %s at %s:%d\n", $$->ident.name, file, lineno);
				  						symbol_exists = 1;
				  					else
				  						symbol_exists = 0;*/

				  					$$ = astnode_alloc(AST_IDENT);
				  					$$->ident.name = yylval.ident.name;

				  					/* If we are inserting a member of a struct/union, we have insert with MEMBER_NS, other than that we go for OTHER_NS */
				  					if (curr_scope->scope_type == MINI)
				  						curr_symbol = symbol_table_insert(curr_scope, $$->ident.name, lineno, file, MEMBER_NS, $$, curr_symbol);
				  					else
				  						curr_symbol = symbol_table_insert(curr_scope, $$->ident.name, lineno, file, OTHER_NS, $$, curr_symbol);

								}
				  ;

pointer_declarator : pointer direct_declarator 	{ /* Declaration of pointer */
				  									$$ = astnode_append($1, $2, PREV);
												}
				   ;

pointer : '*' 								{ /* Simple Pointer */
				   								$$ = astnode_alloc(AST_POINTER);
				   								//$$->pointer.left = NULL;
											}
		| '*' type_qualifier_list 			{ /* Pointer with type qualifier */ 
												$$ = astnode_alloc(AST_POINTER);
												//$$->pointer.left = NULL;
											}
		| '*' pointer 						{ /* Pointer to Pointer */
												$$ = astnode_alloc(AST_POINTER);
												$$->pointer.prev = $2;
											}
		| '*' type_qualifier_list pointer 	{ /* Pointer to Pointer */
												$$ = astnode_alloc(AST_POINTER);
												$$->pointer.prev = $3;
											}
		;

type_qualifier_list : type_qualifier
					| type_qualifier_list type_qualifier
					;

array_declarator : direct_declarator '[' ']' 	{ /* Array of unknown size */
													$$ = astnode_alloc(AST_ARRAY);
													$$->array.size = -1;
													$$->array.prev = $1;

												}
				/* direct_declarator '[' constant_expression ']' */
				 | direct_declarator '[' conditional_expression ']' { /* Array with constant size */
																		if ($3->gen.node_type == AST_NUMBER)
																		{
																			$$ = astnode_alloc(AST_ARRAY);
																			$$->array.size = $3->num.int_value;
																			$$->array.prev = $1;
																		}
																		else
																		{
																			yyerror("Non-constant array size declarator");
																			$$ = NULL;
																		}
				 													}
				 ;

/*constant_expression : conditional_expression
					;*/

function_declarator : direct_declarator '(' parameter_type_list ')'		{ yyerror("Function prototype");}
					| direct_declarator '(' ')'							{ /* Function Declarator */
																			$$ = astnode_alloc(AST_FN);
																			$$->fn.lineno = lineno;
																			$$->fn.filename = strdup(file);
																			astnode_append($$, $1, PREV);
																		}
					| direct_declarator '(' identifier_list ')' 		{yyerror("ident list");}
					;

parameter_type_list : parameter_list 
					| parameter_list ',' ELLIPSIS
					;

parameter_list : parameter_declaration
			   | parameter_list ',' parameter_declaration
			   ;

parameter_declaration : declaration_specifiers declarator
					  | declaration_specifiers
					  | declaration_specifiers abstract_declarator
					  ;

identifier_list : IDENT
				| parameter_list ',' IDENT
				;

initializer : assignment_expression
		   | '{' initializer_list '}' 		
		   | '{' initializer_list ',' '}'
		   ;

initializer_list : initializer
				 | initializer_list ',' initializer
				 | designation initializer
				 | initializer_list ',' designation initializer
				 ;

designation : designator_list '='
			;

designator_list : designator 
				| designator_list designator 
				;

designator : /*'[' constant_expression ']'*/
				'[' conditional_expression ']'
		   | '.' IDENT
		   ;


/* Types */
integer_type_specifier : signed_type_specifier 		{ /* Signed Type Specifier */
														$$ = astnode_alloc(AST_SCALAR);
														$$->scalar.type = $1;
														$$->scalar.sign = SIGNED_T;
													}
					   | unsigned_type_specifier	{ /* Unsigned Type Specifier */
														$$ = astnode_alloc(AST_SCALAR);
														$$->scalar.type = $1;
														$$->scalar.sign = UNSIGNED_T;
					   								}
					   | character_type_specifier 	{ /* Character Type Specifier */
					   									$$ = astnode_alloc(AST_SCALAR);
					   									$$->scalar.type = CHAR_T;
					   									$$->scalar.sign = $1;
					   								}
					   | bool_type_specifier 
					   ;

signed_type_specifier : SHORT 					{$$ = INT_T;}
					  | SHORT INT 				{$$ = INT_T;}
					  | SIGNED SHORT 			{$$ = INT_T;}
					  | SIGNED SHORT INT 		{$$ = INT_T;}
					  | INT 					{$$ = INT_T;}
					  | SIGNED INT 				{$$ = INT_T;}
					  | SIGNED 					{$$ = INT_T;}
					  | LONG 					{$$ = LONG_T;}
					  | LONG INT 				{$$ = LONG_T;}
					  | SIGNED LONG 			{$$ = LONG_T;}
					  | SIGNED LONG INT 		{$$ = LONG_T;}
					  | LONG LONG 				{$$ = LONGLONG_T;}
					  | LONG LONG INT 			{$$ = LONGLONG_T;}
					  | SIGNED LONG LONG 		{$$ = LONGLONG_T;}
					  | SIGNED LONG LONG INT 	{$$ = LONGLONG_T;}
					  ;

unsigned_type_specifier : UNSIGNED SHORT 			{$$ = INT_T;}
						| UNSIGNED SHORT INT 		{$$ = INT_T;}
						| UNSIGNED 					{$$ = INT_T;}
						| UNSIGNED INT 				{$$ = INT_T;}
						| UNSIGNED LONG 			{$$ = LONG_T;}
						| UNSIGNED LONG INT 		{$$ = LONG_T;}
						| UNSIGNED LONG LONG 		{$$ = LONGLONG_T;}
						| UNSIGNED LONG LONG INT 	{$$ = LONGLONG_T;}
						;

character_type_specifier : CHAR 			{$$ = SIGNED_T;}
						 | SIGNED CHAR 		{$$ = SIGNED_T;}
						 | UNSIGNED CHAR 	{$$ = SIGNED_T;}
						 ;

bool_type_specifier : _BOOL 	{$$ = NULL;}
					;

floating_point_type_specifier : FLOAT 					{
															$$ = astnode_alloc(AST_SCALAR);
															$$->scalar.type = FLOAT_T;
															$$->scalar.sign = SIGNED_T;
														}
							  | DOUBLE 					{
							  								$$ = astnode_alloc(AST_SCALAR);
															$$->scalar.type = DOUBLE_T;
															$$->scalar.sign = SIGNED_T;
														}
							  | LONG DOUBLE 			{	
							  								$$ = astnode_alloc(AST_SCALAR);
															$$->scalar.type = LONGDOUBLE_T;
															$$->scalar.sign = SIGNED_T;
							  							}
							  | complex_type_specifier 	{fprintf(stderr, "complex float at %s:%d\n", file, lineno); $$ = NULL;}
							  ;

complex_type_specifier : FLOAT _COMPLEX 		{$$ = NULL;}
					   | DOUBLE _COMPLEX 		{$$ = NULL;}
					   | LONG DOUBLE _COMPLEX 	{$$ = NULL;}
					   ;

enum_type_specifier : enum_type_definition 		{fprintf(stderr, "enum at %s:%d\n", file, lineno); $$ = NULL;}
					| enum_type_reference 		{fprintf(stderr, "enum at %s:%d\n", file, lineno); $$ = NULL;}
					;

enum_type_definition : ENUM '{' enum_definition_list '}' 				{$$ = NULL;}
					 | ENUM '{' enum_definition_list ',' '}' 			{$$ = NULL;}
					 | ENUM enum_tag '{' enum_definition_list '}' 		{$$ = NULL;}
					 | ENUM enum_tag '{' enum_definition_list ',' '}' 	{$$ = NULL;}
					 ;

enum_type_reference : ENUM enum_tag 	{$$ = NULL;}
					;

enum_tag : IDENT 	{$$ = NULL;}
		 ;

enum_definition_list : enum_constant_definition
					 | enum_definition_list ',' enum_constant_definition
					 ;

enum_constant_definition : enum_constant 
						 | enum_constant '=' expression
						 ;

enum_constant : IDENT 	{$$ = NULL;}
			  ;

structure_type_specifier : structure_type_definition
						 | structure_type_reference
						 ;

structure_type_definition : STRUCT '{' {union astnode *n_s = astnode_alloc(AST_STRUCT); n_s->struct_n.mini = symbol_table_alloc(MINI, lineno, file, curr_scope); curr_scope = n_s->struct_n.mini} field_list '}' 		{ /* Structures */

						 																																																	curr_scope = symbol_table_pop(curr_scope);																												

						 																																								

																																																						}				 					
						  | STRUCT structure_tag '{' {curr_scope = symbol_table_alloc(MINI, lineno, file, curr_scope); curr_symbol->ast_node->struct_n.mini = curr_scope; curr_symbol->ast_node->struct_n.complete = 0; } field_list '}' 		{
						  																																																							curr_symbol->ast_node->struct_n.complete = 1;
						  																																																							$$ = curr_symbol->ast_node;
						  																																																																																									
						  																																																							//printf("Node 1 with type %d\n", $$->gen.node_type);
						  																																																							//printf("Node 2 with type %d\n", $$->struct_n.node->gen.node_type);
																																																																																															
						  																																																							print_sym_tab(curr_scope);
						  																																																							curr_scope = symbol_table_pop(curr_scope);
																																					  																								//$2->struct_n.complete = 1;
																																					  																							}
						  ;

structure_type_reference : STRUCT structure_tag 								
						 ;

structure_tag : IDENT 		{ /* Tag is IDENT */
						 		$$ = astnode_alloc(AST_IDENT);
						 		$$->ident.name = yylval.ident.name;
						 		union astnode *n = astnode_alloc(AST_STRUCT);
						 		n->struct_n.node = $$;
						 		n->struct_n.filename = strdup(file);
						 		n->struct_n.lineno = lineno;
						 		n->struct_n.name = yylval.ident.name;
						 		curr_symbol = symbol_table_insert(curr_scope, $$->ident.name, lineno, file, TAG_NS, n, curr_symbol);

						 		/* Check for valid redeclaration here */
								if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
									/* Do Nothing */;
								else
								{
									struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
									fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
									exit(-1);
								}
						 		

							}
			  ;

field_list : component_declaration 				
		   | field_list component_declaration 	{$$ = astnode_append($1, $2, PREV);}
		   ;

component_declaration : type_specifier component_declarator_list ';'  					{
																							union astnode *n = $1;

																							/* Walk along node trail */
																							while (n->gen.node_type == AST_STORAGE)
																								n = n->gen.prev;

																							/* Append the list */
																							n = astnode_append(n, $2, PREV);

																							$$ = astnode_reverse(n, PREV);

																							if ($1->gen.node_type == AST_STORAGE)
																							{
																								union astnode *t1 = $$->gen.prev;
																								union astnode *t2 = $1;

																								/* Walk along node trail again */
																								while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																									t2 = t2->gen.prev;

																								t2->gen.prev = t1;
																								$$->gen.prev = $1;
																							}

																							#if 0
																							printf("Now reverse\n");
																							union astnode *l = $$;
							  																int b = 0;
							  																while (l != NULL)
														  									{
														  										b++;
														  										printf("Node %d with type %d\n", b, l->gen.node_type);
														  										l= l->gen.prev;
														  									}
														  									#endif

																							union astnode *temp = $$;
														  									while (temp != NULL)
														  									{
														  										if(temp->gen.node_type == AST_FN)
														  										{
														  											temp->fn.ret_value = find_ret_value(temp);
														  											break;
														  										}
														  										else if (temp->gen.node_type == AST_ARRAY)
														  										{
														  											temp->array.type = find_ret_value(temp);
														  										}
														  										temp = temp->gen.prev;
														  									}

														  									//$$ = temp;

														  									union astnode *symbol_node = $$;
													  										union astnode *hak = astnode_alloc(AST_FN);
													  										  							
																  							hak->fn.filename = strdup(file);
																  							hak->fn.lineno = lineno;
																  							hak->fn.name = strdup(curr_symbol->name);
																  							hak->fn.ret_value = $$;
																  							curr_symbol->ast_node = hak;
																  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

																  							/* Check for valid redeclaration */
																  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
																  								/* Do Nothing */;
																  							else
																  							{
																  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
																  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
																  								exit(-1);
																  							}

														  									curr_symbol = curr_symbol->list; 

																						}
					  ;

component_declarator_list : component_declarator   								
						  | component_declarator_list ',' component_declarator 	{$$ = astnode_reverse($1, PREV);}
						  ;

component_declarator : simple_component
					 | bit_field
					 ;

simple_component : declarator 	{}//$$ = astnode_reverse($1, PREV);}
				 ;

bit_field : ':' width
		  | declarator ':' width
		  ;

width : /*constant_expression*/
		  conditional_expression
	  ;

union_type_specifier : union_type_definition
					 | union_type_reference
					 ;

union_type_definition : UNION '{' field_list '}'
					  | UNION union_tag '{' field_list '}'
					  ;

union_type_reference : UNION union_tag
					 ;

union_tag : IDENT
		  ;

void_type_specifier : VOID 		{ /* VOID specifier, treat as scalar */
									$$ = astnode_alloc(AST_SCALAR);
									$$->scalar.type = VOID_T;
									$$->scalar.sign = VOID_SIGN;
								}
					;

/*typedef_name : IDENT */
			 ;

type_name : declaration_specifiers 						{ 

														}
		  | declaration_specifiers abstract_declarator
		  ;

abstract_declarator : pointer
					| direct_abstract_declarator
					| pointer direct_abstract_declarator
					;

direct_abstract_declarator : '(' abstract_declarator ')'
						   | '[' ']'
						   | '[' conditional_expression ']' /*| '[' constant_expression ']'*/
						   | direct_abstract_declarator '[' ']'
						   | direct_abstract_declarator '[' conditional_expression ']' /*constant_expression ']'*/
						   | '[' expression ']'
						   | direct_abstract_declarator '[' expression ']'
						   | '[' '*' ']'
						   | direct_abstract_declarator '[' '*' ']'
						   | '(' ')'
						   | '(' parameter_type_list ')'
						   | direct_abstract_declarator '(' ')'
						   | direct_abstract_declarator '(' parameter_type_list ')'
						   ;


 /* Expressions */
primary_expression  : IDENT						{  /* Identifiers */
													$$ = astnode_alloc(AST_IDENT);
													$$->ident.name = yylval.ident.name;
												}	
			   		| constant			
			   		| parenthesized_expression	
			   		;

constant : NUMBER 	{ /* Various Numbers */
			   			$$ = astnode_alloc(AST_NUMBER);
			   			$$->num.int_value = yylval.num.int_value;
			   			$$->num.float_value = yylval.num.float_value;
			   			$$->num.sign = yylval.num.sign;
			   			$$->num.type = yylval.num.type;
					}
		 | CHARLIT 	{ /* Character Literals */
						$$ = astnode_alloc(AST_CHARLIT);
						$$->charlit.c = yylval.char_lit;
					}
		 | STRING 	{ /* Strings */
						$$ = astnode_alloc(AST_STRING);
						strncpy($$->string.word, yylval.string.word, yylval.string.length);
						$$->string.length = yylval.string.length;
					}
		 ;

parenthesized_expression :	'(' expression ')'	{$$ = $2;}
						 ;

postfix_expression : primary_expression
				   | subscript_expression
				   | component_selection_expression
				   | function_call
				   | postincrement_expression
				   | postdecrement_expression
				   | compound_literal
				   ;

subscript_expression : postfix_expression '[' expression ']' 	{ /* Convert a[b] to *(a + b) */
				   													$$ = astnode_alloc(AST_UNOP);
				   													$$->unop.operator = '*';
				   													union astnode *next = astnode_alloc(AST_BINOP);
				   													$$->unop.left = next;
				   													next->binop.operator = '+';
				   													next->binop.left = $1;
				   													next->binop.right = $3; 
																}
					 ;

component_selection_expression : postfix_expression '.' IDENT 		{ /* Direct Component Selection */	
					 													$$ = astnode_alloc(AST_COMP_SELECT);
					 													$$->comp_select.left = $1;
					 													$$->comp_select.right = astnode_alloc(AST_IDENT);
																		$$->comp_select.right->ident.name = yylval.ident.name;
																	}	
							   | postfix_expression INDSEL IDENT 	{ /* Indirect Component Selection -- Convert to Direct */
																		$$ = astnode_alloc(AST_COMP_SELECT);
																		$$->comp_select.right = astnode_alloc(AST_IDENT);
																		$$->comp_select.right->ident.name = yylval.ident.name;

																		union astnode *p = astnode_alloc(AST_UNOP);
																		p->unop.operator = '*';
																		p->unop.left = $1;

																		$$->comp_select.left = p;
							   										}
							   ;

function_call : postfix_expression '(' ')'						{ /* Function with no arguments */
																	$$ = astnode_alloc(AST_FNCALL);
																	$$->fncall.left = $1;
																	$$->fncall.right = NULL;
																}
			  | postfix_expression '(' expression_list ')'		{ /* Function with arguments */
			  														$$ = astnode_alloc(AST_FNCALL);
																	$$->fncall.left = $1;
																	$$->fncall.right = $3;
			  													}
			  ;

expression_list : assignment_expression
				| expression_list ',' assignment_expression		{ /* List of Expressions */
																	//$$ = astnode_alloc(AST_EXPR_LIST);
																	//$$->expr_list.left = $1;
																	//$$->expr_list.right = $3;  
																	//$$->expr_list.next = astnode_append($1, $3, NEXT);
																	$$ = astnode_append($1, $3, NEXT);
																	
																}
				;

postincrement_expression : postfix_expression PLUSPLUS		{ /* a++ */
																$$ = astnode_alloc(AST_UNOP);
																$$->unop.operator = PLUSPLUS;
																$$->unop.left = $1;
															}
						 ;

postdecrement_expression : postfix_expression MINUSMINUS	{ /* a-- */
																$$ = astnode_alloc(AST_UNOP);
																$$->unop.operator = MINUSMINUS;
																$$->unop.left = $1;
															}
						 ;

compound_literal : '(' type_name ')' '{' initializer_list '}'		{$$ = NULL;}
				 | '(' type_name ')' '{' initializer_list ',' '}'	{$$ = NULL;}
				 ;

cast_expression : unary_expression
				| '(' type_name ')' cast_expression 	{$$ = NULL;}
				;

unary_expression : postfix_expression
        		 | sizeof_expression
        		 | unary_minus_expression
        		 | unary_plus_expression
        		 | logical_negation_expression
        		 | bitwise_negation_expression
        		 | address_expression
        		 | indirection_expression
        		 | preincrement_expression
        		 | predecrement_expression
        		 ;  

sizeof_expression : SIZEOF '(' type_name ')'		{  /* sizeof a type */
														$$ = astnode_alloc(AST_SIZEOF);
														$$->size_of.left = $3; 
													} 
				  | SIZEOF unary_expression 		{ /* sizeof a unary expression */
				  										$$ = astnode_alloc(AST_SIZEOF);
				  										$$->size_of.left = $2;
				  									}
				  ;

unary_minus_expression : '-' cast_expression 		{ /* Unary Minus */
				  										$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '-';
				  										$$->unop.left = $2;
													}
					   ;

unary_plus_expression  : '+' cast_expression 		{ /* Unary Plus */
					   									$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '+';
				  										$$->unop.left = $2;
													}
					   ;

logical_negation_expression : '!' cast_expression 	{ /* Unary Negation (Logical) */
					   									$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '!';
				  										$$->unop.left = $2;
													}		
							;

bitwise_negation_expression : '~' cast_expression 	{ /* Unary Negation (Bitwise) */
														$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '~';
				  										$$->unop.left = $2;
													}	 
							;

address_expression : '&' cast_expression 			{ /* Unary Address */
														$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '&';
				  										$$->unop.left = $2;
													}
				   ;

indirection_expression : '*' cast_expression 		{ /* Unary Indirection */
				   										$$ = astnode_alloc(AST_UNOP);
				  										$$->unop.operator = '*';
				  										$$->unop.left = $2;
													}
					   ;

preincrement_expression : PLUSPLUS unary_expression 	{ /* Convert ++a to a=a+1 */
					   										$$ = astnode_alloc(AST_ASSIGN);
					   										$$->assign.left = $2;

					   										/* Create binop of RHS */
					   										union astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->binop.operator = '+';
					   										b_op->binop.left = $2;

					   										/* Create the constant 1 */
					   										union astnode *one = astnode_alloc(AST_NUMBER);
					   										one->num.type = INT_T;
					   										one->num.int_value = 1;

					   										b_op->binop.right = one;
					   										$$->assign.right = b_op;
														}
						;

predecrement_expression : MINUSMINUS unary_expression 	{ /* Convert --a to a=a-1 */
															$$ = astnode_alloc(AST_ASSIGN);
					   										$$->assign.left = $2;

					   										/* Create binop of RHS */
					   										union astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->binop.operator = '-';
					   										b_op->binop.left = $2;

					   										/* Create the constant 1 */
					   										union astnode *one = astnode_alloc(AST_NUMBER);
					   										one->num.type = INT_T;
					   										one->num.int_value = 1;

					   										b_op->binop.right = one;
					   										$$->assign.right = b_op;
														}
						;

multiplicative_expression : cast_expression
						  | multiplicative_expression '*' cast_expression 	{ /* Multiplication */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = '*';
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
						  													}
						  | multiplicative_expression '/' cast_expression 	{ /* Division */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = '/';
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
																			}
						  | multiplicative_expression '%' cast_expression 	{ /* Modulo */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = '%';
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
						  													}
						  ;

additive_expression : multiplicative_expression
					| additive_expression '+' multiplicative_expression		{ /* Addition */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = '+';
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
																			}
					| additive_expression '-' multiplicative_expression		{ /* Subtraction */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = '-';
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
																			}
					;

shift_expression : additive_expression
				 | shift_expression SHL additive_expression 	{ /* Shift Left */
				 													$$ = astnode_alloc(AST_BINOP);
						  											$$->binop.operator = SHL;
						  											$$->binop.left = $1;
						  											$$->binop.right = $3;
				 												}
				 | shift_expression SHR additive_expression		{ /* Shift Right */
				 													$$ = astnode_alloc(AST_BINOP);
						  											$$->binop.operator = SHR;
						  											$$->binop.left = $1;
						  											$$->binop.right = $3;
				 												}
				 ;

relational_expression : shift_expression
					  | relational_expression '<' shift_expression		{ /* Less Than */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = '<';
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
					  													}
					  | relational_expression LTEQ shift_expression		{ /* Less Than or Equal To */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = LTEQ;
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
					  													}
					  | relational_expression '>' shift_expression		{ /* Greater Than */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = '>';
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
					  													}
					  | relational_expression GTEQ shift_expression		{ /* Greater Than or Equal To */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = GTEQ;
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
					  													}
					  ;

equality_expression : relational_expression
					| equality_expression EQEQ relational_expression	{ /* == */
																			$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = EQEQ;
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
																		}
					| equality_expression NOTEQ relational_expression	{ /* != */
																			$$ = astnode_alloc(AST_BINOP);
								  											$$->binop.operator = NOTEQ;
								  											$$->binop.left = $1;
								  											$$->binop.right = $3;
																		}
					;

bitwise_or_expression : bitwise_xor_expression 
					  | bitwise_or_expression '|' bitwise_xor_expression	{ /* Bitwise OR */
																				$$ = astnode_alloc(AST_BINOP);
									  											$$->binop.operator = '|';
									  											$$->binop.left = $1;
									  											$$->binop.right = $3;
					  														}
					  ;

bitwise_xor_expression : bitwise_and_expression
					   | bitwise_xor_expression '^' bitwise_and_expression	{ /* Bitwise XOR */
					   															$$ = astnode_alloc(AST_BINOP);
									  											$$->binop.operator = '^';
									  											$$->binop.left = $1;
									  											$$->binop.right = $3;	
					   														}
					   ;

bitwise_and_expression : equality_expression
					   | bitwise_and_expression '&' equality_expression		{ /* Bitwise AND */
					   															$$ = astnode_alloc(AST_BINOP);
									  											$$->binop.operator = '&';
									  											$$->binop.left = $1;
									  											$$->binop.right = $3;
					   														}
					   ;

logical_or_expression : logical_and_expression
					  | logical_or_expression LOGOR logical_and_expression	{ /* Logical OR (||) */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->binop.operator = LOGOR;
						  														$$->binop.left = $1;
						  														$$->binop.right = $3;
					  														}
					  ;

logical_and_expression : bitwise_or_expression
					   | logical_and_expression LOGAND bitwise_or_expression 	{ /* Logical AND (&&) */
																					$$ = astnode_alloc(AST_BINOP);
										  											$$->binop.operator = LOGAND;
										  											$$->binop.left = $1;
										  											$$->binop.right = $3;
					   															}
					   ;

conditional_expression : logical_or_expression
					   | logical_or_expression '?' expression ':' conditional_expression 	{
					   																			$$ = astnode_alloc(AST_TERNARY);
					   																			$$->ternary.cond = $1;
					   																			$$->ternary.if_true = $3;
					   																			$$->ternary.if_false = $5;
					   																		}
					   ;

assignment_expression : conditional_expression
					  | unary_expression assignment_op assignment_expression	{ /* Recognize assignment, treat as binary operation */
					  																$$ = astnode_alloc(AST_ASSIGN);
											   										$$->assign.left = $1;

											   										/* No additional work if just '=' */
											   										if($2 == '=')
											   											$$->assign.right = $3;										
											   										else
												   									{	/* Create binop of RHS */
												   										union astnode *b_op = astnode_alloc(AST_BINOP);
												   										b_op->binop.left = $1;

						  																switch($2)
						  																{						  															
						  																	case PLUSEQ:	b_op->binop.operator = '+'; break;
						  																	case MINUSEQ:	b_op->binop.operator = '-'; break;
						  																	case TIMESEQ:	b_op->binop.operator = '*'; break;
						  																	case DIVEQ:		b_op->binop.operator = '/'; break;
						  																	case MODEQ:		b_op->binop.operator = '%'; break;
						  																	case SHLEQ:		b_op->binop.operator = SHL; break;
						  																	case SHREQ:		b_op->binop.operator = SHR; break;
						  																	case ANDEQ:		b_op->binop.operator = '&'; break;
						  																	case XOREQ:		b_op->binop.operator = '^'; break;
						  																	case OREQ:		b_op->binop.operator = '|'; break;
						  																}

						  																b_op->binop.right = $3;

						  																$$->assign.right = b_op;
						  															}
						  															
					  															}
					  ;

assignment_op : '=' 		{$$ = '=';}
			  | PLUSEQ		{$$ = PLUSEQ;}	
			  | MINUSEQ		{$$ = MINUSEQ;}
			  | TIMESEQ		{$$ = TIMESEQ;}
			  | DIVEQ		{$$ = DIVEQ;}
			  | MODEQ		{$$ = MODEQ;}
			  | SHLEQ		{$$ = SHLEQ;}
			  | SHREQ		{$$ = SHREQ;}
			  | ANDEQ		{$$ = ANDEQ;}
			  | XOREQ		{$$ = XOREQ;}
			  | OREQ		{$$ = OREQ;}
			  ;

expression : assignment_expression					
		   | expression ',' assignment_expression 	{ /* List of expressions in a single line */
		   												$$ = astnode_alloc(AST_BINOP);
		   												$$->binop.operator = ',';
		   												$$->binop.left = $1;
		   												$$->binop.right = $3;		 
		   											}		
		   ;


/* Statements */
	   
statement : expression_statement
		  | labeled_statement
		  | compound_statement
		  | conditional_statement
		  | iterative_statement
		  | switch_statement
		  | break_statement
		  | continue_statement
		  | return_statement
		  | goto_statement
		  | null_statement
		  ;

conditional_statement : if_statement
					  | if_else_statement
					  ;

iterative_statement : do_statement
					| while_statement
					| for_statement
					;

expression_statement : expression ';' 												{	
																						$$ = $1;

																						//$$ = astnode_alloc(AST_EXPR_LIST);
                                                                    					//$$->expr_list.right = $1;
																						//$$->expr_list.next = $1;

                                                                    					//fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
                                                                    					//print_ast($$, 0);
                                                                   						//fprintf(stdout, "\n---------- END LINE %d ----------\n", lineno);
                                                                					}
					 /*| expression_statement expression ';' *//* I ADDED THIS */ 		/*{

                                                                    $$ = astnode_alloc(AST_EXPR_LIST);
                                                                    $$->expr_list.right = $2;
                                                                    fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
                                                                    print_ast($$, 0);
                                                                    fprintf(stdout, "---------- END LINE %d ----------\n", lineno);
	
																					}*/
					 ;

labeled_statement : label ':' statement 		{ /* If a named label is defined, mark it as defined -- need to fix*/
					 								$$ = astnode_alloc(AST_LABELED_ST);
					 								$$->labeled_st.label = $1;
					 								$$->labeled_st.body = $3;
												}
				  ;

label : named_label
	  | case_label
	  | default_label
	  ;

compound_statement : '{' '}' 	{$$ = NULL;}
				   | '{' {curr_scope = symbol_table_alloc(BLOCK_SCOPE, lineno, file, curr_scope);} declaration_or_statement_list '}' 	{ /* Block Scope */
																																			$$ = astnode_alloc(AST_COMPOUND_ST);
																																			$$->compound_st.body = $3;
																																			//ast_dump(curr_scope,$3,NULL);
																																			curr_scope = symbol_table_pop(curr_scope);
				   																														}
				   ;

declaration_or_statement_list : declaration_or_statement
							  | declaration_or_statement_list declaration_or_statement 	{$$ = astnode_append($1, $2, NEXT);}
							  ;

declaration_or_statement : declaration 
						 | statement
						 ;

if_statement : IF '(' expression ')' statement 		{ /* IF Statement */
						 								$$ = astnode_alloc(AST_IF_ST);
						 								$$->if_st.cond = $3;
						 								$$->if_st.if_true = $5;
						 								$$->if_st.next = NULL;

													}
			 ;

if_else_statement : IF '(' expression ')' statement ELSE statement 		{ /* IF-ELSE Statement */
																			$$ = astnode_alloc(AST_IF_ELSE_ST);
																			$$->if_else_st.cond = $3;
																			$$->if_else_st.if_true = $5;
																			$$->if_else_st.next = $7;
																		}
				  ;

while_statement : WHILE '(' expression ')' statement 	{ /* WHILE Statement */
				  											$$ = astnode_alloc(AST_WHILE_ST);
				  											$$->while_st.cond = $3;
				  											$$->while_st.body = $5;

														}
				;

do_statement : DO statement WHILE '(' expression ')' ';' 	{ /* DO-WHILE Statement */
																$$ = astnode_alloc(AST_DO_WHILE_ST);
																$$->do_while_st.cond = $5;
																$$->do_while_st.body = $2;
															}
			 ;

for_statement : FOR for_expressions statement 	{ /* FOR Statement */
			 										$$ = $2;
			 										$$->for_st.body = $3;
												}
			  ;

for_expressions : '(' ';' ';' ')' 											{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = NULL; $$->for_st.cond = NULL; $$->for_st.right = NULL;}
				| '(' ';' ';' expression ')' 								{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = NULL; $$->for_st.cond = NULL; $$->for_st.right = $4;}
				| '(' ';' expression ';' ')' 								{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = NULL; $$->for_st.cond = $3; $$->for_st.right = NULL;}
				| '(' ';' expression ';' expression ')' 					{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = NULL; $$->for_st.cond = $3; $$->for_st.right = $5;}
				| '(' initial_clause ';' ';' ')' 							{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = $2; $$->for_st.cond = NULL; $$->for_st.right = NULL;}			
				| '(' initial_clause ';' ';' expression ')' 				{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = $2; $$->for_st.cond = NULL; $$->for_st.right = $5;}
				| '(' initial_clause ';' expression ';' ')' 				{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = $2; $$->for_st.cond = $4; $$->for_st.right = NULL;}
				| '(' initial_clause ';' expression ';' expression ')' 		{$$ = astnode_alloc(AST_FOR_ST); $$->for_st.left = $2; $$->for_st.cond = $4; $$->for_st.right = $6;}
				;

initial_clause : expression 
			   | declaration 
			   ;

switch_statement : SWITCH '(' expression ')' statement 	{ /* SWITCH Statement */
			   												$$ = astnode_alloc(AST_SWITCH_ST);
			   												$$->switch_st.cond = $3;
			   												$$->switch_st.body = $5;
														}
				 ;

case_label : CASE conditional_expression /*constant_expression */	{ /* CASE Label */
				 							$$ = astnode_alloc(AST_CASE_LABEL);
				 							$$->case_label.expr = $2;
										}
		   ;

default_label : DEFAULT 			{$$ = astnode_alloc(AST_DEF_LABEL);}
			  ;

break_statement : BREAK ';' 		{$$ = astnode_alloc(AST_BREAK_ST);}
				;

continue_statement : CONTINUE ';' 	{$$ = astnode_alloc(AST_CONT_ST);}
				   ;

return_statement : RETURN ';' 				{ /* RETURN NULL */
				   								$$ = astnode_alloc(AST_RETURN_ST);
				   								$$->return_st.ret = NULL;
											}
				 | RETURN expression ';' 	{ /* RETURN something */
												$$ = astnode_alloc(AST_RETURN_ST);
												$$->return_st.ret = $2;
				 							}
				 ;

goto_statement : GOTO named_label ';' 		{ /* GOTO Statement */
				 								$$ = astnode_alloc(AST_GOTO_ST);
				 								$2->named_label.call = 1; 	/* Indicates that this is a "call" to the label, not a definition */
				 								$$->goto_st.label = $2;
											}
			   ;

named_label : IDENT 		{ /* Named Label */
			   					$$ = astnode_alloc(AST_NAMED_LABEL);
			   					$$->named_label.name = yylval.ident.name;
			   					struct symbol *s = symbol_table_get_info(curr_scope, $$->named_label.name, LABEL_NS);
			   					if (s == NULL)
									curr_symbol = symbol_table_insert(curr_scope, $$->ident.name, lineno, file, LABEL_NS, $$, curr_symbol);
								else
									curr_symbol = s;

							}
			;

null_statement : ';' 	{$$ = NULL;}
			   ;


/* Functions */
translation_unit : top_level_declaration
				 | translation_unit top_level_declaration
				 ;

top_level_declaration : declaration
					  | function_definition
					  ;

function_definition : function_def_specifier '{' {curr_scope = symbol_table_alloc(FN_T, lineno, file, curr_scope);} declaration_or_statement_list '}' 		{
																																								
																																								/* Print symbol table for function */
																																								print_sym_tab(curr_scope);
																																								ast_dump(curr_scope, $4, $1->ident.name);

																																								curr_scope = symbol_table_pop(curr_scope);

																																								//$1->fn.body = $4; - older	

																																								/* the below works */
																																								//$1->gen.prev->fn.body = $4;
																																								//ast_dump($4, $1->ident.name);

																																								//printf("Printing table for function:\n");
																																								//print_sym_tab(curr_scope);
																																								
																																							}
																					
					;


function_def_specifier : declarator 											{ /* Reverse in order to get proper order */
																					$$ = astnode_reverse($1, PREV);
																				}
					   | declarator declaration_list 
					   | declaration_specifiers declarator 						{ /* Similar work as in declaration rule */
					   																union astnode *n = $1;

																					/* Walk along node trail */
																					while (n->gen.node_type == AST_STORAGE)
																						n = n->gen.prev;

																					/* Append the list */
																					n = astnode_append(n, $2, PREV);

																					$$ = astnode_reverse(n, PREV);

																					if ($1->gen.node_type == AST_STORAGE)
																					{
																						union astnode *t1 = $$->gen.prev;
																						union astnode *t2 = $1;

																						/* Walk along node trail again */
																						while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																							t2 = t2->gen.prev;

																						t2->gen.prev = t1;
																						$$->gen.prev = $1;
																					}

																					#if 0
																					printf("Now reverse\n");
																					union astnode *l = $$;
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}
												  									#endif

																					union astnode *temp = $$;
												  									while (temp != NULL)
												  									{
												  										if(temp->gen.node_type == AST_FN)
												  										{
												  											temp->fn.ret_value = find_ret_value(temp);
												  											break;
												  										}
												  										else if (temp->gen.node_type == AST_ARRAY)
												  										{
												  											temp->array.type = find_ret_value(temp);
												  										}
												  										temp = temp->gen.prev;
												  									}

												  									//$$ = temp;

												  									union astnode *symbol_node = $$;
											  										union astnode *hak = astnode_alloc(AST_FN);
											  										  							
														  							hak->fn.filename = strdup(file);
														  							hak->fn.lineno = lineno;
														  							hak->fn.name = strdup(curr_symbol->name);
														  							hak->fn.ret_value = $$;
														  							curr_symbol->ast_node = hak;
														  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

														  							/* Check for valid redeclaration */
														  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
														  								/* Do Nothing */;
														  							else
														  							{
														  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
														  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
														  								exit(-1);
														  							}

												  									curr_symbol = curr_symbol->list; 	/* Makes sure that the current symbol refers to the first symbol in the function body */

					   															}
					   | declaration_specifiers declarator declaration_list
					   ;

declaration_list : declaration
				 | declaration_list declaration
				 ;
				
%% 

/* C Stuff */

int main(int argc, char **argv)
{	
	curr_scope = symbol_table_alloc(GLOBAL_SCOPE, 1, file, NULL);
	yyparse();
	print_sym_tab(curr_scope);
	return 0;
}
