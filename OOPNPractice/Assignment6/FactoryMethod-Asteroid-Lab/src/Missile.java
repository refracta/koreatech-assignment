import java.util.concurrent.ThreadLocalRandom;

import javafx.animation.Transition;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.util.Duration;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * Missile.java: 미사일 + 미사일의 움직임 처리
 */
public class Missile extends Transition {
	private int id;
	private double deltaX;
	private double deltaY;
	private Line M = null;
	public Missile(Location startLoc, Location targetLoc, double theta){
		super();
		id = ThreadLocalRandom.current().nextInt();
		double endX = startLoc.x() + 3*Math.cos(theta);
		double endY = startLoc.y() + 3*Math.sin(theta);	
		M = new Line(startLoc.x(), startLoc.y(), endX, endY);
		M.setStroke(Color.WHITE);
		M.setStrokeWidth(3);
		double distance = Utility.getDistance(startLoc, targetLoc);
		deltaX = targetLoc.x()-startLoc.x();
		deltaY = targetLoc.y()-startLoc.y();
		setCycleDuration(Duration.millis(distance*5));
		setCycleCount(1);
	}
	
	public Line get() {
		return M;
	}
	
	@Override protected void interpolate(double frac) {
		M.setTranslateX(frac*deltaX);
		M.setTranslateY(frac*deltaY);
	}
	
	@Override public boolean equals(Object other) {
		if(other==null||getClass()!=other.getClass()) return false;
		if(this==other) return true;
		Missile m = (Missile)other;
		return id==m.id;
	}
}
