import java.util.concurrent.ThreadLocalRandom;

/**
 * @author 김상진, refracta
 * 팩토리 메소드 패턴: Asteroid
 * AsteroidRectangleFactory.java: 직사각형으로 소행성을 나타냄
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class AsteroidRectangleFactory extends AsteroidFactory {
    @Override
    protected Double[] createPoints(Location centerLoc, int radius) {
        Double[] points = new Double[8];
        int width = radius;
        int height = radius;
        if (ThreadLocalRandom.current().nextBoolean())
            width += ThreadLocalRandom.current().nextInt(radius);
        if (ThreadLocalRandom.current().nextBoolean())
            height += ThreadLocalRandom.current().nextInt(radius);
        // width, height 처리

        points[0] = centerLoc.x() - width;
        points[1] = centerLoc.y() - height;
        points[2] = centerLoc.x() + width;
        points[3] = centerLoc.y() - height;
        points[4] = centerLoc.x() + width;
        points[5] = centerLoc.y() + height;
        points[6] = centerLoc.x() - width;
        points[7] = centerLoc.y() + height;
        // centerLoc을 기준으로 사각형 점 생성

        return points;
    }
}
