#include "list.h"
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *back;
  struct Node *next;
} Node;

struct LinkedList {
  Node *head;
  Node *tail;
  size_t elements;
};

LinkedList* linkedlist_create(void) {
  LinkedList* new = (LinkedList*) malloc(sizeof(LinkedList));
  if (new != NULL) {
    new->head = NULL;
    new->tail = NULL;
    new->elements = 0;
  }
  return new;
}

static Node* node_get(LinkedList *list, size_t index) {
  if (index >= list->elements) {
    return NULL;
  }

  Node *node;
  if (index < list->elements / 2) {
    node = list->head;
    for (size_t i = 0; i < index; i++) {
      node = node->next;
    }
  }
  else {
    node = list->tail;
    for (size_t i = list->elements - 1; i > index; i--) {
      node = node->back;
    }
  }

  return node;
}

static Node* node_create(int val) {
  Node *new = (Node*) malloc(sizeof(Node));
  if (new != NULL) {
    new->val = val;
    new->back = NULL;
    new->next = NULL;
  }
  return new;
}

bool linkedlist_insert(LinkedList *list, size_t index, int val) {
  if (index > list->elements) {
    return false;
  }

  Node *new = node_create(val);
  if (new == NULL) {
    return false;
  }

  if (index == list->elements) {
    if (list->elements > 0) {
      list->tail->next = new;
    }
    new->back = list->tail;
    list->tail = new;
  }
  else {
    Node *pos = node_get(list, index);
    new->back = pos->back;
    new->next = pos;
    pos->back = new;
  }

  if (index == 0) {
    list->head = new;
  }

  list->elements++;
  return true;
}

bool linkedlist_pushleft(LinkedList *list, int val) {
  return linkedlist_insert(list, 0, val);
}

bool linkedlist_pushright(LinkedList *list, int val) {
  return linkedlist_insert(list, list->elements, val);
}

static void node_free(LinkedList *list, Node *node) {
  if (node == list->head) {
    list->head = list->head->next;
  }
  if (node == list->tail) {
    list->tail = list->tail->back;
  }

  if (node->back != NULL) {
    node->back->next = node->next;
  }
  if (node->next != NULL) {
    node->next->back = node->back;
  }

  free(node);
}

bool linkedlist_remove(LinkedList *list, size_t index, int *ret) {
  if (index >= list->elements) {
    return false;
  }

  Node *node = node_get(list, index);

  if (ret != NULL) {
    *ret = node->val;
  }

  node_free(list, node);

  list->elements--;
  return true;
}

bool linkedlist_popleft(LinkedList *list, int *ret) {
  return linkedlist_remove(list, 0, ret);
}

bool linkedlist_popright(LinkedList *list, int *ret) {
  return list->elements > 0 && linkedlist_remove(list, list->elements - 1, ret);
}

bool linkedlist_set(LinkedList *list, size_t index, int val) {
  Node *node = node_get(list, index);
  if (node != NULL) {
    node->val = val;
  }
  return node != NULL;
}

bool linkedlist_get(LinkedList *list, size_t index, int *ret) {
  Node *node = node_get(list, index);
  if (node != NULL) {
    *ret = node->val;
  }
  return node != NULL;
}

bool linkedlist_max(LinkedList *list, int *ret) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    if (n == list->head || n->val > *ret) {
      *ret = n->val;
    }
  }
  return list->elements != 0;
}

bool linkedlist_min(LinkedList *list, int *ret) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    if (n == list->head || n->val < *ret) {
      *ret = n->val;
    }
  }
  return list->elements != 0;
}

bool linkedlist_equals(LinkedList *first, LinkedList *second) {
  if (first->elements != second->elements) {
    return false;
  }

  Node *n1 = first->head;
  Node *n2 = second->head;

  while (n1 != NULL) {
    if (n1->val != n2->val) {
      return false;
    }
    n1 = n1->next;
    n2 = n2->next;
  }

  return true;
}

bool linkedlist_reduce(LinkedList *list, int identity, int (*bifunction)(int val1, int val2), int *ret) {
  if (list->elements == 0) {
    return false;
  }

  *ret = identity;
  for (Node *n = list->head; n != NULL; n = n->next) {
    *ret = bifunction(*ret, n->val);
  }

  return true;
}

bool linkedlist_anymatch(LinkedList *list, bool (*predicate)(int val)) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    if (predicate(n->val)) {
      return true;
    }
  }
  return false;
}

bool linkedlist_allmatch(LinkedList *list, bool (*predicate)(int val)) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    if (!predicate(n->val)) {
      return false;
    }
  }
  return true;
}

void linkedlist_filter(LinkedList *list, bool (*predicate)(int val)) {
  Node *node = list->head;
  while (node != NULL) {
    Node *tmp = node->next;
    if (!predicate(node->val)) {
      node_free(list, node);
      list->elements--;
    }
    node = tmp;
  }
}

void linkedlist_map(LinkedList *list, int (*function)(int val)) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    n->val = function(n->val);
  }
}

void linkedlist_foreach(LinkedList *list, void (*consumer)(int val)) {
  for (Node *n = list->head; n != NULL; n = n->next) {
    consumer(n->val);
  }
}

// Temporary implementation.
static int compare(const void *val1, const void *val2) { return *(int*) val1 - *(int*) val2; }
void linkedlist_sort(LinkedList *list) {
  Node *node = list->head;
  int array[list->elements];

  for (size_t i = 0; i < list->elements; i++) {
    array[i] = node->val;
    node = node->next;
  }

  qsort(array, list->elements, sizeof(int), compare);

  node = list->head;
  for (size_t i = 0; i < list->elements; i++) {
    node->val = array[i];
    node = node->next;
  }
}

void linkedlist_reverse(LinkedList *list) {
  Node *tmp = list->head;
  list->head = list->tail;
  list->tail = tmp;

  Node *node = list->tail;
  while (node != NULL) {
    tmp = node->next;
    node->next = node->back;
    node->back = tmp;
    node = tmp;
  }
}

static void free_nodes(Node *node) {
  while (node != NULL) {
    Node *tmp = node->next;
    free(node);
    node = tmp;
  }
}

void linkedlist_free(LinkedList *list) {
  free_nodes(list->head);
  free(list);
}

size_t linkedlist_findfirst(LinkedList *list, int val, size_t start, size_t end) {
  if (start > end || end >= list->elements) {
    return 0;
  }

  Node *node = node_get(list, start);
  for (; start <= end; start++) {
    if (val == node->val) {
      return start + 1;
    }
    node = node->next;
  }

  return 0;
}

size_t linkedlist_findlast(LinkedList *list, int val, size_t start, size_t end) {
  if (start > end || end >= list->elements) {
    return 0;
  }

  Node *node = node_get(list, end);
  for (; end >= start; end--) {
    if (val == node->val) {
      return end + 1;
    }
    node = node->back;
  }

  return 0;
}

size_t linkedlist_size(LinkedList *list) {
  return list->elements;
}
