#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#include <stddef.h>

static inline void swap(int *val1, int *val2) {
  int tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

void bubblesort(int *array, size_t length);
void selectionsort(int *array, size_t length);
void insertionsort(int *array, size_t length);
void heapsort(int *array, size_t length);
void quicksort(int *array, size_t low, size_t high);
void mergesort(int *array, size_t low, size_t high);
void introsort(int *array, size_t length, size_t level);
void shellsort(int *array, size_t length);
void bogosort(int *array, size_t length, size_t atempts);

#endif
