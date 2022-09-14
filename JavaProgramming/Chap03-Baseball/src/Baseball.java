import java.util.Arrays;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.concurrent.ThreadLocalRandom;

/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 Model 클래스
 *
 * @author refracta
 */
public class Baseball {
    public static final int MAXIMUM_BALL = 3;
    public static final int MAXIMUM_OUT = 3;
    private int[] ball;
    private int out;

    /**
     * 숫자 야구 객체를 만들고 랜덤한 balls를 이용하여 초기화한 뒤 반환한다.
     *
     * @return 초기화된 Baseball 객체
     */
    public static Baseball generateByRandomBalls() {
        Baseball baseball = new Baseball();
        baseball.initByRandomBalls();
        return baseball;
    }

    /**
     * Baseball 객체를 랜덤한 balls를 생성하여 초기화한다.
     */
    public void initByRandomBalls() {
        this.out = 0;
        Set<Integer> balls = new LinkedHashSet<>();
        ThreadLocalRandom random = ThreadLocalRandom.current();
        while (balls.size() < MAXIMUM_BALL) {
            balls.add(random.nextInt(10));
        }
        this.ball = balls.stream().mapToInt(Integer::intValue).toArray();
    }

    /**
     * @param bat 플레이어가 입력한 숫자 배열
     * @return 숫자 야구 이닝 점수 객체
     */
    BaseballScore getScore(int bat[]) {
        int flag[] = new int[10];
        int strikeCount = 0;
        int ballCount = 0;
        int i;
        for (i = 0; i < 3; i++) flag[ball[i]] = 1;
        for (i = 0; i < 3; i++) {
            if (ball[i] == bat[i]) ++strikeCount;
            else if (flag[bat[i]] == 1) ++ballCount;
        }
        return new BaseballScore(strikeCount, ballCount);
    }

    /**
     * 현재 아웃 횟수를 반환한다.
     *
     * @return 아웃 횟수
     */
    public int getOut() {
        return out;
    }

    /**
     * 아웃 횟수를 1 증가시킨다.
     */
    public void addOut() {
        out++;
    }

    /**
     * Baseball 객체를 문자열로 변환한다.
     *
     * @return Baseball 객체 정보 문자열
     */
    @Override
    public String toString() {
        return "Baseball{" +
                "ball=" + Arrays.toString(ball) +
                ", out=" + out +
                '}';
    }
}
