import java.util.concurrent.ThreadLocalRandom;
/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidFactory.java: 팩토리 메소드 패턴에서 생산자
 */
public abstract class AsteroidFactory {
	// 이동방향이 아니라 시작 위치 정보
	private Direction startDirection; 
	// 이동하는 속도는 동일 구간을 이동하는데 걸리는 ms로 표현함 
	// 따라서 값이 작을 수록 빠르게 움직임
	// 레벨이 증가할 수록 빠르게 이동활 확률이 높아짐
	protected int getSpeed(int level) { // level: 1~10
		int speedProb = level*3+15; // 18 ~ 45
		int speed = ThreadLocalRandom.current().nextInt(200);
		int currProb = ThreadLocalRandom.current().nextInt(100);
		if(currProb<=speedProb/2) speed += 2000; 		//  9% ~ 22%
		else if(currProb<=speedProb) speed += 2500;		// 18% ~ 45% 
		else if(currProb<=speedProb*2) speed += 3000;	// 36% ~ 90%
		else speed += 3500;								// 64% ~ 10%
		return speed;
	}
	protected AsteroidSize getRandomSize(int level) {
		int radiusProb = level*3+15;
		int currProb = ThreadLocalRandom.current().nextInt(100);
		if(currProb<=radiusProb/2) return AsteroidSize.LARGE;
		else if(currProb<=radiusProb) return AsteroidSize.SMALL;
		else return AsteroidSize.MEDIUM;
	}
	// 소행성의 크기는 원 개념을 이용하여 반지름으로 나타냄
	// 레벨이 높을수록 크기가 커질 확률이 높아짐
	protected int getRadius(AsteroidSize size) {
		int radius = ThreadLocalRandom.current().nextInt(10);
		return switch(size) {
		case LARGE -> radius += 60;
		case MEDIUM -> radius += 40;
		default -> radius += 10;
		};
	}
	
	protected Location getStartLocation(int radius) {
		int xLoc = ThreadLocalRandom.current().nextInt(AsteroidsGame.WIDTH);
		int yLoc = ThreadLocalRandom.current().nextInt(AsteroidsGame.HEIGHT);
		startDirection = Direction.values()[ThreadLocalRandom.current().nextInt(4)];
		switch(startDirection) {
		case NORTH: 
			return new Location(xLoc, -radius);
		case WEST:  
			return new Location(-radius, yLoc);
		case SOUTH: 
			return new Location(xLoc, radius+AsteroidsGame.HEIGHT);
		default: // EAST
			return new Location(radius+AsteroidsGame.WIDTH, yLoc);
		}
	}
	protected Location getDestLocation(int radius) {
		int xLoc = ThreadLocalRandom.current().nextInt(AsteroidsGame.WIDTH);
		int yLoc = ThreadLocalRandom.current().nextInt(AsteroidsGame.HEIGHT);
		switch(startDirection) {
		case NORTH:
			return new Location(xLoc, radius+AsteroidsGame.HEIGHT);
		case WEST:
			return new Location(radius+AsteroidsGame.WIDTH, yLoc);
		case SOUTH: 
			return new Location(xLoc, -radius);
		default: // EAST
			return new Location(-radius, yLoc);
		}
	}
	// 생성 프레임워크 (template method)
	public final Asteroid createAsteroid(int level) {
		AsteroidSize size = getRandomSize(level);
		int radius = getRadius(size);
		Location startLoc = getStartLocation(radius);
		Location destLoc = getDestLocation(radius);
		Double[] points = createPoints(startLoc, radius);
		return new Asteroid(size, level, startDirection, startLoc, destLoc, getSpeed(level), points);
	}
	public final Asteroid createAsteroid(
		Asteroid asteroid, Location startLoc, Location destLoc) {
		AsteroidSize size = AsteroidSize.MEDIUM;
		if(asteroid.size==AsteroidSize.MEDIUM) size = AsteroidSize.SMALL;
		Double[] points = createPoints(startLoc, getRadius(size));
		return new Asteroid(size, asteroid.level, 
			asteroid.startDirection, startLoc, destLoc, getSpeed(asteroid.level), points);
	}
	// 자식들이 구현해야 하는 팩토리 메소드의 일부분 
	protected abstract Double[] createPoints(Location centerLoc, int radius);
}
