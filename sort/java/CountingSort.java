import java.util.Arrays;

public class CountingSort {
    public static void sort(int[] array) {
        int max = Arrays.stream(array)
                .max()
                .getAsInt();

        int[] countArray = new int[max + 1];
        for (int i = 0; i < array.length; i++) {
            countArray[array[i]]++;
        }

        for (int i = 1; i < countArray.length; i++) {
            countArray[i] += countArray[i - 1];
        }

        int[] outputArray = new int[array.length];
        for (int i = array.length - 1; i >= 0; i--) {
            countArray[array[i]]--;
            outputArray[countArray[array[i]]] = array[i];
        }

        System.arraycopy(outputArray, 0, array, 0, array.length);
    }
}
