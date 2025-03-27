import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.function.Consumer;

public class RBTree implements BSTree {
    private static final Node NIL = new Node(0, Color.BLACK, null, null, null);

    private Node root = NIL;

    private void LL(Node node) {
        Node right = node.right;

        node.right = right.left;
        if (node.right != NIL) {
            node.right.father = node;
        }

        right.father = node.father;

        if (node == root) {
            root = right;
        }
        else if (node.isLeftChild()) {
            node.father.left = right;
        }
        else {
            node.father.right = right;
        }

        right.left = node;
        node.father = right;
    }

    private void RR(Node node) {
        Node left = node.left;

        node.left = left.right;
        if (node.left != NIL) {
            node.left.father = node;
        }

        left.father = node.father;

        if (node == root) {
            root = left;
        }
        else if (node.isLeftChild()) {
            node.father.left = left;
        }
        else {
            node.father.right = left;
        }

        left.right = node;
        node.father = left;
    }

    private void balanceInsert(Node node) {
        while (node != root && node.color == Color.RED && node.father.color == Color.RED) {
            if (node.uncle().color == Color.RED) {
                node.grandpa().color = Color.RED;
                node.uncle().color = Color.BLACK;
                node.father.color = Color.BLACK;
                node = node.grandpa();
            }
            else {
                if (node.father.isLeftChild()) {
                    if (node.isRightChild()) {
                        LL(node.father);
                        node = node.left;
                    }
                    RR(node.grandpa());
                }
                else {
                    if (node.isLeftChild()) {
                        RR(node.father);
                        node = node.right;
                    }
                    LL(node.grandpa());
                }
                node.father.color = Color.BLACK;
                node.brother().color = Color.RED;
                node = node.father;
            }
        }

        root.color = Color.BLACK;
    }

    @Override
    public void insert(int val) {
        Node newNode = new Node(val);

        Node node = root;
        Node father = NIL;

        while (node != NIL) {
            if (val == node.val) {
                return;
            }
            father = node;
            node = val < node.val ? node.left : node.right;
        }

        newNode.father = father;
        if (father == NIL) {
            root = newNode;
        }
        else if (val < father.val) {
            father.left = newNode;
        }
        else {
            father.right = newNode;
        }

        balanceInsert(newNode);
    }

    @Override
    public void remove(int val) {
        // TODO
    }

    @Override
    public boolean search(int val) {
        Node n = root;

        while (n != NIL) {
            if (val == n.val) {
                return true;
            }
            n = val < n.val ? n.left : n.right;
        }

        return false;
    }

    @Override
    public int levels() {
        return levels(root, 0);
    }

    private int levels(Node root, int total) {
        return root == NIL ? total : Math.max(levels(root.left, total + 1), levels(root.right, total + 1));
    }

    @Override
    public int nodes() {
        return nodes(root, 0);
    }

    private int nodes(Node root, int total) {
        return root == NIL ? 0 : nodes(root.left, total) + nodes(root.right, total) + 1;
    }

    private List<Integer> buildList(Node root, Order order) {
        List<Integer> list = new ArrayList<>();

        if (root == NIL) {
            return list;
        }

        switch (order) {
            case PRE -> {
                Deque<Node> stack = new ArrayDeque<>();
                stack.push(root);
                while (!stack.isEmpty()) {
                    Node n = stack.pop();
                    list.add(n.val);

                    if (n.right != NIL) {
                        stack.push(n.right);
                    }
                    if (n.left != NIL) {
                        stack.push(n.left);
                    }
                }
            }
            case IN -> {
                Deque<Node> stack = new ArrayDeque<>();
                Node n = root;
                while (n != NIL || !stack.isEmpty()) {
                    while (n != NIL) {
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

                    if (n.left != NIL) {
                        stack.push(n.left);
                    }
                    if (n.right != NIL) {
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
                    if (n.left != NIL) {
                        deque.add(n.left);
                    }
                    if (n.right != NIL) {
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

    @Override
    public boolean equals(Object obj) {
        return this == obj || (obj instanceof RBTree t && equals(root, t.root));
    }

    private boolean equals(Node t1, Node t2) {
        if (t1 == NIL || t2 == NIL) {
            return t1 == t2;
        }
        return t1.val == t2.val && equals(t1.left, t2.left) && equals(t1.right, t2.right);
    }

    @Override
    public String toString() {
        return buildList(root, Order.BFS).toString();
    }

    private static enum Color {
        BLACK, RED
    };

    private static class Node {
        int val;
        Color color;
        Node father;
        Node left;
        Node right;

        Node(int val, Color color, Node father, Node left, Node right) {
            this.val = val;
            this.color = color;
            this.father = father;
            this.left = left;
            this.right = right;
        }

        Node(int val) {
            this(val, Color.RED, NIL, NIL, NIL);
        }

        boolean isLeftChild() {
            if (father == NIL) {
                throw new NoSuchElementException();
            }
            return father.left == this;
        }

        boolean isRightChild() {
            if (father == NIL) {
                throw new NoSuchElementException();
            }
            return father.right == this;
        }

        Node brother() {
            if (father == NIL) {
                throw new NoSuchElementException();
            }
            return isLeftChild() ? father.right : father.left;
        }

        Node uncle() {
            Node grandpa = grandpa();
            return isLeftChild() ? grandpa.right : grandpa.left;
        }

        Node grandpa() {
            if (father == NIL) {
                throw new NoSuchElementException();
            }
            return father.father;
        }
    }
}
