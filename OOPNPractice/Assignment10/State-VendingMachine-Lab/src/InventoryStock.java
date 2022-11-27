import java.util.ArrayList;
import java.util.EnumMap;
import java.util.List;
import java.util.Map;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴
 * 자동판매기: 재고 목록 
 */
public class InventoryStock {
	private Map<Item, Integer> stock = new EnumMap<>(Item.class);
	{
		for(var item: Item.values()) stock.put(item, 0);
	}
	int numberOfItems = 0;
	
	public InventoryStock() {}
	
	public boolean isEmpty() {
		return numberOfItems == 0;
	}
	
	public void clear() {
		for(var item: Item.values())
			stock.put(item, 0);
		numberOfItems = 0;
	}
	
	public void addItem(Item item, int amount) {
		if(amount<=0) throw new IllegalArgumentException();
		int currentAmount = stock.get(item);
		stock.put(item, currentAmount+amount);
		numberOfItems += amount;
	}
	
	public void setItem(Item item, int amount) {
		if(amount<0) throw new IllegalArgumentException();
		int currentAmount = stock.get(item);
		stock.put(item, amount);
		numberOfItems += amount-currentAmount;
	}
	
	public void removeItem(Item item) {
		int currentAmount = stock.get(item);
		if(currentAmount<=0) throw new IllegalStateException();
		stock.put(item, currentAmount-1);
		--numberOfItems;
	}
	
	public int getNumberOfItems(Item item) {
		return stock.get(item);
	}
	
	// 재고가 있는 제품 목록
	public List<Item> getPurchasbleitems(){
		List<Item> items = new ArrayList<>();
		for(var entry: stock.entrySet()) {
			if(entry.getValue()>0) items.add(entry.getKey());
		}
		return items;
	}
	
	public void debugPrint() {
		for(var item: stock.entrySet()) {
			System.out.println(item.getKey()+": "+item.getValue());
		}
	}
}
