/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴
 * 자동판매기: 자동판매기에서 받는 동전, 지폐의 종류
 */
public enum Currency {
	C10(10), C50(50), C100(100), C500(500), P1000(1000), 
	P5000(5000), P10000(10000);
	public final int value;
	private Currency(int value) {
		this.value = value;
	}
	@Override public String toString() {
		return String.format("%,d원", value);
	}
}
