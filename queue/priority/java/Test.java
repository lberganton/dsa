public class Test {
    public static void main(String[] args) {
        testPQueue(new Heap(Integer::compareTo));
        testPQueue(new Heap((x, y) -> -x.compareTo(y)));
    }

    public static void testPQueue(PQueue pQueue) {
        System.out.printf("%s:%n", pQueue.getClass().getSimpleName());

        pQueue.insert(1);
        pQueue.insert(2);
        pQueue.insert(3);
        pQueue.insert(4);
        pQueue.insert(5);
        pQueue.insert(6);
        pQueue.insert(7);

        System.out.println(pQueue);

        while (pQueue.size() > 0) {
            System.out.println(pQueue.remove());
        }
    }
}
