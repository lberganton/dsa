#include "algorithms.h"
#include <stdio.h>

static size_t quicksort_partition(int *array, size_t low, size_t high) {
  int pivot = array[high];
  size_t pos = low;

  for (size_t i = low; i < high; i++) {
    if (array[i] < pivot) {
      swap(&array[pos], &array[i]);
      pos++;
    }
  }

  swap(&array[pos], &array[high]);
  return pos;
}

void introsort(int *array, size_t length, size_t level) {
  if (length <= 16) {
    insertionsort(array, length);
  }
  else if (level == 0) {
    heapsort(array, length);
  }
  else {
    size_t pivot = quicksort_partition(array, 0, length - 1);

    if (pivot > 0) {
      introsort(array, pivot, level - 1);
    }
    introsort(&array[pivot + 1], length - pivot - 1, level - 1);
  }
}
