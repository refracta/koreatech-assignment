import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Shape;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author refracta
 * Lab 06. 명령 패턴
 * 도형 색 변경 명령 클래스
 */
public class ChangeColorCommand implements Command {
    private Paint originalPaint;
    private Paint changePaint;
    private Shape target;

    public ChangeColorCommand(Color color, Shape target) {
        this.originalPaint = target.getFill();
        this.changePaint = color;
        this.target = target;
        // 원래 색과 변경 색을 멤버 변수로 저장
    }

    @Override
    public void execute() {
        target.setFill(changePaint);
        // 색 변경
    }

    @Override
    public void undo() {
        target.setFill(originalPaint);
        // 원래 색으로 변경
    }
}
