import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * 포켓몬팡 게임 팡 배열 클래스
 *
 * @author refracta
 */
public class PangSequence {
    private Pokemon type;
    private PangDirection direction;
    private int[][] index2DArray;

    public PangSequence(Pokemon type, PangDirection direction, int[][] index2DArray) {
        this.type = type;
        this.direction = direction;
        this.index2DArray = index2DArray;
    }

    public Pokemon getType() {
        return type;
    }

    public PangDirection getDirection() {
        return direction;
    }

    public int[][] getIndex2DArray() {
        return index2DArray;
    }

    public int getLength() {
        return index2DArray.length;
    }

    @Override
    public String toString() {
        return "PangSequence{" +
                "type=" + type +
                ", direction=" + direction +
                ", length=" + getLength() +
                ", index2DArray=" + Arrays.deepToString(index2DArray) +
                '}';
    }

    private static final int PANG_MINIMUM = 3;

    /**
     * gridData에서 유효한 팡 배열이 있는지 검사하고 팡 배열의 리스트를 반환한다.
     * @param gridData
     * @return 팡 배열 리스트
     */
    public static List<PangSequence> getPangSequences(Pokemon[][] gridData) {
        int rLen = gridData.length;
        int cLen = gridData[0].length;
        boolean[][] removedData = new boolean[rLen][cLen];
        List<PangSequence> pangSequences = new ArrayList<>();
        for (int r = 0; r < rLen; r++) {
            for (int c = 0; c < cLen; c++) {
                if (!removedData[r][c]) {
                    Pokemon type = gridData[r][c];

                    int rPlus = 0;
                    for (int rr = r + 1; rr < rLen; rr++) {
                        if (gridData[rr][c] == type) {
                            rPlus++;
                        } else {
                            break;
                        }
                    }
                    int rMinus = 0;
                    for (int rr = r - 1; rr >= 0; rr--) {
                        if (gridData[rr][c] == type) {
                            rMinus++;
                        } else {
                            break;
                        }
                    }

                    if (PANG_MINIMUM <= rPlus + rMinus + 1) {
                        int[][] rPangIndex2DArray = new int[rPlus + rMinus + 1][2];
                        for (int rr = r - rMinus, i = 0; rr <= r + rPlus; rr++, i++) {
                            removedData[rr][c] = true;
                            rPangIndex2DArray[i] = new int[]{rr, c};
                        }
                        pangSequences.add(new PangSequence(type, PangDirection.VERTICAL, rPangIndex2DArray));
                    }


                    int cPlus = 0;
                    for (int cc = c + 1; cc < cLen; cc++) {
                        if (gridData[r][cc] == type) {
                            cPlus++;
                        } else {
                            break;
                        }
                    }
                    int cMinus = 0;
                    for (int cc = c - 1; cc >= 0; cc--) {
                        if (gridData[r][cc] == type) {
                            cMinus++;
                        } else {
                            break;
                        }
                    }
                    if (PANG_MINIMUM <= cPlus + cMinus + 1) {
                        int[][] cPangIndex2DArray = new int[cPlus + cMinus + 1][2];
                        for (int cc = c - cMinus, i = 0; cc <= c + cPlus; cc++, i++) {
                            removedData[r][cc] = true;
                            cPangIndex2DArray[i] = new int[]{r, cc};
                        }
                        pangSequences.add(new PangSequence(type, PangDirection.HORIZONTAL, cPangIndex2DArray));
                    }


                }
            }
        }
        return pangSequences;
    }
}
