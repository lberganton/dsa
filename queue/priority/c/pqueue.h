#ifndef PQUEUE_H
#define PQUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Heap Heap;

Heap*   heap_create(size_t initial_capacity, bool max);
bool    heap_insert(Heap *heap, int val);
bool    heap_remove(Heap *heap, int *ret);
bool    heap_peek(Heap *heap, int *ret);
void    heap_free(Heap *heap);
size_t  heap_size(Heap *heap);

#endif
