import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file ChatServer.java
 * 채팅 프로그램에서 통신 서버와 데이터베이스 서버 역할을 함
 * 채팅룸 목록, 사용자 목록 유지
 */
public class ChatServer {
    private static ChatServer uniqueInstance = null;
    // 데이터베이스 역할을 위한 두 개의 맵
    private Map<String, ChatRoom> chatRooms = new HashMap<>();
    private Map<String, User> users = new HashMap<>();

    private ChatServer() {
    }

    // 싱글톤으로 모델링, 전역변수처럼 사용할 수 있음
    public static ChatServer getServer() {
        if (uniqueInstance == null) uniqueInstance = new ChatServer();
        return uniqueInstance;
    }

    // 데이터베이스 역할을 위한 메소드들
    public void addRoom(String roomName) {
        if (!chatRooms.containsKey(roomName)) // 간단 중복 검사
            chatRooms.put(roomName, new ChatRoom(roomName));
    }

    public void addUser(User user) {
        if (!users.containsKey(user.getUserID())) // 간단 중복 검사
            users.put(user.getUserID(), user);
    }

    public Collection<User> getUsers() {
        return users.values();
    }

    public void addUserToRoom(String userID, String roomName) {
        // 예외 처리 추가
        if (!users.containsKey(Objects.requireNonNull(userID))) {
            throw new IllegalArgumentException("존재하지 않는 사용자: " + userID);
        } else if (!chatRooms.containsKey(Objects.requireNonNull(roomName))) {
            throw new IllegalArgumentException("존재하지 않는 방 이름: " + roomName);
        }

        User user = users.get(userID);
        ChatRoom chatRoom = chatRooms.get(roomName);
        if (chatRoom.addUser(userID)) // 간단 중복 검사
            user.joinRoom(roomName);
    }

    public void deleteUserFromRoom(String userID, String roomName) {
        // 예외 처리 추가
        if (!users.containsKey(Objects.requireNonNull(userID))) {
            throw new IllegalArgumentException("존재하지 않는 사용자: " + userID);
        } else if (!chatRooms.containsKey(Objects.requireNonNull(roomName))) {
            throw new IllegalArgumentException("존재하지 않는 방 이름: " + roomName);
        }

        ChatRoom chatRoom = chatRooms.get(roomName);
        chatRoom.deleteUser(userID);
    }

    // 통신 서버 역할을 위한 메소드들
    // 메시지 삭제 (메시지의 전송자만 가능)
    public void deleteMessage(String roomName, int index) {
        if (!chatRooms.containsKey(Objects.requireNonNull(roomName))) {
            throw new IllegalArgumentException("존재하지 않는 방 이름: " + roomName);
        }
        ChatRoom chatRoom = chatRooms.get(roomName);
        chatRoom.deleteMessage(index);
    }

    // 사용자가 메시지를 전송할 때 사용하는 메소드
    // 사용자가 전송한 메시지를 ChatRoom에 추가함
    // ChatRoom은 관찰자 패턴을 이용하여 가입된 모든 사용자에게 메시지를 전달함
    public void sendMessage(String roomName, ChatMessage message) {
        if (!chatRooms.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException(roomName + " 방이 존재하지 않습니다.");

        ChatRoom chatRoom = chatRooms.get(roomName);
        chatRoom.newMessage(message);
    }

    // ChatRoom에서 각 사용자에게 메시지를 실제 전달할 때 사용
    public boolean forwardMessage(String destID, String roomName, ChatMessage message) {
        if (!users.containsKey(Objects.requireNonNull(destID)))
            throw new IllegalArgumentException(destID + " 사용자가 존재하지 않습니다.");

        User receiver = users.get(destID);
        if (!receiver.isOnline()) return false;
        receiver.update(roomName, message);
        return true;
    }

    public void requestMessages(String receiverID, String roomName) {
        if (!users.containsKey(Objects.requireNonNull(receiverID)))
            throw new IllegalArgumentException(receiverID + " 사용자가 존재하지 않습니다.");
        if (!chatRooms.containsKey(Objects.requireNonNull(roomName)))
            throw new IllegalArgumentException(roomName + " 방이 존재하지 않습니다.");

        chatRooms.get(roomName).updateUser(receiverID);
    }
}
