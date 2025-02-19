import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Stack;
import java.util.function.Consumer;

public class AVL implements BSTree {
    private Node root;

    public AVL() {
        this.root = null;
    }

    @Override
    public boolean equals(Object obj) {
        return this == obj || (obj instanceof AVL t && equals(root, t.root));
    }

    private boolean equals(Node t1, Node t2) {
        if (t1 == null || t2 == null) {
            return t1 == t2;
        }
        return t1.val == t2.val && equals(t1.left, t2.left) && equals(t1.right, t2.right);
    }

    @Override
    public String toString() {
        return buildList(root, Order.BFS).toString();
    }

    private List<Integer> buildList(Node root, Order order) {
        List<Integer> list = new ArrayList<>();

        if (root == null) {
            return list;
        }

        switch (order) {
            case PRE -> {
                Stack<Node> stack = new Stack<>();
                stack.push(root);
                while (!stack.isEmpty()) {
                    Node n = stack.pop();
                    list.add(n.val);

                    if (n.right != null) {
                        stack.push(n.right);
                    }
                    if (n.left != null) {
                        stack.push(n.left);
                    }
                }
            }
            case IN -> {
                Stack<Node> stack = new Stack<>();
                Node n = root;
                while (n != null || !stack.isEmpty()) {
                    while (n != null) {
                        stack.push(n);
                        n = n.left;
                    }
                    n = stack.pop();
                    list.add(n.val);
                    n = n.right;
                }
            }
            case POST -> {
                Stack<Node> stack = new Stack<>();
                stack.push(root);
                while (!stack.isEmpty()) {
                    Node n = stack.pop();
                    list.addFirst(n.val);

                    if (n.left != null) {
                        stack.push(n.left);
                    }
                    if (n.right != null) {
                        stack.push(n.right);
                    }
                }
            }
            case BFS -> {
                Deque<Node> deque = new ArrayDeque<>();
                deque.add(root);
                while (!deque.isEmpty()) {
                    Node n = deque.removeFirst();
                    list.add(n.val);
                    if (n.left != null) {
                        deque.add(n.left);
                    }
                    if (n.right != null) {
                        deque.add(n.right);
                    }
                }
            }
        }

        return list;
    }

    @Override
    public void traversal(Order order, Consumer<Integer> consumer) {
        buildList(root, order).forEach(consumer);
    }

    private int height(Node node) {
        if (node == null) {
            return 0;
        }

        int h1 = node.left == null ? 0 : node.left.height;
        int h2 = node.right == null ? 0 : node.right.height;

        return Math.max(h1, h2) + 1;
    }

    private Node LL(Node node) {
        Node right = node.right;

        node.right = right.left;
        right.left = node;

        node.height = height(node);
        return right;
    }

    private Node RR(Node node) {
        Node left = node.left;

        node.left = left.right;
        left.right = node;

        node.height = height(node);
        return left;
    }

    private int balance_factor(Node node) {
        return node == null ? 0 : height(node.left) - height(node.right);
    }

    private Node balance(Node node) {
        if (node == null) {
            return null;
        }

        if (balance_factor(node) > 1) {
            if (balance_factor(node.left) < 0) {
                node.left = LL(node.left);
            }
            node = RR(node);
        }
        if (balance_factor(node) < -1) {
            if (balance_factor(node.right) > 0) {
                node.right = RR(node.right);
            }
            node = LL(node);
        }

        node.height = height(node);
        return node;
    }

    @Override
    public void insert(int val) {
        root = insert(root, val);
    }

    private Node insert(Node root, int val) {
        if (root == null) {
            return new Node(val);
        }

        if (val < root.val) {
            root.left = insert(root.left, val);
        }
        if (val > root.val) {
            root.right = insert(root.right, val);
        }

        return balance(root);
    }

    @Override
    public int levels() {
        return levels(root, 0);
    }

    private int levels(Node root, int total) {
        return root == null ? total : Math.max(levels(root.left, total + 1), levels(root.right, total + 1));
    }

    @Override
    public int nodes() {
        return nodes(root, 0);
    }

    private int nodes(Node root, int total) {
        return root == null ? 0 : nodes(root.left, total) + nodes(root.right, total) + 1;
    }

    @Override
    public void remove(int val) {
        root = remove(root, val);
    }

    private Node remove(Node root, int val) {
        if (root == null) {
            throw new NoSuchElementException(String.valueOf(val));
        }

        if (val < root.val) {
            root.left = remove(root.left, val);
            return balance(root);
        }
        if (val > root.val) {
            root.right = remove(root.right, val);
            return balance(root);
        }

        if (root.left == null) {
            root = root.right;
            return root;
        }
        if (root.right == null) {
            root = root.left;
            return root;
        }

        Node n = root.left;
        while (n.right != null) {
            n = n.right;
        }

        root.val = n.val;
        root.left = remove(root.left, n.val);
        return balance(root);
    }

    @Override
    public boolean search(int val) {
        Node n = root;

        while (n != null) {
            if (val == n.val) {
                return true;
            }
            n = val < n.val ? n.left : n.right;
        }

        return false;
    }

    private static class Node {
        int val;
        Node left;
        Node right;
        int height;

        Node(int val, Node left, Node right) {
            this.val = val;
            this.left = left;
            this.right = right;
            this.height = 1;
        }

        Node(int val) {
            this(val, null, null);
        }
    }
}
