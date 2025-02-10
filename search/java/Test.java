import java.util.Arrays;
import java.util.stream.IntStream;

public class Test {
    public static final int LEN = 5;

    public static void main(String[] args) {
        int[] array = IntStream.range(0, LEN).toArray();

        System.out.println(Arrays.asList(array));

        System.out.println("Linear (-1): " + LinearSearch.search(array, -1));
        System.out.println("Linear (0): " + LinearSearch.search(array, 0));
        System.out.println("Linear (1): " + LinearSearch.search(array, 1));
        System.out.println("Linear (2): " + LinearSearch.search(array, 2));
        System.out.println("Linear (3): " + LinearSearch.search(array, 3));
        System.out.println("Linear (4): " + LinearSearch.search(array, 4));
        System.out.println("Linear (5): " + LinearSearch.search(array, 5));

        System.out.println("Binary (-1): " + BinarySearch.search(array, -1));
        System.out.println("Binary (0): " + BinarySearch.search(array, 0));
        System.out.println("Binary (1): " + BinarySearch.search(array, 1));
        System.out.println("Binary (2): " + BinarySearch.search(array, 2));
        System.out.println("Binary (3): " + BinarySearch.search(array, 3));
        System.out.println("Binary (4): " + BinarySearch.search(array, 4));
        System.out.println("Binary (5): " + BinarySearch.search(array, 5));
    }
}
