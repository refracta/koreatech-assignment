import java.util.Scanner;

/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 View 클래스
 *
 * @author refracta
 */
public class BaseballView {
    private static Scanner in = new Scanner(System.in);

    /**
     * 현재 아웃 수를 출력한다.
     *
     * @param baseball 숫자 야구 모델 객체
     */
    public void printOutMessage(Baseball baseball) {
        System.out.printf("OUT: %d\n", baseball.getOut());
    }

    /**
     * 숫자 야구 게임 점수를 출력한다.
     *
     * @param score 숫자 야구 게임 점수 객체
     */
    public void printStrikeBallStatus(BaseballScore score) {
        System.out.println(score.toScoreString());
    }

    /**
     * 숫자 야구 게임 상태에 따른 결과 메시지를 출력한다.
     *
     * @param status 숫자 야구 게임 상태 객체
     */
    public void printGameResultMessage(BaseballGameStatus status) {
        System.out.println(status.getResultMessage());
    }

    /**
     * 사용자에게 새 게임을 시작하는지 묻고, 새 게임의 시작 여부를 부울로 반환한다.
     *
     * @return 새 게임의 시작 여부 부울
     */
    public boolean runNewGameConfirm() {
        in.nextLine();
        // 표준 입력 비우기
        while (true) {
            System.out.printf("새 게임(y/n)? ");
            String s = in.nextLine();
            if (s.equalsIgnoreCase("y")) {
                return true;
            } else if (s.equalsIgnoreCase("n")) {
                return false;
            }
        }
    }

    /**
     * 사용자의 숫자 입력을 가져온다. (매 회 숫자 야구 게임 이닝 숫자 입력)
     *
     * @return 사용자의 숫자 입력
     */
    public int[] getPlayerBat() {
        System.out.printf("[0-9]까지 숫자 " + Baseball.MAXIMUM_BALL + "개를 입력하시오: ");
        int[] bat = new int[Baseball.MAXIMUM_BALL];
        for (int i = 0; i < Baseball.MAXIMUM_BALL; i++) {
            bat[i] = in.nextInt();
        }
        return bat;
    }
}
