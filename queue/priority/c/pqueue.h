#ifndef PQUEUE_H
#define PQUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Heap Heap;

Heap*   heap_create(size_t initial_capacity, int (*comparator)(int val1, int val2));
bool    heap_insert(Heap *heap, int val);
bool    heap_remove(Heap *heap, int *ret);
bool    heap_peek(Heap *heap, int *ret);
bool    heap_equals(Heap *first, Heap *second);
void    heap_foreach(Heap *heap, void (*consumer)(int val));
void    heap_free(Heap *heap);
size_t  heap_size(Heap *heap);

#endif
