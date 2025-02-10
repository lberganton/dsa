public class HeapSort {
    public static void sort(int[] array) {
        for (int i = array.length / 2 - 1; i >= 0; i--) {
            siftDown(array, array.length, i);
        }

        int i = array.length;
        while (i > 0) {
            i--;
            Utils.swap(array, 0, i);
            siftDown(array, i, 0);
        }
    }

    private static void siftDown(int[] array, int length, int i) {
        int major = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < length && array[left] > array[major]) {
            major = left;
        }
        if (right < length && array[right] > array[major]) {
            major = right;
        }

        if (i != major) {
            Utils.swap(array, i, major);
            siftDown(array, length, major);
        }
    }
}
