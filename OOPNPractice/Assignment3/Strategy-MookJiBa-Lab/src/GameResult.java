/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file GameResult.java
 * 묵찌바, 가위바위보 게임에서 결과를 나타내는 열거형
 * 묵찌바에서 DRAW는 공격실패
 */
public enum GameResult {
    USERWIN, COMPUTERWIN, DRAW;

    public static GameResult[] getOrderedResultArray() {
        return new GameResult[]{DRAW, COMPUTERWIN, USERWIN};
    }
}
