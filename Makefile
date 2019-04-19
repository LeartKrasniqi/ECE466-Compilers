parser: parser.tab.o ast.o sym_tab.o lex.yy.o
		gcc -o parser parser.tab.o ast.o sym_tab.o lex.yy.o 

lex.yy.o: lexer.l parser.tab.h def.h
		flex lexer.l
		gcc -c lex.yy.c

parser.tab.o: parser.y ast.h sym_tab.h
		bison -vd parser.y
		gcc -c parser.tab.c

sym_tab.o: sym_tab.h sym_tab.c
		gcc -c sym_tab.c

ast.o: ast.c ast.h
		gcc -c ast.c

clean: 
	rm *.o
