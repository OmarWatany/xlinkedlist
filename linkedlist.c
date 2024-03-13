#include "linkedlist.h"

linked_list_t *create_list(void (*add_data)(node *, void *data)) {
    linked_list_t *new_list = (linked_list_t *)malloc(sizeof(linked_list_t));
    new_list->head          = NULL;
    new_list->tail          = NULL;
    new_list->allocate_data = add_data;
    return new_list;
}

int16_t push_front(linked_list_t *list, void *data) {
    node *new_node = malloc(sizeof(node));
    list->allocate_data(new_node, data);
    if (new_node == NULL)
        return EXIT_FAILURE;

    if (list->head == NULL) {
        new_node->link = 0;
        list->tail     = new_node;
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

    list_iterator_t *it = create_list_iterator(list);
    if (list->head == NULL || it == NULL)
        return value;

    node *temp = list->head;
    list->head = next(it);

    if (list->head == NULL) {
        list->tail = NULL;
    } else
        list->head->link ^= (size_t)temp;
    value = temp->data;
    free(temp);
    free(it);
    return value;
}

void *pop_back(linked_list_t *list) {
    void *value = NULL;

    list_iterator_t *it = create_list_iterator(list);
    if (it == NULL)
        return value;
    if (list->tail == list->head)
        pop_front(list);

    node *temp = list->tail;
    list->tail = prev(it);
    if (list->tail != NULL)
        list->tail->link ^= (size_t)temp;
    value = temp->data;
    free(temp);
    free(it);

    return value;
}

void clear_list(linked_list_t *list) {
    // node *temp = list->head;

    list_iterator_t *it = create_list_iterator(list);
    if (it == NULL)
        return;
    while (list->head != NULL) {
        free(pop_front(list));
    }
    free(it);
}

void destroy_list(linked_list_t **list) {
    clear_list(*list);
    free(*list);
    *list = NULL;
}

node *next(list_iterator_t *iterator) {
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
        iterator->next_node = iterator->list->head->link;
    } else {
        iterator->next_node = iterator->prev_node ^ from->link;
    }
    iterator->prev_node = (size_t)from;
    iterator->from      = (node *)iterator->next_node;
    iterator->next_node = iterator->prev_node ^ from->link;
    return iterator->from;
}

list_iterator_t *create_list_iterator(linked_list_t *list) {
    list_iterator_t *it = malloc(sizeof(list_iterator_t));
    if (list == NULL || it == NULL)
        return NULL;
    it->list      = list;
    it->from      = list->head;
    it->next_node = it->prev_node = 0;
    return it;
}

node *prev(list_iterator_t *iterator) {
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
        iterator->prev_node = iterator->list->tail->link;
    } else {
        iterator->prev_node = iterator->next_node ^ from->link;
    }
    iterator->next_node = (size_t)from;
    iterator->from      = (node *)iterator->prev_node;
    iterator->prev_node = iterator->next_node ^ from->link;
    return iterator->from;
}

int16_t dump_list(linked_list_t *list, void (*print_data)(void *)) {
    if (list == NULL)
        return EXIT_FAILURE;

    node *temp = list->head;

    list_iterator_t *it = create_list_iterator(list);
    if (it == NULL)
        return EXIT_FAILURE;

    while (temp != NULL) {
        print_data(temp->data);
        temp = next(it);
    }
    free(it);
    return EXIT_SUCCESS;
}

int16_t reverse_dump_list(linked_list_t *list, void (*print_data)(void *)) {
    node *temp = list->tail;

    if (list == NULL)
        return EXIT_FAILURE;

    list_iterator_t *it = create_list_iterator(list);
    if (it == NULL)
        return EXIT_FAILURE;
    while (temp != NULL) {
        print_data(temp->data);
        temp = prev(it);
    }
    free(it);
    return EXIT_SUCCESS;
}
