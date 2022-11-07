/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidSize.java: 소행성의 크기
 * 소행성의 크기는 3종류
 */
public enum AsteroidSize {
	SMALL, MEDIUM, LARGE;
	
	static AsteroidSize valueOf(int index) {
		if(index<0||index>2) throw new IllegalArgumentException();
		return values()[index];
	}
}


