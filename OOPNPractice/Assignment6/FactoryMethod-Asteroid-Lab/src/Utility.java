/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * Utility.java: 기타 공통적으로 사용하는 상수와 함수
 */
public interface Utility {
	double radian = Math.PI / 180d;
	Location initLoc = new Location(250d, 240d);
	
	public static double getDistance(Location start, Location end) {
		double diffX = start.x()-end.x();
		double diffY = start.y()-end.y();
		return Math.sqrt(diffX*diffX+diffY*diffY);
	}
	
}
