%debug
%{ /* Parser */
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char* msg) {fprintf(stderr, "%s\n", msg);}
int yylex();
extern int lineno;
extern char file[256];
char* print_kw(int token);

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

		struct astnode *astnode_p;

}

%token <num.int_value> IDENT CHARLIT STRING NUMBER INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR ELLIPSIS
%token <num.int_value> TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ ANDEQ OREQ XOREQ AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO
%token <num.int_value> DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC
%token <num.int_value> STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <astnode_p> primary_expression constant_expression parenthesized_expression postfix_expression subscript_expression
%type <astnode_p> component_selection_expression function_call expression_list postincrement_expression postdecrement_expression 
%type <astnode_p> /*compound_literal*/ cast_expression unary_expression sizeof_expression unary_minus_expression unary_plus_expression 
%type <astnode_p> logical_negation_expression bitwise_negation_expression address_expression 
%type <astnode_p> indirection_expression preincrement_expression predecrement_expression multiplicative_expression additive_expression 
%type <astnode_p> shift_expression relational_expression equality_expression bitwise_or_expression bitwise_xor_expression 
%type <astnode_p> bitwise_and_expression logical_or_expression logical_and_expression conditional_expression assignment_expression expression
%type <num.int_value> assignment_op
%type <astnode_p> expression_statement

%start expression_statement

%%
/* TODO - fix expression list */

 /* Grammars */
 expression_statement : expression ';'                          {
                                                                    $$ = astnode_alloc(AST_TOP_EXPR);
                                                                    $$->u.top_expr.left = $1;
                                                                    fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
                                                                    print_ast($$, 0);
                                                                    fprintf(stdout, "\n---------- END LINE %d ----------\n", lineno);
                                                                }
					  | expression_statement expression ';'     { /* More than one expression */	
                                                                    $$ = astnode_alloc(AST_TOP_EXPR);
                                                                    $$->u.top_expr.left = $2;
                                                                    fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
                                                                    print_ast($$, 0);
                                                                    fprintf(stdout, "---------- END LINE %d ----------\n", lineno);
                                                                }
                      ;

 /* Expressions */
primary_expression  : IDENT			{ /* Identifiers */
                                    $$ = astnode_alloc(AST_IDENT);
                                    $$->u.ident.name = yylval.ident.name;
                                }	
			   		        | constant_expression			
			   		        | parenthesized_expression	
			   		        ;

constant_expression : NUMBER 	{ /* Various Numbers */
			   						$$ = astnode_alloc(AST_NUMBER);
			   						$$->u.num.int_value = yylval.num.int_value;
			   						$$->u.num.float_value = yylval.num.float_value;
			   						$$->u.num.sign = yylval.num.sign;
			   						$$->u.num.type = yylval.num.type;
								}
					| CHARLIT 	{ /* Character Literals */
									$$ = astnode_alloc(AST_CHARLIT);
									$$->u.charlit.c = yylval.char_lit;
								}
					| STRING 	{ /* Strings */
									$$ = astnode_alloc(AST_STRING);
									strncpy($$->u.string.word, yylval.string.word, yylval.string.length);
									$$->u.string.length = yylval.string.length;
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
				   /*| compound_literal*/
				   ;

subscript_expression : postfix_expression '[' expression ']' 	{ /* Convert a[b] to *(a + b) */
				   													$$ = astnode_alloc(AST_UNOP);
				   													$$->u.unop.operator = '*';
				   													struct astnode *next = astnode_alloc(AST_BINOP);
				   													$$->u.unop.left = next;
				   													next->u.binop.operator = '+';
				   													next->u.binop.left = $1;
				   													next->u.binop.right = $3; 
																}
					 ;

component_selection_expression : postfix_expression '.' IDENT 		{ /* Direct Component Selection */	
					 													$$ = astnode_alloc(AST_COMP_SELECT);
					 													$$->u.comp_select.left = $1;
					 													$$->u.comp_select.right = astnode_alloc(AST_IDENT);
																		$$->u.comp_select.right->u.ident.name = yylval.ident.name;
																	}	
							   | postfix_expression INDSEL IDENT 	{ /* Indirect Component Selection -- Convert to Direct */
																		$$ = astnode_alloc(AST_COMP_SELECT);
																		$$->u.comp_select.right = astnode_alloc(AST_IDENT);
																		$$->u.comp_select.right->u.ident.name = yylval.ident.name;

																		struct astnode *p = astnode_alloc(AST_UNOP);
																		p->u.unop.operator = '*';
																		p->u.unop.left = $1;

																		$$->u.comp_select.left = p;
							   										}
							   ;

function_call : postfix_expression '(' ')'						{ /* Function with no arguments */
																	$$ = astnode_alloc(AST_FNCALL);
																	$$->u.fncall.left = $1;
																	$$->u.fncall.right = NULL;
																}
			  | postfix_expression '(' expression_list ')'		{ /* Function with arguments */
			  														$$ = astnode_alloc(AST_FNCALL);
																	$$->u.fncall.left = $1;
																	$$->u.fncall.right = $3;
			  													}
			  ;

expression_list : assignment_expression
				| expression_list ',' assignment_expression		{ /* List of Expressions */
																	$$ = astnode_alloc(AST_EXPR_LIST);
																	$$->u.expr_list.left = $1;
																	$$->u.expr_list.right = $3;  
																}
				;

postincrement_expression : postfix_expression PLUSPLUS		{ /* a++ */
																$$ = astnode_alloc(AST_UNOP);
																$$->u.unop.operator = PLUSPLUS;
																$$->u.unop.left = $1;
															}
						 ;

postdecrement_expression : postfix_expression MINUSMINUS	{ /* a-- */
																$$ = astnode_alloc(AST_UNOP);
																$$->u.unop.operator = MINUSMINUS;
																$$->u.unop.left = $1;
															}
						 ;
/* Fix later
compound_literal : '(' type_name ')' '{' initializer_list '}'		{$$ = NULL;}
				 | '(' type_name ')' '{' initializer_list ',' '}'	{$$ = NULL;}
				 ;
*/
cast_expression : unary_expression
				/*| '(' type_name ')' cast_expression 	{$$ = NULL;}*/
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

sizeof_expression : /* SIZEOF '(' type_name ')'		{  sizeof a type -- Fix later 
														  $$ = astnode_alloc(AST_SIZEOF);
														$$->u.size_of.left = $3; 
        		 										$$ = NULL;
													} 
				  |*/ SIZEOF unary_expression 		{ /* sizeof a unary expression */
				  										$$ = astnode_alloc(AST_SIZEOF);
				  										$$->u.size_of.left = $2;
				  									}
				  ;

unary_minus_expression : '-' cast_expression 		{ /* Unary Minus */
				  										$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '-';
				  										$$->u.unop.left = $2;
													}
					   ;

unary_plus_expression  : '+' cast_expression 		{ /* Unary Plus */
					   									$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '+';
				  										$$->u.unop.left = $2;
													}
					   ;

logical_negation_expression : '!' cast_expression 	{ /* Unary Negation (Logical) */
					   									$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '!';
				  										$$->u.unop.left = $2;
													}		
							;

bitwise_negation_expression : '~' cast_expression 	{ /* Unary Negation (Bitwise) */
														$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '~';
				  										$$->u.unop.left = $2;
													}	 
							;

address_expression : '&' cast_expression 			{ /* Unary Address */
														$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '&';
				  										$$->u.unop.left = $2;
													}
				   ;

indirection_expression : '*' cast_expression 		{ /* Unary Indirection */
				   										$$ = astnode_alloc(AST_UNOP);
				  										$$->u.unop.operator = '*';
				  										$$->u.unop.left = $2;
													}
					   ;

preincrement_expression : PLUSPLUS unary_expression 	{ /* Convert ++a to a=a+1 */
					   										$$ = astnode_alloc(AST_ASSIGN);
					   										$$->u.assign.left = $2;

					   										/* Create binop of RHS */
					   										struct astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->u.binop.operator = '+';
					   										b_op->u.binop.left = $2;

					   										/* Create the constant 1 */
					   										struct astnode *one = astnode_alloc(AST_NUMBER);
					   										one->u.num.type = INT_T;
					   										one->u.num.int_value = 1;

					   										b_op->u.binop.right = one;
					   										$$->u.assign.right = b_op;
														}
						;

predecrement_expression : MINUSMINUS unary_expression 	{ /* Convert --a to a=a-1 */
															$$ = astnode_alloc(AST_ASSIGN);
					   										$$->u.assign.left = $2;

					   										/* Create binop of RHS */
					   										struct astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->u.binop.operator = '-';
					   										b_op->u.binop.left = $2;

					   										/* Create the constant 1 */
					   										struct astnode *one = astnode_alloc(AST_NUMBER);
					   										one->u.num.type = INT_T;
					   										one->u.num.int_value = 1;

					   										b_op->u.binop.right = one;
					   										$$->u.assign.right = b_op;
														}
						;

multiplicative_expression : cast_expression
						  | multiplicative_expression '*' cast_expression 	{ /* Multiplication */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = '*';
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
						  													}
						  | multiplicative_expression '/' cast_expression 	{ /* Division */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = '/';
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
																			}
						  | multiplicative_expression '%' cast_expression 	{ /* Modulo */
						  														$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = '%';
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
						  													}
						  ;

additive_expression : multiplicative_expression
					| additive_expression '+' multiplicative_expression		{ /* Addition */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = '+';
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
																			}
					| additive_expression '-' multiplicative_expression		{ /* Subtraction */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = '-';
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
																			}
					;

shift_expression : additive_expression
				 | shift_expression SHL additive_expression 	{ /* Shift Left */
				 													$$ = astnode_alloc(AST_BINOP);
						  											$$->u.binop.operator = SHL;
						  											$$->u.binop.left = $1;
						  											$$->u.binop.right = $3;
				 												}
				 | shift_expression SHR additive_expression		{ /* Shift Right */
				 													$$ = astnode_alloc(AST_BINOP);
						  											$$->u.binop.operator = SHR;
						  											$$->u.binop.left = $1;
						  											$$->u.binop.right = $3;
				 												}
				 ;

relational_expression : shift_expression
					  | relational_expression '<' shift_expression		{ /* Less Than */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = '<';
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
					  													}
					  | relational_expression LTEQ shift_expression		{ /* Less Than or Equal To */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = LTEQ;
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
					  													}
					  | relational_expression '>' shift_expression		{ /* Greater Than */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = '>';
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
					  													}
					  | relational_expression GTEQ shift_expression		{ /* Greater Than or Equal To */
					  														$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = GTEQ;
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
					  													}
					  ;

equality_expression : relational_expression
					| equality_expression EQEQ relational_expression	{ /* == */
																			$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = EQEQ;
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
																		}
					| equality_expression NOTEQ relational_expression	{ /* != */
																			$$ = astnode_alloc(AST_BINOP);
								  											$$->u.binop.operator = NOTEQ;
								  											$$->u.binop.left = $1;
								  											$$->u.binop.right = $3;
																		}
					;

bitwise_or_expression : bitwise_xor_expression 
					  | bitwise_or_expression '|' bitwise_xor_expression	{ /* Bitwise OR */
																				$$ = astnode_alloc(AST_BINOP);
									  											$$->u.binop.operator = '|';
									  											$$->u.binop.left = $1;
									  											$$->u.binop.right = $3;
					  														}
					  ;

bitwise_xor_expression : bitwise_and_expression
					   | bitwise_xor_expression '^' bitwise_and_expression	{ /* Bitwise XOR */
					   															$$ = astnode_alloc(AST_BINOP);
									  											$$->u.binop.operator = '^';
									  											$$->u.binop.left = $1;
									  											$$->u.binop.right = $3;	
					   														}
					   ;

bitwise_and_expression : equality_expression
					   | bitwise_and_expression '&' equality_expression		{ /* Bitwise AND */
					   															$$ = astnode_alloc(AST_BINOP);
									  											$$->u.binop.operator = '&';
									  											$$->u.binop.left = $1;
									  											$$->u.binop.right = $3;
					   														}
					   ;

logical_or_expression : logical_and_expression
					  | logical_or_expression LOGOR logical_and_expression	{ /* Logical OR (||) */
																				$$ = astnode_alloc(AST_BINOP);
						  														$$->u.binop.operator = LOGOR;
						  														$$->u.binop.left = $1;
						  														$$->u.binop.right = $3;
					  														}
					  ;

logical_and_expression : bitwise_or_expression
					   | logical_and_expression LOGAND bitwise_or_expression 	{ /* Logical AND (&&) */
																					$$ = astnode_alloc(AST_BINOP);
										  											$$->u.binop.operator = LOGAND;
										  											$$->u.binop.left = $1;
										  											$$->u.binop.right = $3;
					   															}
					   ;

conditional_expression : logical_or_expression
					   | logical_or_expression '?' expression ':' conditional_expression 	{
					   																			$$ = astnode_alloc(AST_IF_ELSE);
					   																			$$->u.if_else.cond = $1;
					   																			$$->u.if_else.if_true = $3;
					   																			$$->u.if_else.if_false = $5;
					   																		}
					   ;

assignment_expression : conditional_expression
					  | unary_expression assignment_op assignment_expression	{ /* Recognize assignment, treat as binary operation */
					  																$$ = astnode_alloc(AST_ASSIGN);
											   										$$->u.assign.left = $1;

											   										/* No additional work if just '=' */
											   										if($2 == '=')
											   											$$->u.assign.right = $3;										
											   										else
												   									{	/* Create binop of RHS */
												   										struct astnode *b_op = astnode_alloc(AST_BINOP);
												   										b_op->u.binop.left = $1;

						  																switch($2)
						  																{						  															
						  																	case PLUSEQ:	b_op->u.binop.operator = '+'; break;
						  																	case MINUSEQ:	b_op->u.binop.operator = '-'; break;
						  																	case TIMESEQ:	b_op->u.binop.operator = '*'; break;
						  																	case DIVEQ:		b_op->u.binop.operator = '/'; break;
						  																	case MODEQ:		b_op->u.binop.operator = '%'; break;
						  																	case SHLEQ:		b_op->u.binop.operator = SHL; break;
						  																	case SHREQ:		b_op->u.binop.operator = SHR; break;
						  																	case ANDEQ:		b_op->u.binop.operator = '&'; break;
						  																	case XOREQ:		b_op->u.binop.operator = '^'; break;
						  																	case OREQ:		b_op->u.binop.operator = '|'; break;
						  																}

						  																b_op->u.binop.right = $3;

						  																$$->u.assign.right = b_op;
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
		   												$$ = astnode_alloc(AST_EXPR_LIST);
		   												$$->u.expr_list.left = $1;
		   												$$->u.expr_list.right = $3;		 
		   											}		
		   ;

				
%% 

/* C Stuff */

int main(int argc, char **argv)
{	
	yyparse();
	return 0;
}
