public class IntroSort {
    private static final int INSERTION_LENGTH = 16;

    public static void sort(int[] array) {
        sort(array, 0, array.length - 1, (int) (Math.log(array.length) / Math.log(2)));
    }

    private static void sort(int[] array, int low, int high, int level) {
        if (low >= high) {
            return;
        }

        int length = high - low + 1;

        if (length <= INSERTION_LENGTH) {
            insertionSort(array, low, high);
        }
        else if (level == 0) {
            heapSort(array, low, high);
        }
        else {
            int pivot = quicksort(array, low, high);
            sort(array, low, pivot - 1, level - 1);
            sort(array, pivot + 1, high, level - 1);
        }
    }

    private static void insertionSort(int[] array, int low, int high) {
        for (int i = low; i <= high; i++) {
            int val = array[i];
            int j = i - 1;

            while (j >= low && array[j] > val) {
                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = val;
        }
    }

    private static int quicksort(int[] array, int low, int high) {
        int pivot = array[high];
        int pos = low;

        for (int i = low; i < high; i++) {
            if (array[i] < pivot) {
                Utils.swap(array, pos, i);
                pos++;
            }
        }

        Utils.swap(array, pos, high);
        return pos;
    }

    private static void siftDown(int[] array, int high, int i) {
        int major = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < high && array[left] > array[major]) {
            major = left;
        }
        if (right < high && array[right] > array[major]) {
            major = right;
        }

        if (i != major) {
            Utils.swap(array, i, major);
            siftDown(array, high, major);
        }
    }

    private static void heapSort(int[] array, int low, int high) {
        int length = high - low;

        for (int i = low + (length / 2) - 1; i >= low; i--) {
            siftDown(array, high, i);
        }

        int i = high;
        while (i >= low) {
            Utils.swap(array, low, i);
            siftDown(array, i, low);
            i--;
        }
    }
}
