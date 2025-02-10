#include "algorithms.h"

void mergesort(int *array, size_t low, size_t high) {
  size_t length = high - low + 1;

  if (length <= 1) {
    return;
  }

  size_t mid = (low + high) / 2;
  mergesort(array, low, mid);
  mergesort(array, mid + 1, high);

  int new[length];
  size_t i = 0;

  size_t left = low;
  size_t right = mid + 1;

  while (left <= mid && right <= high) {
    if (array[left] < array[right]) {
      new[i++] = array[left++];
    }
    else {
      new[i++] = array[right++];
    }
  }

  while (left <= mid) {
    new[i++] = array[left++];
  }
  while (right <= high) {
    new[i++] = array[right++];
  }

  for (i = 0; i < length; i++) {
    array[low + i] = new[i];
  }
}
