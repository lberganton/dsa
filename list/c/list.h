#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct ArrayList ArrayList;

ArrayList*  arraylist_create(size_t initial_capacity);
bool        arraylist_insert(ArrayList *list, size_t index, int val);
bool        arraylist_pushleft(ArrayList *list, int val);
bool        arraylist_pushright(ArrayList *list, int val);
bool        arraylist_remove(ArrayList *list, size_t index, int *ret);
bool        arraylist_popleft(ArrayList *list, int *ret);
bool        arraylist_popright(ArrayList *list, int *ret);
bool        arraylist_set(ArrayList *list, size_t index, int val);
bool        arraylist_get(ArrayList *list, size_t index, int *ret);
bool        arraylist_max(ArrayList *list, void *ret);
bool        arraylist_min(ArrayList *list, void *ret);
bool        arraylist_equals(ArrayList *first, ArrayList *second);
bool        arraylist_reduce(ArrayList *list, int val, int (*function)(int val1, int val2));
bool        arraylist_anymatch(ArrayList *list, bool (*predicate)(int val));
bool        arraylist_allmatch(ArrayList *list, bool (*predicate)(int val));
void        arraylist_filter(ArrayList *list, bool (*predicate)(int val));
void        arraylist_map(ArrayList *list, int (*function)(int val));
void        arraylist_foreach(ArrayList *list, void (*consumer)(int val));
void        arraylist_sort(ArrayList *list);
void        arraylist_reverse(ArrayList *list);
void        arraylist_clear(ArrayList *list);
void        arraylist_free(ArrayList *list);
size_t      arraylist_findfirst(ArrayList *list, int val, size_t start, size_t end);
size_t      arraylist_findlast(ArrayList *list, int val, size_t start, size_t end);
size_t      arraylist_size(ArrayList *list);

#endif
