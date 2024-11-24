class Animal {
    // Animal 类
}

class Dog extends Animal {
    // Dog 类
}

class Cat extends Animal {
    // Cat 类
}

public class Main {
    public static void main(String[] args) {
        Animal animal = new Dog();
        Dog dog = new Dog();
        Cat cat = new Cat();

        // 使用 instanceof 运算符检查对象是否是某个类的实例
        System.out.println(animal instanceof Animal); // true，因为 animal 是 Animal 类的实例
        System.out.println(dog instanceof Dog);       // true，因为 dog 是 Dog 类的实例
        System.out.println(cat instanceof Cat);       // true，因为 cat 是 Cat 类的实例

        System.out.println(dog instanceof Animal);    // true，因为 Dog 类是 Animal 类的子类
        System.out.println(cat instanceof Animal);    // true，因为 Cat 类是 Animal 类的子类

        System.out.println(animal instanceof Dog);    // false，因为 animal 不是 Dog 类的实例
        System.out.println(animal instanceof Cat);    // false，因为 animal 不是 Cat 类的实例
    }
}
