/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 시작 클래스
 *
 * @author refracta
 */
public class Starter {
    public static void main(String[] args) {
        BaseballController controller = new BaseballController(Baseball.generateByRandomBalls(), new BaseballView());
        controller.playGameWithRestart();
        System.exit(0);
    }
}
