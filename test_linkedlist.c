#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

#define push_front_i(x, y)                                                          \
    {                                                                               \
        int i = y;                                                                  \
        push_front(x, &i);                                                          \
    }

#define dump_str_list(x)                                                            \
    {                                                                               \
        dump_list(x, _print_str);                                                   \
        printf("\n");                                                               \
    }

#define dump_int_list(x)                                                            \
    {                                                                               \
        dump_list(x, _print_int);                                                   \
        printf("\n");                                                               \
    }

void _allocate_str(node_t *node, void *data);
void _allocate_int(node_t *node, void *data);
void _print_str(void *data);
void _print_int(void *data);

int main() {

    linked_list_t *lst      = create_list(_allocate_str);
    linked_list_t *new_list = create_list(_allocate_int);

    push_front_i(new_list, 3);
    push_front_i(new_list, 2);
    push_front_i(new_list, 7);
    dump_int_list(new_list);

    for (int i = 0; i < 7; i++) {
        push_front(lst, "world");
        push_front(lst, "hello");
        push_front(lst, "print");
        push_back(lst, "!");
    }

    dump_str_list(lst);

    list_iterator_t *fast_it = create_list_iterator(lst);
    list_iterator_t *slow_it = create_list_iterator(lst);

    node_t *fast = get_list_head(get_iterators_list(fast_it));
    node_t *slow = get_list_head(get_iterators_list(slow_it));
    set_iterators_from(slow_it, get_list_head(get_iterators_list(slow_it)));

    {
        int length = 1, h_index = 0;
        while (fast != NULL && fast != get_list_tail(get_iterators_list(fast_it))) {
            for (int i = 0; i < 2; i++) {
                if (fast != get_list_tail(get_iterators_list(fast_it)))
                    length++;
                fast = next(fast_it);
            }
            slow = next(slow_it);
            h_index++;
            _print_str(get_node_data(slow));
        }
        printf("\n");
        printf("length = %d \n", length);
        printf("length / 2 = %d \n", h_index);
    }

    free(fast_it);
    free(slow_it);

    destroy_list(&new_list);
    destroy_list(&lst);

    return 0;
}

void _allocate_str(node_t *node, void *data) {
    char *temp = strdup((char *)data);
    set_node_data(node, temp);
}

void _allocate_int(node_t *node, void *data) {
    int *temp = malloc(sizeof(int));
    *temp     = *(int *)data;
    set_node_data(node, temp);
}

void _print_str(void *data) {
    if (data == NULL)
        return;
    printf("%s -> ", (char *)data);
}

void _print_int(void *data) { printf("%d", *(int *)data); }
