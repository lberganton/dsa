public interface PQueue extends Iterable<Integer> {
    void insert(int val);

    int remove();

    int peek();

    int size();
}
