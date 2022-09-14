import java.util.Objects;
/**
 * 2차원 색인 클래스
 *
 * @author refracta
 */
public class Index2D{
    private int row;
    private int column;

    public Index2D(int row, int column) {
        this.row = row;
        this.column = column;
    }

    public int r() {
        return row;
    }

    public void setRow(int row) {
        this.row = row;
    }

    public int c() {
        return column;
    }

    public void setColumn(int column) {
        this.column = column;
    }

    @Override
    public String toString() {
        return "Index2D{" +
                "row=" + row +
                ", column=" + column +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Index2D that = (Index2D) o;
        return row == that.row && column == that.column;
    }

    @Override
    public int hashCode() {
        return Objects.hash(row, column);
    }
}
