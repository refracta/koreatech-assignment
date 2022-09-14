import java.util.Random;

public class Assignment1_4 {
    /**
     * 상속과 포함을 모두 이용하지 않는 RobotFrog 클래스 (의존 관계를 이용한 RobotFrog 설계)
     * Frog 클래스의 객체를, RobotFrog 클래스 메소드 안의 매개변수, 반환 값으로 아주 짧은 시간동안만 사용하여 (의존 관계) RobotFrog를 구현함
     * 모든 함수는 Frog 클래스와, battery 변수를 매개변수를 받아 내부의 로직을 실행하고 변화한 battery 값을 반환함
     */

    public class DependenceBasedRobotFrog {

        // 내부의 Frog 객체를 포함하거나, Frog 클래스를 확장하지 않고 외부의 Frog 객체와 battery에 의존하여 RobotFrog의 메서드들을 구현하였다.
        public static int jump(Assignment1.Frog frog, int battery) {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return battery;
            }
            frog.jump();
            return battery - 1;
        }

        public static int croak(Assignment1.Frog frog, int battery) {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return battery;
            }
            frog.croak();
            return battery - 1;
        }

        public static int charge() {
            System.out.println("100%");
            return 5;
        }
    }

    public static void main(String[] args) {
        // 의존 관계를 이용한 RobotFrog 클래스 작동 확인
        Assignment1.Frog frog = new Assignment1.Frog();
        int battery = DependenceBasedRobotFrog.charge();
        System.out.println("배터리 잔량: " + battery);

        Random random = new Random();
        for (int i = 0; i < 5; i++) {
            battery = random.nextBoolean() ? DependenceBasedRobotFrog.jump(frog, battery) : DependenceBasedRobotFrog.croak(frog, battery);
            System.out.println("배터리 잔량: " + battery);
        }
        battery = random.nextBoolean() ? DependenceBasedRobotFrog.jump(frog, battery) : DependenceBasedRobotFrog.croak(frog, battery);
    }
}
