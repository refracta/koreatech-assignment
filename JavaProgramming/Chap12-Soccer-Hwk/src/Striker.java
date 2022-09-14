import java.util.Objects;

/**
 * @author refracta
 * Strike: 공격수
 * 부모 클래스: Player
 * 요구사항. toString, hashCode, equals, clone, comparTo 재정의
 * toString은 기본적으로 부모의 toString을 활용하는 형태로 각자 알아서
 * compareTo는 부모에 정의된 메소드를 먼저 이용하고, 동일하면 goal을 이용하여 비교
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 */
public final class Striker extends Player implements Cloneable {
    private int goal = 0;
    private int assist = 0;

    public Striker(String name, int number, Team team) {
        super(name, number, team);
    }

    @Override
    public String toString() {
        return "Striker{" +
                "goal=" + goal +
                ", assist=" + assist +
                "} " + super.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Striker striker = (Striker) o;
        return goal == striker.goal && assist == striker.assist;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), goal, assist);
    }

    @Override
    public int compareTo(Player o) {
        int compare = super.compareTo(o);
        if (o instanceof Striker striker) {
            return compare == 0 ? Integer.compare(goal, striker.goal) : compare;
        } else {
            return compare;
        }
    }

	@Override
	protected Striker clone() throws CloneNotSupportedException {
        Striker clone = (Striker) super.clone();
        clone.goal = goal;
        clone.assist = assist;
        return clone;
	}
}
