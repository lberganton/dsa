import java.util.function.Consumer;

public interface BSTree {
    void insert(int val);

    void remove(int val);

    boolean search(int val);

    int nodes();

    int levels();

    void traversal(Order order, Consumer<Integer> consumer);

    static enum Order {
        PRE, IN, POST, BFS
    }
}
