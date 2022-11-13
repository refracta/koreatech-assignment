import java.util.List;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
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

    public List<Card> getCards() {
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
        int score = 0;
        int aceCount = 0;
        int lastAceIndex = 0;
        for (int i = 0; i < cards.size(); i++) {
            Card card = cards.get(i);
            if (card.number() == 1) {
                aceCount++;
                lastAceIndex = i;
                // 에이스인 경우 카운트 증가 및 색인 저장
            } else {
                score += card.getScore();
                // 누적 스코어 계산
            }
        }

        if (aceCount == 1 && cards.size() == 2) {
            isBlackJack = cards.get(lastAceIndex ^ 1).getScore() == 10;
            // lastAceIndex가 아닌 색인의 카드가 J, Q, K이면 블랙잭
            if (isBlackJack) {
                return 21;
                // 블랙잭인 경우 21 반환
            } else {
                score = score + aceCount;
                return score + 10 > 21 ? score : score + 10;
                // 아닌 경우 계산한 점수 반환
            }
        } else {
            return score + aceCount;
            // 기타 경우 ace를 1로 간주하고 score에 더해서 반환
        }
    }

    public static BlackJackGameResult determineResult(
            BlackJackPlayerHand userHand, BlackJackPlayerHand dealerHand) {
        int userScore = userHand.getScore();
        int dealerScore = dealerHand.getScore();
        if (userScore > 21 && dealerScore > 21)
            return BlackJackGameResult.DRAW;
        if (dealerScore > 21)
            return BlackJackGameResult.USERWIN;
        if (userScore > 21)
            return BlackJackGameResult.USERLOST;
        // 버스트 상황 처리
        
        if (userScore == 21 && dealerScore == 21) {
            if (dealerHand.isBlackJack() && userHand.isBlackJack()) {
                return BlackJackGameResult.DRAW;
                // 둘 다 블랙잭인 경우 무승부
            } else {
                return userHand.isBlackJack() ? BlackJackGameResult.USERWIN : BlackJackGameResult.USERLOST;
                // 유저만 블랙잭인 경우 승리 / 아닌 경우 패배
            }
        } else {
            return dealerScore < userScore ? BlackJackGameResult.USERWIN : BlackJackGameResult.USERLOST;
            // 이외 경우에서 스코어 비교로 승패 결정
        }
    }
}
