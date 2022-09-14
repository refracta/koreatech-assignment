/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @version 2021년도 2학기
 * @author refracta
 */
public class SpecialSoldier extends Soldier{
    @Override
    public int attack() {
        return 2 + super.attack();
    }
}
