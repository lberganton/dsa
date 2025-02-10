public class QuickSort {
    public static void sort(int[] array) {
        sort(array, 0, array.length - 1);
    }

    private static void sort(int[] array, int low, int high) {
        if (low >= high) {
            return;
        }

        int pivot = array[high];
        int pos = low;

        for (int i = low; i < high; i++) {
            if (array[i] < pivot) {
                Utils.swap(array, pos, i);
                pos++;
            }
        }

        Utils.swap(array, pos, high);

        sort(array, low, pos - 1);
        sort(array, pos + 1, high);
    }
}
