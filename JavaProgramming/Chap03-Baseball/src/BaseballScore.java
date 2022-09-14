import java.util.Objects;

/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 점수 클래스
 *
 * @author refracta
 */
public class BaseballScore {
    private int strike;
    private int ball;

    /**
     * 숫자 야구 게임 점수 객체를 생성한다.
     *
     * @param strike 스트라이크 수
     * @param ball   볼의 수
     */
    public BaseballScore(int strike, int ball) {
        this.strike = strike;
        this.ball = ball;
    }

    /**
     * 스트라이크 수를 반환한다.
     *
     * @return 스트라이크 수
     */
    public int getStrike() {
        return strike;
    }

    /**
     * 스트라이크 수를 설정한다.
     *
     * @param strike 스트라이크 수
     */
    public void setStrike(int strike) {
        this.strike = strike;
    }

    /**
     * 볼 수를 반환한다.
     *
     * @return 볼 수
     */
    public int getBall() {
        return ball;
    }

    /**
     * 볼 수를 설정한다.
     *
     * @param ball 볼 수
     */
    public void setBall(int ball) {
        this.ball = ball;
    }

    /**
     * 현재 점수 정보를 바탕으로 상태 객체를 생성하여 반환한다.
     *
     * @return 숫자 야구 게임 상태 객체
     */
    public BaseballGameStatus toStatus() {
        if (this.strike == Baseball.MAXIMUM_BALL) return BaseballGameStatus.WIN;
        else if (this.strike == 0 && this.ball == 0) return BaseballGameStatus.OUT;
        else return BaseballGameStatus.CONTINUE;
    }

    /**
     * 숫자 야구 게임 점수를 점수 출력용 문자열로 변환한다.
     *
     * @return 점수 출력용 문자열
     */
    public String toScoreString() {
        return String.format("S: %d, B: %d", strike, ball);
    }

    /**
     * 숫자 야구 게임 점수 객체를 문자열로 변환한다.
     *
     * @return BaseballScore 객체 정보 문자열
     */
    @Override
    public String toString() {
        return "BaseballScore{" +
                "strike=" + strike +
                ", ball=" + ball +
                '}';
    }

    /**
     * 숫자 야구 게임 점수 객체를 비교한 결과를 반환한다.
     *
     * @param o 비교 대상 객체
     * @return 비교 결과 부울
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BaseballScore that = (BaseballScore) o;
        return strike == that.strike && ball == that.ball;
    }

    /**
     * 숫자 야구 게임 점수 객체의 해시코드를 계산하여 반환한다.
     *
     * @return BaseballScore 객체의 해시코드
     */
    @Override
    public int hashCode() {
        return Objects.hash(strike, ball);
    }
}
