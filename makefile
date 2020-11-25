rede: main.o avl.o lista.o
	gcc -o rede main.o avl.o lista.o

main.o: main.c avl.h lista.h
	gcc -c main.c
	
avl.o: avl.c avl.h lista.h
	gcc -c avl.c	
	
lista.o: lista.c lista.h
	gcc -c lista.c	
	
