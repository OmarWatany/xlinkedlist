#include "linked_list.h"
#include <stdio.h>
#include <string.h>

#define push_front_i(x, y)                                                     \
  do {                                                                         \
    int i = y;                                                                 \
    push_front(x, &i);                                                         \
  } while (0);

void _print_string(void *data);
void _allocate_str(node *node, void *data);

void _print_int(void *data);
void _allocate_int(node *node, void *data);

int main() {

  linked_list_t *lst = create_list(_allocate_str, _print_string);
  linked_list_t *int_list = create_list(_allocate_int, _print_int);
  linked_list_t new_list = {NULL, NULL, _allocate_int, _print_int};

  list_iterator_t it = {.list = lst, .from = NULL, .prev_node = 0};

  int d = 8;
  push_front(int_list, &d);
  d = 9;
  push_front(int_list, &d);
  d = 3;
  push_front(int_list, &d);
  dump_list(int_list);
  printf("\n");

  push_front_i(&new_list, 3);
  push_front_i(&new_list, 2);
  push_front_i(&new_list, 7);
  dump_list(&new_list);
  printf("\n");

  push_front(lst, "world");
  push_front(lst, "hello");
  push_front(lst, "print");
  push_back(lst, "!");
  dump_list(lst);
  printf("\n");

  free(pop_front(lst));

  dump_list(lst);
  printf("\n");

  free(pop_back(lst));

  dump_list(lst);
  printf("\n");

  push_back(lst, "!");

  reverse_dump_list(lst);
  printf("\n");

  node *temp = iterator_next(&it);
  printf("\n");
  if (temp != NULL) {
    _print_string(temp->data);
    printf("\n");
  }

  temp = iterator_prev(&it);
  if (temp != NULL) {
    _print_string(temp->data);
    printf("\n");
  }

  temp = iterator_next(&it);
  if (temp != NULL) {
    _print_string(temp->data);
    printf("\n");
  }

  clear_list(&new_list);
  destroy_list(lst);
  destroy_list(int_list);
  return 0;
}

void _print_string(void *data) {
  //
  printf("%s -> ", (char *)data);
}

void _allocate_str(node *node, void *data) {
  char *temp = strdup((char *)data);
  node->data = temp;
}

void _print_int(void *data) { printf("%d", *(int *)data); }

void _allocate_int(node *node, void *data) {
  int *temp = malloc(sizeof(int));
  *temp = *(int *)data;
  node->data = temp;
}
