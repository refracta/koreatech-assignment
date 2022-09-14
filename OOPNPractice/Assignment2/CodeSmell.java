import java.util.ArrayDeque;
import java.util.Optional;
import java.util.Queue;

/**
 * 목적: 시작 위치에서 보석까지의 최단 경로 찾기
 * 1. {@link Tile} 열거형의 2차원 배열인 맵이 주어진다.
 * 2. 이동은 상하좌우로만 할 수 있다.
 * 3. 맵에는 항상 보석이 하나 주어진다.
 * 4. 보석을 찾을 수 없으면 최단 경로의 길이는 -1을 출력해야 한다.
 * 주어진 해결책에서 코드 냄새를 찾아 리펙토링하세요.
 * 요구사항. 주석에 다음을 포함하여 주세요.
 * 1) 리펙토링한 순서
 * 2) 각 코드 냄새를 제거하기 위해 리팩토링한 방법
 *
 * 리팩토링한 순서와 찾은 코드 냄새, 해당 냄새를 해결하기 위한 방법
 * Smell 1. "이해하기 힘든 이름", "주석": map[r][c] == 0, 1, 2, 3 등의 코드를 보고,
 * 주석 없이는 이해하기 힘든 이름(리터럴)이라고 생각했다.
 * Solution 1. enum Tile을 정의하여, PASSAGE, SMART, GEM, WALL 등의 타일 표현 상수를 정의했다.
 * 해당 열거형을 설계할 때 기존과 호환성을 유지하기 위해서 int형 멤버변수인 tileCode를 통해
 * 기존의 int 상수 값으로 열거형을 변환 가능하게 만들었으나, 모든 리팩토링이 끝난 후에
 * 해당 상수가 별다른 의미를 가지지 않고, 상수 값 자체로 사용되는 일이 없는 것을 확인하고
 * 해당 멤버 변수를 삭제하였다. 또한 추가적으로 4줄에 걸친 리터럴을 설명하는
 * 주석 부분을 삭제하고, 열거형 변수를 사용하는 내용의 한줄 주석으로 수정했다.
 *
 * Smell 2. "긴 함수", "데이터 덩어리" - [int solve(int[][]] map)]: solve 함수가 지나치게 길다고 생각했다.
 * Solution 2. solve 함수를 적당한 함수로 분할하고, 클래스로 모델링 하기 위해서 Tile[][] tiles를
 * 래핑하는(wrapping) Map 레코드(클래스)를 정의하였다. 또한 row, column의 관련성이 큰 변수 둘을
 * 한꺼번에 편리하게 다루기 위해서 Location 레코드(클래스)를 생성하였다. 이 클래스는 row와 column 값
 * 두개를 받아 한꺼번에 다룰 수 있게 해준다. 가장 처음 시작한 함수 분할은 시작 위치를 구하는 부분이었다.
 * 해당 코드를 getStartLocation() 함수로 분할하여 무엇을 하는지 메소드 이름으로 하여금 식별이
 * 가능하도록 했다. 그 다음 row와 column 변수에 대해서 따로 선언했던 BFS용 동적 배열(ArrayList)을
 * Location 형 하나에 대해서만 사용하도록 변경했다.
 *
 * Smell 3. "코드 중복" - [int solve(int[][]] map)]: BFS의 4 방향 탐사가 이루어지는 부분에서
 * 4배 가량의 코드 중복이 일어났다.
 * Solution 3. 해당 코드 중복을 없애기 위해, 어떤 부분에서 공통점이 있나 분석해보니,
 * 모든 코드가 각각 row, column 좌표에 대한 검사를 똑같은 방식으로 실시하는 것을 발견하였다.
 * 따라서 [(1, 0), (-1, 0), (0, 1) (0, -1)] 4방향의 좌표를 Location.delta(rowDelta, columnDelta)
 * 함수를 통해 코드 중복을 없애는 방식으로 생성하고(이 부분은 Location 데이터 클래스의 기능이 되어, 해당
 * 클래스가 존재해야 할 당위성을 더해준다.) 반복문을 통해 해당 코드 부분을 처리하면서 코드 중복을
 * 제거할 수 있었다.
 *
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class CodeSmell {
    /**
     * 맵을 구성하는 구성 요소인 타일의 열거형
     */
    public enum Tile {
        PASSAGE, // 통로
        START, // 시작 위치
        GEM, // 보석
        WALL; // 벽
    }

    /**
     * row, column을 한번에 처리하기 위해 만들어진 2차원 좌표(위치) 클래스
     *
     * @param row    맵의 행
     * @param column 맵의 열
     */
    public record Location(int row, int column) {
        public Location delta(int rowDelta, int columnDelta) {
            return new Location(row + rowDelta, column + columnDelta);
        }
    }

    /**
     * 맵의 구성 정보가 담긴 tiles를 래핑(wrapping)하여 맵과 관련된 여러가지 연산을 수행하는 클래스
     *
     * @param tiles {@link Tile}의 2차원 배열
     */
    public record Map(Tile[][] tiles) {
        /**
         * 맵의 최대 행, 최대 열값이 담긴 {@link Location} 객체를 반환한다.
         *
         * @return 맵의 최대 행, 최대 열값이 담긴 {@link Location} 객체
         */
        public Location getLengthLocation() {
            return new Location(tiles.length, tiles[0].length);
        }

        /**
         * 맵의 시작 위치를 반환한다.
         *
         * @return 맵의 시작 위치가 담긴 {@link Location} 객체
         */
        public Optional<Location> getStartLocation() {
            for (int r = 0; r < tiles.length; ++r)
                for (int c = 0; c < tiles[0].length; ++c) {
                    if (tiles[r][c] == Tile.START) {
                        return Optional.of(new Location(r, c));
                    }
                }
            return Optional.empty();
        }

        /**
         * 매개변수로 들어온 위치가 올바른 범위에 있는지 확인하여, 부울 값으로 반환한다.
         *
         * @param location 올바른 범위에 있는지 확인할 {@link Location} 객체
         * @return 해당 위치가 올바른 범위에 있는지에 대한 여부 (부울 값)
         */
        public boolean checkRange(Location location) {
            Location lengthLoc = getLengthLocation();
            return 0 <= location.row && location.row < lengthLoc.row &&
                    0 <= location.column && location.column < lengthLoc.column;
        }

        /**
         * BFS를 이용하여 시작 위치에서 보석까지의 최단 거리를 찾아 반환한다.
         *
         * @return 시작 위치에서 보석까지의 최단 거리 (찾지 못할 경우 -1)
         */
        public int solve() {
            Location lengthLoc = getLengthLocation();

            // 시작 위치 탐색
            Location startLoc = getStartLocation().get();

            boolean[][] visited = new boolean[lengthLoc.row][lengthLoc.column];
            visited[startLoc.row][startLoc.column] = true;

            Queue<Location> locQueue = new ArrayDeque<>();
            locQueue.add(startLoc);

            Queue<Integer> lengthQueue = new ArrayDeque<>();
            lengthQueue.add(0);

            // 시작 위치부터 BFS 수행
            int minLength = -1;
            while (!locQueue.isEmpty()) {
                Location currLoc = locQueue.poll();
                int length = lengthQueue.poll();

                // 4개 방향으로 탐색 진행
                Location[] bfsLoc = new Location[]{
                        currLoc.delta(1, 0),
                        currLoc.delta(-1, 0),
                        currLoc.delta(0, 1),
                        currLoc.delta(0, -1)
                };
                for (Location loc : bfsLoc) {
                    if (checkRange(loc) && !visited[loc.row][loc.column]) {
                        if (tiles[loc.row][loc.column] == Tile.GEM) {
                            minLength = length + 1;
                            break;
                        } else if (tiles[loc.row][loc.column] == Tile.PASSAGE) {
                            visited[loc.row][loc.column] = true;
                            locQueue.add(loc);
                            lengthQueue.add(length + 1);
                        }
                    }
                }
            }
            return minLength;
        }
    }


    public static void main(String[] args) {
        Map map1 = new Map(new Tile[][]{
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.START, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.WALL, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.GEM, Tile.WALL, Tile.PASSAGE, Tile.PASSAGE},
                {Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL}
        });
        System.out.println(map1.solve());
        Map map2 = new Map(new Tile[][]{
                {Tile.WALL, Tile.WALL, Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.START, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.WALL, Tile.WALL, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.GEM, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE},
                {Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL, Tile.WALL}
        });
        System.out.println(map2.solve());
        Map map3 = new Map(new Tile[][]{
                {Tile.WALL, Tile.WALL, Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.WALL, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE, Tile.WALL, Tile.GEM, Tile.WALL},
                {Tile.START, Tile.PASSAGE, Tile.WALL, Tile.PASSAGE, Tile.PASSAGE, Tile.PASSAGE, Tile.WALL},
                {Tile.WALL, Tile.PASSAGE, Tile.WALL, Tile.WALL, Tile.WALL, Tile.PASSAGE, Tile.WALL}
        });
        System.out.println(map3.solve());
    }
}