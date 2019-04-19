/* Lexical Analyzer Header File */

#ifndef __LEXER_H
#define __LEXER_H

enum num_signs {UNSIGNED_T = 0, SIGNED_T = 1};
enum num_types {INT_T = 0, LONG_T, LONGLONG_T, DOUBLE_T, LONGDOUBLE_T, FLOAT_T};

/* Various structs for tokens */
struct identifier
{
	char *name;

} ;

struct string_literal
{
	char word[4096];
	char print_word[4096];
	int length;

} ;

struct number
{
	unsigned long long int_value;
	long double float_value;
	int sign;
	int type;
} ;


/* Definition of yylval union */
typedef union
{
	struct identifier ident;
	struct string_literal string;
	struct number num;
	char char_lit;
	char *kw;
} YYSTYPE;

YYSTYPE yylval;






#endif
