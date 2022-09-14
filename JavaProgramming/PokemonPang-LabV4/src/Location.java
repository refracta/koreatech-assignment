import java.util.concurrent.ThreadLocalRandom;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 * @author refracta 
 * 그리드 위치를 유지하는 클래스
 */

public record Location(int r, int c){
	public boolean isRight(Location other) {
		return r==other.r && c==other.c+1;
	}
	public boolean isLeft(Location other) {
		return r==other.r && c==other.c-1;
	}
	public boolean isUp(Location other) {
		return r==other.r-1 && c==other.c;
	}
	public boolean isDown(Location other) {
		return r==other.r+1 && c==other.c;
	}
	public static boolean valid(int r, int c){
		return (r>=0&&r<PangUtility.GRIDSIZE && 
				c>=0&&c<PangUtility.GRIDSIZE);
	}
	public static Location getRandomLocation() {
		return new Location(
			ThreadLocalRandom.current().nextInt(PangUtility.GRIDSIZE),
			ThreadLocalRandom.current().nextInt(PangUtility.GRIDSIZE)
		);
	}
}

