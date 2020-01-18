# ECE466-Compilers

Assignment 1: Lexer. Lexical analysis of the C language

Assignment 2: Expression Parsing.  Writing an interpreter which understands and evaluates the C expression syntax (limited subset) and transforms it into Abstract Syntax Trees.

Assignment 3: Semantic Analysis.  Parsing declarations, representing types, managing symbol tables.

Assignment 4: Statements.  Completion of the AST to include all statements.

Assignment 5: Quads.  Generation of pseudo-opcodes.

Assignment 6: Target Gode Generation.  Translate quads into x86 assembly.


### How to Run
```
gcc -E input.c | ./parser output.s
cc -m32 output.s
./a.out
```
