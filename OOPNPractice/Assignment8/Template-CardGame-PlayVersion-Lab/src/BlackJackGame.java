import java.util.ArrayList;
import java.util.List;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * @file BlackJackGame.java
 * 탬플릿 메소드 패턴
 * 블랙잭 게임: 2장씩 나누어 줌, 조커를 사용하지 않음
 */
public class BlackJackGame extends CardGame {
	public BlackJackGame() {
		super(2);	// 플레이어 수
	}
	@Override
	protected void dealCards() {
		for(int i=0; i<numberOfPlayers; i++) {
			List<Card> userCard = new ArrayList<>();
			for(int j=0; j<NUMBEROFCARDSPERPLAYER; j++)
				userCard.add(getCard());
			userCards.add(userCard);
		}
	}
}
