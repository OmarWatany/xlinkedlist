#include "linkedlist.h"

struct node_t {
    void  *data;
    size_t link;
};

struct linked_list_t {
    node_t *head, *tail;
    void    (*allocate_data)(node_t *, void *data);
};

struct list_iterator_t {
    linked_list_t *list;
    node_t        *from;
    size_t         prev_node, next_node;
};

linked_list_t *create_list(void (*allocate_data)(node_t *, void *data)) {
    linked_list_t *new_list = (linked_list_t *)malloc(sizeof(linked_list_t));
    new_list->head          = NULL;
    new_list->tail          = NULL;
    new_list->allocate_data = allocate_data;
    return new_list;
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

node_t *get_list_head(linked_list_t *list) { return list->head; }
node_t *get_list_tail(linked_list_t *list) { return list->tail; }

node_t *next(list_iterator_t *iterator) {
    node_t *from = iterator->from;
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
    iterator->from      = (node_t *)iterator->next_node;
    iterator->next_node = iterator->prev_node ^ from->link;
    return iterator->from;
}

node_t *prev(list_iterator_t *iterator) {
    node_t *from = iterator->from;
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
    iterator->from      = (node_t *)iterator->prev_node;
    iterator->prev_node = iterator->next_node ^ from->link;
    return iterator->from;
}

int16_t push_front(linked_list_t *list, void *data) {
    node_t *new_node = malloc(sizeof(node_t));
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
    node_t *new_node = malloc(sizeof(node_t));
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

void set_node_data(node_t *node, void *data) { node->data = data; };

void *get_node_data(node_t *node) { return node->data; }

void *pop_front(linked_list_t *list) {
    void *value = NULL;

    list_iterator_t *it = create_list_iterator(list);
    if (list->head == NULL || it == NULL)
        return value;
    node_t *temp = list->head;
    list->head   = next(it);
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
    if (list == NULL || list->head == NULL)
        return value;

    if (list->tail == list->head)
        return pop_front(list);

    list_iterator_t *it = create_list_iterator(list);
    set_iterators_from(it, list->tail);
    if (it == NULL)
        return value;

    node_t *temp = list->tail;
    list->tail   = prev(it);

    if (list->tail != NULL)
        list->tail->link ^= (size_t)temp;

    value = temp->data;
    free(temp);
    free(it);
    return value;
}

void clear_list(linked_list_t *list) {
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

linked_list_t *get_iterators_list(list_iterator_t *iterator) {
    return iterator->list;
}

void set_iterators_from(list_iterator_t *iterator, node_t *from) {
    if (iterator == NULL || get_iterators_list(iterator) == NULL)
        return;
    iterator->from = from;
}

int16_t dump_list(linked_list_t *list, void (*print_data)(void *)) {
    if (list == NULL)
        return EXIT_FAILURE;

    node_t *temp = list->head;

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
    node_t *temp = list->tail;

    if (list == NULL)
        return EXIT_FAILURE;

    list_iterator_t *it = create_list_iterator(list);
    set_iterators_from(it, temp);
    if (it == NULL)
        return EXIT_FAILURE;
    while (temp != NULL) {
        print_data(temp->data);
        temp = prev(it);
    }
    free(it);
    return EXIT_SUCCESS;
}
