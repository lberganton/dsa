import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.function.Consumer;

public class LinkedStack implements Stack {
    private Node top = null;
    private int elements = 0;

    @Override
    public Iterator<Integer> iterator() {
        return new Itr();
    }

    @Override
    public void push(int val) {
        elements++;
        top = new Node(val, top);
    }

    @Override
    public int pop() {
        if (elements == 0) {
            throw new NoSuchElementException();
        }
        elements--;
        int val = top.val;
        top = top.next;
        return val;
    }

    @Override
    public int peek() {
        if (elements == 0) {
            throw new NoSuchElementException();
        }
        return top.val;
    }

    @Override
    public int size() {
        return elements;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof Stack s) || size() != s.size()) {
            return false;
        }

        Iterator<Integer> iterator = s.iterator();
        for (int i : this) {
            if (i != iterator.next()) {
                return false;
            }
        }

        return true;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder(elements * 2);
        s.append('[');

        Iterator<Integer> iterator = iterator();
        while (iterator.hasNext()) {
            s.append(iterator.next());
            if (iterator.hasNext()) {
                s.append(", ");
            }
        }

        s.append(']');
        return s.toString();
    }

    @Override
    public void forEach(Consumer<? super Integer> action) {
        for (int i : this) {
            action.accept(i);
        }
    }

    private static class Node {
        int val;
        Node next;

        Node(int val, Node next) {
            this.val = val;
            this.next = next;
        }
    }

    private class Itr implements Iterator<Integer> {
        Node cursor = top;

        @Override
        public boolean hasNext() {
            return cursor != null;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            int val = cursor.val;
            cursor = cursor.next;
            return val;
        }
    }
}
