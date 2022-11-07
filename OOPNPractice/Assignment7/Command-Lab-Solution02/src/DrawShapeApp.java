import java.awt.*;
import java.util.Stack;
import java.util.function.Consumer;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;
import javafx.stage.Stage;

/**
 * @author 김상진
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class DrawShapeApp extends Application {
    private static final int HEIGHT = 500;
    private static final int WIDTH = 500;
    private static final int RADIUS = 40;

    private RadioButton drawButton = new RadioButton("추가");
    private RadioButton selectButton = new RadioButton("선택");
    private Button undoButton = new Button("취소");
    private Button redoButton = new Button("재실행");

    private ComboBox<String> shapeChoice = new ComboBox<>();
    private ShapeType currentShape = ShapeType.SQUARE;
    private Shape selectedShape = null;

    private ContextMenu popupMenu = new ContextMenu();

    private Pane centerPane = new Pane();

    private Stack<Command> undoList = new Stack<>();
    private Stack<Command> redoList = new Stack<>();

    private void executeCommand(Command command) {
        command.execute();
        undoList.push(command);
        redoList.clear();
        redoButton.setDisable(true);
    }

    private void drawShape(double x, double y) {
        executeCommand(new DrawShapeCommand(x, y, currentShape, RADIUS, centerPane));
    }

    private void fillShape() {
        ColorPicker picker = new ColorPicker();
        picker.setLayoutX(selectedShape.getBoundsInLocal().getCenterX());
        picker.setLayoutY(selectedShape.getBoundsInLocal().getCenterY());
        centerPane.getChildren().add(picker);
        picker.setOnAction(e -> {
            Color newColor = picker.getValue();
            centerPane.getChildren().remove(picker);
            executeCommand(new ChangeColorCommand(newColor, selectedShape));
        });
    }

    private void deleteShape() {
        executeCommand(new DeleteCommand(centerPane, selectedShape));
    }

    private void selectShape(double x, double y, double screenX, double screenY) {
        var shapeList = centerPane.getChildren();
        for (int i = shapeList.size() - 1; i >= 0; --i) {
            if (shapeList.get(i).getBoundsInLocal().contains(x, y)) {
                selectedShape = (Shape) shapeList.get(i);
                popupMenu.show(centerPane, screenX, screenY);
                break;
            }
        }
    }

    private void mouseHandle(MouseEvent mouseEvent) {
        double x = mouseEvent.getX();
        double y = mouseEvent.getY();
        if (x < RADIUS) x = RADIUS;
        else if (x + RADIUS > WIDTH) x = WIDTH - RADIUS;
        if (y < RADIUS) y = RADIUS;
        else if (y + RADIUS > HEIGHT) y = HEIGHT - RADIUS;
        if (drawButton.isSelected()) drawShape(x, y);
        else selectShape(x, y, mouseEvent.getScreenX(), mouseEvent.getScreenY());
        if (!centerPane.getChildren().isEmpty())
            undoButton.setDisable(false);
    }

    private void undo() {
        if (!undoList.isEmpty()) {
            Command command = undoList.pop();
            redoList.push(command);
            command.undo();
            redoButton.setDisable(false);
            if (undoList.isEmpty()) undoButton.setDisable(true);
        }
    }

    private void redo() {
        if (!redoList.isEmpty()) {
            Command command = redoList.pop();
            undoList.push(command);
            command.execute();
            undoButton.setDisable(false);
            if (redoList.isEmpty()) redoButton.setDisable(true);
        }
    }

    private HBox constructControlPane() {
        String[] shapeList = {"Square", "Circle", "Triangle"};
        shapeChoice.getItems().addAll(shapeList);
        shapeChoice.getSelectionModel().selectFirst();
        shapeChoice.setOnAction(e ->
                currentShape = ShapeType.valueOf(shapeChoice.getSelectionModel().getSelectedItem().toUpperCase())
        );

        ToggleGroup actionGroup = new ToggleGroup();
        actionGroup.getToggles().addAll(drawButton, selectButton);
        drawButton.setSelected(true);
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        undoButton.setDisable(true);
        redoButton.setDisable(true);
        undoButton.setOnAction(e -> undo());
        redoButton.setOnAction(e -> redo());

        HBox controlPane = new HBox();
        controlPane.setPadding(new Insets(10));
        controlPane.setSpacing(10);
        controlPane.getChildren().addAll(shapeChoice, drawButton, selectButton, spacer, undoButton, redoButton);
        return controlPane;
    }

    private void constructPopupMenu() {
        MenuItem fillColorItem = new MenuItem("채우기 색 변경");
        fillColorItem.setOnAction(e -> fillShape());
        MenuItem deleteItem = new MenuItem("삭제");
        deleteItem.setOnAction(e -> deleteShape());
        popupMenu.getItems().addAll(fillColorItem, deleteItem);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        BorderPane mainPane = new BorderPane();

        centerPane.setBackground(
                new Background(new BackgroundFill(Color.WHITE, CornerRadii.EMPTY, Insets.EMPTY)));
        centerPane.setMinWidth(500d);
        centerPane.setMinHeight(500d);
        centerPane.setOnMouseClicked(e -> mouseHandle(e));

        mainPane.setCenter(centerPane);
        mainPane.setTop(constructControlPane());
        primaryStage.setTitle("도형 그리기");
        primaryStage.setScene(new Scene(mainPane));
        primaryStage.setResizable(false);
        primaryStage.show();

        constructPopupMenu();
    }

    public static void main(String[] args) {
        Application.launch(args);
    }

}
