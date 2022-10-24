/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file CoffeeTest.java
 * 테스트 프로그램
 */
public class CoffeeTest {
    public static void main(String[] args) {
        Beverage beverage = new HouseBlend();
        beverage = new Mocha(beverage);
        beverage = new Whip(beverage);
        beverage = new Mocha(beverage);
        System.out.printf("%s: %,d원%n", beverage.getDescription(), beverage.cost());

        beverage = new DarkRoast();
        beverage = new Mocha(beverage);
        beverage = new Milk(beverage);
        System.out.printf("%s: %,d원%n", beverage.getDescription(), beverage.cost());

        /* 구현 기능 테스트 시작 */
        Beverage beverage1 = new HouseBlend();
        beverage1 = new Mocha(beverage1);
        beverage1 = new Whip(beverage1);
        beverage1 = new Milk(beverage1);
        System.out.printf("beverage1: %s: %,d원%n", beverage1.getDescription(), beverage1.cost());

        Beverage beverage2 = new HouseBlend();
        beverage2 = new Milk(beverage2);
        beverage2 = new Mocha(beverage2);
        beverage2 = new Whip(beverage2);
        System.out.printf("beverage2: %s: %,d원%n", beverage2.getDescription(), beverage2.cost());

        Beverage beverage3 = new HouseBlend();
        beverage3 = new Milk(beverage3);
        beverage3 = new Whip(beverage3);
        beverage3 = new Whip(beverage3);
        System.out.printf("beverage3: %s: %,d원%n", beverage3.getDescription(), beverage3.cost());

        Beverage beverage4 = new HouseBlend();
        System.out.printf("beverage4: %s: %,d원%n", beverage4.getDescription(), beverage4.cost());
        Beverage beverage5 = new DarkRoast();
        System.out.printf("beverage5: %s: %,d원%n", beverage5.getDescription(), beverage5.cost());
        Beverage beverage6 = new DarkRoast();
        System.out.printf("beverage6: %s: %,d원%n", beverage5.getDescription(), beverage5.cost());

        System.out.println("beverage1.equals(beverage2): " + beverage1.equals(beverage2));
        System.out.println("beverage1.equals(beverage3): " + beverage1.equals(beverage3));
        System.out.println("beverage4.equals(beverage5): " + beverage4.equals(beverage5));
        System.out.println("beverage5.equals(beverage6): " + beverage5.equals(beverage6));

        try {
            Beverage doubleMilkBeverage = new Milk(beverage3);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
