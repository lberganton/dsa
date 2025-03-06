public class Test {
    public static void main(String[] args) {
        BSTreeTest(new UnbalancedBSTree());
        BSTreeTest(new AVL());
    }

    public static void BSTreeTest(BSTree tree) {
        System.out.printf("%s:%n", tree.getClass().getSimpleName());

        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);

        System.out.println(tree);
        tree.remove(3);
        System.out.println("remove(3): " + tree);
        System.out.println("search(3): " + tree.search((3)));
        System.out.println("search(4): " + tree.search((4)));
        System.out.println("levels(): " + tree.levels());
        System.out.println("nodes(): " + tree.nodes());
        tree.traversal(BSTree.Order.IN, System.out::println);
        tree.insert(0);
        tree.insert(-1);
        tree.insert(-2);
        System.out.println(tree);
    }
}
