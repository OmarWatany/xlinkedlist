CFLAGS=-Wall -Wextra -g

default : linked_list.c linked_list.h test_linked_list.c 
	gcc $(CFLAGS) -o list test_linked_list.c linked_list.c linked_list.h

