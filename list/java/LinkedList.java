import java.util.Arrays;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;
import java.util.OptionalInt;
import java.util.function.Consumer;
import java.util.function.IntBinaryOperator;
import java.util.function.IntConsumer;
import java.util.function.IntPredicate;
import java.util.function.IntUnaryOperator;

public class LinkedList implements List {
    private Node head = null;
    private Node tail = null;
    private int elements = 0;

    @Override
    public Iterator<Integer> iterator() {
        return new Itr();
    }

    @Override
    public ListIterator<Integer> listIterator() {
        return new ListItr();
    }

    private Node getNode(int index) {
        if (index >= elements) {
            return null;
        }

        Node node;
        if (index < elements / 2) {
            node = head;
            for (int i = 0; i < index; i++) {
                node = node.next;
            }
        }
        else {
            node = tail;
            for (int i = elements - 1; i > index; i--) {
                node = node.back;
            }
        }

        return node;
    }

    private void insert(int val, Node node) {
        Node n = new Node(val);

        n.back = node.back;
        n.next = node;

        if (node == head) {
            head.back = n;
        }
        if (node == tail) {
            tail.next = n;
        }

        if (node.back != null) {
            node.back.next = n;
        }
        if (node.next != null) {
            node.next.back = n;
        }

        elements++;
    }

    @Override
    public void insert(int val, int index) {
        if (index > elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }

        Node node = new Node(val);

        if (index == elements) {
            if (elements > 0) {
                tail.next = node;
            }
            node.back = tail;
            tail = node;
        }
        else {
            Node pos = getNode(index);
            node.back = pos.back;
            node.next = pos;
            pos.back = node;
        }

        if (index == 0) {
            head = node;
        }

        elements++;
    }

    @Override
    public void pushLeft(int val) {
        insert(val, 0);
    }

    @Override
    public void pushRight(int val) {
        insert(val, elements);
    }

    private void remove(Node node) {
        if (node == head) {
            head = head.next;
        }
        if (node == tail) {
            tail = tail.back;
        }

        if (node.back != null) {
            node.back.next = node.next;
        }
        if (node.next != null) {
            node.next.back = node.back;
        }
    }

    @Override
    public int remove(int index) {
        if (index >= elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }

        Node node = getNode(index);
        remove(node);
        elements--;

        return node.val;
    }

    @Override
    public int popLeft() {
        return remove(0);
    }

    @Override
    public int popRight() {
        return remove(elements - 1);
    }

    @Override
    public void set(int val, int index) {
        if (index >= elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }
        getNode(index).val = val;
    }

    @Override
    public int get(int index) {
        if (index >= elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }
        return getNode(index).val;
    }

    @Override
    public OptionalInt max() {
        if (elements == 0) {
            return OptionalInt.empty();
        }

        int val = head.val;
        for (Node n = head.next; n != null; n = n.next) {
            if (n.val > val) {
                val = n.val;
            }
        }

        return OptionalInt.of(val);
    }

    @Override
    public OptionalInt min() {
        if (elements == 0) {
            return OptionalInt.empty();
        }

        int val = head.val;
        for (Node n = head.next; n != null; n = n.next) {
            if (n.val < val) {
                val = n.val;
            }
        }

        return OptionalInt.of(val);
    }

    @Override
    public OptionalInt reduce(IntBinaryOperator function) {
        return reduce(0, function);
    }

    @Override
    public OptionalInt reduce(int identity, IntBinaryOperator function) {
        if (elements == 0) {
            return OptionalInt.empty();
        }

        int ret = identity;
        for (int i : this) {
            ret = function.applyAsInt(ret, i);
        }

        return OptionalInt.of(ret);
    }

    @Override
    public int findFirst(int val) {
        return findFirst(val, 0, elements - 1);
    }

    @Override
    public int findFirst(int val, int start, int end) {
        if (start > end || end >= elements) {
            throw new IllegalArgumentException();
        }

        Node node = getNode(start);
        for (; start <= end; start++) {
            if (val == node.val) {
                return start;
            }
            node = node.next;
        }

        return -1;
    }

    @Override
    public int findLast(int val) {
        return findLast(val, 0, elements - 1);
    }

    @Override
    public int findLast(int val, int start, int end) {
        if (start > end || end >= elements) {
            throw new IllegalArgumentException();
        }

        Node node = getNode(end);
        for (; end >= start; end--) {
            if (val == node.val) {
                return end;
            }
            node = node.back;
        }

        return -1;
    }

    @Override
    public boolean anyMatch(IntPredicate predicate) {
        for (int i : this) {
            if (predicate.test(i)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean allMatch(IntPredicate predicate) {
        for (int i : this) {
            if (!predicate.test(i)) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void filter(IntPredicate predicate) {
        Node node = head;
        while (node != null) {
            Node tmp = node.next;
            if (!predicate.test(node.val)) {
                remove(node);
                elements--;
            }
            node = tmp;
        }
    }

    @Override
    public void map(IntUnaryOperator function) {
        for (Node n = head; n != null; n = n.next) {
            n.val = function.applyAsInt(n.val);
        }
    }

    @Override
    public void forEach(IntConsumer consumer) {
        for (int i : this) {
            consumer.accept(i);
        }
    }

    // Temporary implementation.
    @Override
    public void sort() {
        int[] array = new int[elements];

        Node node = head;
        for (int i = 0; i < elements; i++) {
            array[i] = node.val;
            node = node.next;
        }

        Arrays.sort(array);

        node = head;
        for (int i = 0; i < elements; i++) {
            node.val = array[i];
            node = node.next;
        }
    }

    @Override
    public void reverse() {
        Node tmp = head;
        head = tail;
        tail = tmp;

        Node node = tail;
        while (node != null) {
            tmp = node.next;
            node.next = node.back;
            node.back = tmp;
            node = tmp;
        }
    }

    @Override
    public void forEach(Consumer<? super Integer> action) {
        for (int i : this) {
            action.accept(i);
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof LinkedList l) || elements != l.elements) {
            return false;
        }

        Node n1 = head;
        Node n2 = ((LinkedList) obj).head;
        while (n1 != null) {
            if (n1.val != n2.val) {
                return false;
            }
            n1 = n1.next;
            n2 = n2.next;
        }

        return true;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder(elements * 2);
        s.append('[');

        for (Node n = head; n != null; n = n.next) {
            s.append(n.val);
            if (n != tail) {
                s.append(", ");
            }
        }

        s.append(']');
        return s.toString();
    }


    @Override
    public int size() {
        return elements;
    }

    private static class Node {
        int val;
        Node back;
        Node next;

        Node(int val, Node back, Node next) {
            this.val = val;
            this.back = back;
            this.next = next;
        }

        Node(int val) {
            this(val, null, null);
        }
    }

    private class Itr implements Iterator<Integer> {
        Node dummy = new Node(0, null, head);
        Node lastReturn = null;

        @Override
        public boolean hasNext() {
            return dummy.next != null;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            dummy = dummy.next;
            lastReturn = dummy;
            return dummy.val;
        }

        @Override
        public void remove() {
            if (lastReturn == null) {
                throw new IllegalStateException();
            }
            LinkedList.this.remove(lastReturn);
            lastReturn = null;
            dummy = dummy.back;
        }
    }

    private class ListItr implements ListIterator<Integer> {
        int index = -1;
        Node dummy = new Node(0, null, head);
        Node lastReturn = null;

        @Override
        public boolean hasNext() {
            return dummy.next != null;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            index++;
            dummy = dummy.next;
            lastReturn = dummy;
            return dummy.val;
        }

        @Override
        public boolean hasPrevious() {
            return dummy.back != null;
        }

        @Override
        public Integer previous() {
            if (!hasPrevious()) {
                throw new NoSuchElementException();
            }
            index--;
            dummy = dummy.back;
            lastReturn = dummy;
            return dummy.val;
        }

        @Override
        public int nextIndex() {
            return index + 1;
        }

        @Override
        public int previousIndex() {
            return index;
        }

        @Override
        public void remove() {
            if (lastReturn != null) {
                throw new IllegalStateException();
            }
            LinkedList.this.remove(lastReturn);
            lastReturn = null;
            dummy = dummy.back;
            index--;
        }

        @Override
        public void set(Integer e) {
            if (lastReturn != null) {
                throw new IllegalStateException();
            }
            lastReturn.val = e;
        }

        @Override
        public void add(Integer e) {
            if (index == -1) {
                LinkedList.this.insert(e, 0);
                dummy = LinkedList.this.head;
            }
            else if (index + 1 == LinkedList.this.elements) {
                LinkedList.this.insert(e, elements);
                dummy = LinkedList.this.tail;
            }
            else {
                dummy = dummy.next;
                LinkedList.this.insert(e, dummy);
                dummy = dummy.back;
            }
            index++;
        }
    }
}
