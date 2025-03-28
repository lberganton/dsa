#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void array_initialize(int *array, size_t length) {
  srand(time(NULL));
  for (size_t i = 0; i < length; i++) {
    array[i] = rand() % length;
  }
}

void array_print(const char *msg, int *array, size_t length) {
  printf("%-15s: ", msg);
  for (size_t i = 0; i < length; i++) {
    printf("%s%d%s", i==0 ? "[" : " ", array[i], i==length-1 ? "]\n" : ",");
  }
}

int main(void) {
  const size_t LEN = 10;

  int array[LEN];
  array_initialize(array, LEN);
  array_print("Original", array, LEN);

  int tmp[LEN];

  memcpy(tmp, array, sizeof(array));
  fisheryates(tmp, LEN);
  array_print("Fisher-Yates", tmp, LEN);

  return 0;
}
