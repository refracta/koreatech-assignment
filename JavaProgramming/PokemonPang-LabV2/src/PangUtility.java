import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.util.*;
import java.util.function.Consumer;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 *
 * @author refracta
 * 포켓몬팡의 유틸리티 클래스:
 * 1) 뷰, 모델, 컨트럴러에 속하지 않는 static 함수 모음
 * 2) 뷰, 모델, 컨트럴러에 공통으로 필요로 하는 상수 정의
 */

public interface PangUtility {
    public static int NUMBEROFMONS = 7;
    public static int GRIDSIZE = 7;
    public static int POKETMONIMAGESIZE = 80;
    public static int PANG_MINIMUM = 3;
    public static int[][] delta = {{-1, 0}, {1, 0}, {1, -1}, {0, 1}};

    public static void pokemonInfoDialog(String title, String content) {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        ImageView icon = new ImageView(new Image("./image/pokemon.png"));
        icon.setFitHeight(80);
        icon.setPreserveRatio(true);
        alert.setGraphic(icon);
        alert.showAndWait();
    }

    public static boolean pokemonConfirmDialog(String title, String content,
                                               String okButton, String cancelButton) {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        ButtonType buttonTypeOK = new ButtonType(okButton, ButtonData.OK_DONE);
        ButtonType buttonTypeCancel = new ButtonType(cancelButton, ButtonData.CANCEL_CLOSE);
        alert.getButtonTypes().setAll(buttonTypeOK, buttonTypeCancel);
        ImageView icon = new ImageView(new Image("./image/pokemon.png"));
        icon.setFitHeight(80);
        icon.setPreserveRatio(true);
        alert.setGraphic(icon);
        Optional<ButtonType> result = alert.showAndWait();
        return (result.get() == buttonTypeOK);
    }

    /**
     * 특정 좌표 십자 모양 인근의 포켓몬 타입 리스트를 반환한다.
     * @param gridData
     * @param row
     * @param column
     * @return 인근 포켓몬 타입 리스트
     */
    public static List<Pokemon> getNearPokemonList(Pokemon[][] gridData, int row, int column) {
        Set<Pokemon> pokemonSet = new HashSet<>();
        int rLen = gridData.length;
        int cLen = gridData[0].length;
        if ((0 <= row && row < rLen) && (0 <= column && column < cLen)) {
            if (row != 0) {
                pokemonSet.add(gridData[row - 1][column]);
            }
            if (row != rLen - 1) {
                pokemonSet.add(gridData[row + 1][column]);
            }
            if (column != 0) {
                pokemonSet.add(gridData[row][column - 1]);
            }
            if (column != cLen - 1) {
                pokemonSet.add(gridData[row][column + 1]);
            }
        }
        return new ArrayList<>(pokemonSet);
    }

    /**
     * gridData의 특정 지점에서 특정 방향으로의 연속된 type의 개수를 구한다.
     * @param gridData
     * @param type
     * @param row
     * @param column
     * @param isVertical
     * @param isAscending
     * @return 연속 타입 개수
     */
    private static int getChainCount(Pokemon[][] gridData, Pokemon type, int row, int column, boolean isVertical, boolean isAscending) {
        int count = 0;
        int delta = isAscending ? 1 : -1;
        int start = (isVertical ? row : column) + delta;
        int len = isVertical ? gridData.length : gridData[0].length;
        for (int i = start; !isAscending ? (i >= 0) : (i < len); i += delta) {
            Pokemon target = isVertical ? gridData[i][column] : gridData[row][i];
            if (target == type) {
                count++;
            } else {
                break;
            }
        }
        return count;
    }

    /**
     * 팡 힌트 배열 리스트를 계산하여 반환한다.
     * @param gridData
     * @return 팡 힌트 배열 리스트
     */
    public static List<PangHintSequence> getPangHintSequences(Pokemon[][] gridData) {
        int rLen = gridData.length;
        int cLen = gridData[0].length;
        List<PangHintSequence> pangHintSequences = new ArrayList<>();
        for (int r = 0; r < rLen; r++) {
            for (int c = 0; c < cLen; c++) {
                Index2D currentIndex2D = new Index2D(r, c);
                Pokemon type = gridData[r][c];
                List<Pokemon> nearTypes = getNearPokemonList(gridData, r, c);
                nearTypes.remove(type);

                for (Pokemon near : nearTypes) {
                    Consumer<PangSequence> psHandler = ps -> pangHintSequences.add(new PangHintSequence(ps, type, near, currentIndex2D));
                    getPangSequenceWithRC(gridData, near, r, c, true).ifPresent(psHandler);
                    getPangSequenceWithRC(gridData, near, r, c, false).ifPresent(psHandler);
                }
            }
        }
        return pangHintSequences;
    }

    /**
     * 특정 지점의 수직 또는 수평 팡 배열을 가져온다. 매개변수로 받은 지점의 타입은 type 변수로 취급되어 팡 배열이 계산된다.
     * @param gridData
     * @param type
     * @param row
     * @param column
     * @param isVertical
     * @return Optional of PangSequence
     */
    public static Optional<PangSequence> getPangSequenceWithRC(Pokemon[][] gridData, Pokemon type, int row, int column, boolean isVertical) {
        int plus = getChainCount(gridData, type, row, column, isVertical, true);
        int minus = getChainCount(gridData, type, row, column, isVertical, false);
        if (PANG_MINIMUM <= plus + minus + 1) {
            List<Index2D> index2DList = new ArrayList<>();
            int base = isVertical ? row : column;
            for (int i = base - minus; i <= base + plus; i++) {
                index2DList.add(isVertical ? new Index2D(i, column) : new Index2D(row, i));
            }
            return Optional.of(new PangSequence(type, isVertical ? PangDirection.VERTICAL : PangDirection.HORIZONTAL, index2DList));
        } else {
            return Optional.empty();
        }
    }

    /**
     * gridData에서 유효한 팡 배열이 있는지 검사하고 팡 배열의 리스트를 반환한다.
     *
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
                    Consumer<PangSequence> psHandler = ps -> {
                        pangSequences.add(ps);
                        for (Index2D i : ps.getIndex2DList()) {
                            removedData[i.r()][i.c()] = true;
                        }
                    };
                    getPangSequenceWithRC(gridData, type, r, c, true).ifPresent(psHandler);
                    getPangSequenceWithRC(gridData, type, r, c, false).ifPresent(psHandler);
                }
            }
        }
        return pangSequences;
    }
}
