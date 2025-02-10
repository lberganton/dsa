#include "algorithms.h"

void selectionsort(int *array, size_t length) {
  for (size_t i = 0; i < length; i ++) {
    int minor = i;

    for (size_t j = i + 1; j < length; j++) {
      if (array[j] < array[minor]) {
        minor = j;
      }
    }

    swap(&array[i], &array[minor]);
  }
}
