
/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file LastHandBasedStrategy.java
 * 전략패턴: 구체적인 전략 클래스
 * 사용자의 마지막 결과에 따라서 낼마지막으로 낸 타입 20%, 나머지 두 타입을 각각 40%의 확률로 결정
 */
public class LastHandBasedStrategy implements PlayingStrategy {
    private GameModel gameModel;

    public LastHandBasedStrategy(GameModel gameModel) {
        this.gameModel = gameModel;
    }

    @Override
    public HandType computeNextHand() {
        HandType prevUserHand = gameModel.getPrevUserHand();
        if (prevUserHand == null) {
            return RandomStrategy.getRandomNextHand();
            // 이전 수가 없을 때에는 랜덤 타입을 낸다
        } else {
            int length = HandType.values().length;
            HandType left1 = HandType.values()[(prevUserHand.ordinal() + 1) % length];
            HandType left2 = HandType.values()[(prevUserHand.ordinal() + 2) % length];
            // 남은 두개의 수를 가져온다
            HandType[] nextArray = {prevUserHand, left1, left1, left2, left2};
            // 1:2:2의 비율의 타입 배열을 생성한다
            return nextArray[(int) Math.floor(Math.random() * nextArray.length)];
            // 타입 배열에서 다음 수를 뽑는다.
        }
    }
}
