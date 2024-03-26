/**
 * @author 김상진, refracta
 * 상태 패턴: 상태 기반 전이 방식
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public interface IDoorState {
    void open(Door door);

    void close(Door door);

    void lock(Door door);

    void unlock(Door door);
}
