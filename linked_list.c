#include "linked_list.h"
#include <stdlib.h>

linked_list_t *create_list(void (*add_data)(node *, void *data),
                           void (*print_data)(void *data)) {
  linked_list_t *new_list = (linked_list_t *)malloc(sizeof(linked_list_t));
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->allocate_data = add_data;
  new_list->print_data = print_data;
  return new_list;
}

int16_t push_front(linked_list_t *list, void *data) {
  node *new_node = malloc(sizeof(node));
  list->allocate_data(new_node, data);
  if (new_node == NULL)
    return EXIT_FAILURE;

  if (list->head == NULL) {
    new_node->link = 0;
    list->tail = new_node;
  } else {
    new_node->link = (size_t)list->head;
    list->head->link ^= (size_t)new_node;
  }

  list->head = new_node;
  return EXIT_SUCCESS;
}

int16_t push_back(linked_list_t *list, void *data) {
  node *new_node = malloc(sizeof(node));
  list->allocate_data(new_node, data);
  if (new_node == NULL)
    return EXIT_FAILURE;

  if (list->tail != NULL) {
    new_node->link = (size_t)list->tail;
    list->tail->link ^= (size_t)new_node;
    list->tail = new_node;
  } else {
    push_front(list, data);
  }
  return EXIT_SUCCESS;
}

void *pop_front(linked_list_t *list) {
  void *value = NULL;
  if (list->head == NULL)
    return value;

  node *temp = list->head;
  size_t prevNode = 0;
  list->head = next(list, list->head, &prevNode);
  if (list->head == NULL) {
    list->tail = NULL;
  } else
    list->head->link ^= (size_t)temp;
  value = temp->data;
  free(temp);
  return value;
}

void *pop_back(linked_list_t *list) {
  void *value = NULL;
  if (list->tail == list->head)
    pop_front(list);

  node *temp = list->tail;
  size_t prevNode = 0;
  list->tail = prev(list, temp, &prevNode);
  if (list->tail != NULL)
    list->tail->link ^= (size_t)temp;
  value = temp->data;
  free(temp);

  return value;
}

int16_t dump_list(linked_list_t *list) {
  node *temp = list->head;
  size_t prevNode = 0;
  while (temp != NULL) {
    list->print_data(temp->data);
    temp = next(list, temp, &prevNode);
  }
  return EXIT_SUCCESS;
}

int16_t reverse_dump_list(linked_list_t *list) {
  node *temp = list->tail;
  size_t prevNode = 0;
  while (temp != NULL) {
    list->print_data(temp->data);
    temp = prev(list, temp, &prevNode);
  }
  return EXIT_SUCCESS;
}

void clear_list(linked_list_t *list) {
  node *temp = NULL;
  size_t prevNode = 0;
  while (list->head != NULL) {
    temp = next(list, list->head, &prevNode);
    if (temp != NULL)
      temp->link = temp->link ^ (size_t)list->head;
    free(list->head->data);
    free(list->head);
    list->head = temp;
  }
}

void destroy_list(linked_list_t *list) {
  node *temp = NULL;
  size_t prevNode = 0;
  while (list->head != NULL) {
    temp = next(list, list->head, &prevNode);
    if (temp != NULL)
      temp->link = temp->link ^ (size_t)list->head;
    free(list->head->data);
    free(list->head);
    list->head = temp;
  }
  free(list);
}

node *next(linked_list_t *list, node *from, size_t *prev_node) {
  size_t next_node = 0;

  if (from->link == 0)
    return NULL;
  if (from == list->head) {
    next_node = list->head->link;
  } else {
    next_node = *prev_node ^ from->link;
  }
  *prev_node = (size_t)from;
  return (node *)next_node;
}

node *prev(linked_list_t *list, node *from, size_t *prev_node) {
  size_t next_node = 0;
  if (from->link == 0)
    return NULL;
  if (from == list->tail) {
    next_node = list->tail->link;
  } else {
    next_node = *prev_node ^ from->link;
  }
  *prev_node = (size_t)from;
  return (node *)next_node;
}

node *iterator_next(list_iterator_t *iterator) {
  size_t next_node = 0;
  node *from = iterator->from;
  if (from == NULL) {
    if (iterator->list->head) {
      from = iterator->list->head;
    } else
      return NULL;
  }
  if (from->link == 0) {
    return NULL;
  } else if (from == iterator->list->head) {
    next_node = iterator->list->head->link;
  } else {
    next_node = iterator->prev_node ^ from->link;
  }
  iterator->prev_node = (size_t)from;
  iterator->from = (node *)next_node;
  return (node *)next_node;
}

node *iterator_prev(list_iterator_t *iterator) {
  size_t next_node = 0;
  node *from = iterator->from;
  if (from == NULL) {
    if (iterator->list->tail) {
      from = iterator->list->tail;
    } else
      return NULL;
  }
  if (from->link == 0) {
    return NULL;
  } else if (from == iterator->list->tail) {
    next_node = iterator->list->tail->link;
  } else {
    next_node = iterator->prev_node ^ from->link;
  }
  iterator->prev_node = (size_t)from;
  iterator->from = (node *)next_node;
  return (node *)next_node;
}
