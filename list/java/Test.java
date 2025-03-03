public class Test {
    public static void main(String[] args) {
        testList(new ArrayList());
        testList(new LinkedList());
    }

    public static void testList(List list) {
        System.out.printf("%s:%n", list.getClass().getSimpleName());

        list.pushRight(7);
        list.pushRight(4);
        list.pushRight(5);
        list.pushRight(3);
        list.pushRight(2);
        list.pushRight(1);
        list.pushRight(6);

        list.sort();
        list.reverse();

        System.out.println(list);
    }
}
