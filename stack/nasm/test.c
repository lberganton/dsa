#include "stack.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  printf("ArrayStack:\n");
  ArrayStack* as = arraystack_create(0);
  arraystack_push(as, 1);
  arraystack_push(as, 2);
  arraystack_push(as, 3);
  arraystack_push(as, 4);
  arraystack_push(as, 5);
  arraystack_push(as, 6);
  arraystack_push(as, 7);
  arraystack_pop(as, NULL);
  arraystack_pop(as, NULL);
  arraystack_pop(as, NULL);
  arraystack_foreach(as, consumer);
  arraystack_free(as);

  printf("LinkedStack:\n");
  LinkedStack* ls = linkedstack_create();
  linkedstack_push(ls, 1);
  linkedstack_push(ls, 2);
  linkedstack_push(ls, 3);
  linkedstack_push(ls, 4);
  linkedstack_push(ls, 5);
  linkedstack_push(ls, 6);
  linkedstack_push(ls, 7);
  linkedstack_pop(ls, NULL);
  linkedstack_pop(ls, NULL);
  linkedstack_pop(ls, NULL);
  linkedstack_foreach(ls, consumer);
  linkedstack_free(ls);

  return 0;
}
