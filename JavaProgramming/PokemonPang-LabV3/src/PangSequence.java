import java.util.ArrayList;
import java.util.List;

/**
 * 포켓몬팡 게임 팡 배열 클래스
 *
 * @author refracta
 */
public class PangSequence {
    private Pokemon type;
    private PangDirection direction;
    private List<Location> locationList;

    public PangSequence(Pokemon type, PangDirection direction, List<Location> index2DList) {
        this.type = type;
        this.direction = direction;
        this.locationList = new ArrayList<>(index2DList);
    }

    public Pokemon getType() {
        return type;
    }

    public PangDirection getDirection() {
        return direction;
    }

    public List<Location> getLocationList() {
        return new ArrayList<>(locationList);
    }

    public int getLength() {
        return locationList.size();
    }

    @Override
    public String toString() {
        return "PangSequence{" +
                "type=" + type +
                ", direction=" + direction +
                ", length=" + getLength() +
                ", locationList=" + locationList +
                '}';
    }
}
