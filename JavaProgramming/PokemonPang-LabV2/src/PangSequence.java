import java.util.*;

/**
 * 포켓몬팡 게임 팡 배열 클래스
 *
 * @author refracta
 */
public class PangSequence {
    private Pokemon type;
    private PangDirection direction;
    private List<Index2D> index2DList;

    public PangSequence(Pokemon type, PangDirection direction, List<Index2D> index2DList) {
        this.type = type;
        this.direction = direction;
        this.index2DList = new ArrayList<>(index2DList);
    }

    public Pokemon getType() {
        return type;
    }

    public PangDirection getDirection() {
        return direction;
    }

    public List<Index2D> getIndex2DList() {
        return new ArrayList<>(index2DList);
    }

    public int getLength() {
        return index2DList.size();
    }

    @Override
    public String toString() {
        return "PangSequence{" +
                "type=" + type +
                ", direction=" + direction +
                ", length=" + getLength() +
                ", index2DSet=" + index2DList +
                '}';
    }
}
