#include "algorithms.h"

void bubblesort(int *array, size_t length) {
  for (size_t i = 0; i < length - 1; i ++) {
    for (size_t j = 0; j < length - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
      }
    }
  }
}
