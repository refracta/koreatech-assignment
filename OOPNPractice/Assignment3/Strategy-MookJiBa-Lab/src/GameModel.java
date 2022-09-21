/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file: GameModel.java
 * 묵찌바 게임에 필요한 데이터를 유지하고 게임 로직 제공
 */
public class GameModel {
    private ComputerPlayer computer
    // = new ComputerPlayer(new RandomStrategy());
    // = new ComputerPlayer(new LastHandBasedStrategy(this));
    = new ComputerPlayer(new AverageBasedStrategy(this));
    @SuppressWarnings("unused")
    private HandType prevUserHand = null;
    private HandType currUserHand = HandType.MOOK;
    private boolean playingMookJiBa = false;
    private boolean isUserAttack = false;

    // 새 게임을 할 때마다 객체를 생성하는 대신 사용 (상태 초기화)
    public void init() {
        playingMookJiBa = false;
        isUserAttack = false;
    }

    // 기본 Getter
    public boolean isUserAttack() {
        return isUserAttack;
    }

    public boolean playingMookJiBa() {
        return playingMookJiBa;
    }

    public void setUserHand(HandType userHand) {
        currUserHand = userHand;
    }

    public HandType getComputerCurrentHand() {
        return computer.getHand();
    }

    // 다음 컴퓨터 손 계산함
    public HandType getComputerNextHand() {
        HandType nextHand = computer.nextHand();
        prevUserHand = currUserHand;
        return nextHand;
    }

    // 묵찌바 게임 결과 판단
    // @return 묵찌바 게임의 결과
    public GameResult playMookJiBa() {
        HandType computer = getComputerCurrentHand();
        if (currUserHand == computer) {
            return isUserAttack ? GameResult.USERWIN : GameResult.COMPUTERWIN;
        } else {
            switch (playGawiBawiBo()) {
                case USERWIN:
                    isUserAttack = true;
                    break;
                case COMPUTERWIN:
                    isUserAttack = false;
                    break;
            }
            return GameResult.DRAW;
        }
    }

    // 가위바위보 게임 결과 판단
    // @return 가위바위보 게임의 결과
    public GameResult playGawiBawiBo() {
        int computer = getComputerCurrentHand().ordinal();
        int user = currUserHand.ordinal();
        GameResult result = GameResult.getOrderedResultArray()[(3 + user - computer) % 3];
        playingMookJiBa = result != GameResult.DRAW;
        isUserAttack = result == GameResult.USERWIN;
        return result;
    }

    public HandType getPrevUserHand() {
        return prevUserHand;
    }

    public HandType getCurrUserHand() {
        return currUserHand;
    }


}
