public class MergeSort {
    public static void sort(int[] array) {
        sort(array, 0, array.length - 1);
    }

    private static void sort(int[] array, int low, int high) {
        int length = high - low + 1;

        if (length <= 1) {
            return;
        }

        int mid = (low + high) / 2;
        sort(array, low, mid);
        sort(array, mid + 1, high);

        int left = low;
        int right = mid + 1;

        int[] sorted = new int[length];
        int i = 0;

        while (left <= mid && right <= high) {
            if (array[left] < array[right]) {
                sorted[i++] = array[left++];
            }
            else {
                sorted[i++] = array[right++];
            }
        }

        while (left <= mid) {
            sorted[i++] = array[left++];
        }
        while (right <= high) {
            sorted[i++] = array[right++];
        }

        System.arraycopy(sorted, 0, array, low, length);
    }
}
