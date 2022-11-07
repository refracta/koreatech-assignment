import java.net.URISyntaxException;
import java.util.HashMap;
import java.util.Map;
import javafx.scene.media.AudioClip;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2022년도 1학기 학기
 * @author 김상진 
 * mp3 파일을 play하여주는 클래스
 */
public class Sound {
	public static String dir;
    static {
        dir = "file:///" + System.getProperty("user.dir").replace('\\', '/').replaceAll(" ", "%20");
        try {
            dir = new java.net.URI(dir).toASCIIString();
        } 
        catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }
    private static AudioClip fire = new AudioClip(dir + "/fire.mp3");
	private static AudioClip small_explosion = new AudioClip(dir + "/bangSmall.mp3");
	private static AudioClip medium_explosion = new AudioClip(dir + "/bangMedium.mp3");
	private static AudioClip large_explosion = new AudioClip(dir + "/bangLarge.mp3");
	private static AudioClip thrust = new AudioClip(dir + "/thrust.mp3");
		
	private static Map<String, AudioClip> soundBox = new HashMap<>();
	static{
		soundBox.put("fire", fire);
		soundBox.put("small_explosion", small_explosion);
		soundBox.put("medium_explosion", medium_explosion);
		soundBox.put("large_explosion", large_explosion);
		soundBox.put("thrust", thrust);
	}
	
	public static void play(String key){	
		AudioClip clip = soundBox.get(key);
		if(clip!=null){
			clip.play();
		}
	}
	public static void stop(String key){
		AudioClip clip = soundBox.get(key);
		if(clip!=null){
			clip.stop();
		}
	}
}
