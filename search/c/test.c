#include "algorithms.h"
#include <stdio.h>

int main(void) {
  const size_t TAM = 5;
  int array[TAM];

  for (size_t i = 0; i < TAM; i++) {
    array[i] = i;
  }

  for (size_t i = 0; i < TAM; i++) {
    printf("%s%d%s", i==0 ? "[" : " ", array[i], i==TAM-1 ? "]\n" : ",");
  }

  printf("Linear (-1): %d\n", linearsearch(array, TAM, -1));
  printf("Linear (0): %d\n", linearsearch(array, TAM, 0));
  printf("Linear (1): %d\n", linearsearch(array, TAM, 1));
  printf("Linear (2): %d\n", linearsearch(array, TAM, 2));
  printf("Linear (3): %d\n", linearsearch(array, TAM, 3));
  printf("Linear (4): %d\n", linearsearch(array, TAM, 4));
  printf("Linear (5): %d\n", linearsearch(array, TAM, 5));

  printf("Binary (-1): %d\n", binarysearch(array, TAM, -1));
  printf("Binary (0): %d\n", binarysearch(array, TAM, 0));
  printf("Binary (1): %d\n", binarysearch(array, TAM, 1));
  printf("Binary (2): %d\n", binarysearch(array, TAM, 2));
  printf("Binary (3): %d\n", binarysearch(array, TAM, 3));
  printf("Binary (4): %d\n", binarysearch(array, TAM, 4));
  printf("Binary (5): %d\n", binarysearch(array, TAM, 5));

  return 0;
}
