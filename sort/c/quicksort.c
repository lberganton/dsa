#include "algorithms.h"

void quicksort(int *array, size_t low, size_t high) {
  if (low >= high) {
    return;
  }

  int pivot = array[high];
  size_t pos = low;

  for (size_t i = low; i < high; i++) {
    if (array[i] < pivot) {
      swap(&array[pos], &array[i]);
      pos++;
    }
  }

  swap(&array[pos], &array[high]);

  if (pos > 0) {
    quicksort(array, low, pos - 1);
  }
  quicksort(array, pos + 1, high);
}
