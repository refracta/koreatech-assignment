import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * @file CardGameView.java
 * 탬플릿 메소드 패턴
 * 카드 게임을 선택하는 뷰
 */
public class CardGameView extends Application {
	private ComboBox<String> cardGameChoice = new ComboBox<>();
	private ComboBox<Integer> numberOfCardPlayers = new ComboBox<>();
	String[] sCardGameTypes = {"블랙잭", "포커", "원카드"};
	private CardGame cardGame;
	private BlackJackGameView gameView = null;
	
	public void startGame() {
		if(gameView!=null) gameView.close();
		String cardGameType = cardGameChoice.getSelectionModel().getSelectedItem();
		switch(cardGameType) {
		case "포커":		
		case "원카드":
		default:
			cardGame = new BlackJackGame();
		}
		int numberOfPlayers = numberOfCardPlayers.getSelectionModel().getSelectedItem();
		gameView = new BlackJackGameView(cardGame, numberOfPlayers);
		gameView.show();
	}
	public void closeAllWindows() {
		if(gameView != null) {
			gameView.close();
		}
	}
	@Override
	public void start(Stage primaryStage) throws Exception {
		Button startButton = new Button("Card Game 시작");	
		Button closeAllButton = new Button("모두 닫기");
		startButton.setMinWidth(160);
		closeAllButton.setMinWidth(160);
		
		cardGameChoice.getItems().addAll(sCardGameTypes);
		cardGameChoice.getSelectionModel().select(0);
		cardGameChoice.setVisibleRowCount(5);
		cardGameChoice.setMinWidth(160);
		
		numberOfCardPlayers.getItems().addAll(2,3,4,5);
		numberOfCardPlayers.getSelectionModel().select(0);
		numberOfCardPlayers.setVisibleRowCount(5);
		numberOfCardPlayers.setMinWidth(160);
		
		VBox buttonBox = new VBox();
		buttonBox.setPadding(new Insets(10));
		buttonBox.setSpacing(10);
		buttonBox.setAlignment(Pos.CENTER);
		buttonBox.getChildren().addAll(cardGameChoice,numberOfCardPlayers,
				startButton,closeAllButton);
		
		startButton.setOnAction(e->startGame());
		closeAllButton.setOnAction(e->closeAllWindows());
		
		primaryStage.setTitle("Card Game");
		primaryStage.setScene(new Scene(buttonBox,300,300));
		primaryStage.setX(50);
		primaryStage.setY(100);
		primaryStage.show();
		primaryStage.getScene().getWindow()
			.addEventFilter(WindowEvent.WINDOW_CLOSE_REQUEST, e->closeAllWindows());
	}

	public static void main(String[] args) {
		Application.launch(args);
	}

}