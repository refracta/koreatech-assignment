import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Queue;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진 
 * @file CardGame.java
 * 탬플릿 메소드 패턴
 */
public abstract class CardGame {
	public static final int TOTALNUMBEROFCARDS = 52;
	public final int NUMBEROFCARDSPERPLAYER;
	private List<Card> originalDeck 
		= new ArrayList<>(TOTALNUMBEROFCARDS+2);
	protected Queue<Card> remainingDeck = new ArrayDeque<>();
	protected List<List<Card>> userCards = new ArrayList<>();
	protected int numberOfPlayers;
	
	public CardGame(int numberOfCardsPerPlayer) {
		if(numberOfCardsPerPlayer<0||numberOfCardsPerPlayer>TOTALNUMBEROFCARDS)
			throw new IllegalArgumentException("사용자마다 나누어 주는 카드 수가 잘못 설정");
		NUMBEROFCARDSPERPLAYER = numberOfCardsPerPlayer;
	}
	// 탬플릿 메소드
	public final void init(int numberOfPlayers){
		originalDeck.clear();
		remainingDeck.clear();
		userCards.clear();
		CardFace[] cardFaces = CardFace.values();
		for(int i=0; i<TOTALNUMBEROFCARDS; i++){
			originalDeck.add(new Card(i % 13 + 1, cardFaces[i/13]));
		}
		if(needJokerCards()) {
			originalDeck.add(new Card(0, CardFace.SPADES));
			originalDeck.add(new Card(0, CardFace.DIAMONDS));
		}
		shuffle();
		remainingDeck.addAll(originalDeck);
		setNumberOfPlayers(numberOfPlayers);
		dealCards();
	}
	// hook: 원하면 섞는 알고리즘을 변경할 수 있음
	protected void shuffle(){
		Collections.shuffle(originalDeck);
	}
	// hook: 원하면 조커 카드를 추가할 수 있음
	protected boolean needJokerCards() {
		return false;
	}
	// Concrete Method
	private void setNumberOfPlayers(int numberOfPlayers) {
		if(numberOfPlayers<=0 || numberOfPlayers>=TOTALNUMBEROFCARDS/NUMBEROFCARDSPERPLAYER)
			throw new IllegalArgumentException("플레이어 수가 적절하지 않음");
		this.numberOfPlayers = numberOfPlayers;
	}
	// Abstract Method
	// 카드를 각 플레이어에게 나누어주기
	protected abstract void dealCards();
	public Card getCard() {
        return remainingDeck.poll();
    }
	public List<List<Card>> getUserCards(){
		return userCards;
	}
}
