import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author refracta
 * Lab 06. 명령 패턴
 * 도형 그리기 명령 클래스
 */
public class DrawShapeCommand implements Command {
    private double x;
    private double y;
    private ShapeType type;
    private int radius;
    private Pane pane;
    private Shape shape;

    /**
     * 멤버 변수의 상태와 값을 이용해서 실제 Shape 객체를 만드는 함수
     * @return 주어진 조건에 맞게 만들어진 Shape 객체
     */
    private Shape createShape() {
        Shape shape = null;
        switch (type) {
            case SQUARE:
                shape = new Rectangle(x - radius, y - radius, radius * 2, radius * 2);
                break;
            case CIRCLE:
                shape = new Circle(x, y, radius);
                break;
            case TRIANGLE:
                Polygon triangle = new Polygon();
                final double radian = Math.PI / 180F;
                triangle.getPoints().addAll(new Double[]{
                        x + radius * Math.cos(30 * radian),
                        y + radius * Math.sin(30 * radian),
                        x + radius * Math.cos(150 * radian),
                        y + radius * Math.sin(150 * radian),
                        x + radius * Math.cos(270 * radian),
                        y + radius * Math.sin(270 * radian)
                });
                shape = triangle;
        }
        shape.setStroke(Color.BLACK);
        shape.setFill(null);
        shape.setStrokeWidth(5d);
        return shape;
    }

    public DrawShapeCommand(double x, double y, ShapeType type, int radius, Pane pane) {
        this.x = x;
        this.y = y;
        this.type = type;
        this.radius = radius;
        // 도형 형태, 조건들을 저장
        this.pane = pane;
        // 대상 pane을 멤버 변수로 저장
        this.shape = createShape();
        // 실제로 사용할 도형 객체 생성
    }

    @Override
    public void execute() {
        pane.getChildren().add(shape);
        // 도형을 pane에 추가
    }

    @Override
    public void undo() {
        pane.getChildren().remove(shape);
        // 추가한 도형을 pane에서 제거
    }
}
