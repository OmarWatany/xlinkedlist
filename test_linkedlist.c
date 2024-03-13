#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

#define push_front_i(x, y)                                                          \
    {                                                                               \
        int i = y;                                                                  \
        push_front(x, &i);                                                          \
    }

void _print_string(void *data);
void _allocate_str(node *node, void *data);

void _print_int(void *data);
void _allocate_int(node *node, void *data);

int main() {

    linked_list_t *lst      = create_list(_allocate_str);
    linked_list_t  new_list = {NULL, NULL, _allocate_int};

    list_iterator_t *it = create_list_iterator(lst);

    push_front_i(&new_list, 3);
    push_front_i(&new_list, 2);
    push_front_i(&new_list, 7);
    dump_list(&new_list, _print_int);
    printf("\n");

    push_front(lst, "world");
    push_front(lst, "hello");
    push_front(lst, "print");
    push_back(lst, "!");
    dump_list(lst, _print_string);
    printf("\n");

    free(pop_front(lst));

    dump_list(lst, _print_string);
    printf("\n");

    free(pop_back(lst));

    dump_list(lst, _print_string);
    printf("\n");

    push_back(lst, "!");

    reverse_dump_list(lst, _print_string);
    printf("\n");

    node *temp = it->list->head;
    while (temp != NULL) {
        _print_string(temp->data);
        temp = next(it);
    }
    printf("\n");

    temp = it->from = it->list->tail;
    while (temp != NULL) {
        _print_string(temp->data);
        temp = prev(it);
    }
    printf("\n");

    free(it);
    clear_list(&new_list);
    destroy_list(&lst);

    return 0;
}

void _print_string(void *data) { printf("%s -> ", (char *)data); }

void _allocate_str(node *node, void *data) {
    char *temp = strdup((char *)data);
    node->data = temp;
}

void _print_int(void *data) { printf("%d", *(int *)data); }

void _allocate_int(node *node, void *data) {
    int *temp  = malloc(sizeof(int));
    *temp      = *(int *)data;
    node->data = temp;
}
