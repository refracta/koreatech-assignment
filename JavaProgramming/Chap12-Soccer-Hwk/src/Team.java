import java.util.Objects;

/**
 * @author refracta
 * Team: 축구 구단 정보
 * 요구사항. toString, hashCode, equals, clone 재정의
 * toString은 각자 알아서
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 */
public final class Team implements Comparable<Team>, Cloneable {
    private String name;
    private String country;
    public int currentLeaguePos = 0;  // 비시즌에서는 0

    public Team(String name, String country) {
        this.name = Objects.requireNonNull(name);
        this.country = Objects.requireNonNull(country);
    }

    public void setCurrentLeaguePos(int pos) {
        if (pos >= 0) currentLeaguePos = pos;
    }

    @Override
    public String toString() {
        return "Team{" +
                "name='" + name + '\'' +
                ", country='" + country + '\'' +
                ", currentLeaguePos=" + currentLeaguePos +
                '}';
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, country, currentLeaguePos);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Team team = (Team) o;
        return currentLeaguePos == team.currentLeaguePos && Objects.equals(name, team.name) && Objects.equals(country, team.country);
    }

    @Override
    public int compareTo(Team o) {
        return Integer.compare(currentLeaguePos, o.currentLeaguePos);
    }

	@Override
	protected Team clone() throws CloneNotSupportedException {
		return (Team) super.clone();
	}
}
