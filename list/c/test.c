#include "list.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  printf("ArrayList:\n");
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

  printf("LinkedList:\n");
  LinkedList* ll = linkedlist_create();

  linkedlist_pushright(ll, 7);
  linkedlist_pushright(ll, 4);
  linkedlist_pushright(ll, 5);
  linkedlist_pushright(ll, 3);
  linkedlist_pushright(ll, 2);
  linkedlist_pushright(ll, 1);
  linkedlist_pushright(ll, 6);

  linkedlist_sort(ll);
  linkedlist_reverse(ll);
  linkedlist_foreach(ll, consumer);

  linkedlist_free(ll);
  return 0;
}
