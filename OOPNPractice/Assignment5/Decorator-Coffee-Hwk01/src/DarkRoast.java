/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file DarkRoast.java
 * 장식패턴에서 구체적인 장식대상 클래스
 * 다크로스트 커피
 */
public class DarkRoast extends Beverage {
    private static final int COST = 1200;

    public DarkRoast() {
        setDescription("다크로스트 커피");
    }

    @Override
    public int cost() {
        return COST;
    }
}
