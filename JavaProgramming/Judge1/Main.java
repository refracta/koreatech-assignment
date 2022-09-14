import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.stream.Collectors;

import static java.lang.Integer.parseInt;
/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 과제 07. 배열 (judge.koreatech.ac.kr)
 * @author refracta 
 */
public class Main {
    private static Deque<Integer> get(String s) {
        return Arrays.stream(s.split(" ")).map(Integer::parseInt).collect(Collectors.toCollection(ArrayDeque::new));
    }
	
	public static void main(String[] args) throws IOException {
		char selectProblem = 'A';
		if(selectProblem == 'A') {
			problemA(args);
		} else if (selectProblem == 'B') {
			problemB(args);
		}
	}
	
	// https://judge.koreatech.ac.kr/showsource.php?id=63763
    public static void problemA(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        /* String testCase = "2\n" +
                "2 3 2\n" +
                "0 1 1 1\n" +
                "2 2 2\n" +
                "1 1 0 0";
        BufferedReader bf = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(testCase.getBytes()))); */
        int numOfCase = parseInt(bf.readLine());
        for (int i = 0; i < numOfCase; i++) {
            Deque<Integer> mnkSplit = get(bf.readLine());
            int m = mnkSplit.poll();
            int n = mnkSplit.poll();
            int k = mnkSplit.poll();
            int matrix[][] = new int[m][n];
            Deque<Integer> rcSet = get(bf.readLine());
            for (int j = 0; j < k; j++) {
                int r = rcSet.poll();
                int c = rcSet.poll();
                for (int rr = 0; rr < m; rr++) {
                    matrix[rr][c]++;
                }
                for (int cc = 0; cc < n; cc++) {
                    matrix[r][cc]++;
                }
            }
            // 행렬 구성
            int count = 0;
            for (int rr = 0; rr < m; rr++) {
                for (int cc = 0; cc < n; cc++) {
                    count += matrix[rr][cc] % 2 == 1 ? 1 : 0;
                }
            }
            // 홀수 셀 세기
            System.out.println(count);
        }
    }

	// https://judge.koreatech.ac.kr/showsource.php?id=63761
    public static void problemB(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        /* String testCase = "3\n" +
                "7\n" +
                "-1 -2 -3 -4 3 2 1\n" +
                "5\n" +
                "1 5 0 -2 3\n" +
                "5\n" +
                "-1 1 -1 1 -1";
        BufferedReader bf = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(testCase.getBytes()))); */
        int numOfCase = parseInt(bf.readLine());
        for (int i = 0; i < numOfCase; i++) {
            bf.readLine();
            Integer zeroOrMinusCountP1 = get(bf.readLine()).stream().reduce(1, (acc, integer) -> acc == 0 || integer == 0 ? 0 : acc + (integer < 0 ? 1 : 0));
            // 요소에 0이 있으면 0, 0이 없고 음수가 있으면 음수 개수가 홀수일 때 -1, 그 외의 경우에는 1을 반환하면 된다.
            // 해당 람다식과 reduce 함수 호출은 요소에 0이 있으면 0을, 0이 없고 음수가 있으면 음수 개수 + 1을 반환한다.
            System.out.println(zeroOrMinusCountP1 == 0 ? 0 : (zeroOrMinusCountP1 % 2 == 0 ? -1 : 1));
            // 결과 출력
        }
    }
}
