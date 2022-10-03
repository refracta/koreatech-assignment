import java.util.*;

/*
 * Q1. 이 실습에서는 관찰자 패턴을 사용하여 구현하고 있다.
 * 특히, 채팅방(ChatRoom)을 관찰 대상, 채팅방의 참여자(User)를 관찰자로 모델링하였다.
 * 관찰자 패턴은 크게 push 또는 pull 방법으로 구현할 수 있다.
 * 현재 제시된 소스는 어느 방식으로 구현되어 있는지 설명하시오.
 * A1. pull 방식으로 구현되어 있다. 관찰 대상인 ChatRoom의 updateUsers, updateUser 흐름을 확인해보면
 * 관찰자인 User에게 최종적으로 ChatServer.forwardMessage를 이용하여 User의 update 메소드를 호출해주는 것을 확인할 수 있는데
 * 이 메소드는 roomName와 ChatMessage를 인자로 받게 된다.
 * 그런데 이 때, 바뀐 ChatRoom 객체(이 객체는 심지어 roomName와 roomLogs를 이용해야 얻을 수 있음)가 내포하고 있는 다른 변화한 정보들과,
 * ChatMessage가 가지고 있는 정보들 중 어떤 것이 이번 update간 변화했는지에 대한 내용을 직접 관찰자에게 알려주고 있지는 않다.
 * 따라서 pull 방식으로 구현되어있다고 볼 수 있다.
 * (만약 ChatMessage가 변경 고지의 기본 단위 타입이라고 생각한다면,
 * roomName의 단일한 변화 대상을 직접 고지했다는 점에서는 push라고 볼 수 있는 여지도 있는 것 같음)
 *
 * Q2. 관찰자인 참여자는 하나만 관찰하는 형태가 아니다.
 * 여러 개의 채팅방을 관찰하고 있을 수 있다.
 * 종류는 같지만 관찰 대상이 복수일 수 있는 구조이다.
 * 관찰자는 관찰 대상을 어떻게 구분하는지 간단히 설명하시오.
 * A2. 관찰자는 갱신 메소드에 같이 포함되어 호출되는 roomName 매개변수 식별자를 통해서 서로 다른 채팅방에서 온 갱신 호출을 식별할 수 있다.
 *
 * Q3. 실제 코드를 보면 이 두 객체 외에 관찰 대상과 관찰자로 모델링하는 것이 있다.
 * 그것이 무엇인지 제시하시오.
 * A3. ChatServer(관찰 대상)과 ChatRoom(관찰자)이다. ChatServer는 ChatRoom List를 서버 상태로 가지고 있다가. 이에 변화가 있으면 관찰자인 ChatRoom에게
 * ChatRoom이 가진 deleteUser, deleteMessage, deleteMessage, updateUser와 같은 메소드를 이용하여 고지한다.
 */

/**
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file ChatRoom.java
 * 관찰자 패턴: subject
 * 사용자 목록과 채팅 메시지 목록 유지
 * 채팅룸 목록, 사용자 목록 유지
 */
public class ChatRoom {
    private String roomName;
    private List<ChatMessage> roomLog = new ArrayList<>();
    // Map<사용자ID, 마지막 받은 메시지 색인>
    // 관찰자 목록
    private Map<String, Integer> userList = new HashMap<>();

    public ChatRoom(String name) {
        roomName = Objects.requireNonNull(name);
    }

    public String getRoomName() {
        return roomName;
    }

    // 관찰자 추가
    public boolean addUser(String userID) {
        if (!userList.containsKey(userID)) {
            // userList에 없는 경우
            userList.put(userID, roomLog.size());
            // 현재 채팅방의 마지막 메시지 색인 값으로 추가
            return true;
            // 성공시 true 반환
        } else {
            return false;
            // 추가 실패시 false 반환
        }
    }

    // 관찰자 삭제
    public boolean deleteUser(String userID) {
        if (!userList.containsKey(Objects.requireNonNull(userID)))
            return false;
        userList.remove(userID);
        return true;
    }

    public void newMessage(ChatMessage message) {
        // 예외 처리 추가
        if (!userList.containsKey(Objects.requireNonNull(message).getSenderID())) {
            throw new IllegalArgumentException("존재하지 않는 전송자");
        } else if (roomLog.contains(message)) {
            throw new IllegalArgumentException("중복된 메시지");
        }

        message.setIndex(roomLog.size());
        roomLog.add(message);
        updateUsers();
    }

    // 관찰자 패턴에서 notifyObservers에 해당
    public void updateUsers() {
        userList.keySet().forEach(key -> updateUser(key));
    }

    public void updateUser(String userID) {
        // 예외 처리 추가
        if (!userList.containsKey(Objects.requireNonNull(userID))) {
            throw new IllegalArgumentException("존재하지 않는 사용자");
        }

        for (int i = userList.get(userID); i < roomLog.size(); i++) {
            ChatMessage message = roomLog.get(i);
            if (message.isDeleted()) {
                userList.put(userID, i + 1);
                // 색인 갱신
                continue;
                // 삭제된 메시지인 경우, forwardMessage를 호출하지 않고 넘어감
            }

            boolean fmResult = ChatServer.getServer().forwardMessage(userID, roomName, message);
            if (fmResult) {
                // Online 상태일 때만 색인 갱신 처리
                userList.put(userID, i + 1);
                // 색인 갱신
            } else {
                break;
            }
        }
    }

    public void deleteMessage(int index) {
        if (index >= roomLog.size()) {
            throw new IllegalArgumentException("잘못된 메시지 색인");
        }
        roomLog.get(index).setDeleteFlag();
        // 메시지의 deleteFlag를 true로 설정 
    }
}
