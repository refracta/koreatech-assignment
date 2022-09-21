import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file AverageBasedStrategy.java
 * 전략패턴: 구체적인 전략 클래스
 * 사용자가 결과적으로 모든 수를 골고루(같은 횟수로, 표본 공간 각 요소의 기댓값에 가깝게) 낼 것이라고 가정하고
 * 사용자가 여지까지 내지 않은 수들을 다음에 낼 수로 예측하고, 이에 따라 게임을 진행한다.
 * (묵찌빠의 경우, 컴퓨터가 공격시) 사용자가 내지 않은 수 중에서 결정함
 * (묵찌빠의 경우, 사용자가 공격시) 사용자가 내지 않은 수를 이기는 수로 결정함
 * (가위바위보의 경우) 사용자가 내지 않은 수를 이기는 수로 결정함
 */
public class AverageBasedStrategy implements PlayingStrategy {
    private GameModel gameModel;

    public AverageBasedStrategy(GameModel gameModel) {
        this.gameModel = gameModel;
    }

    int counts[] = new int[HandType.values().length];
    // 사용자가 낸 타입을 집계하는 배열

    @Override
    public HandType computeNextHand() {
        HandType prevUserHand = gameModel.getPrevUserHand();
        // 사용자가 이전에 낸 수 가져온다
        if (prevUserHand == null) {
            return RandomStrategy.getRandomNextHand();
            // 이전 수가 없을 때에는 랜덤 타입을 낸다
        } else {
            counts[prevUserHand.ordinal()]++;
            // 타입 카운트를 집계한다
            int minCount = Arrays.stream(counts).min().getAsInt();
            // 최소 타입 카운트 수를 가져온다
            List<Integer> targetList = new ArrayList<>();
            for (int i = 0; i < counts.length; i++) {
                if (counts[i] == minCount) {
                    targetList.add(i);
                }
            }
            // counts를 순회하며, minCount와 값이 같은 색인을 targetList 색인 동적 배열에 집어넣는다
            HandType predicted = HandType.values()[targetList.get((int) Math.floor(Math.random() * targetList.size()))];
            // 사용자가 다음에 낼 수를 고른다 (targetList의 길이가 2 이상인 경우 모든 수를 동일한 확률로 선택함)
            if (gameModel.playingMookJiBa() && !gameModel.isUserAttack()) {
                // (묵찌빠의 경우, 컴퓨터가 공격시) 사용자가 내지 않은 수 중에서 결정함
                return predicted;
            } else {
                // * (묵찌빠의 경우, 사용자가 공격시) 사용자가 내지 않은 수를 이기는 수로 결정함
                // * (가위바위보의 경우) 사용자가 내지 않은 수를 이기는 수로 결정함
                return predicted.winValueOf();
            }
        }
    }
}
