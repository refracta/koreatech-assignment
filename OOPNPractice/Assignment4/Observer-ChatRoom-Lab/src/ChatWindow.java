import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;

import java.util.List;
import java.util.Optional;

/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file UserChatWindow.java
 * 각 사용자의 채팅창 (View+Controller 역할, 모델은 User 클래스)
 * 관찰자 패턴: User subject에 대한 관찰자
 */
public class ChatWindow extends Stage {
    private final Background yellowBackground =
            new Background(new BackgroundFill(Color.YELLOW, CornerRadii.EMPTY, Insets.EMPTY));
    private User user;
    private CheckBox isOnline = new CheckBox("온라인");
    private ComboBox<String> roomChoice = new ComboBox<>();
    private ListView<Pane> chatArea = new ListView<>();
    private TextArea sendArea = new TextArea();
    private Button sendButton = new Button("전송");
    private int selectedIndex = -1;
    private boolean rowSelected = false;

    public ChatWindow(User user) {
        this.user = user;
        BorderPane mainPane = new BorderPane();

        chatArea.setEditable(false);
        chatArea.getSelectionModel().selectedItemProperty()
                .addListener((o, oV, nV) -> messageSelected());
        mainPane.setTop(constructChoiceView());
        mainPane.setCenter(chatArea);
        mainPane.setBottom(constructSendView());

        VBox topPane = new VBox();
        topPane.getChildren().addAll(constructMenuBar(), mainPane);

        setTitle(user.getUserID());
        setScene(new Scene(topPane, 300, 300));
    }

    public static boolean chatConfirmDialog(String title, String content,
                                            String okButton, String cancelButton) {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        ButtonType buttonTypeOK = new ButtonType(okButton, ButtonData.OK_DONE);
        ButtonType buttonTypeCancel = new ButtonType(cancelButton, ButtonData.CANCEL_CLOSE);
        alert.getButtonTypes().setAll(buttonTypeOK, buttonTypeCancel);
        ImageView icon = new ImageView(new Image("koreatech.jpg"));
        icon.setFitHeight(80);
        icon.setPreserveRatio(true);
        alert.setGraphic(icon);
        Optional<ButtonType> result = alert.showAndWait();
        return (result.isPresent() && result.get() == buttonTypeOK);
    }

    private HBox constructChoiceView() {
        HBox choiceView = new HBox();
        roomChoice.getItems().addAll(user.getRooms());
        roomChoice.getSelectionModel().select(0);
        roomChoice.getSelectionModel().selectedItemProperty()
                .addListener((o, ov, nv) -> roomChanged(nv));
        roomChoice.setMinWidth(200);
        isOnline.setSelected(true);
        isOnline.setOnAction(e -> onlineStatusChanged());
        choiceView.setPadding(new Insets(10));
        choiceView.setSpacing(10);
        choiceView.getChildren().addAll(roomChoice, isOnline);
        return choiceView;
    }

    private HBox constructSendView() {
        HBox sendView = new HBox();
        sendView.setPadding(new Insets(10));
        sendView.setSpacing(10);
        sendView.getChildren().addAll(sendArea, sendButton);
        sendArea.setPrefRowCount(2);
        sendArea.setPrefColumnCount(40);
        sendArea.focusedProperty().addListener((o, ov, nv) -> {
            chatArea.getSelectionModel().clearSelection();
            rowSelected = false;
        });
        sendButton.setMinWidth(60);
        sendButton.setMinHeight(60);
        sendButton.setOnAction(e -> sendMessage());
        return sendView;
    }

    private MenuBar constructMenuBar() {
        MenuItem leaveRoomMenuItem = new MenuItem("채팅방 나가기");
        MenuItem clearRoomMenuItem = new MenuItem("채팅방 지우기");
        MenuItem deleteMessageMenuItem = new MenuItem("메시지 삭제");
        leaveRoomMenuItem.setOnAction(e -> leaveRoom());
        clearRoomMenuItem.setOnAction(e -> clearRoom());
        deleteMessageMenuItem.setOnAction(e -> deleteMessage());
        Menu setupMenu = new Menu("설정");
        setupMenu.getItems().addAll(leaveRoomMenuItem, clearRoomMenuItem, deleteMessageMenuItem);
        MenuBar menuBar = new MenuBar();
        menuBar.getMenus().add(setupMenu);
        return menuBar;
    }

    public void onlineStatusChanged() {
        user.setOnline(isOnline.isSelected());
        if (user.isOnline()) {
            sendButton.setDisable(false);
            sendArea.setEditable(true);
            for (var roomName : user.getRooms())
                ChatServer.getServer().requestMessages(user.getUserID(), roomName);
        } else {
            sendButton.setDisable(true);
            sendArea.setEditable(false);
        }
    }

    public void roomChanged(String roomName) {
        if (roomName != null)
            updateChatArea(roomName);
    }

    public void sendMessage() {
        String roomName = roomChoice.getSelectionModel().getSelectedItem();
        String message = sendArea.getText();
        if (message.length() != 0) {
            ChatServer.getServer().sendMessage(roomName, new ChatMessage(user.getUserID(), message));
            sendArea.setText("");
            sendArea.requestFocus();
        }
    }

    public void leaveRoom() {
        String roomName = roomChoice.getSelectionModel().getSelectedItem();
        if (chatConfirmDialog("코리아텍 ChatTalk",
                roomName + "에서 나가시겠습니까???",
                "나가기", "취소")) {
            user.leaveRoom(roomName);
            ChatServer.getServer().deleteUserFromRoom(user.getUserID(), roomName);
            if (user.getRooms().length >= 1) {
                roomChoice.getItems().remove(roomName);
                roomChoice.getSelectionModel().select(0);
                roomName = roomChoice.getSelectionModel().getSelectedItem();
                update(roomName);
            } else close();
        }
    }

    private void messageSelected() {
        selectedIndex = chatArea.getSelectionModel().getSelectedIndex();
        rowSelected = true;
    }

    private void deleteMessage() {
        if (rowSelected) {
            String roomName = roomChoice.getSelectionModel().getSelectedItem();
            List<ChatMessage> roomLog = user.getRoomLog(roomName);
            ChatMessage toDeleteMessage = roomLog.get(selectedIndex);
            user.deleteMessage(roomName, selectedIndex);
            if (toDeleteMessage.getSenderID().equals(user.getUserID())) {
                ChatServer.getServer().deleteMessage(roomName, toDeleteMessage.getIndex());
            }
            update(roomName);
        }
    }

    public void clearRoom() {
        String roomName = roomChoice.getSelectionModel().getSelectedItem();
        if (chatConfirmDialog("코리아텍 ChatTalk",
                roomName + "의 내용을 모두 지우시겠습니까?",
                "지우기", "취소")) {
            user.clearRoom(roomName);
            update(roomName);
        }
    }

    // user에서 통보할 때 사용하는 메소드
    public void update(String roomName) {
        roomChoice.getSelectionModel().select(roomName);
        updateChatArea(roomName);
    }

    private void updateChatArea(String roomName) {
        chatArea.getItems().clear();
        List<ChatMessage> chats = user.getRoomLog(roomName);
        for (ChatMessage chat : chats) {
            String message = chat.getSenderID() + ": " + chat.getContent();
            StackPane pane = new StackPane();
            pane.setPadding(new Insets(5d));
            Text text = new Text(message);
            text.setWrappingWidth(260d);
            text.setTextAlignment(TextAlignment.JUSTIFY);
            pane.getChildren().add(text);
            if (chat.getSenderID().equals(user.getUserID()))
                pane.setBackground(yellowBackground);
            chatArea.getItems().add(pane);
        }
    }
}
