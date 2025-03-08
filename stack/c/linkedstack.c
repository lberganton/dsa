#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

struct LinkedStack {
  Node *top;
  size_t elements;
};

LinkedStack* linkedstack_create(void) {
  LinkedStack* new = (LinkedStack*) malloc(sizeof(LinkedStack));
  if (new != NULL) {
    new->top = NULL;
    new->elements = 0;
  }
  return new;
}

static Node* node_create(int val, Node *next) {
  Node *new = (Node*) malloc(sizeof(Node));
  if (new != NULL) {
    new->val = val;
    new->next = next;
  }
  return new;
}

bool linkedstack_push(LinkedStack *stack, int val) {
  Node *new = node_create(val, stack->top);
  if (new == NULL) {
    return false;
  }
  stack->top = new;
  stack->elements++;
  return true;
}

bool linkedstack_pop(LinkedStack *stack, int *ret) {
  if (stack->elements == 0) {
    return false;
  }
  if (ret != NULL) {
    *ret = stack->top->val;
  }
  Node *tmp = stack->top->next;
  free(stack->top);
  stack->top = tmp;
  return true;
}

bool linkedstack_peek(LinkedStack* stack, int *ret) {
  if (stack->elements == 0) {
    return false;
  }
  *ret = stack->top->val;
  return true;
}

bool linkedstack_equals(LinkedStack *first, LinkedStack *second) {
  if (first->elements != second->elements) {
    return false;
  }

  Node *n1 = first->top;
  Node *n2 = second->top;

  while (n1 != NULL) {
    if (n1->val != n2->val) {
      return false;
    }
    n1 = n1->next;
    n2 = n2->next;
  }

  return true;
}

void linkedstack_foreach(LinkedStack *stack, void (*consumer)(int val)) {
  for (Node *n = stack->top; n != NULL; n = n->next) {
    consumer(n->val);
  }
}

static void free_nodes(Node *node) {
  while (node != NULL) {
    Node *tmp = node->next;
    free(node);
    node = tmp;
  }
}

void linkedstack_free(LinkedStack *stack) {
  free_nodes(stack->top);
  free(stack);
}

size_t linkedstack_size(LinkedStack *stack) {
  return stack->elements;
}
