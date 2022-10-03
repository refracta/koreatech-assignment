import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.util.ArrayList;
import java.util.List;

/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file KoreaTechChatTalk.java
 * 채팅 프로그램에서 뷰+컨트롤러 역할
 */
public class KoreaTechChatTalk extends Application {
    private List<ChatWindow> chatWindows = new ArrayList<>();
    private Button startButton = new Button("코리아텍 ChatTalk 시작");

    public static void main(String[] args) {
        Application.launch(args);
    }

    // 그룹 채팅 시뮬레이션
    // 두 개의 채팅방을 만들고 총 5명의 사용자 중 한 방에는 4명, 또 다른 방에는 3명 참여
    public void prepareSimulation() {
        ChatServer chatServer = ChatServer.getServer();
        chatServer.addUser(new User("홍길동"));
        chatServer.addUser(new User("임꺽정"));
        chatServer.addUser(new User("장길산"));
        chatServer.addUser(new User("장보고"));
        chatServer.addUser(new User("잭스패로우"));
        chatServer.addRoom("객체지향개발론및실습");
        chatServer.addRoom("놀자");
        chatServer.addUserToRoom("홍길동", "객체지향개발론및실습");
        chatServer.addUserToRoom("임꺽정", "객체지향개발론및실습");
        chatServer.addUserToRoom("장길산", "객체지향개발론및실습");
        chatServer.addUserToRoom("장보고", "객체지향개발론및실습");
        chatServer.addUserToRoom("홍길동", "놀자");
        chatServer.addUserToRoom("임꺽정", "놀자");
        chatServer.addUserToRoom("잭스패로우", "놀자");
        for (User user : chatServer.getUsers()) {
            ChatWindow chatWindow = new ChatWindow(user);
            user.setView(chatWindow);
            chatWindows.add(chatWindow);
        }
    }

    public void startTalkSimulation() {
        startButton.setDisable(true);

        double x = 400;
        double y = 100;
        for (var chatWindow : chatWindows) {
            chatWindow.setX(x);
            chatWindow.setY(y);
            chatWindow.show();
            x += 350;
            if (x == 1100) {
                y += 350;
                x = 50;
            }
        }
    }

    public void stopTalkSimulation() {
        for (ChatWindow chatWindow : chatWindows)
            chatWindow.close();
        startButton.setDisable(false);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("KoreaTech ChatTalk");
        primaryStage.setScene(new Scene(constructButtonPane(), 300, 300));
        primaryStage.setX(50);
        primaryStage.setY(100);
        primaryStage.show();
        primaryStage.getScene().getWindow()
                .addEventFilter(WindowEvent.WINDOW_CLOSE_REQUEST, e -> stopTalkSimulation());
        prepareSimulation();
    }

    private VBox constructButtonPane() {
        Button closeAllButton = new Button("대화창 모두 닫기");
        startButton.setMinWidth(160);
        closeAllButton.setMinWidth(160);

        VBox buttonPane = new VBox();
        buttonPane.setPadding(new Insets(10));
        buttonPane.setSpacing(10);
        buttonPane.setAlignment(Pos.CENTER);
        buttonPane.getChildren().addAll(startButton, closeAllButton);

        startButton.setOnAction(e -> startTalkSimulation());
        closeAllButton.setOnAction(e -> stopTalkSimulation());
        return buttonPane;
    }
}
