/**
 * @author refracta
 * 잘못된 매개변수 예외 클래스
 */
public abstract class MWInvalidParameterException extends Exception {
    public MWInvalidParameterException(String message) {
        super(message);
    }
}
