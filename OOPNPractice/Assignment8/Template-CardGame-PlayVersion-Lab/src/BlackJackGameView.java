import java.util.List;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진  
 * @file BlackJackGameView.java
 * 탬플릿 메소드 패턴
 * 블랙잭 게임을 진행하는 뷰
 */
public class BlackJackGameView extends Stage {
	private TextField gameInfoField = new TextField();
	private TilePane userPane = new TilePane();
	private TilePane dealerPane = new TilePane();
	private Button hitButton = new Button("Hit");
	private static int PREFCARDWIDTH = 100;
	private CardGame cardGame;
	private int numberOfPlayers;
	private BlackJackPlayerHand userHand;
	private BlackJackPlayerHand dealerHand;

	public BlackJackGameView(CardGame cardGame, int numberOfPlayers) {
		this.numberOfPlayers = numberOfPlayers;
		this.cardGame = cardGame;
		doLayout();
		newGame();
	}
	
	private void newGame() {
		gameInfoField.setText("");
		cardGame.init(numberOfPlayers);
		var cards = cardGame.getUserCards();
		this.userHand = new BlackJackPlayerHand(cards.get(0));
		this.dealerHand = new BlackJackPlayerHand(cards.get(1));
		dealUserCards();
		dealComputerCards();
		hitButton.setDisable(false);
	}
	
	private ImageView getCardImageView(Card card) {
		Image cardImage = new Image(card.fileName());
		ImageView cardView = new ImageView(cardImage);
		cardView.setFitWidth(PREFCARDWIDTH);
		cardView.setPreserveRatio(true);
		return cardView;
	}
	
	private void dealUserCards() {
		userPane.getChildren().clear();
		for(Card card: userHand.getCards())
			userPane.getChildren().add(getCardImageView(card));
	}
	
	private void dealComputerCards() {
		dealerPane.getChildren().clear();
		List<Card> dealerCards = dealerHand.getCards();
		for(int i=0; i<dealerCards.size()-1; i++)
			dealerPane.getChildren().add(getCardImageView(dealerCards.get(i)));
		ImageView backView = new ImageView(new Image("/image/blue_back.png"));
		backView.setFitWidth(PREFCARDWIDTH);
		backView.setPreserveRatio(true);
		dealerPane.getChildren().add(backView);
	}
	
	private void doHit() {
		Card card = cardGame.getCard();
		userHand.addCard(card);
		userPane.getChildren().add(getCardImageView(card));
		if(userHand.getScore()>21) {
			hitButton.setDisable(true);
			doStand();
		}
	}
	
	private void doStand() {
		hitButton.setDisable(true);
		dealerPane.getChildren().clear();
		for(Card card: dealerHand.getCards())
			dealerPane.getChildren().add(getCardImageView(card));
		while(dealerHand.getScore()<17){ 
			Card card = cardGame.getCard();
			dealerHand.addCard(card);
			dealerPane.getChildren().add(getCardImageView(card));
		}
		//System.out.println("사용자 점수: "+userHand.getScore()+", "+userHand.isBlackJack());
		//System.out.println("딜러 점수: "+dealerHand.getScore()+", "+dealerHand.isBlackJack());
		showResult();
	}
	
	private void showResult() {
		BlackJackGameResult result 
			= BlackJackPlayerHand.determineResult(userHand, dealerHand);
		switch(result) {
		case DRAW: gameInfoField.setText("무승부"); break;
		case USERWIN: gameInfoField.setText("사용자 승"); break;
		default: gameInfoField.setText("딜러 승"); break;
		}
	}
	
	public void doLayout() {
		BorderPane mainPane = new BorderPane();
		
		gameInfoField.setEditable(false);
		mainPane.setTop(gameInfoField);
		
		VBox cardPane = new VBox();
		cardPane.setAlignment(Pos.CENTER);
		cardPane.setSpacing(10d);
		cardPane.setPadding(new Insets(10d));
		cardPane.getChildren().addAll(userPane, dealerPane);
		
		Button standButton = new Button("Stand");
		Button newGameButton = new Button("new");
		hitButton.setOnAction(e->doHit());
		standButton.setOnAction(e->doStand());
		newGameButton.setOnAction(e->newGame());
		
		HBox buttonPane = new HBox();
		buttonPane.setAlignment(Pos.CENTER);
		buttonPane.setSpacing(10d);
		buttonPane.setPadding(new Insets(10d));
		buttonPane.getChildren().addAll(hitButton, standButton, newGameButton);
		
		mainPane.setCenter(cardPane);
		mainPane.setBottom(buttonPane);
		setScene(new Scene(mainPane));
	}
}
