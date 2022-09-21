
/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file RandomStrategy.java
 * 전략패턴: 구체적인 전략 클래스
 * 낼 손으로 랜덤으로 결정
 */
public class RandomStrategy implements PlayingStrategy {
    @Override
    public HandType computeNextHand() {
        return getRandomNextHand();
    }

    public static HandType getRandomNextHand() {
        return HandType.values()[(int) Math.floor(Math.random() * HandType.values().length)];
    }
}
