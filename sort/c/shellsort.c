#include "algorithms.h"

#define GAP 2

void shellsort(int *array, size_t length) {
  size_t h = length / GAP;

  while (h > 0) {
    for (size_t i = h; i < length; i++) {
      for (size_t j = i; j > h - 1 && array[j] < array[j - h]; j -= h) {
        swap(&array[j], &array[j - h]);
      }
    }
    h /= GAP;
  }
}
