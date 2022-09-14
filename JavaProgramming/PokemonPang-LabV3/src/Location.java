import java.util.Objects;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 프로젝트: 포켓몬팡
 *
 * @author refracta
 * 그리드 위치를 유지하는 클래스
 */

public record Location(int r, int c) {
    public static boolean valid(int r, int c) {
        return (r >= 0 && r < PangUtility.GRIDSIZE &&
                c >= 0 && c < PangUtility.GRIDSIZE);
    }

    public boolean isValid() {
        return Location.valid(r, c);
    }

    /*
     * 해당 타입의 배열에서 현재 색인의 값을 가져온다.
     */
    public <T> T get(T[][] array) {
        return array[r][c];
    }

    /*
     * 해당 타입의 배열에서 현재 색인에 값을 덧씌운다.
     */
    public <T> void set(T[][] array, T target) {
        array[r][c] = target;
    }

    /*
     * 해당 타입의 배열의 두 위치를 뒤바꾼다.
     */
    public static <T> void swap(T[][] array, Location src, Location dest) {
        T srcTemp = src.get(array);
        array[src.r()][src.c()] = dest.get(array);
        array[dest.r()][dest.c()] = srcTemp;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Location location = (Location) o;
        return r == location.r && c == location.c;
    }

    @Override
    public int hashCode() {
        return Objects.hash(r, c);
    }
}

