import java.security.SecureRandom;

public class BogoSort {
    public static void sort(int[] array, int attempts) {
        int cur = 0;
        SecureRandom random = new SecureRandom();
        while (!isSorted(array) && (attempts <= 0 || cur < attempts)) {
            if (attempts > 0) {
                cur++;
            }
            shuffle(array, random);
        }
    }

    private static boolean isSorted(int[] array) {
        for (int i = 0; i < array.length - 1; i++) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }

    private static void shuffle(int[] array, SecureRandom random) {
        for (int i = 0; i < array.length; i++) {
            int r = random.nextInt(array.length);
            int tmp = array[r];
            array[r] = array[i];
            array[i] = tmp;
        }
    }
}
