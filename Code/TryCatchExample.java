import java.util.Scanner;

public class TryCatchExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.println("Enter a number:");
            int number = scanner.nextInt();
            //scanner.nextLine(); // 用这段代码消耗掉换行符，不然name为空
            System.out.println("Enter your name:");
            String name = scanner.nextLine();
            System.out.println("You entered: " + number);
            System.out.println("Your name is: " + name);
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        } finally {
            scanner.close(); // 在 finally 块中关闭资源
        }
    }
}
