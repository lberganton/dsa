#include "algorithms.h"
#include <string.h>

void countingsort(int *array, size_t length) {
  int max = array[0];

  for (size_t i = 1; i < length; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  size_t count_length = max + 1;
  int count[count_length];
  memset(count, 0, sizeof(count));

  for (size_t i = 0; i < length; i++) {
    count[array[i]]++;
  }

  for (size_t i = 1; i < count_length; i++) {
    count[i] += count[i - 1];
  }

  int output[length];
  for (size_t i = length; i > 0; i--) {
    size_t j = array[i - 1];
    count[j]--;
    output[count[j]] = array[i - 1];
  }

  memcpy(array, output, sizeof(output));
}
