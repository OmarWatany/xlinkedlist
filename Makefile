CFLAGS=-Wall -Wextra -g

default : linkedlist.c linkedlist.h
	gcc $(CFLAGS) -o list linkedlist.c linkedlist.h
