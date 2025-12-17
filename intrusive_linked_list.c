#include <iso646.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
} Node;
typedef struct Data {
  uint16_t x;
  uint16_t y;
  Node node;
} Data;

#define CONTAINER_OF(ptr, Type, member)                                        \
  ((Type *)((char *)(1 ? (ptr) : &((Type *)0)->member) -                       \
            offsetof(Type, member)))

void foo(Node *data) {
  struct Data *element = CONTAINER_OF(data, Data, node);
  printf("%d,%d\n", element->x, element->y);
}
void foo_any_list(Node *current, void (*node_action)(Node *)) {
  while (current) {
    node_action(current);
    current = current->next;
  }
}
Data *new_data(uint16_t x, uint16_t y) {
  Data *d = malloc(sizeof(Data));
  d->x = x;
  d->y = y;
  d->node.next = NULL;
  return d;
}

Node *add_node(Node *node, Node *new_node) {
  new_node->next = node;
  return new_node;
}
Node *remove_node(Node **node) {
  if (node == NULL) {
    return NULL;
  }
  Node *removed = *node;
  *node = (*node)->next;
  removed->next = NULL;
  return removed;
}

const Node *get_nth_node(const Node *node, size_t n) {
  if (node == NULL) {
    return NULL;
  }

  size_t idx = 0;

  while (node != NULL && idx < n) {

    node = node->next;
    idx++;
  }
  return node;
}
Node *remove_nth_node(Node **node, size_t n) {

  if (node == NULL) {
    return NULL;
  }

  size_t idx = 0;

  while (*node != NULL && idx < n) {

    node = &(*node)->next;
    idx++;
  }

  return remove_node(node);
}

int main() {
  /*what ever function*/
  Data *current = new_data(7, 7);
  Node *node = add_node(&current->node, &new_data(20, 20)->node);
  node = add_node(node, &new_data(10, 15)->node);
  node = add_node(node, &new_data(30, 40)->node);
  node = add_node(node, &new_data(20, 10)->node);

  Node *deleted = remove_nth_node(&node, 3);
  foo_any_list(node, foo);
}
