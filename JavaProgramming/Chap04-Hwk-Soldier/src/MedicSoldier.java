/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta
 *
 * 두 클래스를 정의해 보면 SpecialSoldier가 훨씬 정의하기 편하다는 것을 알 수 있다.
 * 또 상속을 하게 되면 SpecialSoldier도 Soldier 리모컨으로 처리할 수 있는 이점이 있다.
 * 그러면 포함 관계는 어떤 이점이 있을까? 이 예에 대해서만 생각하지 말고 일반적으로 생각하여 그 답변을 MedicSoldier를 정의한 파일 프로그램 주석에 포함하시오.
 *
 * A. 포함 관계에는 피포함 객체의 기능을 독립적으로 사용할 수 있는 강점이 존재한다. (Subtyping),
 * 객체 지향 프로그래밍에서 주요하게 다뤄지는 원칙으로 개방 폐쇄 원칙(Open-Closed Principle)에 따르면
 * 클래스는 확장에 대해서는 열려 있어야 하지만 코드 변경에 대해서는 닫혀 있어야 한다.
 * 포함 관계를 사용하면 이 개방 폐쇄 원칙을 위반하지 않고 유연한 확장이 가능케하는 구현이 가능하다.
 * 그 예로는 특정한 알고리즘을 캡슐화하여 정의 한 뒤 상호 교체가 가능하게 만드는 디자인 패턴인 전략 패턴(Strategy pattern)과
 * 상속/구현과 동시에 내부 멤버로 기능을 붙일 클래스를 포함하고 기능을 붙여 확장하는 장식자 패턴(Decorator pattern),
 * 포함하는 객체의 기능을 다른 객체로 넘겨, 피위임 되는 객체의 변경이 다른 객체에 미치는 영향을 줄이고 기능을 위임하여 대리로 수행하게 하는 대리자 패턴(Delegate pattern) 등이 있다.
 * 이 디자인 패턴들은 포함 관계를 사용하여 얻을수 있는 이점을 잘 보여주는 예시이다.
 *
 */
public class MedicSoldier {
    private Soldier soldier;

    public MedicSoldier(Soldier soldier) {
        this.soldier = soldier;
    }

    public int attack() {
        return soldier.attack();
    }

    public void defend(int hitPower) {
        soldier.defend(hitPower);
    }

    public void heal() {
        soldier.heal();
        soldier.heal();
    }

    public boolean isLive() {
        return soldier.isLive();
    }

    public int getHealth() {
        return soldier.getHealth();
    }
}
