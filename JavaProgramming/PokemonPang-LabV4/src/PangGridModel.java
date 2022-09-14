import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

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
    private int score = 0;
    private int comboCount = 0;
    private int gameOverCount = 60;
    private int pangCount = 0;
    // 팡 개수를 세기 위한 카운터

    private boolean ghostTime = false;

    private PangGridView view;
    // 전체가 아니라 일부 위치가 갱신하기 위한 위치 목록
    private List<Location> locationList = new ArrayList<>();

    public PangGridModel(PangGridView view) {
        this.view = view;
    }

    public void initAssign() {
        randomAssign();
        removePang();
        view.update(gridData);
        score = comboCount = pangCount = 0;
        gameOverCount = 60;
        ghostTime = false;
        view.updateCombo("0");
        view.updateScore("0");
    }

    private void removePang() {
        int[][] checkMatrix = new int[PangUtility.GRIDSIZE][PangUtility.GRIDSIZE];
        if (checkColumn(checkMatrix)) {
            for (int r = 0; r < PangUtility.GRIDSIZE; r++)
                for (int c = 0; c < PangUtility.GRIDSIZE; c++)
                    if (checkMatrix[r][c] == 2) changePokemon(r, c);
        }
        checkMatrix = new int[PangUtility.GRIDSIZE][PangUtility.GRIDSIZE];
        if (checkRow(checkMatrix)) {
            for (int r = 0; r < PangUtility.GRIDSIZE; r++)
                for (int c = 0; c < PangUtility.GRIDSIZE; c++)
                    if (checkMatrix[r][c] == 2) changePokemon(r, c);
        }
    }

    /**
     * 주어진 위치의 포켓몬을 바꾸어 팡을 제거함
     * * 현재 포켓몬과 주변 4개와 다른 포켓몬으로 교체
     */
    private void changePokemon(int r, int c) {
        Set<Pokemon> set = EnumSet.range(Pokemon.BULBASAUR, Pokemon.SQUIRTLE);
        set.remove(gridData[r][c]);
        for (var d : PangUtility.delta)
            if (Location.valid(r + d[0], c + d[1])) set.remove(gridData[r + d[0]][c + d[1]]);
        Pokemon[] list = new Pokemon[set.size()];
        set.toArray(list);
        gridData[r][c] = list[ThreadLocalRandom.current().nextInt(list.length)];
    }

    /**
     * 행 기준으로 팡의 존재를 검사
     * 팡이 발견된 위치는 모두 1로 바꾸고
     * 초기 팡 제거를 위해 포켓몬을 바꾸어야 하는 위치는 2로 바꿈
     */
    private boolean checkRow(int[][] checkMatrix) {
        boolean found = false;
        for (int r = 0; r < PangUtility.GRIDSIZE; ++r) {
            int c = 0;
            while (c < PangUtility.GRIDSIZE - 2) {
                if (gridData[r][c].isNormal()) {
                    int count = 1;
                    for (int i = c + 1; i < PangUtility.GRIDSIZE; ++i) {
                        if (gridData[r][c] == gridData[r][i]) ++count;
                        else break;
                    }
                    if (count >= 3) {
                        updatePangScore(count);
                        found = true;
                        for (int i = c; i < c + count; i++) checkMatrix[r][i] = 1;
                        checkMatrix[r][c + 2] = 2;
                        if (count >= 6) checkMatrix[r][c + 5] = 2;
                        if (count == 5) ghostTime = true;
                    }
                    c += count;
                } else ++c;
            }
        }
        return found;
    }

    /**
     * 열 기준으로 팡의 존재를 검사
     * 팡이 발견된 위치는 모두 1로 바꾸고
     * 초기 팡 제거를 위해 포켓몬을 바꾸어야 하는 위치는 2로 바꿈
     */
    private boolean checkColumn(int[][] checkMatrix) {
        boolean found = false;
        for (int c = 0; c < PangUtility.GRIDSIZE; ++c) {
            int r = 0;
            while (r < PangUtility.GRIDSIZE - 2) {
                if (gridData[r][c].isNormal()) {
                    int count = 1;
                    for (int i = r + 1; i < PangUtility.GRIDSIZE; ++i) {
                        if (gridData[r][c] == gridData[i][c]) ++count;
                        else break;
                    }
                    if (count >= 3) {
                        updatePangScore(count);
                        found = true;
                        for (int i = r; i < r + count; ++i) checkMatrix[i][c] = 1;
                        checkMatrix[r + 2][c] = 2;
                        if (count >= 6) checkMatrix[r + 5][c] = 2;
                        if (count == 5) ghostTime = true;
                    }
                    r += count;
                } else ++r;
            }
        }
        return found;
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
    }

    boolean findHints() {
        List<Location> hintLocs = getHintLocations();
        if (!hintLocs.isEmpty()) {
            view.updateHintLoc(hintLocs.get(ThreadLocalRandom.current().nextInt(hintLocs.size())));
            return true;
        } else {
            view.updateHintLoc(null);
            return hasSpecialPokemon();
        }
    }

    private List<Location> getHintLocations() {
        List<Location> hintLocs = new ArrayList<>();
        for (int r = 0; r < PangUtility.GRIDSIZE; r++) {
            for (int c = 0; c < PangUtility.GRIDSIZE; c++) {
                if (leftEquals(r, c) || rightEquals(r, c) || upEquals(r, c) || downEquals(r, c)) {
                    hintLocs.add(new Location(r, c));
                }
            }
        }
        return hintLocs;
    }

    private boolean hasSpecialPokemon() {
        for (int r = 0; r < PangUtility.GRIDSIZE; r++)
            for (int c = 0; c < PangUtility.GRIDSIZE; c++)
                if (gridData[r][c].isSpecial()) return true;
        return false;
    }

    //======= 특수 아이템 처리 =========
    private Location getNormalLoc() {
        while (true) {
            Location location = Location.getRandomLocation();
            if (gridData[location.r()][location.c()].isNormal()) return location;
        }
    }

    public void insertSpecialPokemon() {
        locationList.clear();
        if (ghostTime) {
            Location ghostLoc = getNormalLoc();
            gridData[ghostLoc.r()][ghostLoc.c()] = Pokemon.DUSKULL;
            ghostTime = false;
            locationList.add(ghostLoc);
        }
        if (pangCount % 10 == 0) {
            Location targetLoc = getNormalLoc();
            gridData[targetLoc.r()][targetLoc.c()] = Pokemon.DRAGONITE;
            locationList.add(targetLoc);
            // 10개의 팡마다 망나뇽 추가
        }
        if (comboCount % 10 == 0) {
            Location targetLoc = getNormalLoc();
            gridData[targetLoc.r()][targetLoc.c()] = Pokemon.SNORLAX;
            locationList.add(targetLoc);
            // 10 콤보마다 잠맘보 추가
        }

        view.update(gridData, locationList);
    }

    public void processSpecialPokemon(Location loc) {
        switch (gridData[loc.r()][loc.c()]) {
            case DRAGONITE:
                Sound.play("dragonite");
                clearRowAndColumn(loc);
                Sound.stop("dragonite");
                break;
            case DUSKULL:
                removeRandomPokemon(loc);
                break;
            default: //case SNORLAX:
                Sound.play("snorlax");
                increaseGameTime(loc);
                Sound.stop("snorlax");
                break;
        }
    }

    private void clearRowAndColumn(Location loc) {
        for (int c = 0; c < PangUtility.GRIDSIZE; c++) {
            gridData[loc.r()][c] = Pokemon.POKEBALL;
        }
        for (int r = 0; r < PangUtility.GRIDSIZE; r++) {
            gridData[r][loc.c()] = Pokemon.POKEBALL;
        }
    }

    private void removeRandomPokemon(Location loc) {
        Pokemon removePokemon = Pokemon.getRandomNormalPokemon();
        int count = 1;
        locationList.clear();
        for (int r = 0; r < PangUtility.NUMBEROFMONS; r++) {
            for (int c = 0; c < PangUtility.NUMBEROFMONS; c++) {
                if (gridData[r][c] == removePokemon) {
                    changeToPokeball(r, c);
                    ++count;
                }
            }
        }
        changeToPokeball(loc.r(), loc.c());
        updateSpecialScore(100 * count);
        view.update(gridData, locationList);
    }

    private void increaseGameTime(Location loc) {
        gameOverCount += 15;
        gridData[loc.r()][loc.c()] = Pokemon.POKEBALL;
    }

    /*
     * 점수 계산 방식:
     * 1) 제거한 포켓몬 수 x 100
     * 2) 5개 연속짜리 제거할 경우 보너스 500점 추가
     * 3) 현재 콤보 수 x 100
     */
    private void updatePangScore(int count) {
        score += count * 100;
        if (count == 5) score += 500;
        score += comboCount * 100;
        view.updateScore(score + "");
    }

    private void updateSpecialScore(int specialScore) {
        score += specialScore;
        view.updateScore(score + "");
    }

    public void updateCombo(boolean flag) {
        comboCount = flag ? comboCount + 1 : 0;
        view.updateCombo(comboCount + "");
    }

    public void updateGameTime() {
        --gameOverCount;
        view.updateTime(gameOverCount + "");
    }

    public boolean isGameOver() {
        return gameOverCount == 0;
    }

    public boolean isSpecialPokemon(Location loc) {
        return gridData[loc.r()][loc.c()].isSpecial();
    }

    public int getCombo() {
        return comboCount;
    }

    /**
     * 팡이 있는 곳에 포켓몬을 포켓몬공으로 바꾸세요.
     */
    public boolean checkAndMark() {
        int[][] checkMatrix = new int[PangUtility.NUMBEROFMONS][PangUtility.NUMBEROFMONS];
        boolean flag = checkColumn(checkMatrix);
        flag = checkRow(checkMatrix) || flag;
        if (flag) {
            locationList.clear();
            for (int r = 0; r < PangUtility.NUMBEROFMONS; ++r)
                for (int c = 0; c < PangUtility.NUMBEROFMONS; ++c)
                    if (checkMatrix[r][c] >= 1) changeToPokeball(r, c);
            view.update(gridData, locationList);
            pangCount++;
            return true;
        }
        return false;
    }

    private void changeToPokeball(int r, int c) {
        gridData[r][c] = Pokemon.POKEBALL;
        locationList.add(new Location(r, c));
    }

    /*
     * 팡 위치 위에 있는 포켓몬들을 아래로 내려 포켓볼들이 맨 위에 위치하도록 함
     */
    public void pushUpMarked() {
        Queue<Pokemon> queue = new ArrayDeque<>();
        for (int c = 0; c < PangUtility.GRIDSIZE; ++c) {
            queue.clear();
            boolean hasBall = false;
            for (int r = PangUtility.GRIDSIZE - 1; r >= 0; r--) {
                if (gridData[r][c] == Pokemon.POKEBALL) hasBall = true;
                else queue.add(gridData[r][c]);
            }
            if (hasBall) {
                int r = PangUtility.GRIDSIZE - 1;
                while (!queue.isEmpty()) {
                    gridData[r][c] = queue.poll();
                    --r;
                }
                for (; r >= 0; --r) gridData[r][c] = Pokemon.POKEBALL;
            }
        }
        view.update(gridData);
    }

    /**
     * 포켓몬공이 있는 위치를 새로운 랜덤 포켓몬으로 교체함
     * 포켓몬공은 모두 위로 이동한 후에 사용되는 메소드
     */
    public void replaceMarked() {
        // 볼 있는 위치만 교체
        for (int c = 0; c < PangUtility.GRIDSIZE; c++) {
            for (int r = 0; r < PangUtility.GRIDSIZE; r++) {
                if (gridData[r][c] == Pokemon.POKEBALL)
                    gridData[r][c] = Pokemon.getRandomNormalPokemon();
                else break;
            }
        }
        view.update(gridData);
    }

    /**
     * 사용자가 클릭한 두 개의 셀이 인접한 셀이고 교환하였을 때 팡이 되는지?
     */
    public boolean isValidSwap(Location srcLoc, Location destLoc) {
        if (srcLoc.isRight(destLoc)) return (leftEquals(srcLoc) || rightEquals(destLoc));
        else if (srcLoc.isLeft(destLoc)) return (rightEquals(srcLoc) || leftEquals(destLoc));
        else if (srcLoc.isDown(destLoc)) return (upEquals(srcLoc) || downEquals(destLoc));
        else if (srcLoc.isUp(destLoc)) return (downEquals(srcLoc) || upEquals(destLoc));
        else return false;
    }

    /**
     * 사용자가 선택한 두 개의 셀을 실제 교환함
     */
    public void swap(Location srcLoc, Location destLoc) {
        Pokemon tmp = gridData[srcLoc.r()][srcLoc.c()];
        gridData[srcLoc.r()][srcLoc.c()] = gridData[destLoc.r()][destLoc.c()];
        gridData[destLoc.r()][destLoc.c()] = tmp;
        locationList.clear();
        locationList.add(srcLoc);
        locationList.add(destLoc);
        view.update(gridData, locationList);
    }

    private boolean equals(Pokemon... list) {
        if (list.length <= 1) throw new IllegalArgumentException();
        Pokemon p = list[0];
        for (int i = 1; i < list.length; i++)
            if (p != list[i]) return false;
        return true;
    }

    /*
     *  1) x@xx
     *  2) 	 x
     * 		x@
     *  	 x
     *  3) 	 x
     *  	 x
     *  	x@
     *  4) 	x@
     *  	 x
     *  	 x
     */
    private boolean rightEquals(Location loc) {
        return rightEquals(loc.r(), loc.c());
    }

    private boolean rightEquals(int r, int c) {
        return
                ((Location.valid(r, c + 3) // <x>@xx
                        && equals(gridData[r][c], gridData[r][c + 2], gridData[r][c + 3])) ||
                        (Location.valid(r - 1, c + 1) && Location.valid(r + 1, c + 1)
                                && equals(gridData[r][c], gridData[r - 1][c + 1], gridData[r + 1][c + 1])) ||
                        (Location.valid(r - 2, c + 1)
                                && equals(gridData[r][c], gridData[r - 1][c + 1], gridData[r - 2][c + 1])) ||
                        (Location.valid(r + 2, c + 1)
                                && equals(gridData[r][c], gridData[r + 1][c + 1], gridData[r + 2][c + 1])));
    }

    /*
     *  1) xx@x
     *  2) 	x
     * 		@x
     *  	x
     *  3) 	x
     *  	x
     *  	@x
     *  4) 	@x
     *  	x
     *  	x
     */
    private boolean leftEquals(Location loc) {
        return leftEquals(loc.r(), loc.c());
    }

    private boolean leftEquals(int r, int c) {
        return ((Location.valid(r, c - 3)
                && equals(gridData[r][c], gridData[r][c - 2], gridData[r][c - 3])) ||
                (Location.valid(r - 1, c - 1) && Location.valid(r + 1, c - 1)
                        && equals(gridData[r][c], gridData[r - 1][c - 1], gridData[r + 1][c - 1])) ||
                (Location.valid(r - 2, c - 1)
                        && equals(gridData[r][c], gridData[r - 1][c - 1], gridData[r - 2][c - 1])) ||
                (Location.valid(r + 2, c - 1)
                        && equals(gridData[r][c], gridData[r + 1][c - 1], gridData[r + 2][c - 1])));
    }

    /*
     *  1) 	x
     *  	x
     *  	@
     *  	x
     *  2) 	x@x
     * 		 x
     *  3) 	xx@
     *  	  x
     *  4) 	@xx
     *  	x
     */
    private boolean upEquals(Location loc) {
        return upEquals(loc.r(), loc.c());
    }

    private boolean upEquals(int r, int c) {
        return ((Location.valid(r - 3, c)
                && equals(gridData[r][c], gridData[r - 2][c], gridData[r - 3][c])) ||
                (Location.valid(r - 1, c - 1) && Location.valid(r - 1, c + 1)
                        && equals(gridData[r][c], gridData[r - 1][c - 1], gridData[r - 1][c + 1])) ||
                (Location.valid(r - 1, c - 2)
                        && equals(gridData[r][c], gridData[r - 1][c - 1], gridData[r - 1][c - 2])) ||
                (Location.valid(r - 1, c + 2)
                        && equals(gridData[r][c], gridData[r - 1][c + 1], gridData[r - 1][c + 2])));

    }

    /*
     *  1) 	x
     *  	@
     *  	x
     *  	x
     *  2) 	 x
     * 		x@x
     *  3) 	  x
     *  	xx@
     *  4) 	x
     *  	@xx
     */
    private boolean downEquals(Location loc) {
        return downEquals(loc.r(), loc.c());
    }

    private boolean downEquals(int r, int c) {
        return ((Location.valid(r + 3, c)
                && equals(gridData[r][c], gridData[r + 2][c], gridData[r + 3][c])) ||
                (Location.valid(r + 1, c - 1) && Location.valid(r + 1, c + 1)
                        && equals(gridData[r][c], gridData[r + 1][c - 1], gridData[r + 1][c + 1])) ||
                (Location.valid(r + 1, c - 2)
                        && equals(gridData[r][c], gridData[r + 1][c - 1], gridData[r + 1][c - 2])) ||
                (Location.valid(r + 1, c + 2)
                        && equals(gridData[r][c], gridData[r + 1][c + 1], gridData[r + 1][c + 2])));
    }
}
