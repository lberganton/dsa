import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Heap implements PQueue {
    private static final int INITIAL_CAPACITY = 16;

    private int[] array;
    private int elements;
    private Comparator<Integer> comparator;

    public Heap(int initialCapacity, Comparator<Integer> comparator) {
        if (initialCapacity <= 0) {
            throw new IllegalArgumentException("Invalid initial capacity: " + String.valueOf(initialCapacity));
        }
        this.array = new int[initialCapacity];
        this.elements = 0;
        this.comparator = comparator;
    }

    public Heap(Comparator<Integer> comparator) {
        this(INITIAL_CAPACITY, comparator);
    }

    public Heap(int initialCapacity) {
        this(initialCapacity, Integer::compareTo);
    }

    public Heap() {
        this(INITIAL_CAPACITY, Integer::compareTo);
    }

    private void siftUp(int i) {
        while (i > 0 && comparator.compare(array[i], array[i / 2]) > 0) {
            Utils.swap(array, i, i / 2);
            i /= 2;
        }
    }

    @Override
    public void insert(int val) {
        if (elements == array.length) {
            array = Arrays.copyOf(array, array.length * 2);
        }
        array[elements++] = val;
        siftUp(elements - 1);
    }

    private void siftDown(int i) {
        int max = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < elements && comparator.compare(array[left], array[max]) > 0) {
            max = left;
        }
        if (right < elements && comparator.compare(array[right], array[max]) > 0) {
            max = right;
        }

        if (i != max) {
            Utils.swap(array, i, max);
            siftDown(max);
        }
    }

    @Override
    public int remove() {
        if (elements == 0) {
            throw new NoSuchElementException();
        }
        int val = array[0];
        array[0] = array[--elements];
        siftDown(0);
        return val;
    }

    @Override
    public int peek() {
        if (elements == 0) {
            throw new NoSuchElementException();
        }
        return array[0];
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
        if (!(obj instanceof PQueue h) || size() != h.size()) {
            return false;
        }

        Iterator<Integer> iterator = h.iterator();
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

        for (int i = elements - 1; i >= 0; i--) {
            s.append(array[i]);
            if (i > 0) {
                s.append(", ");
            }
        }

        s.append(']');
        return s.toString();
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Itr();
    }

    private class Itr implements Iterator<Integer> {
        int cursor = -1;

        @Override
        public boolean hasNext() {
            return cursor + 1 < Heap.this.elements;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            return Heap.this.array[++cursor];
        }
    }
}
