#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

#define push_front_i(x, y)                                                          \
    {                                                                               \
        int i = y;                                                                  \
        push_front(x, &i);                                                          \
    }

void _print_string(void *data);
void _allocate_str(node_t *node, void *data);

void _print_int(void *data);
void _allocate_int(node_t *node, void *data);

int main() {

    linked_list_t *lst      = create_list(_allocate_str);
    linked_list_t *new_list = create_list(_allocate_int);

    list_iterator_t *it = create_list_iterator(lst);

    push_front_i(new_list, 3);
    push_front_i(new_list, 2);
    push_front_i(new_list, 7);
    // dump_list(new_list, _print_int);
    // printf("\n");

    push_front(lst, "world");
    push_front(lst, "hello");
    push_front(lst, "print");
    dump_list(lst, _print_string);
    printf("\n");

    free(pop_back(lst));
    dump_list(lst, _print_string);
    printf("\n");

    push_back(lst, "!");
    reverse_dump_list(lst, _print_string);
    printf("\n");

    node_t *temp = get_list_head(get_iterators_list(it));
    while (temp != NULL) {
        _print_string(get_node_data(temp));
        temp = next(it);
    }
    printf("\n");
    temp = get_list_tail(get_iterators_list(it));
    set_iterators_from(it, temp);
    while (temp != NULL) {
        _print_string(get_node_data(temp));
        temp = prev(it);
    }
    printf("\n");

    free(it);
    destroy_list(&new_list);
    destroy_list(&lst);

    return 0;
}

void _print_string(void *data) { printf("%s -> ", (char *)data); }

void _allocate_str(node_t *node, void *data) {
    char *temp = strdup((char *)data);
    set_node_data(node, temp);
}

void _print_int(void *data) { printf("%d", *(int *)data); }

void _allocate_int(node_t *node, void *data) {
    int *temp = malloc(sizeof(int));
    *temp     = *(int *)data;
    set_node_data(node, temp);
}
