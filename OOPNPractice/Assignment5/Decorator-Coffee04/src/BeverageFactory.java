import java.lang.reflect.Constructor;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 *
 * @author 김상진, refracta
 * @version 2022년도 2학기
 * @file BeverageFactory.java
 * 생성 메소드가 정의되어 있는 클래스 (자바 reflection 활용)
 */
public class BeverageFactory {
    private static final Map<String, Restriction> restrictionTable = new HashMap<>();

    /**
     * 첨가물의 제한 횟수를 설정한다.
     *
     * @param condiment   첨가물
     * @param maxAddition 제한 횟수
     */
    public static void addAdditionRestriction(String condiment, int maxAddition) {
        if (restrictionTable.containsKey(condiment)) {
            Restriction restriction = restrictionTable.get(condiment);
            restriction.maxAddition = maxAddition;
        } else {
            Restriction restriction = new Restriction();
            restriction.maxAddition = maxAddition;
            restrictionTable.put(condiment, restriction);
        }
    }

    /**
     * 커피에 첨가물 제한을 추가한다.
     *
     * @param condiment 제한할 첨가물
     * @param coffee    커피
     */
    public static void addCoffeeRestriction(String condiment, String coffee) {
        if (restrictionTable.containsKey(coffee)) {
            Restriction restriction = restrictionTable.get(coffee);
            restriction.exclusionList.add(condiment);
        } else {
            Restriction restriction = new Restriction();
            restriction.exclusionList.add(condiment);
            restrictionTable.put(coffee, restriction);
        }
    }

    /**
     * @param key 첨가물 또는 커피
     * @return 삭제된 제한
     */
    public static Restriction removeRestriction(String key) {
        return restrictionTable.remove(key);
    }

    public static Beverage createCoffee(String coffee, String... list)
            throws Exception {
        Beverage beverage = createBaseCoffee(coffee);
        beverage = decorateBaseCoffeeV3(beverage, list);
        return beverage;
    }

    private static Beverage createBaseCoffee(String coffee) throws Exception {
        Class<? extends Beverage> coffeeClass
                = Class.forName(coffee).asSubclass(Beverage.class);
        if (coffeeClass.getSuperclass() != Beverage.class || coffeeClass == CondimentDecorator.class)
            throw new IllegalArgumentException("Must use Concrete Decoretee");

        Constructor<? extends Beverage> coffeeConstructor = coffeeClass.getDeclaredConstructor();
        Beverage beverage = coffeeConstructor.newInstance();
        return beverage;
    }

    /**
     * 재료 리스트에 있는 각 재료들의 포함 횟수로 구성된 누계 맵을 반환한다.
     *
     * @param list 재료 리스트
     * @return 재료들의 누계가 계산된 맵
     */
    private static Map<String, Integer> toCountMap(String... list) {
        Map<String, Integer> map = new HashMap<>();
        for (String e : list) {
            map.put(e, map.getOrDefault(e, 0) + 1);
        }
        return map;
    }

    private static Beverage decorateBaseCoffeeV3(Beverage beverage, String... list) throws Exception {
        if (list.length == 0) return beverage;
        String beverageName = beverage.getClass().getSimpleName();
        Set<String> exclusionList = restrictionTable.getOrDefault(beverageName, new Restriction()).exclusionList;

        Map<String, Integer> countMap = toCountMap(list);
        Iterator<Map.Entry<String, Integer>> iterator = countMap.entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry<String, Integer> next = iterator.next();
            String element = next.getKey();
            int count = next.getValue();
            if (exclusionList.contains(element)) {
                throw new IllegalArgumentException(element + "(은)는 " + beverageName + "에 넣을 수 없습니다.");
                // exclusionList 처리
            }
            if (restrictionTable.containsKey(element)) {
                Restriction restriction = restrictionTable.get(element);
                if (count > restriction.maxAddition) {
                    throw new IllegalArgumentException(element + "(은)는 " + restriction.maxAddition + "개보다 많이 넣을 수 없습니다. (" + count + ">" + restriction.maxAddition + ")");
                    // maxAddition 처리
                }
            }
            for (int i = 0; i < count; i++) {
                Class<? extends CondimentDecorator> condimentClass = Class.forName(element).asSubclass(CondimentDecorator.class);
                Constructor<? extends CondimentDecorator> condimentConstructor = condimentClass.getDeclaredConstructor(Beverage.class);
                // 생성자를 protected로 수정하여, BeverageFactory의 restriction 검사를 거치지 않고는, 외부에서 객체 생성이 가능하지 않게 처리함
                beverage = condimentConstructor.newInstance(beverage);
                // countMap을 이용하여 효율적인 생성
            }
        }
        return beverage;
    }
}
