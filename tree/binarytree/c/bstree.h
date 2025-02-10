#ifndef _BST_H
#define _BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct AVL AVL;

typedef enum Order {
  ORDER_PRE, ORDER_IN, ORDER_POST, ORDER_BFS
} Order;

AVL*    avl_create(void);
void    avl_insert(AVL *avl, int val);
void    avl_remove(AVL *avl, int val);
bool    avl_search(AVL *avl, int val);
void    avl_free(AVL *avl);
void    avl_traversal(AVL *avl, Order order, void (*consumer)(int val));
size_t  avl_nodes(AVL *avl);
size_t  avl_levels(AVL *avl);

#endif
