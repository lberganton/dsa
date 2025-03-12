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

size_t int_log2(size_t n) {
  size_t log = n;
  while (n > 1) {
    n >>= 1;
    log++;
  }
  return log;
}

int compare(const void *val1, const void *val2) {
  return *(int*) val1 - *(int*) val2;
}

int main(void) {
  const size_t LEN = 10;

  int array[LEN];
  array_initialize(array, LEN);
  array_print("Original", array, LEN);

  int tmp[LEN];

  memcpy(tmp, array, sizeof(array));
  qsort(tmp, LEN, sizeof(int), compare);
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
  heapsort(tmp, LEN);
  array_print("Heapsort sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  quicksort(tmp, 0, LEN - 1);
  array_print("Quick sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  mergesort(tmp, 0, LEN - 1);
  array_print("Merge sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  introsort(tmp, LEN, int_log2(LEN) * 2.0);
  array_print("Intro sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  shellsort(tmp, LEN);
  array_print("Shell sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  countingsort(tmp, LEN);
  array_print("Counting Sort", tmp, LEN);

  memcpy(tmp, array, sizeof(array));
  bogosort(tmp, LEN, 1000000);
  array_print("Bogo sort", tmp, LEN);

  return 0;
}
