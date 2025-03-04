import java.util.ListIterator;
import java.util.OptionalInt;
import java.util.function.IntBinaryOperator;
import java.util.function.IntConsumer;
import java.util.function.IntPredicate;
import java.util.function.IntUnaryOperator;

public interface List extends Iterable<Integer> {
    void insert(int val, int index);

    void pushLeft(int val);

    void pushRight(int val);

    int remove(int index);

    int popLeft();

    int popRight();

    void set(int val, int index);

    int get(int index);

    OptionalInt max();

    OptionalInt min();

    OptionalInt reduce(IntBinaryOperator function);

    OptionalInt reduce(int identity, IntBinaryOperator function);

    int findFirst(int val);

    int findFirst(int val, int start, int end);

    int findLast(int val);

    int findLast(int val, int start, int end);

    boolean anyMatch(IntPredicate predicate);

    boolean allMatch(IntPredicate predicate);

    void filter(IntPredicate predicate);

    void map(IntUnaryOperator function);

    void forEach(IntConsumer consumer);

    void sort();

    void reverse();

    int size();

    ListIterator<Integer> listIterator();
}
