#include "pqueue.h"
#include <stdlib.h>

struct Heap {
  int *array;
  size_t allocated;
  size_t elements;
  int (*comparator)(int val1, int val2);
};

static inline int default_comparator(int val1, int val2) {
  return val1 - val2;
}

Heap* heap_create(size_t initial_capacity, int (*comparator)(int val1, int val2)) {
  Heap *new = (Heap*) malloc(sizeof(Heap));
  if (new == NULL) {
    return NULL;
  }

  new->comparator = comparator == NULL ? default_comparator : comparator;
  new->allocated = initial_capacity != 0 ? initial_capacity : 16;
  new->elements = 0;

  new->array = (int*) malloc(new->allocated * sizeof(int));
  if (new->array == NULL) {
    free(new);
    return NULL;
  }

  return new;
}

static bool increase(Heap *heap) {
  int *new = (int*) realloc(heap->array, heap->allocated * 2);
  if (new == NULL) {
    return false;
  }

  heap->array = new;
  heap->allocated *= 2;

  return true;
}

static inline void swap(int *val1, int *val2) {
  int tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

static void siftup(Heap *heap, size_t i) {
  while (i > 0 && heap->comparator(heap->array[i], heap->array[i / 2]) > 0) {
    swap(&heap->array[i], &heap->array[i / 2]);
    i /= 2;
  }
}

bool heap_insert(Heap *heap, int val) {
  if (heap->elements == heap->allocated && !increase(heap)) {
    return false;
  }

  size_t i = heap->elements;
  heap->array[i] = val;
  heap->elements++;

  siftup(heap, i);

  return true;
}

static void siftdown(Heap *heap, size_t i) {
  size_t max = i;
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  if (left < heap->elements && heap->comparator(heap->array[left], heap->array[max]) > 0) {
    max = left;
  }
  if (right < heap->elements && heap->comparator(heap->array[right], heap->array[max]) > 0) {
    max = right;
  }

  if (i != max) {
    swap(&heap->array[i], &heap->array[max]);
    siftdown(heap, max);
  }
}

bool heap_remove(Heap *heap, int *ret) {
  if (heap->elements == 0) {
    return false;
  }

  *ret = heap->array[0];
  heap->elements--;

  if (heap->elements == 0) {
    return true;
  }

  heap->array[0] = heap->array[heap->elements];
  siftdown(heap, 0);

  return true;
}

bool heap_peek(Heap *heap, int *ret) {
  if (heap->elements == 0) {
    return false;
  }
  *ret = heap->array[0];
  return true;
}

bool heap_equals(Heap *first, Heap *second) {
  if (first->elements != second->elements) {
    return false;
  }
  for (size_t i = 0; i < first->elements; i++) {
    if (first->array[i] != second->array[i]) {
      return false;
    }
  }
  return true;
}

void heap_foreach(Heap *heap, void (*consumer)(int val)) {
  for (size_t i = 0; i < heap->elements; i++) {
    consumer(heap->array[i]);
  }
}

void heap_free(Heap *heap) {
  free(heap->array);
  free(heap);
}

size_t heap_size(Heap *heap) {
  return heap->elements;
}
