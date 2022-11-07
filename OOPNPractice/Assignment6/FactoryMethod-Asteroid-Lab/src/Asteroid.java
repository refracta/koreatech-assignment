import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * Asteroid.java: 소행성
 */
public class Asteroid extends Polygon{
	public final AsteroidSize size;
	public final int level;
	public final Direction startDirection;
	private Location startLoc;
	private Location destLoc;
	private int speed;
	
	// 주어진 좌표를 다각형의 꼭짓점으로 사용하여 소행성을 생성함
	public Asteroid(AsteroidSize size, int level, 
		Direction startDirection, Location startLoc, Location destLoc, int speed, Double[] points) {
		this.size = size;
		this.level = level;
		this.startDirection = startDirection;
		this.startLoc = startLoc;
		this.destLoc = destLoc;
		this.speed = speed;
		getPoints().addAll(points);
		setStroke(Color.LIGHTGRAY);
		setFill(null);
		setStrokeWidth(3);
	}
	
	public Location getStartLoc() {
		return startLoc;
	}
	public Location getDestLoc() {
		return destLoc;
	}
	public int getSpeed() {
		return speed;
	}
	public void setDestLoc(Location destLoc) {
		this.destLoc = destLoc;
	}
	
	public Location[] getNewDestinationLocs() {
		Location[] destLocs = new Location[2];
		switch(startDirection) {
		case NORTH, SOUTH:
			destLocs[0] = new Location(destLoc.x()+200, destLoc.y());
			destLocs[1] = new Location(destLoc.x()-200, destLoc.y());
			break;
		case EAST:
			destLocs[0] = new Location(startLoc.x(), destLoc.y()+200);
			destLocs[1] = new Location(destLoc.x(), destLoc.y()-200);
			break;
		default: // WEST
			destLocs[0] = new Location(destLoc.x(), destLoc.y()-200);
			destLocs[1] = new Location(startLoc.x(), destLoc.y()+200);
			break;
		}
		return destLocs;
	}
}
