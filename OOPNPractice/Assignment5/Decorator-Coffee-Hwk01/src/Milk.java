import java.util.Iterator;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file Milk.java
 * 장식패턴에서 구체적인 장식자 클래스
 * 우유 첨가물
 */
public class Milk extends CondimentDecorator {
    public Milk(Beverage beverage) {
        super(beverage);
        if (beverage instanceof CondimentDecorator decorator) {
            Iterator<Beverage> iterator = decorator.getIterator();
            while (iterator.hasNext()) {
                Beverage next = iterator.next();
                if (next instanceof Milk) {
                    throw new IllegalArgumentException("우유는 한 개 이상 넣을 수 없습니다.");
                }
            }
        }
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", 우유";
    }

    @Override
    public int cost() {
        return beverage.cost() + 500;
    }

}
