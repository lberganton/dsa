#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

static inline void swap(int *val1, int *val2) {
  int tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

typedef struct ArrayList ArrayList;
typedef struct LinkedList LinkedList;

ArrayList*  arraylist_create(size_t initial_capacity);
bool        arraylist_insert(ArrayList *list, size_t index, int val);
bool        arraylist_pushleft(ArrayList *list, int val);
bool        arraylist_pushright(ArrayList *list, int val);
bool        arraylist_remove(ArrayList *list, size_t index, int *ret);
bool        arraylist_popleft(ArrayList *list, int *ret);
bool        arraylist_popright(ArrayList *list, int *ret);
bool        arraylist_set(ArrayList *list, size_t index, int val);
bool        arraylist_get(ArrayList *list, size_t index, int *ret);
bool        arraylist_max(ArrayList *list, int *ret);
bool        arraylist_min(ArrayList *list, int *ret);
bool        arraylist_equals(ArrayList *first, ArrayList *second);
bool        arraylist_reduce(ArrayList *list, int indentity, int (*function)(int val1, int val2), int *ret);
bool        arraylist_anymatch(ArrayList *list, bool (*predicate)(int val));
bool        arraylist_allmatch(ArrayList *list, bool (*predicate)(int val));
void        arraylist_filter(ArrayList *list, bool (*predicate)(int val));
void        arraylist_map(ArrayList *list, int (*function)(int val));
void        arraylist_foreach(ArrayList *list, void (*consumer)(int val));
void        arraylist_sort(ArrayList *list);
void        arraylist_reverse(ArrayList *list);
void        arraylist_free(ArrayList *list);
size_t      arraylist_findfirst(ArrayList *list, int val, size_t start, size_t end);
size_t      arraylist_findlast(ArrayList *list, int val, size_t start, size_t end);
size_t      arraylist_size(ArrayList *list);

LinkedList* linkedlist_create(void);
bool        linkedlist_insert(LinkedList *list, size_t index, int val);
bool        linkedlist_pushleft(LinkedList *list, int val);
bool        linkedlist_pushright(LinkedList *list, int val);
bool        linkedlist_remove(LinkedList *list, size_t index, int *ret);
bool        linkedlist_popleft(LinkedList *list, int *ret);
bool        linkedlist_popright(LinkedList *list, int *ret);
bool        linkedlist_set(LinkedList *list, size_t index, int val);
bool        linkedlist_get(LinkedList *list, size_t index, int *ret);
bool        linkedlist_max(LinkedList *list, int *ret);
bool        linkedlist_min(LinkedList *list, int *ret);
bool        linkedlist_equals(LinkedList *first, LinkedList *second);
bool        linkedlist_reduce(LinkedList *list, int indentity, int (*function)(int val1, int val2), int *ret);
bool        linkedlist_anymatch(LinkedList *list, bool (*predicate)(int val));
bool        linkedlist_allmatch(LinkedList *list, bool (*predicate)(int val));
void        linkedlist_filter(LinkedList *list, bool (*predicate)(int val));
void        linkedlist_map(LinkedList *list, int (*function)(int val));
void        linkedlist_foreach(LinkedList *list, void (*consumer)(int val));
void        linkedlist_sort(LinkedList *list);
void        linkedlist_reverse(LinkedList *list);
void        linkedlist_free(LinkedList *list);
size_t      linkedlist_findfirst(LinkedList *list, int val, size_t start, size_t end);
size_t      linkedlist_findlast(LinkedList *list, int val, size_t start, size_t end);
size_t      linkedlist_size(LinkedList *list);

#endif
