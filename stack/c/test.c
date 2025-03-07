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
  return 0;
}
