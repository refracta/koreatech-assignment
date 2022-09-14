import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.PauseTransition;
import javafx.animation.SequentialTransition;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.util.Duration;


/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 * @author refracta
 * 포켓몬팡의 컨트롤러 클래스: 사용자 상호작용 부분과 각종 타이머 사건 처리
 */
public class PangGridController {
	// 게임 종료 타이머: 1초마다 알람, gameOverCount를 통해 게임 시간 조절
	private Timeline gameOverTimeline = new Timeline();
	private SequentialTransition processClickTransition = new SequentialTransition();
	private PangGridView view = null;
	private PangGridModel model = null;
	private Location srcLoc = null;		// 첫 번째 클릭 위치
	private Location destLoc = null;	// 두 번째 클릭 위치

	/**
	 * 게임 종료 타이머를 재시작
	 */
	private void restartGameOverTimeLine(){
		gameOverTimeline.stop();
		gameOverTimeline.jumpTo(Duration.ZERO);
		gameOverTimeline.play();
	}

	/**
	 * 1초마다 gameOverTimeline에 의해 호출되는 함수
	 */
	public void gameOverHandle() {
		model.updateGameTime();
		if(model.isGameOver()) {
			gameOver();
		}
	}

	/**
	 * 마우스 클릭 처리 메소드
	 */
	private void mouseClickHandle(MouseEvent mouseEvent) {
		view.removeEffect();;
		double x = mouseEvent.getX()+1;
		double y = mouseEvent.getY()+1;

		int r = (int)(y/PangUtility.POKETMONIMAGESIZE);
    	int c = (int)(x/PangUtility.POKETMONIMAGESIZE);
    	if(srcLoc==null){
    		srcLoc = new Location(r,c);
    		view.showEffect(srcLoc);
    	}
    	else{
    		destLoc = new Location(r,c);
    		if(model.isValidSwap(srcLoc,destLoc)){
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
	}

	private void processClick(){
		processClickTransition.play();
	}

	private void checkForAdditionalPang() {
		Sound.play("pang");
		if(model.checkAndMark()) processClick();
		else{
			if(!model.findHints()) gameOver();
		}
	}

	private void setupProcessClickTransition() {
		PauseTransition pushUpTransition = new PauseTransition(Duration.millis(100));
		pushUpTransition.setOnFinished(event->model.pushUpMarked());
		PauseTransition replaceTransition = new PauseTransition(Duration.millis(100));
		replaceTransition.setOnFinished(event->model.replaceMarked());
		processClickTransition.getChildren().addAll(pushUpTransition, replaceTransition);
		processClickTransition.setOnFinished(event->checkForAdditionalPang());
	}

	public PangGridController(PangGridView view, PangGridModel model){
		this.view = view;
		this.model = model;
		view.getCenter().setOnMouseClicked(e->mouseClickHandle(e));

		gameOverTimeline.getKeyFrames().add(
			new KeyFrame(Duration.millis(1000),e->gameOverHandle()));
		gameOverTimeline.setCycleCount(Animation.INDEFINITE);
		setupProcessClickTransition();
	}

	public void startGame(){
		Sound.play("opening");
		PangUtility.pokemonInfoDialog("PokemonPang 게임시작", "게임을 시작하시겠습니까???");
		Sound.stop("opening");
		initGame();
	}
	/**
	 * 새 게임마다 새롭게 초기화되어야 하는 것들을 초기화
	 */
	public void initGame(){
		model.initAssign();
		restartGameOverTimeLine();
		Sound.play("pokemon");
	}

	private void gameOver(){
		gameOverTimeline.stop(); 	// 타이머 종료
		Sound.stop("pokemon");
		final Window stage = view.getScene().getWindow();
		stage.hide();
		Platform.runLater(new Runnable() {
            @Override
            public void run() {
					if(PangUtility.pokemonConfirmDialog("PokemonPang 게임종료", "새 게임을 하시겠습니까???",
							"새 게임", "게임 종료")){
						initGame();
						((Stage)stage).show();
					}
					else Platform.exit();
            }
        });
	}
}
