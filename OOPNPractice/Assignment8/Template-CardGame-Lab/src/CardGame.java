import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file CardGame.java
 * 탬플릿 메소드 패턴
 */
public abstract class CardGame {
    public static final int TOTAL_NUMBER_OF_CARDS = 52;
    public final int NUMBER_OF_CARDS_PER_PLAYER;
    private List<Card> originalDeck
            = new ArrayList<>(TOTAL_NUMBER_OF_CARDS);
    protected Queue<Card> remainingDeck = new ArrayDeque<>();
    protected List<List<Card>> userCards = new ArrayList<>();
    protected int numberOfPlayers;

    public CardGame(int numberOfCardsPerPlayer) {
        if (numberOfCardsPerPlayer < 0 || numberOfCardsPerPlayer > TOTAL_NUMBER_OF_CARDS)
            throw new IllegalArgumentException("사용자마다 나누어 주는 카드 수가 잘못 설정");
        NUMBER_OF_CARDS_PER_PLAYER = numberOfCardsPerPlayer;
    }

    // 탬플릿 메소드
    public final void init(int numberOfPlayers) {
        originalDeck.clear();
        remainingDeck.clear();
        userCards.clear();
        CardFace[] cardFaces = CardFace.values();
        for (int i = 0; i < TOTAL_NUMBER_OF_CARDS; i++) {
            originalDeck.add(new Card(i % 13 + 1, cardFaces[i / 13]));
        }
        if (needJokerCards()) {
            originalDeck.add(new Card(0, CardFace.SPADES));
            originalDeck.add(new Card(0, CardFace.DIAMONDS));
        }
        shuffle();
        remainingDeck.addAll(originalDeck);
        setNumberOfPlayers(numberOfPlayers);
        dealCards();
    }

    // hook: 원하면 섞는 알고리즘을 변경할 수 있음
    protected void shuffle() {
        for (int i = originalDeck.size() - 1; i > 0; i--) {
            int randomIndex = ThreadLocalRandom.current().nextInt(i + 1);
            // 이미 뽑은 카드는 제외한 범위에서 랜덤 인덱스 생성
            Card temp = originalDeck.get(i);
            originalDeck.set(i, originalDeck.get(randomIndex));
            originalDeck.set(randomIndex, temp);
            // 교환
        }
    }

    // hook: 원하면 조커 카드를 추가할 수 있음
    protected boolean needJokerCards() {
        return false;
    }

    // Concrete Method
    private void setNumberOfPlayers(int numberOfPlayers) {
        if (numberOfPlayers <= 0 || numberOfPlayers >= TOTAL_NUMBER_OF_CARDS / NUMBER_OF_CARDS_PER_PLAYER)
            throw new IllegalArgumentException("플레이어 수가 적절하지 않음");
        this.numberOfPlayers = numberOfPlayers;
    }

    // Abstract Method
    // 카드를 각 플레이어에게 나누어주기
    protected abstract void dealCards();

    public Card getCard() {
        return remainingDeck.poll();
    }

    public List<List<Card>> getUserCards() {
        return userCards;
    }

    // debug용
    public void display() {
        for (var cards : userCards) {
            for (var card : cards) {
                System.out.print(card + ", ");
            }
            System.out.println();
        }
    }
}
