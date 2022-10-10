/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file Beverage.java
 * 장식패턴에서 장식대상 추상클래스
 * 기본 예제
 */
public abstract class Beverage {
    private String description = "이름없는 음료";

    public String getDescription() {
        return description;
    }

    // 이 메소드의 문제점???
    public void setDescription(String description) {
        this.description = description;
    }

    public abstract int cost();
}
