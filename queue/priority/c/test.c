#include "pqueue.h"
#include <stdio.h>

int main(void) {
  printf("Max Heap:\n");
  Heap* maxh = heap_create(0, true);
  heap_insert(maxh, 1);
  heap_insert(maxh, 2);
  heap_insert(maxh, 3);
  heap_insert(maxh, 4);
  heap_insert(maxh, 5);
  heap_insert(maxh, 6);
  heap_insert(maxh, 7);
  while (heap_size(maxh) > 0) {
    int ret;
    heap_remove(maxh, &ret);
    printf("%d\n", ret);
  }
  heap_free(maxh);

  printf("Min Heap:\n");
  Heap* minh = heap_create(0, false);
  heap_insert(minh, 1);
  heap_insert(minh, 2);
  heap_insert(minh, 3);
  heap_insert(minh, 4);
  heap_insert(minh, 5);
  heap_insert(minh, 6);
  heap_insert(minh, 7);
  while (heap_size(minh) > 0) {
    int ret;
    heap_remove(minh, &ret);
    printf("%d\n", ret);
  }
  heap_free(minh);

  return 0;
}
