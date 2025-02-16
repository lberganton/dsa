#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#include <stddef.h>

static inline void swap(int *val1, int *val2) {
  int tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

void fisheryates(int *array, size_t length);

#endif
