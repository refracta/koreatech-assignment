/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta
 * @file Dog.java
 * 강아지 클래스
 * 전략 객체를 유지하기 위한 멤버 변수를 추가해야 하며,
 * 이 객체를 설정하기 위한
 * void setBarkStrategy(BarkStrategy barkStrategy)를
 * 추가해야 하고, bark 메소드는 이 전략을 사용하도록 수정해야 함
 */
public class Dog {
	private String name;
	private BarkStrategy barkStrategy;

	public void setBarkStrategy(BarkStrategy barkStrategy) {
		this.barkStrategy = barkStrategy;
	}

	public Dog(String name) {
		this.name = name;
	}
	public void bark() {
		System.out.printf("%s: 멍멍%n", name);
	}
}
