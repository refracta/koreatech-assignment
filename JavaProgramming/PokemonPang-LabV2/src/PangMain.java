import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 * @author refracta 
 * 포켓몬팡의 메인
 * MVC 모델 이용
 */
public class PangMain extends Application{
	private PangGridView view = new PangGridView();
	private PangGridModel model = new PangGridModel(view);
	private PangGridController controller = new PangGridController(view, model);
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		controller.startGame();
		primaryStage.setTitle("JavaFX PokemonPang");
		primaryStage.setScene(new Scene(view));
		primaryStage.show();
	}
	public static void main(String[] args) {
		Application.launch(args);
	}
}
