#include "bstree.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  printf("UBSTree:\n");
  UBSTree *bstree = ubstree_create();

  ubstree_insert(bstree, 1);
  ubstree_insert(bstree, 2);
  ubstree_insert(bstree, 3);
  ubstree_insert(bstree, 4);
  ubstree_insert(bstree, 5);
  ubstree_insert(bstree, 6);
  ubstree_insert(bstree, 7);
  ubstree_remove(bstree, 3);
  printf("nodes(): %zu\n", ubstree_nodes(bstree));
  printf("levels(): %zu\n", ubstree_levels(bstree));
  printf("search(3): %d\n", ubstree_search(bstree, 3));
  printf("search(4): %d\n", ubstree_search(bstree, 4));
  ubstree_traversal(bstree, ORDER_IN, consumer);
  ubstree_free(bstree);
  return 0;
}
