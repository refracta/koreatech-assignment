/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제3 - 숫자 야구 게임을 객체지향으로
 * 숫자 야구 게임 상태 열거형
 *
 * @author refracta
 */
public enum BaseballGameStatus {
    CONTINUE("진행"), WIN("사용자 승"), OUT("컴퓨터 승");
    private final String resultMessage;

    /**
     * BaseballGameStatus 객체를 생성한다.
     *
     * @param resultMessage 상태에 따른 결과 메시지
     */
    BaseballGameStatus(String resultMessage) {
        this.resultMessage = resultMessage;
    }

    /**
     * 열거형의 결과 메시지를 반환한다.
     *
     * @return 결과 메시지
     */
    public String getResultMessage() {
        return resultMessage;
    }
}
