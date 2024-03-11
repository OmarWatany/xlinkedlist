# XLinkedList

XLinkedList is a simple C implementation of a doubly linked list data structure, designed to be easy to use and integrate into your projects.

## Features

- **Doubly Linked List:** Implements a doubly linked list for efficient insertion, deletion, and traversal.
- **Generic:** Supports any data type through the use of void pointers.
- **Easy to Use:** Simple interface with intuitive functions for list manipulation.

## Getting Started

To get started with XLinkedList, you can follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/OmarWatany/xlinkedlist.git
   ```

2. Include the `xlinkedlist.h` header file in your project.

3. Compile your project along with `xlinkedlist.c`:

   ```bash
   gcc -o your_program your_program.c xlinkedlist.c
   ```

4. Start using XLinkedList in your code by including the necessary functions.

## Usage

Here's a basic example of how to use XLinkedList in your C code:

```c
#include <stdio.h>
#include "xlinkedlist.h"

void _print_string(void *data);
void _allocate_str(node *node, void *data);

int main() {
    // Create a new linked list
    linked_list_t *list = create_list(_allocate_str, _print_string);

    // Add elements to the list at beginning
    push_front(list, "World");
    push_front(list, "Hello");

    // Add elements to the list at back
    push_back(list, "!");

    // Traverse and print the list
    list_iterator_t it = {.list = list};
    node *current = list->head;
    while (current != NULL) {
        _print_string(current->data);
        current = iterator_next(&it);
    }
    printf("\n");

    // Traverse and print the list from back
    current = it.from = list->tail;
    while (current != NULL) {
        _print_string(current->data);
        current = iterator_prev(&it);
    }
    printf("\n");

    // or using dump_list function
    dump_list(list);
    printf("\n");

    // for deleting nodes from front or back
    free(pop_back(list));
    free(pop_front(list));

    // Free list nodes
    clear_list(list);

    // Free all memory allocated by the list
    destroy_list(list);

  return 0;
}

void _print_string(void *data) {
    printf("%s ", (char *)data);
}

void _allocate_str(node *node, void *data) {
    char *temp = strdup((char *)data);
    node->data = temp;
}

```

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.