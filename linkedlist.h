#include <stdlib.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node            node;
typedef struct linked_list_t   linked_list_t;
typedef struct list_iterator_t list_iterator_t;

struct node {
    void  *data;
    size_t link;
};

struct linked_list_t {
    node *head, *tail;
    void  (*allocate_data)(node *, void *data);
};

struct list_iterator_t {
    linked_list_t *list;
    node          *from;
    size_t         prev_node, next_node;
};

linked_list_t *create_list(void (*add_data)(node *, void *data));

int16_t push_front(linked_list_t *list, void *data);
int16_t push_back(linked_list_t *list, void *data);

void *pop_front(linked_list_t *list);
void *pop_back(linked_list_t *list);
void  clear_list(linked_list_t *list);
void  destroy_list(linked_list_t **list);

list_iterator_t *create_list_iterator(linked_list_t *list);

node *next(list_iterator_t *iterator);
node *prev(list_iterator_t *iterator);

int16_t dump_list(linked_list_t *list, void (*print_data)(void *));
int16_t reverse_dump_list(linked_list_t *list, void (*print_data)(void *));

#endif // LINKED_LIST_H
