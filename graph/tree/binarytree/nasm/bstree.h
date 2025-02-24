#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct UBSTree UBSTree;

typedef enum Order {
  ORDER_PRE, ORDER_IN, ORDER_POST, ORDER_BFS
} Order;

UBSTree*  ubstree_create(void);
void      ubstree_insert(UBSTree *bstree, int val);
void      ubstree_remove(UBSTree *bstree, int val);
bool      ubstree_search(UBSTree *bstree, int val);
void      ubstree_free(UBSTree *bstree);
void      ubstree_traversal(UBSTree *bstree, Order order, void (*consumer)(int val));
size_t    ubstree_nodes(UBSTree *bstree);
size_t    ubstree_levels(UBSTree *bstree);

#endif
