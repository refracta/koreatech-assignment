/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta 
 * @file DogTest.java
 * 테스트 프로그램
 */
public class DogTest {
	
	public static void main(String[] args) {
		Dog mimi = new Dog("미미");
		mimi.setBarkStrategy(new WalStrategy());
		mimi.bark();
		Dog general = new Dog("장군");
		general.setBarkStrategy(new MeongStrategy());
		general.bark();		
		general.setBarkStrategy(new WalStrategy());
		general.bark();		
	}

}
