public class ShellSort {
    private static final int GAP = 2;

    public static void sort(int[] array) {
        int h = array.length / GAP;
        while (h > 0) {
            for (int i = h; i < array.length; i++) {
                for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                    Utils.swap(array, j, j - h);
                }
            }
            h /= GAP;
        }
    }
}
