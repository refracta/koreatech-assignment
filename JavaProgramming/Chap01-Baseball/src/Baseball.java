/*
 ============================================================================
 Name        : Baseball.java
 Author      : refracta
 Version     : 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 Copyright   : 2020년도 2학기 과제1
 Description : 숫자 야구 게임
  - 주어진 C 소스를 자바로 바꾸세요.
  - 자바에서 main 메소드를 포함하는 클래스를 정의하고
  - 필요한 모든 메소드를 static 메소드로 정의하여 구현하시오.
 ============================================================================
 */

import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class Baseball {
    private static Scanner in = new Scanner(System.in);
    // scanf 사용 부분의 포팅을 위한 전역 Scanner 선언

    /*
     * Java에서 난수는 ThreadLocalRandom.current() 객체를 이용함 (다른 방법도 있음)
     * 이를 위해 다음 import문이 필요함
     * import java.util.concurrent.ThreadLocalRandom;
     *
     * 사용 방법은 다음과 같음 nextInt(n)이면 0부터 n-1까지 정수 중 랜덤값 하나를 생성하여 반환함
     * ball[i] = ThreadLocalRandom.current().nextInt(10); // 0~9
     */
    static void pitch(int ball[]) {
        int flag[] = new int[10];
        ThreadLocalRandom random = ThreadLocalRandom.current();
        for (int i = 0; i < 3; i++) {
            while (true) {
                ball[i] = random.nextInt(10);
                if (flag[ball[i]] == 0) {
                    flag[ball[i]] = 1;
                    break;
                }
            }
        }
    }

    /*
     * 자바에서는 int compare(int[] ball, int[] bat) 형태로 정의
     */
    static int compare(int ball[], int bat[]) {
        int flag[] = new int[10];
        int scount = 0;
        int bcount = 0;
        int i;
        for (i = 0; i < 3; i++) flag[ball[i]] = 1;
        for (i = 0; i < 3; i++) {
            if (ball[i] == bat[i]) ++scount;
            else if (flag[bat[i]] == 1) ++bcount;
        }
        if (scount == 3)
            return 1;
        else if (scount == 0 && bcount == 0) return -1;
        else {
            System.out.printf("S: %d, B: %d\n", scount, bcount);
            return 0;
        }
    }

    /*
     * Java 배열
     * int[] bat = new int[3]; 자동으로 0으로 모두 초기화
     *
     * 자바에서 타자 값 입력
     * for(int i=0; i<3; i++) bat[i] = in.nextInt();
     */
    static void playGame() {
        int bat[] = new int[3];
        int ball[] = new int[3];
        int result;
        int out = 0;
        pitch(ball);
        while (true) {
            // System.out.println(Arrays.stream(ball).boxed().collect(Collectors.toList()));
            // 빠른 디버그용 코드
            System.out.printf("[0-9]까지 숫자 3개를 입력하시오: ");
            for (int i = 0; i < 3; i++) bat[i] = in.nextInt();
            result = compare(ball, bat);
            if (result == 1) {
                System.out.printf("사용자 승\n");
                break;
            } else if (result == -1) {
                ++out;
                System.out.printf("OUT: %d\n", out);
                if (out == 3) {
                    System.out.printf("컴퓨터 승\n");
                    break;
                }
            }
        }
    }

    /*
     * Java
     * boolean done()
     * getchar -> in.nextLine를 이용하여 문자열 입력 후 문자열 비교
     * 예) String s = in.nextLine(); s = s.toLowerCase(); if(s.equals("n"))
     */
    static boolean done() {
        System.out.printf("새 게임(y/n)? ");
        in.nextLine();
        // 표준 입력 비우기
        String s = in.nextLine();
        return s.equalsIgnoreCase("n");
        // toLowerCase를 사용하지 않고 바로 String을 비교
    }

    public static void main(String[] args) {
        do {
            playGame();
        } while (!done());
        System.exit(0);
        // 종료 코드 0 (EXIT_SUCCESS)으로 죵료
    }
}
