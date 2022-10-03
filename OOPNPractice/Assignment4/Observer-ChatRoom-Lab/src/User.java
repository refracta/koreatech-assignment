import java.util.*;

/**
 * @author 김상진
 * 채팅 프로그램에서 사용자 역할을 함
 * 가입된 채팅방마다 채팅메시지 목록 유지
 * 채팅방에 대해서는 관찰자, 채팅창에 대해서는 subject
 * @version 2022년도 2학기 관찰자 패턴 실습
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file User.java
 */
public class User {
    private String userID;
    private boolean online = true;
    // Map<채팅방, 채팅메시지 목록>
    private Map<String, List<ChatMessage>> roomLogs = new HashMap<>();
    // 뷰와 사용자는 1:1 관계. Hard Coded Notification
    private ChatWindow chatWindow;

    public User(String userID) {
        this.userID = Objects.requireNonNull(userID);
    }

    public String getUserID() {
        return userID;
    }

    public boolean isOnline() {
        return online;
    }

    public void setOnline(boolean flag) {
        online = flag;
    }

    public void setView(ChatWindow chatWindow) {
        this.chatWindow = chatWindow;
    }

    public void notifyView(String roomName) {
        chatWindow.update(roomName);
    }

    public void joinRoom(String roomName) {
        if (roomLogs.containsKey(Objects.requireNonNull(roomName))) return;

        roomLogs.put(roomName, new ArrayList<ChatMessage>());
    }

    public void leaveRoom(String roomName) {
        if (!roomLogs.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException("가입되지 않은 채팅방");

        roomLogs.remove(roomName);
    }

    public void deleteMessage(String roomName, int index) {
        if (!roomLogs.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException("가입되지 않은 채팅방");

        List<ChatMessage> roomLog = roomLogs.get(roomName);
        if (index >= roomLog.size()) throw new IndexOutOfBoundsException();
        roomLog.remove(index);
    }

    public void update(String roomName, ChatMessage message) {
        if (!roomLogs.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException("가입되지 않은 채팅방");

        roomLogs.get(roomName).add(Objects.requireNonNull(message));
        notifyView(roomName);
    }

    public List<ChatMessage> getRoomLog(String roomName) {
        if (!roomLogs.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException("가입되지 않은 채팅방");
        return roomLogs.get(roomName);
    }

    public void clearRoom(String roomName) {
        if (!roomLogs.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException("가입되지 않은 채팅방");
        roomLogs.get(roomName).clear();
    }

    public String[] getRooms() {
        String[] roomNames = new String[roomLogs.size()];
        roomLogs.keySet().toArray(roomNames);
        return roomNames;
    }

}
