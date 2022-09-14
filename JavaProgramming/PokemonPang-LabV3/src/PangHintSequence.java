import java.util.List;

public class PangHintSequence extends PangSequence {
    private Pokemon originalType;
    private Pokemon changedType;
    private Location originalIndex;

    public PangHintSequence(Pokemon type, PangDirection direction, List<Location> index2DList, Pokemon originalType, Pokemon changedType, Location originalIndex) {
        super(type, direction, index2DList);
        this.originalType = originalType;
        this.changedType = changedType;
        this.originalIndex = originalIndex;
    }

    public PangHintSequence(PangSequence pangSequence, Pokemon originalType, Pokemon changedType, Location originalIndex) {
        super(pangSequence.getType(), pangSequence.getDirection(), pangSequence.getLocationList());
        this.originalType = originalType;
        this.changedType = changedType;
        this.originalIndex = originalIndex;
    }

    public Pokemon getOriginalType() {
        return originalType;
    }

    public void setOriginalType(Pokemon originalType) {
        this.originalType = originalType;
    }

    public Pokemon getChangedType() {
        return changedType;
    }

    public void setChangedType(Pokemon changedType) {
        this.changedType = changedType;
    }

    public Location getOriginalIndex() {
        return originalIndex;
    }

    public void setOriginalIndex(Location originalIndex) {
        this.originalIndex = originalIndex;
    }

    @Override
    public String toString() {
        return "PangHintSequence{" +
                "originalType=" + originalType +
                ", originalIndex=" + originalIndex +
                ", PangSequence=" + super.toString() + "} ";
    }
}
