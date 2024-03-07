#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t traversingNode = 0;

int main() {
  linkedList *lst = create_list(_add_string, _print_string);
  push_front(lst, "world");
  push_front(lst, "hello");
  push_front(lst, "print");
  push_back(lst, "!");

  dump_list(lst);
  printf("\n");

  pop_front(lst);

  dump_list(lst);
  printf("\n");

  pop_back(lst);

  dump_list(lst);
  printf("\n");

  push_back(lst, "!");

  reverse_dump_list(lst);
  printf("\n");

  destroy_list(lst);
}

linkedList *create_list(void (*add_data)(node *, void *data),
                        void (*print_data)(void *data)) {
  linkedList *newList = (linkedList *)malloc(sizeof(linkedList));
  newList->head = NULL;
  newList->add_data = add_data;
  newList->print_data = print_data;
  return newList;
}

void push_front(linkedList *list, void *data) {
  node *newNode = malloc(sizeof(node));
  list->add_data(newNode, data);

  if (list->head == NULL) {
    newNode->link = 0;
    list->tail = newNode;
  } else {
    newNode->link = (size_t)list->head;
    list->head->link ^= (size_t)newNode;
  }

  list->head = newNode;
}

void push_back(linkedList *list, void *data) {
  node *newNode = malloc(sizeof(node));
  list->add_data(newNode, data);

  if (list->tail != NULL) {
    newNode->link = (size_t)list->tail;
    list->tail->link ^= (size_t)newNode;
    list->tail = newNode;
  } else {
    push_front(list, data);
  }
}

void pop_front(linkedList *list) {
  if (list->head != NULL) {
    node *temp = list->head;
    list->head = next(list, list->head);
    if (list->head == NULL) {
      list->tail = NULL;
    } else
      list->head->link ^= (size_t)temp;
    free(temp->data);
    free(temp);
  }
}

void pop_back(linkedList *list) {
  if (list->tail != list->head) {
    node *temp = list->tail;
    list->tail = prev(list, temp);
    if (list->tail != NULL)
      list->tail->link ^= (size_t)temp;
    free(temp->data);
    free(temp);
  } else {
    pop_front(list);
  }
}

void dump_list(linkedList *list) {
  node *temp = list->head;
  while (temp != NULL) {
    list->print_data(temp->data);
    temp = next(list, temp);
  }
}

void reverse_dump_list(linkedList *list) {
  node *temp = list->tail;
  while (temp != NULL) {
    list->print_data(temp->data);
    temp = prev(list, temp);
  }
}

void destroy_list(linkedList *list) {
  node *temp = NULL;
  while (list->head != NULL) {
    temp = next(list, list->head);
    if (temp != NULL)
      temp->link = temp->link ^ (size_t)list->head;
    free(list->head->data);
    free(list->head);
    list->head = temp;
  }
  free(list);
}

node *next(linkedList *list, node *from) {
  size_t nextNode = 0;

  if (from->link == 0)
    return NULL;
  if (from == list->head) {
    nextNode = list->head->link;
  } else {
    nextNode = traversingNode ^ from->link;
  }
  traversingNode = (size_t)from;
  return (node *)nextNode;
}

node *prev(linkedList *list, node *from) {
  size_t pNode = 0;
  if (from->link == 0)
    return NULL;
  if (from == list->tail) {
    pNode = list->tail->link;
  } else {
    pNode = traversingNode ^ from->link;
  }
  traversingNode = (size_t)from;
  return (node *)pNode;
}

void _print_string(void *data) {
  //
  printf("%s -> ", (char *)data);
}

void _add_string(node *node, void *data) {
  char *temp = strdup((char *)data);
  node->data = temp;
}
