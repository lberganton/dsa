#include "bstree.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  AVL *avl = avl_create();

  avl_insert(avl, 1);
  avl_insert(avl, 2);
  avl_insert(avl, 3);
  avl_insert(avl, 4);
  avl_insert(avl, 5);
  avl_insert(avl, 6);
  avl_insert(avl, 7);

  avl_remove(avl, 3);

  avl_traversal(avl, ORDER_IN, consumer);

  avl_free(avl);
  return 0;
}
