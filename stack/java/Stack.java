public interface Stack extends Iterable<Integer> {
    void push(int val);

    int pop();

    int peek();

    int size();
}
