public class SelectionSort {
    public static void sort(int[] array) {
        for (int i = 0; i < array.length; i++) {
            int minor = i;

            for (int j = i + 1; j < array.length; j++) {
                if (array[j] < array[minor]) {
                    minor = j;
                }
            }

            Utils.swap(array, i, minor);
        }
    }
}
