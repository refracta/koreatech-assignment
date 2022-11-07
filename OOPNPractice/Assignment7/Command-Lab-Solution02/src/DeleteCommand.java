import javafx.scene.Node;
import javafx.scene.layout.Pane;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author refracta
 * Lab 06. 명령 패턴
 * 도형 삭제 명령 클래스
 */
public class DeleteCommand implements Command{
    private Pane pane;
    private Node target;

    public DeleteCommand(Pane pane, Node target) {
        this.pane = pane;
        this.target = target;
        // 대상 pane과 삭제할 target을 멤버 변수로 저장
    }

    @Override
    public void execute() {
        pane.getChildren().remove(target);
        // target을 pane에서 삭제
    }

    @Override
    public void undo() {
        pane.getChildren().add(target);
        // 삭제한 target을 pane에서 되돌리기
    }
}
