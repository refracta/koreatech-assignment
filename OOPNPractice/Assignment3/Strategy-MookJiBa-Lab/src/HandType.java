import javafx.scene.image.Image;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @file HandType.java
 * @author 김상진
 * 묵찌바, 가위바위보 게임의 손 모습을 나타내는 열거형
 */
public enum HandType {
	MOOK("주먹.jpeg"){
		@Override public HandType winValueOf(){
			return BA;
		}
	}, 
	JI("가위.jpeg"){
		@Override public HandType winValueOf(){
			return MOOK;
		}
	}, 
	BA("보.jpeg"){
		@Override public HandType winValueOf(){
			return JI;
		}
	};
	private final Image image;
	private HandType(String filename) {
		image = new Image(filename);
	}
	public Image getImage() {
		return image;
	}
	public static HandType valueOf(int n){
		HandType[] enumList = HandType.values();
		assert(n>=0&&n<enumList.length);
		return HandType.values()[n];
	}
	// 가위바위보 게임에서 이 손을 이기는 손
	public abstract HandType winValueOf();
}
