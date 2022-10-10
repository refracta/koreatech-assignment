import java.util.HashMap;
import java.util.Iterator;
import java.util.Objects;

/**
 * @author 김상진, refracta(2020136110)
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @file CondimentDecorator.java
 * 장식패턴에서 장식자 추상 클래스
 */
public abstract class CondimentDecorator extends Beverage {
    protected Beverage beverage;

    protected CondimentDecorator(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public abstract String getDescription();


    /**
     * 각 재료들의 포함 횟수로 구성된 누계 맵을 반환한다.
     *
     * @return 재료들의 누계가 계산된 맵
     */
    protected HashMap<String, Integer> getCountMap() {
        HashMap<String, Integer> map = new HashMap<>();
        Iterator<Beverage> iterator = getIterator();
        while (iterator.hasNext()) {
            String name = iterator.next().getClass().getSimpleName();
            map.put(name, map.getOrDefault(name, 0) + 1);
        }
        return map;
    }

    /**
     * 커피의 모든 구성요소를 순회하는 반복자를 반환한다.
     *
     * @return 커피의 모든 구성요소를 순회하는 반복자
     */
    protected Iterator<Beverage> getIterator() {
        return new Iterator<>() {
            private Beverage currentBeverage = CondimentDecorator.this;

            @Override
            public boolean hasNext() {
                return currentBeverage instanceof Beverage;
            }

            @Override
            public Beverage next() {
                Beverage resultBeverage = currentBeverage;
                if (currentBeverage instanceof CondimentDecorator decorator) {
                    currentBeverage = decorator.beverage;
                    return resultBeverage;
                } else if (currentBeverage instanceof Beverage) {
                    resultBeverage = currentBeverage;
                    currentBeverage = null;
                    return resultBeverage;
                } else {
                    throw new RuntimeException("더 이상 객체가 존재하지 않습니다.");
                }
            }
        };
    }

    /**
     * 동일한 재료가 들어간 커피인지에 대한 부울 값을 반환한다.
     *
     * @param o 비교할 다른 객체
     * @return 동일한 재료가 들어간 커피인지에 대한 부울 값
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CondimentDecorator that)) return false;
        return Objects.equals(getCountMap(), that.getCountMap());
    }
}
