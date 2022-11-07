import java.util.ArrayList;
import java.util.List;

import javafx.animation.Transition;
import javafx.geometry.Bounds;
import javafx.scene.shape.Rectangle;
import javafx.util.Duration;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidMovement.java: 소행성 움직임을 처리하는 클래스
 */
public class AsteroidMovement extends Transition {
	private Asteroid asteroid;
	private double deltaX;
	private double deltaY;
	private UserShip ship;
	private boolean shipCrashed = false;
	private List<Missile> missileList;
	private AsteroidsGame game = null;
	public AsteroidMovement(Asteroid asteroid, UserShip ship, 
		List<Missile> missileList, AsteroidsGame game) {
		this.asteroid = asteroid;
		Location startLoc = asteroid.getStartLoc();
		Location targetLoc = asteroid.getDestLoc();
		this.ship = ship;
		this.missileList = missileList;
		this.game = game;
		deltaX = targetLoc.x()-startLoc.x();
		deltaY = targetLoc.y()-startLoc.y();
		setCycleDuration(Duration.millis(asteroid.getSpeed()));
		setCycleCount(1);
	}
	@Override protected void interpolate(double frac) {
		asteroid.setTranslateX(frac*deltaX);
		asteroid.setTranslateY(frac*deltaY);
		if(shipCrashed) return;
		Bounds aBound = asteroid.getBoundsInLocal();
		Rectangle aRec = new Rectangle(
			aBound.getMinX()+asteroid.getTranslateX(),
			aBound.getMinY()+asteroid.getTranslateY(),
			aBound.getWidth(), aBound.getHeight());
		if(!ship.hasCrashed()) {
			Bounds sBound = ship.getBoundsInLocal();
			Rectangle sRec = new Rectangle(
				sBound.getMinX()+ship.getTranslateX(),
				sBound.getMinY()+ship.getTranslateY(),
				sBound.getWidth(), sBound.getHeight());
			if(aRec.intersects(sRec.getBoundsInLocal())) {
				shipCrashed = true;
				game.explodeShip();
			}
		}
		List<Missile> cloned = new ArrayList<>(missileList);
		for(var missile: cloned) {
			Bounds mBound = missile.get().getBoundsInLocal();
			Rectangle mRec = new Rectangle(
				mBound.getMinX()+missile.get().getTranslateX(),
				mBound.getMinY()+missile.get().getTranslateY(),
				mBound.getWidth(), mBound.getHeight());
			if(aRec.intersects(mRec.getBoundsInLocal())) {
				missileList.remove(missile);
				stop();
				missile.stop();
				game.explodeAsteroid(asteroid, missile);
			}
		}
	}
}
