import java.util.Random;

public class Assignment1 {
    /**
     * 기본 개구리 클래스
     */
    public static class Frog {
        public void jump() {
            System.out.println("폴짝폴짝");
        }

        public void croak() {
            System.out.println("개굴개굴");
        }
    }

    /**
     * 상속을 이용한 로봇 개구리 클래스
     * 장점:
     * 1. Frog 클래스의 변수와 메서드들을 모두 상속 받았기 때문에, 개구리의 기본적인 행동에 대해서 추가적인 구현할 필요가 없음.
     * 2. Frog 클래스의 레퍼런스 변수에 담아서 사용할 수 있음 (다형성)
     * 단점:
     * 1. 다중 상속이 불가능한 언어의 경우, 이미 Frog 클래스를 상속받았기 때문에 다른 클래스를 확장할 수 없음 (Robot과 Frog를 동시에 상속 받는 방식과 같은)
     * 2. 불필요한 부모 클래스의 변수와 메소드를 사용하여야 함
     * 3. 추상 클래스를 상속하고, 피상속 클래스가 구현 클래스인 경우, 모든 미구현된 메소드들을 구현해야 함
     */
    public static class InheritedRobotFrog extends Frog {
        private int battery;

        public InheritedRobotFrog() {
            charge();
            System.out.println("100%!");
        }

        @Override
        public void jump() {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return;
            }
            battery--;
            super.jump();
        }

        @Override
        public void croak() {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return;
            }
            battery--;
            super.croak();
        }

        public void charge() {
            battery = 5;
        }
    }

    /**
     * 포함을 이용한 로봇 개구리 클래스
     * 장점
     * 1. 포함된 Frog 계열 클래스의 객체를 바꿔 끼워서 다양한 개구리의 동작을 사용 가능 (PoisonFrog를 포함하는 방법 등)
     * 2. 큰 규모의 코드를 작성할 때, 상속을 이용하는 것 보다 여러 클래스를 만든 뒤 포함 관계를 이용하여 작성하면 효율적으로 기능들을 관리할 수 있음
     * 단점
     * 1. 모든 것을 그대로 물려받는 상속과 달리
     * 2. 다형성을 이용하지 못한다. (Frog형 참조 변수에 IncludeBasedRobotFrog 객체를 넣을 수 없음, 이를 이용하기 위해서는 별도의 어댑터 인터페이스를 구현해야함)
     */
    public static class IncludeBasedRobotFrog {
        private Frog frog;
        private int battery;

        public IncludeBasedRobotFrog(Frog frog) {
            this.frog = frog;
            charge();
            System.out.println("100%!");
        }

        public IncludeBasedRobotFrog() {
            this(new Frog());
        }

        public void jump() {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return;
            }
            battery--;
            this.frog.jump();
        }

        public void croak() {
            if (battery <= 0) {
                System.out.println("배터리가 부족합니다.");
                return;
            }
            battery--;
            this.frog.croak();
        }

        public void charge() {
            battery = 5;
        }
    }

    public static void main(String[] args) {
        Frog frog = new Frog();
        frog.jump();
        frog.croak();
        // 기본 개구리 클래스 작동 확인

        Random random = new Random();

        InheritedRobotFrog inheritedRobotFrog = new InheritedRobotFrog();
        // 상속을 이용한 로봇 개구리 클래스 작동 확인
        System.out.println("InheritedRobotFrog 배터리 잔량: " + inheritedRobotFrog.battery);
        for (int i = 0; i < 5; i++) {
            if (random.nextBoolean()) {
                inheritedRobotFrog.jump();
            } else {
                inheritedRobotFrog.croak();
            }
            System.out.println("InheritedRobotFrog 배터리 잔량: " + inheritedRobotFrog.battery);
        }
        inheritedRobotFrog.jump();

        IncludeBasedRobotFrog includeBasedRobotFrog = new IncludeBasedRobotFrog();
        // 포함을 이용한 로봇 개구리 클래스 작동 확인
        System.out.println("IncludeBasedRobotFrog 배터리 잔량: " + includeBasedRobotFrog.battery);
        for (int i = 0; i < 5; i++) {
            if (random.nextBoolean()) {
                includeBasedRobotFrog.jump();
            } else {
                includeBasedRobotFrog.croak();
            }
            System.out.println("IncludeBasedRobotFrog 배터리 잔량: " + includeBasedRobotFrog.battery);
        }
        includeBasedRobotFrog.jump();
    }
}

