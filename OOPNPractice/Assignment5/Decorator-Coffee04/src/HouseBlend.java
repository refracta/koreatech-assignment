/**
 * 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 *
 * @author 김상진
 * @version 2021년도 2학기
 * @file HouseBlend.java
 * 장식패턴에서 구체적인 장식대상 클래스
 * HouseBlend
 */
public class HouseBlend extends Beverage {
    protected HouseBlend() {
        setDescription("하우스블랜드 커피");
    }

    @Override
    public int cost() {
        return 1000;
    }
}
