public class Test {
    public static void main(String[] args) {
        ArrayList l = new ArrayList();

        l.pushRight(7);
        l.pushRight(4);
        l.pushRight(5);
        l.pushRight(3);
        l.pushRight(2);
        l.pushRight(1);
        l.pushRight(6);

        l.sort();
        l.reverse();

        System.out.println(l);
    }
}
