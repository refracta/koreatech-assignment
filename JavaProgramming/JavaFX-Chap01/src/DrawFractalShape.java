import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

import static java.lang.Math.min;
import static java.lang.Math.toRadians;

/**
 * 한국기술교육대학교 컴퓨터공학부 자바프로그래밍 2021학년도 2학기 과제4 - JavaFX: 여러 도형과 이미지를 이용하여 새 개체 정의하기
 *
 * @author refracta
 */
public class DrawFractalShape extends Application {

    /**
     * 프랙탈 트리를 그리는 클래스를 정의한다.
     */
    public static class FractalTree extends Group {
        public FractalTree(double startX, double startY, double angle, double length, int order) {
            constructFractalTree(startX, startY, angle, length, order, true, new ArrayList<>());
        }

        /**
         * 시작 위치와 초기 생성 조건 매개변수를 토대로 프랙탈 트리를 생성한다.
         *
         * @param startX   시작 좌표 X
         * @param startY   시작 좌표 Y
         * @param angle    시작 줄기 각도
         * @param length   시작 줄기 길이
         * @param order    프랙탈 반복 차수
         * @param isFirst  첫 실행 확인 flag (재귀 처리용)
         * @param lineList 이미지 좌표 교정용 Line 배열 (재귀 처리용)
         */
        private void constructFractalTree(double startX, double startY, double angle, double length, int order, boolean isFirst, List<Line> lineList) {
            if (order > 0) {
                double nextX = startX + length * Math.cos(angle);
                double nextY = startY + length * Math.sin(angle);
                Line line = new Line(startX, startY, nextX, nextY);
                // 프랙탈 트리의 줄기를 생성하기 위해 좌표를 계산하고 Line 객체를 생선한다.

                // 현재 차수에 따라 색상을 지정한다, 루트 줄기에서 멀어지면 초록색, 아니면 갈색으로 지정한다.
                if (order > 3) {
                    line.setStroke(Color.SADDLEBROWN);
                } else {
                    line.setStroke(Color.GREEN);
                }
                lineList.add(line);
                ThreadLocalRandom random = ThreadLocalRandom.current();

                // 다음 줄기의 진행 각도에 0 ~ 45도 사이의 랜덤한 각변화를 주며 길이를 0.6 ~ 0.9 사이의 값으로 스케일 하여 프랙탈 트리를 그린다.
                constructFractalTree(nextX, nextY, angle + toRadians(random.nextInt(0, 45 + 1)), length * random.nextDouble(0.6, 0.9), order - 1, false, lineList);
                constructFractalTree(nextX, nextY, angle - toRadians(random.nextInt(0, 45 + 1)), length * random.nextDouble(0.6, 0.9), order - 1, false, lineList);

                // 시작 좌표를 보장해주기 위한 이동 처리 후 addAll 호출
                if (isFirst) {
                    double minX = lineList.stream().mapToDouble(l -> min(l.getStartX(), l.getEndX())).min().getAsDouble();
                    double minY = lineList.stream().mapToDouble(l -> min(l.getStartY(), l.getEndY())).min().getAsDouble();
                    for (Line l : lineList) {
                        l.setTranslateX(l.getLayoutX() + startX - minX);
                        l.setTranslateY(l.getLayoutY() + startY - minY);
                    }
                    getChildren().addAll(lineList);
                }
            }
        }
    }

    public static class FractalRectangle extends Group {
        // Sierpinski carpet
        public FractalRectangle(double startX, double startY, double length, double order) {
            constructFractalRectangle(startX, startY, length, order);
        }


        /**
         * 시작 위치와 초기 생성 조건 매개변수를 토대로 프랙탈 사각형을 생성한다.
         *
         * @param startX 시작 좌표 X
         * @param startY 시작 좌표 Y
         * @param length 사각형의 길이
         * @param order  프랙탈 반복 차수
         */
        private void constructFractalRectangle(double startX, double startY, double length, double order) {
            if (order > 0) {
                // 프랙탈 사각형의 중앙에 길이가 1/3배인 사각형을 생성한다.
                Rectangle rectangle = new Rectangle(startX + length / 3, startY + length / 3, length / 3, length / 3);
                rectangle.setFill(Color.BLACK);
                getChildren().add(rectangle);

                // 프랙탈 사각형의 9분할 사각형중 중앙과 인접한 외곽에 위치한 8개의 사각형의 중앙에 길이가 1/9배인 사각형을 생선한다. (재귀적으로 처리됨)
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (!(x == 1 && y == 1))
                            constructFractalRectangle(startX + x * length / 3, startY + y * length / 3, length / 3, order - 1);
                    }
                }
            }
        }
    }

    @Override
    public void start(Stage mainStage) throws Exception {
        FractalTree tree1 = new FractalTree(0d, 0d, toRadians(270d + 45d), 70d, 12);
        FractalTree tree2 = new FractalTree(250d, 0d, toRadians(270d - 45d), 70d, 12);
        FractalRectangle rectangle = new FractalRectangle(0d, 300d, 200d, 5);
        // Group을 확장한 Fractal 객체 생성

        ImageView iView = new ImageView(new Image("fractal_world.png"));
        iView.setFitWidth(200d);
        iView.setPreserveRatio(true);
        iView.setX(500d - iView.getFitWidth());
        iView.setY(500d - 250d);
        // 프랙탈 도형 설명 이미지 초기화

        Pane pane = new Pane();
        pane.getChildren().addAll(tree1, tree2, rectangle, iView);

        mainStage.setTitle("Welcome To Fractal World!");
        mainStage.setScene(new Scene(pane, 500d, 500d));
        mainStage.show();
        // Scene, Stage 초기화 후 실행
    }

    public static void main(String[] args) {
        Application.launch(args);
    }

}
