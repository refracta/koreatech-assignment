import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.stream.Stream;

import static java.lang.Integer.parseInt;
import static java.util.Arrays.stream;
import static java.util.stream.Collectors.joining;

/**
 * 한국기술교육대학교 컴퓨터공학부
 * 2021년도 1학기 학기 과제 08. 문자열 (judge.koreatech.ac.kr)
 *
 * @author refracta
 */
public class Main {

    // Short coding을 해보려고 가독성을 포기하고 함수형 프로그래밍을 남용하였으나 코드 길이를 그렇게 많이 줄이지는 못한 것 같습니다...
    public static void main(String[] args) throws IOException {
        char selectProblem = 'A';
        if (selectProblem == 'A') {
            problemA();
        } else if (selectProblem == 'B') {
            problemB();
        }
    }

    // https://judge.koreatech.ac.kr/showsource.php?id=64263
    public static void problemA() throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int numOfCase = parseInt(bf.readLine());
        for (int i = 0; i < numOfCase; i++) {
            bf.readLine();
            var maps = stream(bf.readLine().split(" ")).map(e -> stream(e.split("")).filter(s -> !s.equals(" "))).map(e -> {
                var m = new TreeMap<String, Integer>();
                e.forEach(c -> m.put(c, m.getOrDefault(c, 0) + 1));
                return m;
            }).toList();
            // "bella label roller"를 [{b:1,e:1,l:2,a:1},{l:2,a:1,b:1,e:1},{r:1,o:1,l:2,e:1,r:1}] 꼴로 변환
            System.out.println(maps.stream().map(m -> m.keySet()).reduce(new TreeSet<>(maps.get(0).keySet()), (a, s) -> {
                a.retainAll(s);
                return a;
            }).stream().map(s -> s.repeat(maps.stream().map(m -> m.get(s)).min(Integer::compare).get())).collect(joining("")));
            // 위의 map list에서 keySet의 교집합을 구해서 ['e', 'l'] 꼴로 변환한 뒤 map list에서 각 철자의 minimum을 구하고 string joining.
            // 알파벳 순서는 TreeMap을 사용하였기 때문에 유지됨
        }
    }

    // https://judge.koreatech.ac.kr/showsource.php?id=64264
    public static void problemB() throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int numOfCase = parseInt(bf.readLine());
        for (int i = 0; i < numOfCase; i++) {
            String l = bf.readLine();
            String[] p = l.split("#");
            boolean lastSharp = l.charAt(l.length() - 1) == '#';
            System.out.println(Stream.concat(stream(p).limit(p.length - (lastSharp ? 0 : 1)).map(s -> s.length() >= 2 ? Stream.concat(stream(s.substring(0, s.length() - 2).split("")), Stream.of(s.substring(s.length() - 2))).filter(r -> !r.equals("")).map(t -> parseInt(t)) : Stream.of(parseInt(s))).flatMap(s -> s), lastSharp ? Stream.empty() : stream(p[p.length - 1].split("")).map(t -> parseInt(t))).map(t -> String.valueOf((char) (96 + t))).collect(joining()));
            /*
               <전체 문자열>을 "#" splitting 이후 <잘려진 문자열> 처리에 대해서
               마지막 <잘려진 문자열>이 아닌 경우 -> [...(마지막 두 글자를 제외한 <잘려진 문자열>).split(""), <잘려진 문자열>의 마지막 두 글자]
               마지막 <잘려진 문자열>인 경우 ->
                    <전체 문자열>이 #으로 끝나지 않는 경우 -> (<잘려진 문자열>).split("")
                    <전체 문자열>이 #으로 끝나는 경우 -> (마지막 <잘려진 문자열>이 아닌 경우)와 똑같이 처리
               이후 parseInt 후 (char) ('a' - 1 + i)로 mapping한 뒤 stringify
            */
        }
    }
}
