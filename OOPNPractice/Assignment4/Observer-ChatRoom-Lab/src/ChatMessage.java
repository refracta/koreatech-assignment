import java.util.Objects;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file ChatMessage.java
 * 채팅 메시지 클래스
 * 전송자와 전송 메시지 유지
 */
public class ChatMessage {
    private String senderID;
    private String content;
    private int index;
    private boolean deleteFlag = false;

    public ChatMessage(String senderID, String content) {
        this.senderID = Objects.requireNonNull(senderID);
        this.content = Objects.requireNonNull(content);
    }

    public String getSenderID() {
        return senderID;
    }

    public String getContent() {
        return content;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        if (index < 0) throw new IndexOutOfBoundsException();
        this.index = index;
    }

    public boolean isDeleted() {
        return deleteFlag;
    }

    public void setDeleteFlag() {
        deleteFlag = true;
    }
}
