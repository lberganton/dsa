import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.function.Consumer;

public class UnbalancedBSTree implements BSTree {
    private Node root;

    public UnbalancedBSTree() {
        this.root = null;
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
        else if (val > root.val) {
            root.right = insert(root.right, val);
        }

        return root;
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
            return root;
        }
        if (val > root.val) {
            root.right = remove(root.right, val);
            return root;
        }

        if (root.left == null) {
            return root.right;
        }
        if (root.right == null) {
            return root.left;
        }

        Node n = root.left;
        while (n.right != null) {
            n = n.right;
        }

        root.val = n.val;
        root.left = remove(root.left, n.val);
        return root;
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

    @Override
    public int nodes() {
        return nodes(root);
    }

    private int nodes(Node root) {
        return root == null ? 0 : nodes(root.left) + nodes(root.right) + 1;
    }

    @Override
    public int levels() {
        return levels(root, 0);
    }

    private int levels(Node root, int total) {
        return root == null ? total : Math.max(levels(root.left, total + 1), levels(root.right, total + 1));
    }

    @Override
    public boolean equals(Object obj) {
        return this == obj || (obj instanceof UnbalancedBSTree t && equals(root, t.root));
    }

    private boolean equals(Node t1, Node t2) {
        if (t1 == null || t1 == null) {
            return t1 == t2;
        }
        return t1.val == t2.val && equals(t1.left, t2.left) && equals(t1.right, t2.right);
    }

    @Override
    public String toString() {
        return buildList(root, BSTree.Order.BFS).toString();
    }

    @Override
    public void traversal(BSTree.Order order, Consumer<Integer> consumer) {
        buildList(root, order).forEach(consumer);
    }

    private List<Integer> buildList(Node root, Order order) {
        List<Integer> list = new ArrayList<>();

        if (root == null) {
            return list;
        }

        switch (order) {
            case PRE -> {
                Deque<Node> stack = new ArrayDeque<>();
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
                Deque<Node> stack = new ArrayDeque<>();
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
                Deque<Node> stack = new ArrayDeque<>();
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

    private static class Node {
        int val;
        Node left;
        Node right;

        Node(int val, Node left, Node right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }

        Node(int val) {
            this(val, null, null);
        }
    }
}
