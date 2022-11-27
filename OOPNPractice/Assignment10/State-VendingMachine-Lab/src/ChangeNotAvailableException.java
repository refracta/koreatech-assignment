/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴 
 * 자동판매기 거스름 제공 불가 예외: checked 예외 
 */
public class ChangeNotAvailableException extends Exception {
	private static final long serialVersionUID = -6480831563798786756L;
	// 거스름을 제공할 수 없지만 다른 물품을 구매할 수 있으면 이 값을 false로 설정함 
	public final boolean changeReturned;
	public ChangeNotAvailableException(boolean flag) {
		super("거스름돈 준비 불가");
		changeReturned = flag;
	}
}
