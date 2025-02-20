#include "bstree.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  printf("UnbalancedBSTree:\n");
  UnbalancedBSTree *bstree = unbalancedbstree_create();
  unbalancedbstree_insert(bstree, 1);
  unbalancedbstree_insert(bstree, 2);
  unbalancedbstree_insert(bstree, 3);
  unbalancedbstree_insert(bstree, 4);
  unbalancedbstree_insert(bstree, 5);
  unbalancedbstree_insert(bstree, 6);
  unbalancedbstree_insert(bstree, 7);
  unbalancedbstree_remove(bstree, 3);
  unbalancedbstree_traversal(bstree, ORDER_IN, consumer);
  unbalancedbstree_free(bstree);

  printf("AVL:\n");
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
