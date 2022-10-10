/**
 * 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 *
 * @author 김상진, refracta(2020136110)
 * @version 2021년도 2학기
 * @file CoffeeTest.java
 * 생성 메소드 추가 버전
 * 인자로 클래스 이름과 같은 문자열을 제공해야 함
 * 한글을 사용하고 싶으면 별도 매핑 테이블이 필요함
 */

class Dog {
}

public class CoffeeTest {
    static {
        BeverageFactory.addAdditionRestriction("Whip", 1);
        BeverageFactory.addAdditionRestriction("Milk", 1);
        BeverageFactory.addAdditionRestriction("Mocha", 2);
        BeverageFactory.addCoffeeRestriction("Mocha", "DarkRoast");
    }

    public static void main(String[] args) throws Exception {
        Beverage beverage = BeverageFactory.createCoffee("HouseBlend", "Mocha", "Whip", "Mocha");
        System.out.printf("%s: %,d원%n", beverage.getDescription(), beverage.cost());
        try {
            beverage = BeverageFactory.createCoffee("DarkRoast", "Milk", "Mocha");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            beverage = BeverageFactory.createCoffee("Dog", "Milk", "Mocha");
        } catch (Exception e) {
            e.printStackTrace();
        }

        /* 구현 기능 테스트 시작 */
        try {
            Beverage coffee = BeverageFactory.createCoffee("HouseBlend", "Mocha", "Mocha", "Mocha");
        } catch (Exception e) {
            e.printStackTrace();
        }
        Beverage coffee = BeverageFactory.createCoffee("HouseBlend", "Mocha", "Mocha");
        System.out.printf("%s: %,d원%n", coffee.getDescription(), coffee.cost());
    }
}
