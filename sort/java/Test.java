import java.security.SecureRandom;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        SecureRandom random = new SecureRandom();
        int[] array = random.ints(10, 0, 10).toArray();

        printArray("Original", array);

        int[] tmp = array.clone();
        Arrays.sort(tmp);
        printArray("Expected", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        BubbleSort.sort(tmp);
        printArray("Bubble Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        SelectionSort.sort(tmp);
        printArray("Selection Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        InsertionSort.sort(tmp);
        printArray("Insertion Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        QuickSort.sort(tmp);
        printArray("Quick Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        MergeSort.sort(tmp);
        printArray("Merge Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        HeapSort.sort(tmp);
        printArray("Heap Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        IntroSort.sort(tmp);
        printArray("Intro Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        ShellSort.sort(tmp);
        printArray("Shell Sort", tmp);

        System.arraycopy(array, 0, tmp, 0, array.length);
        BogoSort.sort(tmp, 1000000);
        printArray("Bogo Sort", tmp);
    }

    public static void printArray(String msg, int[] array) {
        System.out.printf("%-15s: ", msg);
        for (int i = 0; i < array.length; i++) {
            if (i == 0)
                System.out.print('[');

            System.out.print(array[i]);

            if (i == array.length - 1)
                System.out.print(']');
            else
                System.out.print(',');
        }
        System.out.println();
    }
}
