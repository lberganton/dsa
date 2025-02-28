import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;
import java.util.OptionalInt;
import java.util.function.IntBinaryOperator;
import java.util.function.IntConsumer;
import java.util.function.IntPredicate;
import java.util.function.IntUnaryOperator;

public class ArrayList implements List {
    private static final int INITIAL_CAPACITY = 16;
    private static final int INSERTION_SORT_MIN = 16;

    private int[] array;
    private int elements;

    public ArrayList(int initialCapacity) {
        if (initialCapacity <= 0) {
            throw new IllegalArgumentException("Invalid initial capacity: " + String.valueOf(initialCapacity));
        }
        this.array = new int[initialCapacity];
        this.elements = 0;
    }

    public ArrayList() {
        this(INITIAL_CAPACITY);
    }

    @Override
    public void insert(int val, int index) {
        if (index > elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }

        if (elements == array.length) {
            int[] newArray = new int[array.length * 2];
            System.arraycopy(array, 0, newArray, 0, array.length);
            array = newArray;
        }

        for (int i = elements; i > index; i--) {
            array[i] = array[i - 1];
        }

        array[index] = val;
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

    @Override
    public int remove(int index) {
        if (index >= elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }

        int val = array[index];

        for (int i = index + 1; i < elements; i++) {
            array[i - 1] = array[i];
        }

        elements--;
        return val;
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
        array[index] = val;
    }

    @Override
    public int get(int index) {
        if (index >= elements) {
            throw new IndexOutOfBoundsException(String.valueOf(index));
        }
        return array[index];
    }

    @Override
    public OptionalInt max() {
        if (elements == 0) {
            return OptionalInt.empty();
        }

        int val = array[0];

        for (int i = 1; i < elements; i++) {
            if (array[i] > val) {
                val = array[i];
            }
        }

        return OptionalInt.of(val);
    }

    @Override
    public OptionalInt min() {
        if (elements == 0) {
            return OptionalInt.empty();
        }

        int val = array[0];

        for (int i = 1; i < elements; i++) {
            if (array[i] < val) {
                val = array[i];
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

        int accumulator = identity;
        for (int i : this) {
            accumulator = function.applyAsInt(accumulator, i);
        }

        return OptionalInt.of(accumulator);
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

        for (; start <= end; start++) {
            if (val == array[start]) {
                return start;
            }
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

        for (; end >= start; end--) {
            if (val == array[end]) {
                return end;
            }
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
        ListIterator<Integer> itr = listIterator();
        while (itr.hasNext()) {
            if (!predicate.test(itr.next())) {
                itr.remove();
            }
        }
    }

    @Override
    public void map(IntUnaryOperator function) {
        for (int i = 0; i < elements; i++) {
            array[i] = function.applyAsInt(array[i]);
        }
    }

    @Override
    public void forEach(IntConsumer consumer) {
        for (int i : this) {
            consumer.accept(i);
        }
    }

    private void introSort(int low, int high, int level) {
        if (low >= high) {
            return;
        }

        int length = high - low + 1;

        if (length <= INSERTION_SORT_MIN) {
            insertionSort(low, high);
        }
        else if (level == 0) {
            heapSort(low, high);
        }
        else {
            int pivot = quickSort(low, high);
            introSort(low, pivot - 1, level - 1);
            introSort(pivot + 1, high, level - 1);
        }
    }

    private void insertionSort(int low, int high) {
        for (int i = low; i <= high; i++) {
            int val = array[i];
            int j = i - 1;

            while (j >= low && array[j] > val) {
                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = val;
        }
    }

    private int quickSort(int low, int high) {
        int pivot = array[high];
        int pos = low;

        for (int i = low; i < high; i++) {
            if (array[i] < pivot) {
                Utils.swap(array, pos, i);
                pos++;
            }
        }

        Utils.swap(array, pos, high);
        return pos;
    }

    private void siftDown(int high, int i) {
        int major = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < high && array[left] > array[major]) {
            major = left;
        }
        if (right < high && array[right] > array[major]) {
            major = right;
        }

        if (i != major) {
            Utils.swap(array, i, major);
            siftDown(high, major);
        }
    }

    private void heapSort(int low, int high) {
        int length = high - low;

        for (int i = low + (length / 2) - 1; i >= low; i--) {
            siftDown(high, i);
        }

        int i = high;
        while (i >= low) {
            Utils.swap(array, low, i);
            siftDown(i, low);
            i--;
        }
    }

    @Override
    public void sort() {
        introSort(0, elements - 1, (int) (Math.log(elements) / Math.log(2)));
    }

    @Override
    public void reverse() {
        if (elements <= 1) {
            return;
        }

        for (int i = 0; i < elements / 2; i++) {
            int tmp = array[i];
            array[i] = array[elements - i - 1];
            array[elements - i - 1] = tmp;
        }
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
        if (!(obj instanceof ArrayList l) || elements != l.elements) {
            return false;
        }

        ArrayList other = (ArrayList) obj;
        for (int i = 0; i < elements; i++) {
            if (array[i] != other.array[i]) {
                return false;
            }
        }

        return true;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder(elements * 2);
        s.append('[');

        for (int i = 0; i < elements; i++) {
            s.append(array[i]);
            if (i < elements - 1) {
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

    public ListIterator<Integer> listIterator() {
        return new ListItr();
    }

    private class Itr implements Iterator<Integer> {
        int cursor = -1;
        int lastReturn = -1;

        @Override
        public boolean hasNext() {
            return cursor + 1 < ArrayList.this.elements;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            cursor++;
            lastReturn = cursor;
            return ArrayList.this.array[cursor];
        }

        @Override
        public void remove() {
            if (lastReturn < 0) {
                throw new IllegalStateException();
            }
            ArrayList.this.remove(lastReturn);
            lastReturn = -1;
            cursor--;
        }
    }

    private class ListItr implements ListIterator<Integer> {
        int cursor = -1;
        int lastReturn = -1;

        @Override
        public boolean hasNext() {
            return cursor + 1 < ArrayList.this.elements;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            cursor++;
            lastReturn = cursor;
            return ArrayList.this.array[cursor];
        }

        @Override
        public boolean hasPrevious() {
            return cursor >= 0;
        }

        @Override
        public Integer previous() {
            if (!hasPrevious()) {
                throw new NoSuchElementException();
            }
            cursor--;
            lastReturn = cursor;
            return ArrayList.this.array[cursor];
        }

        @Override
        public int nextIndex() {
            return cursor + 1;
        }

        @Override
        public int previousIndex() {
            return cursor;
        }

        @Override
        public void remove() {
            if (lastReturn < 0) {
                throw new IllegalStateException();
            }
            ArrayList.this.remove(lastReturn);
            lastReturn = -1;
            cursor--;
        }

        @Override
        public void set(Integer e) {
            if (lastReturn < 0) {
                throw new IllegalStateException();
            }
            ArrayList.this.array[lastReturn] = e;
        }

        @Override
        public void add(Integer e) {
            ArrayList.this.insert(e, cursor + 1);
            cursor++;
        }
    }
}
