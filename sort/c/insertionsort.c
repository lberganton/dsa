#include "algorithms.h"

void insertionsort(int *array, size_t length) {
  for (size_t i = 1; i < length; i++) {
    for (size_t j = i; j > 0 && array[j] < array[j - 1]; j--) {
      swap(&array[j], &array[j - 1]);
    }
  }
}
