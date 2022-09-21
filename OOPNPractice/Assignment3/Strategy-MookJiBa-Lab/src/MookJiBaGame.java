import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 전략 패턴 실습
 * MookJiBaGame.java: 묵지바 메인 클래스
 */
public class MookJiBaGame extends Application{
	private GameModel gameModel = new GameModel();
	private GameView gameView = new GameView(gameModel);
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setTitle("묵찌빠 게임");
		primaryStage.setScene(new Scene(gameView));
		primaryStage.show();
	}
	
	public static void main(String[] args) {
		Application.launch(args);
	}
}
