#include "algorithms.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static bool issorted(int *array, size_t length) {
  for (size_t i = 1; i < length; i++) {
    if (array[i] < array[i - 1]) {
      return false;
    }
  }
  return true;
}

static void shuffle(int *array, size_t length) {
  for (size_t i = 0; i < length; i++) {
    swap(&array[i], &array[rand() % (i + 1)]);
  }
}

void bogosort(int *array, size_t length, size_t atempts) {
  size_t cur = 0;
  srand(time(NULL));
  while (!issorted(array, length) && (atempts == 0 || cur < atempts)) {
    shuffle(array, length);
    cur++;
  }
}
