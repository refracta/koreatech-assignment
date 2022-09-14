import java.util.concurrent.ThreadLocalRandom;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta 
 * @file Soldier.java
 * 군인 클래스
 * ThreadLocalRandom.current()는 난수 발생해주는 객체
 * nextInt(n)은 0~(n-1) 사이의 난수 발생
 * nextBoolean()은 true 또는 false 중 하나를 랜덤하게 줌
 */
public class Soldier {
	private int health = 10;
	// 공격할 때 상대방에 입힐 수 있는 최대 피해
	public int attack() {
		return ThreadLocalRandom.current().nextInt(5);
	}
	// 상대방이 공격하였을 때 실제로 받는 피해 반영
	public void defend(int hitPower) {
		if(ThreadLocalRandom.current().nextBoolean())
			health -= hitPower;
		else health -= hitPower/2;
		if(health<0) health = 0;
	}
	public void heal() {
		health += ThreadLocalRandom.current().nextInt(2);
		if(health>10) health = 10;
	}
	public boolean isLive() {
		return health>0;
	}
	public int getHealth() {
		return health;
	}
}
