public class TestNum {
    public static void main(String[] args) {
        ComplexNumber c1 = new ComplexNumber(-1, -2);
        ComplexNumber c2 = new ComplexNumber(1, -2);

        // 测试加法
        System.out.println("Addition: " + c1.add(c2));

        // 测试减法
        System.out.println("Subtraction: " + c1.subtract(c2));

        // 测试乘法
        System.out.println("Multiplication: " + c1.multiply(c2));

        // 测试除法
        System.out.println("Division: " + c1.divide(c2));

        // 测试toString()方法
        System.out.println("c1: " + c1);

        // 测试equals()方法
        ComplexNumber c3 = new ComplexNumber(-1, -2);
        System.out.println("c1 equals c3? " + c1.equals(c3));
    }
}
