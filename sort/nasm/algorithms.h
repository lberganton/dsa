#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>

void bubblesort(int *array, size_t length);
void selectionsort(int *array, size_t length);
void insertionsort(int *array, size_t length);
void quicksort(int *array, size_t low, size_t high);

#endif
