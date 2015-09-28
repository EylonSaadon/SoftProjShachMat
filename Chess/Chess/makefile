all: Chess

clean:
	-rm Data_Structures.o Chess.o Logic.o Minimax.o chessprog 

Chess: Data_Structures.o Logic.o Minimax.o Chess.o
	gcc -o chessprog Data_Structures.o Logic.o Minimax.o Chess.o -lm -std=c99 -pedantic-errors -g -lxml2

Data_Structures.o: Data_Structures.h Data_Structures.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm Data_Structures.c

Logic.o: Logic.h Logic.c
	gcc -I/usr/include/libxml2 -std=c99 -pedantic-errors -c -Wall -g -lm Logic.c

Minimax.o: Minimax.h Minimax.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm Minimax.c

Chess.o: Chess.h Chess.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Chess.c