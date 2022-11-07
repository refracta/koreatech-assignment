import java.util.Stack;

/**
 * @author refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * Lab 06. 명령 패턴
 * 명령 관리자 클래스
 */
public class CommandManager {
    private Stack<Command> undoStack = new Stack<>();
    private Stack<Command> redoStack = new Stack<>();

    /**
     * UndoStack이 비었는지의 여부를 반환
     *
     * @return undoStack.isEmpty()의 반환 값
     */
    public boolean isUndoEmpty() {
        return undoStack.isEmpty();
    }

    /**
     * RedoStack이 비었는지의 여부를 반환
     *
     * @return redoStack.isEmpty()의 반환 값
     */
    public boolean isRedoEmpty() {
        return redoStack.isEmpty();
    }

    /**
     * 명령 실행 함수: 명령을 실행하고 undoStack에 추가한 뒤 redoStack을 비움
     *
     * @param command 실행할 명령
     */
    public void execute(Command command) {
        command.execute();
        undoStack.push(command);
        redoStack.clear();
    }

    /**
     * 명령 취소 함수: 명령을 취소하고 redoStack에 추가함
     * @return 취소 성공 여부
     */
    public boolean undo() {
        if (!undoStack.isEmpty()) {
            Command command = undoStack.pop();
            redoStack.push(command);
            command.undo();
            return true;
        }
        return false;
    }

    /**
     * 명령 재실행 함수: 명령을 재실행하고 undoStack에 추가함
     * @return 재실행 성공 여부
     */
    public boolean redo() {
        if (!redoStack.isEmpty()) {
            Command command = redoStack.pop();
            undoStack.push(command);
            command.execute();
            return true;
        }
        return false;
    }
}
