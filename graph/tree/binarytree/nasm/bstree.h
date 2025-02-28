#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct UBSTree UBSTree;
typedef struct AVL AVL;

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

AVL*      avl_create(void);
void      avl_insert(AVL *avl, int val);
void      avl_remove(AVL *avl, int val);
bool      avl_search(AVL *avl, int val);
void      avl_free(AVL *avl);
void      avl_traversal(AVL *avl, Order order, void (*consumer)(int val));
size_t    avl_nodes(AVL *avl);
size_t    avl_levels(AVL *avl);

#endif
