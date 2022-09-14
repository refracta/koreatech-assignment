import java.util.Objects;

/**
 * @author refracta
 * Player: 축구 선수 추상 클래스
 * 요구사항. toString, hashCode, equals, clone, compareTo 재정의
 * equals와 hashcode는 항상 모든 멤버 변수를 이용하여 비교/계산함
 * team 멤버는 깊은 복사가 필요하다고 가정함
 * toString은 각자 알아서
 * compareTo는 name을 이용하여 먼저 비교하고, 그다음 number를 이용하여 비교
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 */
public abstract class Player implements Comparable<Player>, Cloneable {
    private String name;
    private int number;
    private Team team;

    public Player(String name, int number, Team team) {
        setName(name);
        setNumber(number);
        this.team = Objects.requireNonNull(team);
    }

    public void setName(String name) {
        this.name = Objects.requireNonNull(name);
    }

    public void setNumber(int number) {
        if (number < 0) throw new IllegalArgumentException("");
        this.number = number;
    }


    @Override
    public String toString() {
        return "Player{" +
                "name='" + name + '\'' +
                ", number=" + number +
                ", team=" + team +
                '}';
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, number, team);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Player player = (Player) o;
        return number == player.number && Objects.equals(name, player.name) && Objects.equals(team, player.team);
    }

    @Override
    public int compareTo(Player o) {
        return Integer.compare(number, o.number);
    }

    @Override
    protected Player clone() throws CloneNotSupportedException {
        return (Player) super.clone();
    }
}
