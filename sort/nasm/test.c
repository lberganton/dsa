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

int comparator(const void *val1, const void *val2) {
  int i1 = *(int*) val1;
  int i2 = *(int*) val2;
  return i1 == i2 ? 0 : i1 < i2 ? -1 : 1;
}

int main(void) {
  const size_t LEN = 10;

  int array[LEN];
  array_initialize(array, LEN);
  array_print("Original", array, LEN);

  int tmp[LEN];

  memcpy(tmp, array, sizeof(array));
  qsort(tmp, LEN, sizeof(int), comparator);
  array_print("Expected", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  bubblesort(tmp, LEN);
  array_print("Bubble sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  selectionsort(tmp, LEN);
  array_print("Selection sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  insertionsort(tmp, LEN);
  array_print("Insertion sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  quicksort(tmp, 0, LEN - 1);
  array_print("Quick sort", tmp, LEN);

  return 0;
}
