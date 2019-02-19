parser: parser.tab.o ast.o lex.yy.o
		gcc -o parser parser.tab.o ast.o lex.yy.o 

lex.yy.o: lexer.l parser.tab.h def.h
		flex lexer.l
		gcc -c lex.yy.c

parser.tab.o: parser.y ast.h
		bison -vd parser.y
		gcc -c parser.tab.c

ast.o: ast.c ast.h
		gcc -c ast.c
