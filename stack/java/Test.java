public class Test {
    public static void main(String[] args) {
        testStack(new ArrayStack());
        testStack(new LinkedStack());
    }

    public static void testStack(Stack stack) {
        System.out.printf("%s:%n", stack.getClass().getSimpleName());

        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);
        stack.push(6);
        stack.push(7);

        stack.pop();
        stack.pop();
        stack.pop();

        System.out.println(stack);
    }
}
