#include "bstree.h"
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define QLEN 1024

typedef bool Color;
static const Color RED = true;
static const Color BLACK = false;

typedef struct Node {
  int val;
  Color color;
  struct Node *father;
  struct Node *left;
  struct Node *right;
} Node;

struct RBTree {
  Node *root;
};

RBTree* rbtree_create(void) {
  RBTree *new = (RBTree*) malloc(sizeof(RBTree));
  if (new != NULL) {
    new->root = NULL;
  }
  return new;
}

static inline bool is_left_child(Node *node) {
  return node->father->left == node;
}

static inline bool is_right_child(Node *node) {
  return node->father->right == node;
}

static void LL(RBTree *rbtree, Node *node) {
  Node *right = node->right;

  node->right = right->left;
  if (node->right != NULL) {
    node->right->father = node;
  }

  right->father = node->father;

  if (node == rbtree->root) {
    rbtree->root = right;
  }
  else if (is_left_child(node)) {
    node->father->left = right;
  }
  else {
    node->father->right = right;
  }

  right->left = node;
  node->father = right;
}

static void RR(RBTree *rbtree, Node *node) {
  Node *left = node->left;

  node->left = left->right;
  if (node->left != NULL) {
    node->left->father = node;
  }

  left->father = node->father;

  if (node == rbtree->root) {
    rbtree->root = left;
  }
  else if (is_left_child(node)) {
    node->father->left = left;
  }
  else {
    node->father->right = left;
  }

  left->right = node;
  node->father = left;
}

static void insert_fixup(RBTree *rbtree, Node *node) {
  while (node != rbtree->root && node->color == RED && node->father->color == RED) {
    Node *grandpa = node->father->father;

    if (is_left_child(node->father)) {
      Node *uncle = grandpa->right;

      if (uncle != NULL && uncle->color == RED) {
        grandpa->color = RED;
        uncle->color = BLACK;
        node->father->color = BLACK;
        node = grandpa;
      }
      else {
        if (is_right_child(node)) {
          LL(rbtree, node->father);
          node = node->left;
        }
        RR(rbtree, grandpa);
        grandpa->color = RED;
        node->father->color = BLACK;
        node = node->father;
      }
    }
    else {
      Node *uncle = grandpa->left;

      if (uncle != NULL && uncle->color == RED) {
        grandpa->color = RED;
        uncle->color = BLACK;
        node->father->color = BLACK;
        node = grandpa;
      }
      else {
        if (is_left_child(node)) {
          RR(rbtree, node->father);
          node = node->right;
        }
        LL(rbtree, grandpa);
        grandpa->color = RED;
        node->father->color = BLACK;
        node = node->father;
      }
    }
  }

  rbtree->root->color = BLACK;
}

static inline Node* node_create(int val, Node *father) {
  Node *new = (Node*) malloc(sizeof(Node));
  if (new != NULL) {
    new->val = val;
    new->color = RED;
    new->father = father;
    new->left = new->right = NULL;
  }
  return new;
}

void rbtree_insert(RBTree *rbtree, int val) {
  Node **node = &rbtree->root;
  Node *father = NULL;

  while (*node != NULL) {
    if (val == (*node)->val) {
      return;
    }
    father = *node;
    node = val < (*node)->val ? &(*node)->left : &(*node)->right;
  }

  *node = node_create(val, father);
  if (*node != NULL) {
    insert_fixup(rbtree, *node);
  }
}

// TODO
void rbtree_remove(RBTree *rbtree, int val);

bool rbtree_search(RBTree *rbtree, int val) {
  Node *n = rbtree->root;
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

void rbtree_free(RBTree *rbtree) {
  node_free(rbtree->root);
  free(rbtree);
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

void rbtree_traversal(RBTree *rbtree, Order order, void (*consumer)(int val)) {
  switch (order) {
    case ORDER_PRE:
      preoder(rbtree->root, consumer);
      return;
    case ORDER_IN:
      inorder(rbtree->root, consumer);
      return;
    case ORDER_POST:
      postorder(rbtree->root, consumer);
      return;
    case ORDER_BFS:
      bfs(rbtree->root, consumer);
  }
}

static size_t nodes(Node *node) {
  return node == NULL ? 0 : nodes(node->left) + nodes(node->right) + 1;
}

size_t rbtree_nodes(RBTree *rbtree) {
  return nodes(rbtree->root);
}

static size_t levels(Node *node, size_t level) {
  return node == NULL ? level : MAX(levels(node->left, level + 1), levels(node->right, level + 1));
}

size_t rbtree_levels(RBTree *rbtree) {
  return levels(rbtree->root, 0);
}
