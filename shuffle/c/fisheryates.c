#include "algorithms.h"
#include <stdlib.h>

void fisheryates(int *array, size_t length) {
  for (size_t i = length; i > 0; i--) {
    swap(&array[i - 1], &array[rand() % i]);
  }
}
