/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file Whip.java
 * 장식패턴에서 구체적인 장식자 클래스
 * 크림 첨가물
 */
public class Whip extends CondimentDecorator {
    public Whip(Beverage beverage) {
        super(beverage);
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", 크림";
    }

    @Override
    public int cost() {
        return beverage.cost() + 500;
    }
}
