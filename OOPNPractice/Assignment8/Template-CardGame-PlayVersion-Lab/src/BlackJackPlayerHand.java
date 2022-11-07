import java.util.List;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진  
 * @file BlackJackPlayerHand.java
 * 탬플릿 메소드 패턴
 * 블랙잭 게임에서 각 플레이어의 패 정보 유지
 */
public class BlackJackPlayerHand {
	private List<Card> cards;
	private int score = 0;
	private boolean isBlackJack = false;
	public BlackJackPlayerHand(List<Card> cards) {
		this.cards = cards;
		score = computeScore();
	}
	public void init() {
		cards.clear();
		score = 0;
		isBlackJack = false;
	}
	public List<Card> getCards(){
		return cards;
	}
	public void addCard(Card card) {
		cards.add(card);
		score = computeScore();
	}
	public int getScore() {
		return score;
	}
	public boolean isBlackJack() {
		return isBlackJack;
	}
	private int computeScore() {
		isBlackJack = false;
		int sum = 0;
		int count = 0;
		for(var card: cards) {
			if(card.number()==1) ++count;
			else if(card.number()>=11) sum += 10;
			else sum += card.number();
		}
		if(sum>21) return sum+count;
		else if(count!=0){
			switch(count) {
			case 1:
				if(cards.size()==2&&
					(cards.get(0).number()>=11||cards.get(1).number()>=11)) {
					isBlackJack = true;
					return 21;
				}
			default:
				int count11 = count+10;
				return (sum+count11<=21)? sum+count11: sum+count;
			}
		}
		else return sum;
	}
	public static BlackJackGameResult determineResult(
		BlackJackPlayerHand userHand, BlackJackPlayerHand dealerHand) {
		int dealer = dealerHand.getScore();
		int user = userHand.getScore();
		if(dealer>21&&user>21) return BlackJackGameResult.DRAW;
		else if(dealer>21) return BlackJackGameResult.USERWIN;
		else if(user>21) return BlackJackGameResult.USERLOST;
		else if(dealer==21&&user==21) {
			if(dealerHand.isBlackJack()&&userHand.isBlackJack())
				return BlackJackGameResult.DRAW;
			else return dealerHand.isBlackJack()? 
				BlackJackGameResult.USERLOST: BlackJackGameResult.USERWIN;
		} 
		else return (dealer>=user)?  
			BlackJackGameResult.USERLOST: BlackJackGameResult.USERWIN;
	}
}
