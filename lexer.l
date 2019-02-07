 /* Lexical Analyzer */

%option noyywrap
%{	
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lexer.h"	
#include "tokens-manual.h"

char file[256] = "<stdin>";
int state = 0;
int lineno = 1;

void int_info(char *buf, int sign, int type);
void oct_info(char *buf, int sign, int type);
void hex_info(char *buf, int sign, int type);
void real_info(char *buf, int sign, int type);
void add2string(char *buf, char esc);
void print_char(char c);
char* print_kw(int token);
void warn_msg(char *file_name, int line_number, char *msg);
%}
%x CHAR_STATE
%x STRING_STATE
%x ESC_STATE
%x COMMENT_STATE
%x INFO_STATE

DEC	[1-9]+[0-9]*				
OCT	0[0-7]*						
HEX	0[xX][a-fA-F0-9]+			
REAL 	[0-9]*\.[0-9]*				
EXP 	[eE][+-]?{DEC}+				
P 	[pP][+-]?{DEC}+				

%%
 /* File Name */
#					{BEGIN(INFO_STATE);}

<INFO_STATE>^[0-9]+			{lineno = (int)strtol(yytext, (char **)NULL, 10);}
<INFO_STATE>\"(\\.|[^\\\"])*\"		{/* Copy the file name appropriately */
						strncpy(file, yytext + 1, strlen(yytext) - 2); 
						file[strlen(yytext) - 2] = '\0';
					}
<INFO_STATE>.				{/* Ignore other stuff */ ;}
<INFO_STATE>\n 				{BEGIN(INITIAL);}


 /* Ignore Whitespace */
[ \t]+		{;}


 /* Key Words */
"auto"			{return AUTO;}
"break"			{return BREAK;}
"case"			{return CASE;}
"char"			{return CHAR;}
"const"			{return CONST;}
"continue"		{return CONTINUE;}
"default"		{return DEFAULT;}
"do"			{return DO;}
"double"		{return DOUBLE;}
"else"			{return ELSE;}
"enum"			{return ENUM;}
"extern"		{return EXTERN;}
"float"			{return FLOAT;}
"for"			{return FOR;}
"goto"			{return GOTO;}
"if"			{return IF;}
"inline"		{return INLINE;}
"int"			{return INT;}
"long"			{return LONG;}
"register"		{return REGISTER;}
"restrict"		{return RESTRICT;}
"return"		{return RETURN;}
"short"			{return SHORT;}
"signed"		{return SIGNED;}
"sizeof"		{return SIZEOF;}
"static"		{return STATIC;}
"struct"		{return STRUCT;}
"switch"		{return SWITCH;}
"typedef"		{return TYPEDEF;}
"union"			{return UNION;}
"unsigned"		{return UNSIGNED;}
"void"			{return VOID;}
"volatile"		{return VOLATILE;}
"while"			{return WHILE;}
"_Bool"			{return _BOOL;}
"_Complex"		{return _COMPLEX;}
"_Imaginary"		{return _IMAGINARY;}


 /* Identifiers -- Note: Cannot begin with a number */
[a-zA-Z_][a-zA-Z0-9_]*	{yylval.ident.name = strdup(yytext); return IDENT;}


 /* Character Literals */
L?\'					{state = CHARLIT; BEGIN(CHAR_STATE);}

<CHAR_STATE>[^\n\\\']+			{ /* Non-escape Characters */ 
						if (yyleng > 1)
							warn_msg(file, lineno, "Unsupported multibyte character literal truncated to first byte");
						yylval.char_lit = yytext[0]; 
					}
<CHAR_STATE>\n 				{ /* Unexpected newline error */
						fprintf(stderr, "%s: %d: Error: Unexpected newline in char\n", file, lineno);
						exit(-1);
					}
<CHAR_STATE>\\				{ /* Escape Characters */
						BEGIN(ESC_STATE);
					}
<CHAR_STATE>\'				{ /* End of char */
						BEGIN(INITIAL);
						state = 0;
						return CHARLIT;
					}


 /* String Literals */ 
\"					{ /* Initialize string stuff */
						yylval.string.length = 0; 
						state = STRING; 
						BEGIN(STRING_STATE);
					}
<STRING_STATE>[^\n\\\"]*		{ /* Non-escape Characters */
						add2string(yytext, (char)NULL);
					}
<STRING_STATE>\\			{ /* Escape Characters */	
						BEGIN(ESC_STATE);
 					}
<STRING_STATE>\"			{ /* End of string */
						BEGIN(INITIAL);
						state = 0;
						return STRING;
					}


 /* Escape Codes */
<ESC_STATE>[0abfnrtv'"\\?]	{ /* Deal with the Escape Characters */								
					char esc_char;
					switch(yytext[0])
					{
						case '0': 	esc_char = '\0'; break;
						case 'a': 	esc_char = '\a'; break;
						case 'b': 	esc_char = '\b'; break;
						case 'f': 	esc_char = '\f'; break;
						case 'n': 	esc_char = '\n'; break;
						case 'r': 	esc_char = '\r'; break;
						case 't': 	esc_char = '\t'; break;
						case 'v': 	esc_char = '\v'; break;
						case '\'': 	esc_char = '\''; break;
						case '"': 	esc_char = '\"'; break;
						case '\\': 	esc_char = '\\'; break;
						case '?':	esc_char = '\?'; break;
					}
					switch(state)
					{
						case CHARLIT:	yylval.char_lit = esc_char; 
								BEGIN(CHAR_STATE); 
								break;

						case STRING:	add2string((char *)NULL, esc_char);
								BEGIN(STRING_STATE); 	
					}
				}
<ESC_STATE>[0-7]{1,3}		{ /* Octal Escapes */
					int oct_num;
					sscanf(yytext, "%o", &oct_num);
					if (oct_num > 255)
					{
						fprintf(stderr, "%s: %d: Warning: Octal escape sequence \\%s out of range\n", file, lineno, yytext);
						oct_num = 255;
					}
					char oct_char = (char)oct_num;
					switch(state)
					{
						case CHARLIT:	yylval.char_lit = oct_char;
								BEGIN(CHAR_STATE);
								break;

						case STRING:	add2string((char *)NULL, oct_char);
								BEGIN(STRING_STATE);
					}

				}
<ESC_STATE>[xX][0-9a-fA-F]+	{ /* Hex Escapes */
					int hex_num;
					sscanf(yytext + 1, "%x", &hex_num);
					if (hex_num > 255)
					{
						fprintf(stderr, "%s: %d: Warning: Hex escape sequence \\%s out of range\n", file, lineno, yytext);
						hex_num = 255;
					}
					char hex_char = (char)hex_num;
					switch(state)
					{
						case CHARLIT:	yylval.char_lit = hex_char;
								BEGIN(CHAR_STATE);
								break;

						case STRING:	add2string((char *)NULL, hex_char);
								BEGIN(STRING_STATE);
					}
					
				}


 /* Operators */
[-~!%^&*+=\|<.>/?]	{return yytext[0];}
"->"         		{return INDSEL;}
"++"         		{return PLUSPLUS;}
"--"         		{return MINUSMINUS;}
"<<"         		{return SHL;}
">>"         		{return SHR;}
"<="         		{return LTEQ;}
">="         		{return GTEQ;}
"=="         		{return EQEQ;}
"!="         		{return NOTEQ;}
"&&"         		{return LOGAND;}
"||"         		{return LOGOR;}
"..."			{return ELLIPSIS;}
"*="         		{return TIMESEQ;}
"/="         		{return DIVEQ;}
"%="         		{return MODEQ;}
"+="         		{return PLUSEQ;}
"-="         		{return MINUSEQ;}
"<<="        		{return SHLEQ;}
">>="        		{return SHREQ;}
"&="         		{return ANDEQ;}
"|="         		{return OREQ;}
"^="         		{return XOREQ;}


 /* Punctuation */
[](){}[;:,]		{return yytext[0];}


 /* Numberic Constants */ 
{DEC}				{ /* Deal with simple integers */			
					int_info(yytext, SIGNED_T, INT_T);
					return NUMBER;
				}
{DEC}"U"			{ /* Unsigned integers */
					yytext[yyleng - 1] = '\0';
					int_info(yytext, UNSIGNED_T, INT_T);
					return NUMBER;
				}
{DEC}"L"			{ /* Signed long */
					yytext[yyleng - 1] = '\0';
					int_info(yytext, SIGNED_T, LONG_T);
					return NUMBER;
				}
{DEC}"LL"			{ /* Signed long long */
					yytext[yyleng - 2] = '\0';
					int_info(yytext, SIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{DEC}"LLU"			{ /* Unsigned long long */
					yytext[yyleng - 3] = '\0';
					int_info(yytext, UNSIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{OCT}				{ /* Deal with simple octals */
					oct_info(yytext, SIGNED_T, INT_T);
					return NUMBER;
				}
{OCT}"U"			{ /* Unsigned octal */
					yytext[yyleng - 1] = '\0';
					oct_info(yytext, UNSIGNED_T, INT_T);
					return NUMBER;
				}
{OCT}"L"			{ /* Signed long octal */
					yytext[yyleng - 1] = '\0';
					oct_info(yytext, SIGNED_T, LONG_T);
					return NUMBER;
				}
{OCT}"LL"			{ /* Signed long long octal */
					yytext[yyleng - 2] = '\0';
					oct_info(yytext, SIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{OCT}"LLU"			{ /* Unsigned long long octal */
					yytext[yyleng - 3] = '\0';
					oct_info(yytext, UNSIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{HEX}				{ /* Deal with simple hexadecimals */
					hex_info(yytext, SIGNED_T, INT_T);
					return NUMBER;
				}
{HEX}"U"			{ /* Unsigned hex */
					yytext[yyleng - 1] = '\0';
					hex_info(yytext, UNSIGNED_T, INT_T);
					return NUMBER;
				}
{HEX}"L"			{ /* Signed long hex */
					yytext[yyleng - 1] = '\0';
					hex_info(yytext, SIGNED_T, LONG_T);
					return NUMBER;
				}
{HEX}"LL"			{ /* Signed long long hex */
					yytext[yyleng - 2] = '\0';
					hex_info(yytext, SIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{HEX}"LLU"			{ /* Unsigned long long hex */
					yytext[yyleng - 3] = '\0';
					hex_info(yytext, SIGNED_T, LONGLONG_T);
					return NUMBER;
				}
{HEX}{P}			{ /* "p" form hexadecimal floats */
					real_info(yytext, SIGNED_T, DOUBLE_T);				
					return NUMBER;
				}	
{REAL}				{ /* Dealing with simple doubles */
					real_info(yytext, SIGNED_T, DOUBLE_T);
					return NUMBER;
				}
{REAL}"L"			{ /* Signed long double */
					yytext[yyleng - 1] = '\0';
					real_info(yytext, SIGNED_T, LONGDOUBLE_T);
					return NUMBER;
				}
[0]?{DEC}+{EXP}[f]?		{ /* Dealing with exponents */
					if(yytext[yyleng - 1] == 'f')
						real_info(yytext, SIGNED_T, FLOAT_T);
					else
						real_info(yytext, SIGNED_T, DOUBLE_T);
					return NUMBER;
				}
{REAL}"f"			{ /* Explicit float type */
					yytext[yyleng - 1] = '\0';
					real_info(yytext, SIGNED_T, FLOAT_T);
					return NUMBER;
				}

 /* Ignore Comments */
\/\*            		{BEGIN(COMMENT_STATE);}
<COMMENT_STATE>.|\n    		{ /* Ignore everything */ ;}
<COMMENT_STATE>\*\/   		{BEGIN(INITIAL);}
\/\/.*\n        		{ /* Ignore single-line comments */  ;}

 /* Update line numbers */
\n 				{lineno++;}

 /* Throw error if no appropriate token is found */
.				{fprintf(stderr, "Error: Undefined token: %s\n", yytext); exit(-1);}

%%

void int_info(char *buf, int sign, int type)
{
	yylval.num.int_value = strtoull(buf, (char **)NULL, 10);
	yylval.num.sign = sign;	
	yylval.num.type = type;
}

void oct_info(char *buf, int sign, int type)
{
	sscanf(buf, "%llo", &yylval.num.int_value);
	yylval.num.sign = sign;
	yylval.num.type = type;	
}

void hex_info(char *buf, int sign, int type)
{
	sscanf(buf, "%llx", &yylval.num.int_value);
	yylval.num.sign = sign;
	yylval.num.type = type;	
}

void real_info(char *buf, int sign, int type)
{
	sscanf(buf, "%Lf", &yylval.num.float_value);
	yylval.num.sign = sign;
	yylval.num.type = type;	
}

void add2string(char *buf, char esc)
{
	if(buf == (char *)NULL)
	{
		yylval.string.word[yylval.string.length] = esc;
		yylval.string.length += 1;
	}
	else
	{	
		int string_length;

		if(strlen(buf) > 4096)
		{
			warn_msg(file, lineno, "Long string truncated to first 4k bytes");
			string_length = 4096;
		}
		else
			string_length = strlen(buf); 

		for(int i = 0; i < string_length; i++)
			yylval.string.word[yylval.string.length + i] = buf[i];

		yylval.string.length += string_length;
	}
	
}

void print_char(char c)
{
	switch(c)
	{
		case '\0':	fprintf(stdout, "\\0"); break;
		case '\a': 	fprintf(stdout, "\\a"); break; 
		case '\b': 	fprintf(stdout, "\\b"); break;
		case '\f': 	fprintf(stdout, "\\f"); break;
		case '\n': 	fprintf(stdout, "\\n"); break;
		case '\r': 	fprintf(stdout, "\\r"); break;
		case '\t': 	fprintf(stdout, "\\t"); break;
		case '\v': 	fprintf(stdout, "\\v"); break;
		case '\'': 	fprintf(stdout, "\\\'"); break;
		case '\"': 	fprintf(stdout, "\\\""); break;
		case '\\': 	fprintf(stdout, "\\\\"); break;
		default:	if (c > 127 || c < 32)
					fprintf(stdout, "\\%03o", (unsigned char)c);
				else
					fprintf(stdout, "%c", c);
				break;
	}
}

char* print_kw(int token)
{
	switch(token)
	{
		case INDSEL:		return "INDSEL"; 
		case PLUSPLUS:		return "PLUSPLUS";
		case MINUSMINUS:	return "MINUSMINUS";
		case SHL:		return "SHL";
		case SHR:		return "SHR";
		case LTEQ:		return "LTEQ";
		case GTEQ:		return "GTEQ";
		case EQEQ:		return "EQEQ";
		case NOTEQ:		return "NOTEQ";
		case LOGAND:		return "LOGAND";
		case LOGOR:		return "LOGOR";
		case ELLIPSIS:		return "ELLIPSIS";
		case TIMESEQ:		return "TIMESEQ";
		case DIVEQ:		return "DIVEQ";
		case MODEQ:		return "MODEQ";
		case PLUSEQ:		return "PLUSEQ";
		case MINUSEQ:		return "MINUSEQ";
		case SHLEQ:		return "SHLEQ";
		case SHREQ:		return "SHREQ";
		case ANDEQ:		return "ANDEQ";
		case OREQ:		return "OREQ";
		case XOREQ:		return "XOREQ";
		case AUTO:		return "AUTO";
		case BREAK:		return "BREAK";
		case CASE:		return "CASE";
		case CHAR:		return "CHAR";
		case CONST:		return "CONST";
		case CONTINUE:		return "CONTINUE";
		case DEFAULT:		return "DEFAULT";
		case DO:		return "DO";
		case DOUBLE:		return "DOUBLE";
		case ELSE:		return "ELSE";
		case ENUM:		return "ENUM";
		case EXTERN:		return "EXTERN";
		case FLOAT:		return "FLOAT";
		case FOR:		return "FOR";
		case GOTO:		return "GOTO";
		case IF:		return "IF";
		case INLINE:		return "INLINE";
		case INT:		return "INT";
		case LONG:		return "LONG";
		case REGISTER:		return "REGISTER";
		case RESTRICT:		return "RESTRICT";
		case RETURN:		return "RETURN";
		case SHORT:		return "SHORT";
		case SIGNED:		return "SIGNED";
		case SIZEOF:		return "SIZEOF";
		case STATIC:		return "STATIC";
		case STRUCT:		return "STRUCT";
		case SWITCH:		return "SWITCH";
		case TYPEDEF:		return "TYPEDEF";
		case UNION:		return "UNION";
		case UNSIGNED:		return "UNSIGNED";
		case VOID:		return "VOID";
		case VOLATILE:		return "VOLATILE";
		case WHILE:		return "WHILE";
		case _BOOL:		return "_BOOL";
		case _COMPLEX:		return "_COMPLEX";
		case _IMAGINARY:	return "_IMAGINARY";
		default:		return "ERROR"; 
	}
}

void warn_msg(char *file_name, int line_number, char *msg)
{
	fprintf(stderr, "%s: %d: Warning: %s\n", file_name, line_number, msg);
}


 /* Test program */
int main(int argc, char **argv)
{
	int t;
	while ( (t = yylex()) )
	{
		if(t < 255)
			fprintf(stdout, "%s\t %d\t %c\n", file, lineno, (char)t);
		else
		{
			switch(t)
			{
				case IDENT:	fprintf(stdout, "%s\t %d\t IDENT\t %s\n", file, lineno, yylval.ident.name);
						break;

				case CHARLIT:	fprintf(stdout, "%s\t %d\t CHARLIT\t ", file, lineno); 
						print_char(yylval.char_lit);
						fprintf(stdout, "\n");
						break;

				case STRING:	fprintf(stdout, "%s\t %d\t STRING\t ", file, lineno);
						for(int i = 0; i < yylval.string.length; i++)
							print_char(yylval.string.word[i]);
						fprintf(stdout, "\n");
						break;

				case NUMBER:	fprintf(stdout, "%s\t %d\t NUMBER\t ", file, lineno);
								
						if(yylval.num.type == INT_T || yylval.num.type == LONG_T || yylval.num.type == LONGLONG_T)
							fprintf(stdout, "INTEGER\t %lld\t", yylval.num.int_value);
						else
							fprintf(stdout, "REAL\t %Lg\t", yylval.num.float_value);
								
						if(yylval.num.sign == UNSIGNED_T)
							fprintf(stdout, "UNSIGNED,");

						switch(yylval.num.type)
						{
							case INT_T:		fprintf(stdout, "INT\n"); break;
							case LONG_T:		fprintf(stdout, "LONG\n"); break;
							case LONGLONG_T: 	fprintf(stdout, "LONGLONG\n"); break;
							case DOUBLE_T: 		fprintf(stdout, "DOUBLE\n"); break;
							case LONGDOUBLE_T: 	fprintf(stdout, "LONGDOUBLE\n"); break;
							case FLOAT_T: 		fprintf(stdout, "FLOAT\n"); break;
							default: 		break;
						}
								
						break;

				default:	fprintf(stdout, "%s\t %d\t %s\n", file, lineno, print_kw(t));
						break;
			}
		}

	}

	return 0;

}
