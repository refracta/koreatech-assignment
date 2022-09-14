import java.util.Arrays;
import java.util.List;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 *
 * @author refracta
 * 포켓몬팡의 모델 클래스: 게임 로직 구현
 */

public class PangGridModel {
    private Pokemon[][] gridData
            = new Pokemon[PangUtility.NUMBEROFMONS][PangUtility.NUMBEROFMONS];
    /*
     * 뷰 및 뷰와 통신할 때 사용하는 데이터
     */
    private PangGridView view;

    public PangGridModel(PangGridView view) {
        this.view = view;
    }

    public void initAssign() {
        randomAssign();
//		debugAssign();
        view.update(gridData);
    }

    /**
     * 7개 포켓몬들을 임의로 배치
     */
    private void randomAssign() {
        for (int r = 0; r < gridData.length; r++) {
            for (int c = 0; c < gridData[r].length; c++) {
                gridData[r][c] = Pokemon.getRandomNormalPokemon();
            }
        }

        List<PangSequence> pangSequences;
        while (!(pangSequences = PangSequence.getPangSequences(gridData)).isEmpty()) {
			// 검색된 팡 배열이 있으면
            for (PangSequence p : pangSequences) {
                int[][] index2DArray = p.getIndex2DArray();
                for (int[] index2D : index2DArray) {
                    int r = index2D[0];
                    int c = index2D[1];
                    gridData[r][c] = Pokemon.getRandomNormalPokemonWithIgnoreArray(new Pokemon[]{p.getType()});
                	// 팡 배열을 구성하는 색인을 순회하면서 팡 배열의 타입과 다른 포켓몬을 랜덤하게 배치한다.
				}
            }
        }
    }


    private String toDebugInfo(Pokemon[][] gridData) {
        StringBuilder sb = new StringBuilder();
        List<Pokemon> pokemons = Arrays.asList(Pokemon.values());
        for (int r = 0; r < gridData.length; r++) {
            for (int c = 0; c < gridData[r].length - 1; c++) {
                sb.append(pokemons.indexOf(gridData[r][c]) + 1);
                sb.append(" ");
            }
            sb.append(pokemons.indexOf(gridData[r][gridData.length - 1]) + 1);
            sb.append("\n");
        }
        return sb.toString();
    }

    // 디버깅용
    private void debugAssign() {
        int[][] list = {
                {4, 4, 4, 4, 4, 4, 4},
                {3, 0, 2, 2, 2, 0, 1},
                {6, 3, 6, 0, 6, 0, 3},
                {6, 6, 5, 0, 2, 0, 5},
                {6, 2, 0, 2, 4, 3, 5},
                {6, 2, 3, 3, 3, 5, 5},
                {6, 1, 0, 5, 1, 4, 6},
        };
        for (int r = 0; r < gridData.length; r++) {
            for (int c = 0; c < gridData[r].length; c++) {
                gridData[r][c] = Pokemon.values()[list[r][c]];
            }
        }
    }
}
