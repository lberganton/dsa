#include "bstree.h"
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define QLEN 1024

typedef struct Node {
  int val;
  size_t height;
  struct Node *left;
  struct Node *right;
} Node;

struct AVL {
  Node *root;
};

AVL* avl_create(void) {
  AVL *new = (AVL*) malloc(sizeof(AVL));
  if (new != NULL) {
    new->root = NULL;
  }
  return new;
}

static inline size_t height(Node *node) {
  if (node == NULL) {
    return 0;
  }

  size_t h1 = node->left == NULL ? 0 : node->left->height;
  size_t h2 = node->right == NULL ? 0 : node->right->height;

  return MAX(h1, h2) + 1;
}

static inline Node* LL(Node *node) {
  Node *right = node->right;

  node->right = right->left;
  right->left = node;

  node->height = height(node);
  return right;
}

static inline Node* RR(Node *node) {
  Node *left = node->left;

  node->left = left->right;
  left->right = node;

  node->height = height(node);
  return left;
}

static inline int balance_factor(Node *node) {
  return (int) height(node->left) - height(node->right);
}

static inline Node* balance(Node *node) {
  if (node == NULL) {
    return NULL;
  }

  if (balance_factor(node) > 1) {
    if (balance_factor(node->left) < 0) {
      node->left = LL(node->left);
    }
    node = RR(node);
  }
  else if (balance_factor(node) < -1) {
    if (balance_factor(node->right) > 0) {
      node->right = RR(node->right);
    }
    node = LL(node);
  }

  node->height = height(node);
  return node;
}

static inline Node* node_create(int val) {
  Node *new = (Node*) malloc(sizeof(Node));
  if (new != NULL) {
    new->val = val;
    new->height = 1;
    new->left = new->right = NULL;
  }
  return new;
}

static Node* insert(Node *node, int val) {
  if (node == NULL) {
    return node_create(val);
  }

  if (val < node->val) {
    node->left = insert(node->left, val);
  }
  else if (val > node->val) {
    node->right = insert(node->right, val);
  }

  return balance(node);
}

void avl_insert(AVL *avl, int val) {
  avl->root = insert(avl->root, val);
}

static Node* remove(Node *root, int val) {
  if (root == NULL) {
    return NULL;
  }

  if (val < root->val) {
    root->left = remove(root->left, val);
    return balance(root);
  }
  if (val > root->val) {
    root->right = remove(root->right, val);
    return balance(root);
  }

  if (root->left == NULL || root->right == NULL) {
    Node *tmp = root->left == NULL ? root->right : root->left;
    free(root);
    return tmp;
  }

  Node *n = root->left;
  while (n->right != NULL) {
    n = n->right;
  }

  root->val = n->val;
  root->left = remove(root->left, n->val);
  return balance(root);
}

void avl_remove(AVL *avl, int val) {
  avl->root = remove(avl->root, val);
}

bool avl_search(AVL *avl, int val) {
  Node *n = avl->root;
  while (n != NULL) {
    if (val == n->val) {
      return true;
    }
    n = val < n->val ? n->left : n->right;
  }
  return false;
}

static void node_free(Node *node) {
  if (node == NULL) {
    return;
  }
  node_free(node->left);
  node_free(node->right);
  free(node);
}

void avl_free(AVL *avl) {
  node_free(avl->root);
  free(avl);
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

void avl_traversal(AVL *avl, Order order, void (*consumer)(int val)) {
  switch (order) {
    case ORDER_PRE:
      preoder(avl->root, consumer);
      return;
    case ORDER_IN:
      inorder(avl->root, consumer);
      return;
    case ORDER_POST:
      postorder(avl->root, consumer);
      return;
    case ORDER_BFS:
      bfs(avl->root, consumer);
  }
}

static size_t nodes(Node *node) {
  return node == NULL ? 0 : nodes(node->left) + nodes(node->right) + 1;
}

size_t avl_nodes(AVL *avl) {
  return nodes(avl->root);
}

static size_t levels(Node *node, size_t level) {
  return node == NULL ? 0 : MAX(levels(node->left, level + 1), levels(node->right, level + 1));
}

size_t avl_levels(AVL *avl) {
  return levels(avl->root, 0);
}
