import java.util.ArrayList;
import java.util.EnumMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴
 * 자판기가 유지하는 돈, 사용자가 투입한 돈, 거스름 돈을 나타내기 위해 사용
 */
public class CashRegister {
	private Map<Currency, Integer> register = new EnumMap<>(Currency.class);
	{
		for(var currency: Currency.values()) register.put(currency, 0);
	}
	private int balance = 0;
	
	public CashRegister() {}
	public void clear() {
		for(var currency: Currency.values()) register.put(currency, 0);
		balance = 0;
	}
	
	public List<Entry<Currency, Integer>> getHoldingCash(){
		List<Entry<Currency, Integer>> entryList = new ArrayList<>();
		for(var entry: register.entrySet())
			if(entry.getValue()>0) entryList.add(entry);
		return entryList;
	}
	
	public void add(Currency money, int amount) {
		if(amount<=0) throw new IllegalArgumentException();
		int currentAmount = register.get(money);
		register.put(money, currentAmount+amount);
		balance += amount*money.value;
	}
	
	public void set(Currency money, int amount) {
		if(amount<0) throw new IllegalArgumentException();
		int diff = amount-register.get(money);
		register.put(money, amount);
		balance += diff*money.value;
	}
	
	public void remove(Currency money, int amount) {
		if(amount<=0) throw new IllegalArgumentException();
		int currentAmount = register.get(money);
		if(currentAmount<amount) throw new IllegalStateException();
		register.put(money, currentAmount-amount);
		balance -= amount*money.value;
	}
	
	public int getBalance() {
		return balance;
	}
	
	public int getAmount(Currency money) {
		return register.get(money);
	}
	
	public CashRegister getChange(int changeAmount) {
		if(changeAmount<0) throw new IllegalArgumentException(); 
		CashRegister changeRegister = new CashRegister();
		if(changeAmount==0) return changeRegister;
		//System.out.println("거스름액: "+changeAmount);
		boolean changePossible = false;
		Currency[] moneys = Currency.values();
		// 탐욕적 방법. 가장 큰 액면가부터 이용
		for(int i=moneys.length-1; i>=0; i--) {
			int currentAmount = register.get(moneys[i]);
			//System.out.printf("%d: %d%n", moneys[i].value, currentAmount);
			if(currentAmount==0) continue;
			int amountNeeded = 0;
			if(moneys[i].value>changeAmount) continue;
			else {
				amountNeeded = changeAmount/moneys[i].value;
				//System.out.println(moneys[i].value+"원: 필요한 개수: "+amountNeeded);
			}
			int amountUsed = (amountNeeded>=currentAmount)? currentAmount: amountNeeded;
			changeRegister.add(moneys[i], amountUsed);
			changeAmount -= amountUsed*moneys[i].value;
			//System.out.println("남은 거스름액: "+changeAmount);
			if(changeAmount==0) {
				changePossible = true;
				break;
			}
		}
		if(!changePossible) changeRegister.clear();
		return changeRegister;
	}
	
	public void debugPrint() {
		for(var entry: register.entrySet()) {
			System.out.println(entry.getKey()+": "+entry.getValue());
		}
		System.out.printf("총금액: %,d원%n", balance);
	}
}
