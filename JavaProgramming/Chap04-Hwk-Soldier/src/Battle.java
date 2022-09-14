
/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta
 * @file Battle.java
 * 두 명의 군인이 전투
 */
public class Battle {
	// 라운드마다 각자 공격을 함
	// 공격 후 죽지 않았으면 회복 가능
	public static void battle(Soldier a, Soldier b) {
		int round = 1;
		while(true) {
			a.defend(b.attack());
			b.defend(a.attack());
			System.out.printf("Attack Round %d: A(%d), B(%d)%n",
				round, a.getHealth(), b.getHealth());
			if(!a.isLive() || !b.isLive()) break;
			a.heal();
			b.heal();
			System.out.printf("Healing Round %d: A(%d), B(%d)%n",
				round, a.getHealth(), b.getHealth());
			++round;
		}
		if(!a.isLive() && !b.isLive()) System.out.println("DRAW");
		else if(!a.isLive()) System.out.println("B win");
		else System.out.println("A win");
	}
	public static void main(String[] args) {
		Soldier alice = new Soldier();
		Soldier bob = new Soldier();
		battle(alice, bob);

		Soldier special = new SpecialSoldier();
		Soldier medic = new AbstractSoldierAdapter() {
			private MedicSoldier soldier = new MedicSoldier(new Soldier());

			@Override
			public int attack() {
				return soldier.attack();
			}

			@Override
			public void defend(int hitPower) {
				soldier.defend(hitPower);
			}

			@Override
			public void heal() {
				soldier.heal();
			}

			@Override
			public boolean isLive() {
				return soldier.isLive();
			}

			@Override
			public int getHealth() {
				return soldier.getHealth();
			}
		};
		battle(special, medic);
	}

}
