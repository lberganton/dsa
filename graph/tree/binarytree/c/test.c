#include "bstree.h"
#include <stdio.h>

void consumer(int val) {
  printf("%d\n", val);
}

int main(void) {
  printf("UBSTree:\n");
  UBSTree *bstree = ubstree_create();

  ubstree_insert(bstree, 4);
  ubstree_insert(bstree, 2);
  ubstree_insert(bstree, 6);
  ubstree_insert(bstree, 1);
  ubstree_insert(bstree, 3);
  ubstree_insert(bstree, 5);
  ubstree_insert(bstree, 7);
  ubstree_remove(bstree, 3);
  printf("nodes(): %zu\n", ubstree_nodes(bstree));
  printf("levels(): %zu\n", ubstree_levels(bstree));
  printf("search(3): %d\n", ubstree_search(bstree, 3));
  printf("search(4): %d\n", ubstree_search(bstree, 4));
  ubstree_traversal(bstree, ORDER_BFS, consumer);
  ubstree_free(bstree);

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
  printf("nodes(): %zu\n", avl_nodes(avl));
  printf("levels(): %zu\n", avl_levels(avl));
  printf("search(3): %d\n", avl_search(avl, 3));
  printf("search(4): %d\n", avl_search(avl, 4));
  avl_traversal(avl, ORDER_BFS, consumer);
  avl_free(avl);

  return 0;
}
