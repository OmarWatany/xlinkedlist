#include <stdlib.h>

typedef struct node node;
typedef struct linkedList linkedList;

struct node {
  void *data;
  size_t link;
};

struct linkedList {
  node *head, *tail;
  void (*add_data)(node *, void *data);
  void (*print_data)(void *data);
};

linkedList *create_list(void (*add_data)(node *, void *data),
                        void (*print_data)(void *data));

void push_front(linkedList *list, void *data);
void push_back(linkedList *list, void *data);
void pop_front(linkedList *list);
void pop_back(linkedList *list);
void dump_list(linkedList *list);
void reverse_dump_list(linkedList *list);
void destroy_list(linkedList *list);

node *next(linkedList *list, node *from);
node *prev(linkedList *list, node *from);

void _print_string(void *data);
void _add_string(node *node, void *data);
