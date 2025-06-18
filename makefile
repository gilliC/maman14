
assembler:  assembler.c transformMacros.c assembler.h transformMacros.h
	gcc -ansi -pedantic -Wall -g assembler.c transformMacros.c  -o assembler