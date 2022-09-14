import javafx.animation.*;
import javafx.application.Platform;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.util.Duration;


/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 *
 * @author refracta
 * 포켓몬팡의 컨트롤러 클래스: 사용자 상호작용 부분과 각종 타이머 사건 처리
 */
public class PangGridController {
    // 게임 종료 타이머: 1초마다 알람, gameOverCount를 통해 게임 시간 조절
    private Timeline gameOverTimeline = new Timeline();
    private Timeline hintTimeline = new Timeline();
    private SequentialTransition processClickTransition = new SequentialTransition();
    private PangGridView view = null;
    private PangGridModel model = null;
    private Location srcLoc = null;        // 첫 번째 클릭 위치
    private Location destLoc = null;    // 두 번째 클릭 위치

    /*
     *  콤보 관련 멤버들
     *  콤보는 최초 3초 이전에 계속 팡하면 콤보 증가, 그 다음에 2.5초, 2초, 1초
     */
    private Timeline comboTimeline = new Timeline();
    private int[] comboTime = {3000, 2500, 2000, 1000};
    private int comboTimeIndex = 0;

    /**
     * 게임 종료 타이머를 재시작
     */
    private void restartGameOverTimeLine() {
        gameOverTimeline.stop();
        gameOverTimeline.jumpTo(Duration.ZERO);
        gameOverTimeline.play();
    }

    private void restartHintTimeLine() {
        view.removeHint();
        hintTimeline.stop();
        hintTimeline.jumpTo(Duration.ZERO);
        hintTimeline.play();
    }

    // 콤보 타이머를 재시작
    // 콤보 시간 내에 팡을 못하면 콤보 수를 0으로 바꾸고 comboTimeIndex를 하나 증가
    // 원래 뜻 추정: 콤보 시간 내에 팡을 못하면 콤보 수를 0으로 바꾸고 comboTimeIndex를 하나 감소
    // comboTimeIndex는 3이 최대값
    private void restartComboTimeLine() {
        Duration targetDuration = new Duration(comboTime[comboTimeIndex]);
        comboTimeline.getKeyFrames().clear();
        comboTimeline.getKeyFrames().add(new KeyFrame(targetDuration, e -> {
            model.updateCombo(false);
            if (comboTimeIndex > 0) {
                comboTimeIndex--;
            }
            restartComboTimeLine();
        }));
        comboTimeline.stop();
        // comboTime의 타이머의 설정 (타이머 시간은 comboTimeIndex에 의해 결정)
        // 현재 콤보 수가 0이 아니면 새롭게 설정하지 않고 기존 설정대로 재시작하면 됨
        comboTimeline.jumpTo(Duration.ZERO);
        comboTimeline.play();
    }

    /**
     * 1초마다 gameOverTimeline에 의해 호출되는 함수
     */
    public void gameOverHandle() {
        model.updateGameTime();
        if (model.isGameOver()) {
            gameOver();
        }
    }

    /**
     * 마우스 클릭 처리 메소드
     */
    private void mouseClickHandle(MouseEvent mouseEvent) {
        view.removeEffect();

        double x = mouseEvent.getX() + 1;
        double y = mouseEvent.getY() + 1;

        int r = (int) (y / PangUtility.POKETMONIMAGESIZE);
        int c = (int) (x / PangUtility.POKETMONIMAGESIZE);
        if (srcLoc == null) {
            srcLoc = new Location(r, c);
            if (model.isSpecialPokemon(srcLoc)) {
                model.processSpecialPokemon(srcLoc);
                finalizeSuccessfulClick();
                srcLoc = null;
            } else view.showEffect(srcLoc);
        } else {
            destLoc = new Location(r, c);
            if (model.isValidSwap(srcLoc, destLoc)) {
                model.swap(srcLoc, destLoc);
                model.checkAndMark();
                finalizeSuccessfulClick();
            }
            view.removeEffect();
            srcLoc = destLoc = null;
        }
    }

    private void finalizeSuccessfulClick() {
        processClick();
        restartHintTimeLine();
        // 팡 성공으로 콤보 수 증가
        if (comboTimeIndex < comboTime.length - 1) {
            comboTimeIndex++;
        }
        restartComboTimeLine();
        model.updateCombo(true);
    }

    private void processClick() {
        processClickTransition.play();
    }

    private void checkForAdditionalPang() {
        Sound.play("pang");
        if (model.checkAndMark()) {
            processClick();
        } else {
            model.insertSpecialPokemon();
            if (!model.findHints()) gameOver();
        }
    }

    private void setupProcessClickTransition() {
        PauseTransition pushUpTransition = new PauseTransition(Duration.millis(100));
        pushUpTransition.setOnFinished(event -> model.pushUpMarked());
        PauseTransition replaceTransition = new PauseTransition(Duration.millis(100));
        replaceTransition.setOnFinished(event -> model.replaceMarked());
        processClickTransition.getChildren().addAll(pushUpTransition, replaceTransition);
        processClickTransition.setOnFinished(event -> checkForAdditionalPang());
    }

    public PangGridController(PangGridView view, PangGridModel model) {
        this.view = view;
        this.model = model;
        view.getCenter().setOnMouseClicked(e -> mouseClickHandle(e));

        gameOverTimeline.getKeyFrames().add(
                new KeyFrame(Duration.millis(1000), e -> gameOverHandle()));
        gameOverTimeline.setCycleCount(Animation.INDEFINITE);
        hintTimeline.getKeyFrames().add(
                new KeyFrame(Duration.millis(3000), e -> {
                    model.findHints();
                    view.showHint();
                }));
        hintTimeline.setCycleCount(1);
        setupProcessClickTransition();
    }

    public void startGame() {
        Sound.play("opening");
        PangUtility.pokemonInfoDialog("PokemonPang 게임시작", "게임을 시작하시겠습니까???");
        Sound.stop("opening");
        initGame();
    }

    /**
     * 새 게임마다 새롭게 초기화되어야 하는 것들을 초기화
     */
    public void initGame() {
        comboTimeIndex = 0;
        model.initAssign();
        restartGameOverTimeLine();
        restartHintTimeLine();
        restartComboTimeLine();
        Sound.play("pokemon");
    }

    private void gameOver() {
        gameOverTimeline.stop();    // 타이머 종료
        hintTimeline.stop();
        comboTimeline.stop();
        Sound.stop("pokemon");
        final Window stage = view.getScene().getWindow();
        stage.hide();
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                if (PangUtility.pokemonConfirmDialog("PokemonPang 게임종료", "새 게임을 하시겠습니까???",
                        "새 게임", "게임 종료")) {
                    initGame();
                    ((Stage) stage).show();
                } else Platform.exit();
            }
        });
    }
}
