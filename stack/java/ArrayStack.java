import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.function.Consumer;

public class ArrayStack implements Stack {
    private static final int INITIAL_CAPACITY = 16;

    private int[] array;
    private int top;

    public ArrayStack(int initialCapacity) {
        if (initialCapacity <= 0) {
            throw new IllegalArgumentException("Invalid initial capacity: " + String.valueOf(initialCapacity));
        }
        this.array = new int[initialCapacity];
        top = 0;
    }

    public ArrayStack() {
        this(INITIAL_CAPACITY);
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Itr();
    }

    @Override
    public void push(int val) {
        if (top == array.length) {
            array = Arrays.copyOf(array, array.length * 2);
        }
        array[top++] = val;
    }

    @Override
    public int pop() {
        if (top == 0) {
            throw new NoSuchElementException();
        }
        return array[--top];
    }

    @Override
    public int peek() {
        if (top == 0) {
            throw new NoSuchElementException();
        }
        return array[top - 1];
    }

    @Override
    public int size() {
        return top;
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
        StringBuilder s = new StringBuilder(top * 2);
        s.append('[');

        for (int i = top - 1; i >= 0; i--) {
            s.append(array[i]);
            if (i > 0) {
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

    private class Itr implements Iterator<Integer> {
        int cursor = top;

        @Override
        public boolean hasNext() {
            return cursor > 0;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            return ArrayStack.this.array[--cursor];
        }
    }
}
