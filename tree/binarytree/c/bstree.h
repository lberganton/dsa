#ifndef _BST_H
#define _BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct UnbalancedBSTree UnbalancedBSTree;
typedef struct AVL AVL;

typedef enum Order {
  ORDER_PRE, ORDER_IN, ORDER_POST, ORDER_BFS
} Order;

UnbalancedBSTree* unbalancedbstree_create(void);
void              unbalancedbstree_insert(UnbalancedBSTree *bstree, int val);
void              unbalancedbstree_remove(UnbalancedBSTree *bstree, int val);
bool              unbalancedbstree_search(UnbalancedBSTree *bstree, int val);
void              unbalancedbstree_free(UnbalancedBSTree *bstree);
void              unbalancedbstree_traversal(UnbalancedBSTree *bstree, Order order, void (*consumer)(int val));
size_t            unbalancedbstree_nodes(UnbalancedBSTree *bstree);
size_t            unbalancedbstree_levels(UnbalancedBSTree *bstree);

AVL*              avl_create(void);
void              avl_insert(AVL *avl, int val);
void              avl_remove(AVL *avl, int val);
bool              avl_search(AVL *avl, int val);
void              avl_free(AVL *avl);
void              avl_traversal(AVL *avl, Order order, void (*consumer)(int val));
size_t            avl_nodes(AVL *avl);
size_t            avl_levels(AVL *avl);

#endif
