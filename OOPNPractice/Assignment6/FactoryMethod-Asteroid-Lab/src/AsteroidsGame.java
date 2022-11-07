import java.util.ArrayList;
import java.util.List;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.PauseTransition;
import javafx.animation.RotateTransition;
import javafx.animation.SequentialTransition;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;
/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidsGame.java: Asteroid 게임
 * Asteroid 게임 중 소행성 등장하는 부분만 구현
 */
public class AsteroidsGame extends Application {
	public static final int WIDTH = 500;
	public static final int HEIGHT = 500;
	public static final int MAXLEVEL = 10;
	// GUI Nodes
	private BorderPane mainPane = new BorderPane();
	private Button newgameButton = new Button("게임 시작");
	private TextField scoreField = new TextField();
	// 
	private UserShip usership = new UserShip();
	private Pane space = new Pane();
	private List<Missile> missileList = new ArrayList<>();
	// usership movement
	private RotateTransition clockwiseRotation 
		= new RotateTransition(Duration.millis(50d), usership);
	private RotateTransition anticlockwiseRotation 
		= new RotateTransition(Duration.millis(50d), usership);
	private Asteroid prevAsteroid = null;
	// 게임 로직
	private Timeline asteroidGenerationTimeline = new Timeline();
	private int gameLevel = 1;
	private int score = 0;
	private AsteroidFactory asteroidFactory 
//		= new AsteroidDiamondFactory();
//		= new AsteroidRectangleFactory();
		= new AsteroidPolygonFactory();
	
	// 주어진 행성을 출발지에서 목적지까지 이동
	private void moveAsteroid(Asteroid asteroid) {
		AsteroidMovement asteriodTransition 
			= new AsteroidMovement(asteroid, usership, missileList, this);
		asteriodTransition.play();
		asteriodTransition.setOnFinished(e->space.getChildren().remove(asteroid));
	}
	
	// 주어진 행성을 반으로 나누어 각 반을 다시 목적지까지 이동
	public void explodeAsteroid(Asteroid asteroid, Missile missile) {
		if(prevAsteroid==asteroid) return;
		prevAsteroid = asteroid;
		space.getChildren().remove(asteroid);
		space.getChildren().remove(missile.get());
		updateScore(asteroid.size);
		if(asteroid.size!=AsteroidSize.SMALL) {
			Location startLoc = asteroid.getStartLoc();
			Location centerLoc = new Location(
				startLoc.x()+asteroid.getTranslateX(),
				startLoc.y()+asteroid.getTranslateY());
			Location[] destLocs = asteroid.getNewDestinationLocs();
			
			Asteroid left = asteroidFactory.createAsteroid(asteroid, centerLoc, destLocs[0]);
			Asteroid right = asteroidFactory.createAsteroid(asteroid, centerLoc, destLocs[1]);
			space.getChildren().add(left);
			space.getChildren().add(right);
			moveAsteroid(left);
			moveAsteroid(right);
		}
	}

	private void updateScore(AsteroidSize size) {
		switch(size) {
		case LARGE:
			Sound.play("large_explosion");
			score += 250;
			break;
		case MEDIUM:
			Sound.play("medium_explosion");
			score += 100;
			break;
		default:
			Sound.play("small_explosion");
			score += 25;
		}
		scoreField.setText(""+score);
	}
	
	// 초기 위치에서 재시작
	private void restartUserShip() {
		RotateTransition cancelRotateTransition 
			= new RotateTransition(Duration.millis(10d), usership);
		cancelRotateTransition.setToAngle(0);
		cancelRotateTransition.setCycleCount(1);
		cancelRotateTransition.setOnFinished(e->{
			usership.init();
			space.getChildren().add(usership);
		});
		cancelRotateTransition.play();
	}
	
	// 주인공 우주선 폭파
	public void explodeShip() {
		if(usership.hasCrashed()) return;
		if(usership.isMoving()) usership.stop();		
		Sound.play("ship_explosion");
		usership.explode();
		PauseTransition explodeTransition = new PauseTransition(Duration.millis(500d));
		explodeTransition.setOnFinished(e->space.getChildren().remove(usership));
		PauseTransition restartTransition = new PauseTransition(Duration.millis(500d));
		restartTransition.setOnFinished(e->restartUserShip());
		SequentialTransition st = new SequentialTransition();
		st.getChildren().addAll(explodeTransition, restartTransition);
		st.play();
	}
	
	// 행성 생성
	private void createAsteroid() {
		mainPane.requestFocus();
		Asteroid asteroid = asteroidFactory.createAsteroid(gameLevel);	
		space.getChildren().add(asteroid);
		moveAsteroid(asteroid);
	}
	
	// 키보드 조작 처리
	public void keyHandle(KeyEvent event) {	
		switch(event.getCode()){
		case LEFT: anticlockwiseRotation.play(); break;
		case RIGHT: clockwiseRotation.play(); break;
		case UP: 
			if(usership.hasCrashed()||usership.isMoving()) break;
			Sound.play("thrust");
			usership.move();
			break;
		case DOWN: 
			if(usership.isMoving()) usership.stop(); 
			break;
		case SPACE: 
			fireMissile();
			break;
		case SHIFT: 
			if(usership.isMoving()) usership.stop();
			usership.jump();
			break;
		default:
		}
		event.consume(); 
	}

	// 미사일 발사
	private void fireMissile() {
		usership.realign();
		Location startLoc = usership.getCurrentLoc();
		Location targetLoc = usership.computeTarget();
		Missile missile = new Missile(startLoc,targetLoc,usership.getTheta());
		missileList.add(missile);
		space.getChildren().add(missile.get());
		missile.setOnFinished(e->{
			space.getChildren().remove(missile.get());
			missileList.remove(missile);
		});
		missile.play();
		Sound.play("fire");
	}
	
	private void newgame() {
		asteroidGenerationTimeline.stop();
		if(usership.isMoving()) usership.stop(); 
		scoreField.setText("0");
		space.getChildren().clear();
		gameLevel = 1;
		score = 0;
		restartUserShip();
		asteroidGenerationTimeline.play();
		space.requestFocus();
	}
	
	private Pane constructControlPane() {
		HBox controlPane = new HBox();
		controlPane.setSpacing(10);
		controlPane.setPadding(new Insets(10));
		Region spacer = new Region();
		HBox.setHgrow(spacer, Priority.ALWAYS);
		scoreField.setEditable(false);
		scoreField.setText("0");
		controlPane.getChildren().addAll(newgameButton,spacer,scoreField);
		newgameButton.setOnAction(e->newgame());
		return controlPane;
	}
	
	@Override
	public void start(Stage mainStage) throws Exception {
		mainPane.setOnKeyPressed(e->keyHandle(e));
		
		space.setBackground(
			new Background(new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY)));
		mainPane.setTop(constructControlPane());
		mainPane.setCenter(space);
		
		mainStage.setTitle("KoreaTech Asteroid");
		mainStage.setScene(new Scene(mainPane,500,500));
		mainStage.setResizable(false);
		mainStage.show();	
		
		// 2초마다 소행성 생성
		asteroidGenerationTimeline.getKeyFrames().add(
			new KeyFrame(Duration.millis(2000),e->createAsteroid()));
		asteroidGenerationTimeline.setCycleCount(Animation.INDEFINITE);
		//asteroidGenerationTimeline.setCycleCount(3);
	
		clockwiseRotation.setByAngle(20);
		clockwiseRotation.setCycleCount(1);
		clockwiseRotation.setOnFinished(e->usership.changeAngle(20));
		anticlockwiseRotation.setByAngle(-20);
		anticlockwiseRotation.setCycleCount(1);
		anticlockwiseRotation.setOnFinished(e->usership.changeAngle(-20));
	}

	public static void main(String[] args) {
		Application.launch(args);
	}
}