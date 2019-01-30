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
void warn_msg(char *file_name, int line_number, char *msg);
%}
%x CHAR_STATE
%x STRING_STATE
%x ESC_STATE
%x COMMENT_STATE
%x INFO_STATE

DEC		[1-9]+[0-9]*				
OCT		0[0-7]*						
HEX		0[xX][a-fA-F0-9]+			
REAL 	[0-9]*\.[0-9]*				
EXP 	[eE][+-]?{DEC}+				
P 		[pP][+-]?{DEC}+				

%%
 /* File Name */
#									{BEGIN(INFO_STATE);}

<INFO_STATE>^[0-9]+					{lineno = (int)strtol(yytext, (char **)NULL, 10);}
<INFO_STATE>\"(\\.|[^\\\"])*\"		{/* Copy the file name appropriately */
										strncpy(file, yytext + 1, strlen(yytext) - 2); 
										file[strlen(yytext) - 2] = '\0';
									}
<INFO_STATE>.						{/* Ignore other stuff */ ;}
<INFO_STATE>\n 						{BEGIN(INITIAL);}


 /* Ignore Whitespace */
[ \t]+		{;}


 /* Key Words */
"auto"			{yylval.kw = "AUTO"; return AUTO;}
"break"			{yylval.kw = "BREAK"; return BREAK;}
"case"			{yylval.kw = "CASE"; return CASE;}
"char"			{yylval.kw = "CHAR"; return CHAR;}
"const"			{yylval.kw = "CONST"; return CONST;}
"continue"		{yylval.kw = "CONTINUE"; return CONTINUE;}
"default"		{yylval.kw = "DEFAULT"; return DEFAULT;}
"do"			{yylval.kw = "DO"; return DO;}
"double"		{yylval.kw = "DOUBLE"; return DOUBLE;}
"else"			{yylval.kw = "ELSE"; return ELSE;}
"enum"			{yylval.kw = "ENUM"; return ENUM;}
"extern"		{yylval.kw = "EXTERN"; return EXTERN;}
"float"			{yylval.kw = "FLOAT"; return FLOAT;}
"for"			{yylval.kw = "FOR"; return FOR;}
"goto"			{yylval.kw = "GOTO"; return GOTO;}
"if"			{yylval.kw = "IF"; return IF;}
"inline"		{yylval.kw = "INLINE"; return INLINE;}
"int"			{yylval.kw = "INT"; return INT;}
"long"			{yylval.kw = "LONG"; return LONG;}
"register"		{yylval.kw = "REGISTER"; return REGISTER;}
"restrict"		{yylval.kw = "RESTRICT"; return RESTRICT;}
"return"		{yylval.kw = "RETURN"; return RETURN;}
"short"			{yylval.kw = "SHORT"; return SHORT;}
"signed"		{yylval.kw = "SIGNED"; return SIGNED;}
"sizeof"		{yylval.kw = "SIZEOF"; return SIZEOF;}
"static"		{yylval.kw = "STATIC"; return STATIC;}
"struct"		{yylval.kw = "STRUCT"; return STRUCT;}
"switch"		{yylval.kw = "SWITCH"; return SWITCH;}
"typedef"		{yylval.kw = "TYPEDEF"; return TYPEDEF;}
"union"			{yylval.kw = "UNION"; return UNION;}
"unsigned"		{yylval.kw = "UNSIGNED"; return UNSIGNED;}
"void"			{yylval.kw = "VOID"; return VOID;}
"volatile"		{yylval.kw = "VOLATILE"; return VOLATILE;}
"while"			{yylval.kw = "WHILE"; return WHILE;}
"_Bool"			{yylval.kw = "_BOOL"; return _BOOL;}
"_Complex"		{yylval.kw = "_COMPLEX"; return _COMPLEX;}
"_Imaginary"	{yylval.kw = "_IMAGINARY"; return _IMAGINARY;}


 /* Identifiers -- Note: Cannot begin with a number */
[a-zA-Z_][a-zA-Z0-9_]*	{yylval.ident.name = strdup(yytext); return IDENT;}


 /* Character Literals */
L?\'					{state = CHARLIT; BEGIN(CHAR_STATE);}

<CHAR_STATE>[^\n\\\']+	{	/* Non-escape Characters */ 
							if (yyleng > 1)
								warn_msg(file, lineno, "Unsupported multibyte character literal truncated to first byte");
							yylval.char_lit = yytext[0]; 
						}
<CHAR_STATE>\n 			{	/* Unexpected newline error */
							fprintf(stderr, "%s: %d: Error: Unexpected newline in char\n", file, lineno);
							exit(-1);
						}
<CHAR_STATE>\\			{	/* Escape Characters */
							BEGIN(ESC_STATE);
						}
<CHAR_STATE>\'			{	/* End of char */
							BEGIN(INITIAL);
							state = 0;
							return CHARLIT;
						}


 /* String Literals */ 
\"							{	/* Initialize string stuff */
								yylval.string.length = 0; 
								//yylval.string.word[0] = '\0'; 
								state = STRING; 
								BEGIN(STRING_STATE);
							}
<STRING_STATE>[^\n\\\"]*	{	/* Non-escape Characters */
								add2string(yytext, (char)NULL);
							}
<STRING_STATE>\\			{	/* Escape Characters */	
								BEGIN(ESC_STATE);
 							}
<STRING_STATE>\"			{	/* End of string */
								BEGIN(INITIAL);
								state = 0;
								return STRING;
							}


 /* Escape Codes */
<ESC_STATE>[0abfnrtv'"\\?]	{	/* Deal with the Escape Characters */
								
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
<ESC_STATE>[0-7]{1,3}		{	/* Octal Escapes */
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
<ESC_STATE>[xX][0-9a-fA-F]+		{	/* Hex Escapes */
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
"->"         		{yylval.kw = "INDSEL"; return INDSEL;}
"++"         		{yylval.kw = "PLUSPLUS"; return PLUSPLUS;}
"--"         		{yylval.kw = "MINUSMINUS"; return MINUSMINUS;}
"<<"         		{yylval.kw = "SHL"; return SHL;}
">>"         		{yylval.kw = "SHR"; return SHR;}
"<="         		{yylval.kw = "LTEQ"; return LTEQ;}
">="         		{yylval.kw = "GTEQ"; return GTEQ;}
"=="         		{yylval.kw = "EQEQ"; return EQEQ;}
"!="         		{yylval.kw = "NOTEQ"; return NOTEQ;}
"&&"         		{yylval.kw = "LOGAND"; return LOGAND;}
"||"         		{yylval.kw = "LOGOR"; return LOGOR;}
"..."				{yylval.kw = "ELLIPSIS"; return ELLIPSIS;}
"*="         		{yylval.kw = "TIMESEQ"; return TIMESEQ;}
"/="         		{yylval.kw = "DIVEQ"; return DIVEQ;}
"%="         		{yylval.kw = "MODEQ"; return MODEQ;}
"+="         		{yylval.kw = "PLUSEQ"; return PLUSEQ;}
"-="         		{yylval.kw = "MINUSEQ"; return MINUSEQ;}
"<<="        		{yylval.kw = "SHLEQ"; return SHLEQ;}
">>="        		{yylval.kw = "SHREQ"; return SHREQ;}
"&="         		{yylval.kw = "ANDEQ"; return ANDEQ;}
"|="         		{yylval.kw = "OREQ"; return OREQ;}
"^="         		{yylval.kw = "XOREQ"; return XOREQ;}


 /* Punctuation */
[](){}[;:,]		{return yytext[0];}


 /* Numberic Constants */ 
{DEC}				{	/* Deal with simple integers */			
						int_info(yytext, SIGNED_T, INT_T);
						return NUMBER;
					}
{DEC}"U"			{	/* Unsigned integers */
						yytext[yyleng - 1] = '\0';
						int_info(yytext, UNSIGNED_T, INT_T);
						return NUMBER;
					}
{DEC}"L"			{	/* Signed long */
						yytext[yyleng - 1] = '\0';
						int_info(yytext, SIGNED_T, LONG_T);
						return NUMBER;
					}
{DEC}"LL"			{	/* Signed long long */
						yytext[yyleng - 2] = '\0';
						int_info(yytext, SIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{DEC}"LLU"			{	/* Unsigned long long */
						yytext[yyleng - 3] = '\0';
						int_info(yytext, UNSIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{OCT}				{	/* Deal with simple octals */
						oct_info(yytext, SIGNED_T, INT_T);
						return NUMBER;
					}
{OCT}"U"			{	/* Unsigned octal */
						yytext[yyleng - 1] = '\0';
						oct_info(yytext, UNSIGNED_T, INT_T);
						return NUMBER;
					}
{OCT}"L"			{	/* Signed long octal */
						yytext[yyleng - 1] = '\0';
						oct_info(yytext, SIGNED_T, LONG_T);
						return NUMBER;
					}
{OCT}"LL"			{	/* Signed long long octal */
						yytext[yyleng - 2] = '\0';
						oct_info(yytext, SIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{OCT}"LLU"			{	/* Unsigned long long octal */
						yytext[yyleng - 3] = '\0';
						oct_info(yytext, UNSIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{HEX}				{	/* Deal with simple hexadecimals */
						hex_info(yytext, SIGNED_T, INT_T);
						return NUMBER;
					}
{HEX}"U"			{	/* Unsigned hex */
						yytext[yyleng - 1] = '\0';
						hex_info(yytext, UNSIGNED_T, INT_T);
						return NUMBER;
					}
{HEX}"L"			{	/* Signed long hex */
						yytext[yyleng - 1] = '\0';
						hex_info(yytext, SIGNED_T, LONG_T);
						return NUMBER;
					}
{HEX}"LL"			{	/* Signed long long hex */
						yytext[yyleng - 2] = '\0';
						hex_info(yytext, SIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{HEX}"LLU"			{	/* Unsigned long long hex */
						yytext[yyleng - 3] = '\0';
						hex_info(yytext, SIGNED_T, LONGLONG_T);
						return NUMBER;
					}
{HEX}{P}			{	/* "p" form hexadecimal floats */
						real_info(yytext, SIGNED_T, DOUBLE_T);				
						return NUMBER;
					}	
{REAL}				{	/* Dealing with simple doubles */
						real_info(yytext, SIGNED_T, DOUBLE_T);
						return NUMBER;
					}
{REAL}"L"			{	/* Signed long double */
						yytext[yyleng - 1] = '\0';
						real_info(yytext, SIGNED_T, LONGDOUBLE_T);
						return NUMBER;
					}
[0]?{DEC}+{EXP}[f]?	{	/* Dealing with exponents */
						if(yytext[yyleng - 1] == 'f')
							real_info(yytext, SIGNED_T, FLOAT_T);
						else
							real_info(yytext, SIGNED_T, DOUBLE_T);
						return NUMBER;
					}
{REAL}"f"			{	/* Explicit float type */
						yytext[yyleng - 1] = '\0';
						real_info(yytext, SIGNED_T, FLOAT_T);
						return NUMBER;
					}

 /* Ignore Comments */
\/\*            		{BEGIN(COMMENT_STATE);}
<COMMENT_STATE>.|\n    	{ /* Ignore everything */ ;}
<COMMENT_STATE>\*\/   		{BEGIN(INITIAL);}
\/\/.*\n        		{ /* Ignore single-line comments */  ;}

 /* Update line numbers */
\n 				{lineno++;}

 /* Throw error if no appropriate token is found */
.				{fprintf(stderr, "Error: Undefined token: %s\n", yytext); exit(-1);}

%%

void int_info(char *buf, int sign, int type)
{
	yylval.num.int_value = atoi(buf);
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
		for(int i = 0; i < strlen(buf); i++)
			yylval.string.word[yylval.string.length + i] = buf[i];

		yylval.string.length += strlen(buf);
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
				case IDENT:		fprintf(stdout, "%s\t %d\t IDENT\t %s\n", file, lineno, yylval.ident.name);
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
									case INT_T:			fprintf(stdout, "INT\n");break;
									case LONG_T:		fprintf(stdout, "LONG\n");break;
									case LONGLONG_T: 	fprintf(stdout, "LONGLONG\n");break;
									case DOUBLE_T: 		fprintf(stdout, "DOUBLE\n");break;
									case LONGDOUBLE_T: 	fprintf(stdout, "LONGDOUBLE\n");break;
									case FLOAT_T: 		fprintf(stdout, "FLOAT\n");break;
									default: 			break;
								}
								
								break;

				default:		fprintf(stdout, "%s\t %d\t %s\n", file, lineno, yylval.kw);
								break;
			}
		}

	}

	return 0;

}
