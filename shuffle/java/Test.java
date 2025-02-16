import java.security.SecureRandom;

public class Test {
    public static void main(String[] args) {
        SecureRandom random = new SecureRandom();
        int[] array = random.ints(10, 0, 10).toArray();

        printArray("Original", array);

        int[] tmp = array.clone();
        FisherYatesShuffle.shuffle(tmp);
        printArray("Fisher-Yates", tmp);
    }

    public static void printArray(String msg, int[] array) {
        System.out.printf("%-15s: ", msg);
        for (int i = 0; i < array.length; i++) {
            if (i == 0)
                System.out.print('[');

            System.out.print(array[i]);

            if (i == array.length - 1)
                System.out.print(']');
            else
                System.out.print(',');
        }
        System.out.println();
    }
}
