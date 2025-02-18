#include "bstree.h"
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define QLEN 1024

typedef struct Node {
  int val;
  struct Node *left;
  struct Node *right;
} Node;

struct UnbalancedBSTree {
  Node *root;
};

UnbalancedBSTree* unbalancedbstree_create(void) {
  UnbalancedBSTree *new = (UnbalancedBSTree*) malloc(sizeof(UnbalancedBSTree));
  if (new != NULL) {
    new->root = NULL;
  }
  return new;
}

static inline Node* node_create(int val) {
  Node *new = (Node*) malloc(sizeof(Node));
  if (new != NULL) {
    new->val = val;
    new->left = new->right = NULL;
  }
  return new;
}

void unbalancedbstree_insert(UnbalancedBSTree *bstree, int val) {
  Node **n = &bstree->root;

  while (*n != NULL) {
    if (val == (*n)->val) {
      return;
    }
    n = val < (*n)->val ? &(*n)->left : &(*n)->right;
  }

  *n = node_create(val);
}

void unbalancedbstree_remove(UnbalancedBSTree *bstree, int val) {
  Node **root = &bstree->root;

  while (*root == NULL || val != (*root)->val) {
    if (*root == NULL) {
      return;
    }
    root = val < (*root)->val ? &(*root)->left : &(*root)->right;
  }

  if ((*root)->left == NULL || (*root)->right == NULL) {
    Node *tmp = (*root)->left == NULL ? (*root)->right : (*root)->left;
    free(*root);
    *root = tmp;
    return;
  }

  Node **n = &(*root)->left;
  while ((*n)->right != NULL) {
    n = &(*n)->right;
  }

  (*root)->val = (*n)->val;
  Node *tmp = *n;
  *n = NULL;
  free(tmp);
}

bool unbalancedbstree_search(UnbalancedBSTree *bstree, int val);

static void node_free(Node *node) {
  if (node == NULL) {
    return;
  }
  node_free(node->left);
  node_free(node->right);
  free(node);
}

void unbalancedbstree_free(UnbalancedBSTree *bstree) {
  node_free(bstree->root);
  free(bstree);
}

static void preoder(Node *node, void (*consumer)(int val)) {
  if (node == NULL) {
    return;
  }
  consumer(node->val);
  preoder(node->left, consumer);
  preoder(node->right, consumer);
}

static void inorder(Node *node, void (*consumer)(int val)) {
  if (node == NULL) {
    return;
  }
  inorder(node->left, consumer);
  consumer(node->val);
  inorder(node->right, consumer);
}

static void postorder(Node *node, void (*consumer)(int val)) {
  if (node == NULL) {
    return;
  }
  postorder(node->left, consumer);
  postorder(node->right, consumer);
  consumer(node->val);
}

static void bfs(Node *root, void (*consumer)(int val)) {
  if (root == NULL) {
    return;
  }

  Node *queue[QLEN] = {root};
  size_t begin = 0;
  size_t len = 1;

  while (len > 0) {
    Node *node = queue[begin];
    len--;

    consumer(node->val);

    if (len < QLEN && node->left != NULL) {
      size_t index = (begin + len + 1) % QLEN;
      queue[index] = node->left;
      len++;
    }
    if (len < QLEN && node->right != NULL) {
      size_t index = (begin + len + 1) % QLEN;
      queue[index] = node->right;
      len++;
    }

    begin = (begin + 1) % QLEN;
  }
}

void unbalancedbstree_traversal(UnbalancedBSTree *bstree, Order order, void (*consumer)(int val)) {
  switch (order) {
    case ORDER_PRE:
      preoder(bstree->root, consumer);
      return;
    case ORDER_IN:
      inorder(bstree->root, consumer);
      return;
    case ORDER_POST:
      postorder(bstree->root, consumer);
      return;
    case ORDER_BFS:
      bfs(bstree->root, consumer);
  }
}

static size_t nodes(Node *node) {
  return node == NULL ? 0 : nodes(node->left) + nodes(node->right) + 1;
}

size_t unbalancedbstree_nodes(UnbalancedBSTree *bstree) {
  return nodes(bstree->root);
}

static size_t levels(Node *node, size_t level) {
  return node == NULL ? level : MAX(levels(node->left, level + 1), levels(node->right, level + 1));
}

size_t unbalancedbstree_levels(UnbalancedBSTree *bstree) {
  return levels(bstree->root, 0);
}
