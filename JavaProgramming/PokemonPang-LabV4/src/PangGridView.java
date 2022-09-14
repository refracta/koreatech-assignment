import java.util.List;

import javafx.animation.Animation;
import javafx.animation.PauseTransition;
import javafx.animation.SequentialTransition;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.effect.Blend;
import javafx.scene.effect.BlendMode;
import javafx.scene.effect.Glow;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.util.Duration;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 * @author refracta 
 * 포켓몬팡의 뷰 클래스: 화면 처리
 * BorderPane 상속, Top과 center만 사용
 * 7x7 이미지는 ImageView 2차원 배열 사용
 */
public class PangGridView extends BorderPane {
	// GUI Nodes
	private Group pangGrid = new Group();
	private TextField timeLeftField = new TextField();
	private TextField scoreField = new TextField();
	private TextField comboField = new TextField();
	// 선택 효과
	private Rectangle srcBorder = new Rectangle(0,0,	
		PangUtility.POKETMONIMAGESIZE, PangUtility.POKETMONIMAGESIZE);
	// 힌트 효과
	private SequentialTransition hintEffect = new SequentialTransition();
	private Location hintLoc = null;
	// Main Grid
	private ImageView[][] gridView 
		= new ImageView[PangUtility.NUMBEROFMONS][PangUtility.NUMBEROFMONS];

	public PangGridView(){
		for(int r=0; r<gridView.length; r++){
			for(int c=0; c<gridView[r].length; c++){
				gridView[r][c] = new ImageView(Pokemon.POKEBALL.getImage());
				gridView[r][c].setLayoutX(c*80);
				gridView[r][c].setLayoutY(r*80);
				gridView[r][c].setFitWidth(80);
				gridView[r][c].setPreserveRatio(true);
				pangGrid.getChildren().add(gridView[r][c]);
			}
		}
		setTop(constructStatePane());
		setCenter(pangGrid);
		srcBorder.setStroke(Color.GOLD);
		srcBorder.setStrokeWidth(2);
		srcBorder.setFill(null);
	}
	
	private HBox constructStatePane(){
		HBox statePane = new HBox();
		statePane.setPadding(new Insets(10));
		statePane.setSpacing(10);
		statePane.setAlignment(Pos.CENTER);
		timeLeftField.setEditable(false);
		scoreField.setEditable(false);
		timeLeftField.setMaxWidth(80);
		scoreField.setMaxWidth(120);
		comboField.setMaxWidth(80);
		statePane.getChildren().addAll(
			new Label("남은 시간"),
			timeLeftField,
			new Label("점수"),
			scoreField,
			new Label("콤보"),
			comboField
		);
		return statePane;
	}
	
	public void updateTime(String timeLeft){
		timeLeftField.setText(timeLeft);
	}
	public void updateScore(String score){
		scoreField.setText(score);
	}
	public void updateCombo(String comboCount){
		comboField.setText(comboCount);
	}
	public void updateHintLoc(Location hintLoc){
		this.hintLoc = hintLoc;
	}
	
	public void update(Pokemon[][] gridData) {
		for(int r=0; r<PangUtility.GRIDSIZE; r++)
			for(int c=0; c<PangUtility.GRIDSIZE; c++)
				gridView[r][c].setImage(gridData[r][c].getImage());
	}
	
	public void update(Pokemon[][] gridData, List<Location> locationList) {
		for(Location loc: locationList)
			gridView[loc.r()][loc.c()].setImage(gridData[loc.r()][loc.c()].getImage());
	}
	
	public void showEffect(Location loc) {
		srcBorder.setLayoutX(loc.c()*PangUtility.POKETMONIMAGESIZE);
		srcBorder.setLayoutY(loc.r()*PangUtility.POKETMONIMAGESIZE);
		pangGrid.getChildren().add(srcBorder);
	}
	
	public void removeEffect() {
		pangGrid.getChildren().remove(srcBorder);
	}
	
	public void showHint(){
		if(hintLoc==null) return;
		hintEffect.stop();
		hintEffect.getChildren().clear();
		PauseTransition blendEffect = new PauseTransition(Duration.millis(300));
		blendEffect.setOnFinished(event->{
			Blend blend = new Blend();
			blend.setMode(BlendMode.COLOR_BURN);
			gridView[hintLoc.r()][hintLoc.c()].setEffect(blend);
		});
		PauseTransition glowEffect = new PauseTransition(Duration.millis(100));
		glowEffect.setOnFinished(event->{
			Glow glow = new Glow();
			glow.setLevel(1.0);
			gridView[hintLoc.r()][hintLoc.c()].setEffect(glow);
		});
		hintEffect.getChildren().addAll(glowEffect,blendEffect);
		hintEffect.setCycleCount(Animation.INDEFINITE);
		hintEffect.play();
	}
	public void removeHint(){
		if(hintLoc==null) return;
		gridView[hintLoc.r()][hintLoc.c()].setEffect(null);
		hintEffect.stop();
	}
}
