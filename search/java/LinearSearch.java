public class LinearSearch {
    public static int search(int[] array, int val) {
        for (int i = 0; i < array.length; i++) {
            if (val == array[i]) {
                return i;
            }
        }
        return -1;
    }
}
