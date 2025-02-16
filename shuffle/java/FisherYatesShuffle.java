import java.security.SecureRandom;

public class FisherYatesShuffle {
    public static void shuffle(int[] array) {
        SecureRandom random = new SecureRandom();
        for (int i = array.length - 1; i >= 0; i--) {
            Utils.swap(array, i, random.nextInt(i + 1));
        }
    }
}
