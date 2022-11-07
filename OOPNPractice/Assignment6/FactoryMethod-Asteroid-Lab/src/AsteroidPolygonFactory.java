import java.util.concurrent.ThreadLocalRandom;

/**
 * @author 김상진, refracta
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidPolygonFactory.java: 다각형으로 소행성을 나타냄
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class AsteroidPolygonFactory extends AsteroidFactory {
    @Override
    protected Double[] createPoints(Location centerLoc, int radius) {
        int numberOfPoints = ThreadLocalRandom.current().nextInt(10, 15 + 1);
        // 기본 10개에 랜덤으로 5개 이내의 점을 추가하는 형태로 구현
        Double[] points = new Double[numberOfPoints * 2];
        double[] angles = ThreadLocalRandom.current().doubles(numberOfPoints, 0, 2 * Math.PI).sorted().toArray();
        // 0 ~ 360도 사이의 각을 numberOfPoints만큼 생성
        for (int i = 0; i < numberOfPoints; i++) {
            double r = ThreadLocalRandom.current().nextDouble(radius, radius * 1.5);
            // 1 ~ 1.5 radius 사이의 반지름 랜덤 생성
            points[2 * i] = centerLoc.x() + r * Math.cos(angles[i]);
            points[2 * i + 1] = centerLoc.y() + r * Math.sin(angles[i]);
            // 생성한 각도를 순회하면서 centerLoc을 중심으로 해당 각도로 r만큼 떨어진 곳의 점을 생성함
        }
        return points;
    }
}
