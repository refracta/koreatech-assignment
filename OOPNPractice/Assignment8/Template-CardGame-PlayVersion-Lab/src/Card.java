/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file Card.java
 * 탬플릿 메소드 패턴
 * 카드 한 장을 나타내는 클래스
 * 모양과 숫자
 * 0이면 조커
 */
public record Card(int number, CardFace face) {
    public Card {
        if (number < 0 && number > 13) throw new IllegalArgumentException();
    }

    public String fileName() {
        if (number == 0)
            return face == CardFace.SPADES ? "/image/joker_black.png" : "/image/joker_red.png";
        return String.format("/image/%d%c.png", number, face.toString().charAt(0));
    }

    /**
     * 카드의 실제 점수를 반환하는 함수
     * @return 카드의 실제 점수
     */
    public int getScore() {
        return number < 11 ? number : 10;
    }
}