#include "list.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  ArrayList* al = arraylist_create(0);

  arraylist_pushright(al, 7);
  arraylist_pushright(al, 4);
  arraylist_pushright(al, 5);
  arraylist_pushright(al, 3);
  arraylist_pushright(al, 2);
  arraylist_pushright(al, 1);
  arraylist_pushright(al, 6);

  arraylist_sort(al);
  arraylist_reverse(al);
  arraylist_foreach(al, consumer);

  arraylist_free(al);
  return 0;
}
