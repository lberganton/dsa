#include "algorithms.h"

static void siftdown(int *array, size_t length, size_t i) {
  size_t major = i;
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  if (left < length && array[left] > array[major]) {
    major = left;
  }
  if (right < length && array[right] > array[major]) {
    major = right;
  }

  if (i != major) {
    swap(&array[i], &array[major]);
    siftdown(array, length, major);
  }
}

void heapsort(int *array, size_t length) {
  for (size_t i = length / 2; i > 0; i--) {
    siftdown(array, length, i - 1);
  }

  while (length > 0) {
    length--;
    swap(&array[0], &array[length]);
    siftdown(array, length, 0);
  }
}
