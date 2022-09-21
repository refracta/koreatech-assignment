import java.util.Objects;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * @file: ComputerPlayer.java
 * 묵찌바, 가위바위보에서 컴퓨터 역할을 하는 클래스
 * 전략 패턴: 전략을 활용하는 클라이언트 클래스
 */
public class ComputerPlayer{
	private HandType computerHand;
	private PlayingStrategy strategy;
	public ComputerPlayer(PlayingStrategy strategy) {
		setStrategy(strategy);
	}
	public void setStrategy(PlayingStrategy strategy) {
		this.strategy = Objects.requireNonNull(strategy);
	}  // dependency injection
	public HandType getHand() {
		return computerHand;
	}
	public HandType nextHand(){
		return computerHand = strategy.computeNextHand();
	}
}
