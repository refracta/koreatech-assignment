import java.util.ArrayList;
import java.util.List;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진, refracta
 * @file PokerGame.java
 * 탬플릿 메소드 패턴
 * 포커 게임: 5장씩 나누어줌, 조커는 사용하지 않음
 */
public class PokerGame extends CardGame {
	public PokerGame() {
		super(5);
	}
	@Override
	protected void dealCards() {
		for (int i = 0; i < numberOfPlayers; i++) {
			List<Card> userCard = new ArrayList<>();
			for (int j = 0; j < NUMBER_OF_CARDS_PER_PLAYER; j++) {
				userCard.add(getCard());
			}
			userCards.add(userCard);
		}
	}
}
