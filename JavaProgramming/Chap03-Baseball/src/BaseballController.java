/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 Controller 클래스
 *
 * @author refracta
 */
public class BaseballController {
    private Baseball model;
    private BaseballView view;

    /**
     * Controller 객체를 생성한다.
     *
     * @param model Baseball 객체 (Model 객체)
     * @param view  BaseballView 객체 (View 객체)
     */
    public BaseballController(Baseball model, BaseballView view) {
        this.model = model;
        this.view = view;
    }

    /**
     * 숫자 야구 게임을 시작하고 게임 결과 객체를 반환한다.
     *
     * @return 숫자 야구 게임 상태 객체, BaseballGameStatus.WIN = 사용자 승리, BaseballGameStatus.OUT = 컴퓨터 승리
     */
    public BaseballGameStatus playGame() {
        BaseballGameStatus status;
        gameLoop:
        while (true) {
            int[] playerBat = view.getPlayerBat();
            BaseballScore score = model.getScore(playerBat);
            switch (status = score.toStatus()) {
                case CONTINUE:
                    view.printStrikeBallStatus(score);
                    break;
                case WIN:
                    break gameLoop;
                case OUT:
                    model.addOut();
                    view.printOutMessage(model);
                    if (model.getOut() >= Baseball.MAXIMUM_OUT) {
                        break gameLoop;
                    }
            }
        }
        view.printGameResultMessage(status);
        return status;
    }

    /**
     * 숫자 야구 게임을 시작한다. 게임이 끝나면 사용자의 입력을 받아 재시작하거나 게임을 종료한다.
     */
    public void playGameWithRestart() {
        while (true) {
            playGame();
            if (view.runNewGameConfirm()) {
                model.initByRandomBalls();
            } else {
                break;
            }
        }
    }
}
