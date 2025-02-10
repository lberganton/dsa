#include "algorithms.h"

int linearsearch(int *array, int length, int val) {
  for (int i = 0; i < length; i++) {
    if (val == array[i]) {
      return i;
    }
  }
  return -1;
}
