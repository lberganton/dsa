public class BinarySearch {
    public static int search(int[] array, int val) {
        int low = 0;
        int high = array.length - 1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (val == array[mid]) {
                return mid;
            }

            if (val < array[mid]) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return -1;
    }
}
