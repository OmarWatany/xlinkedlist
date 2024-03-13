CFLAGS=-Wall -Wextra -g

default : linkedlist.c linkedlist.h test_linkedlist.c 
	gcc $(CFLAGS) -o list test_linkedlist.c linkedlist.c linkedlist.h

