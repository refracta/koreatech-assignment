/**
 * @author 김상진
 * 상태 패턴
 * 자동판매기
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class VendingMachine {
    private InventoryStock inventoryStock = new InventoryStock(); // 자판기가 보유하고 있는 음료 정보
    // 자판기가 보유하고 있는 돈 정보 (고객이 투입한 돈도 포함)
    private CashRegister cashRegister = new CashRegister();
    private CashRegister userCashRegister = new CashRegister(); // 고객이 투입한 돈 정보
    private VendingMachineState currentState;

    public VendingMachineState getCurrentState() {
        return currentState;
    }

    public void changeState(VendingMachineState currentState) {
        this.currentState = currentState;
    }

    // InventoryStock 상호작용
    public boolean isEmpty() {
        return inventoryStock.isEmpty();
    }

    public int getNumberOfItems(Item item) {
        return inventoryStock.getNumberOfItems(item);
    }

    // 상태 변화가 필요할 수 있음
    public void clearItems() {
        inventoryStock.clear();
    }

    // 상태 변화가 필요할 수 있음
    public void setItems(Item item, int amount) {
        inventoryStock.setItem(item, amount);
    }

    // 상태 변화가 필요할 수 있음
    public void removeItem(Item item) {
        inventoryStock.removeItem(item);
    }

    // cashRegister 상호작용
    public int getBalance() {
        return cashRegister.getBalance();
    }

    public void setCash(Currency currency, int amount) {
        cashRegister.set(currency, amount);
    }

    public int getAmount(Currency currency) {
        return cashRegister.getAmount(currency);
    }

    // userCashRegister 상호작용
    public int getInsertedBalance() {
        return userCashRegister.getBalance();
    }

    public void setUserCashRegister(CashRegister changeRegister) {
        userCashRegister = changeRegister;
    }

    // 실제 투입된 돈을 처리하는 메소드
    // 고객이 투입한 돈은 자판기 보유 돈에도 포함하여 처리함
    public void addCash(Currency currency, int amount) {
        userCashRegister.add(currency, amount);
        cashRegister.add(currency, amount);
    }

    // vendingMachine 자체와 상호작용
    public void insertCash(Currency currency, int amount) {
        if (!inventoryStock.getPurchasbleitems().isEmpty()) {
            addCash(currency, amount);
        }
    }

    public void selectItem(Item item) throws ChangeNotAvailableException {
        int changeAmount = userCashRegister.getBalance() - item.price;
        CashRegister changeRegister = getChange(changeAmount);
        if (changeRegister.getBalance() != changeAmount) {
            boolean canBuyAnyItem = canBuyAnyItem();
            if (!canBuyAnyItem) {
                cancel();
            }
            throw new ChangeNotAvailableException(!canBuyAnyItem);
        } else {
            inventoryStock.setItem(item, inventoryStock.getNumberOfItems(item) - 1);
            userCashRegister = changeRegister;
            if (!canBuyAnyItem()) {
                cancel();
            }
        }
    }

    public void cancel() {
        returnChange();
    }

    // 거스름 처리
    public CashRegister getChange(int price) {
        return cashRegister.getChange(price);
    }

    public void returnChange() {
        for (var cash : userCashRegister.getHoldingCash()) {
            if (cash.getValue() > 0)
                cashRegister.remove(cash.getKey(), cash.getValue());
        }
        userCashRegister.clear();
    }

    // 주어진 item을 구입할 수 있는지 여부를 알려줌
    boolean canBuyItem(Item item) {
        int changeAmount = userCashRegister.getBalance() - item.price;
        if (changeAmount < 0) return false;
        else if (changeAmount == 0) return true;
        else {
            CashRegister changeRegister = getChange(changeAmount);
            return changeRegister.getBalance() == changeAmount;
        }
    }

    // 구입할 수 있는 것이 있는지 여부를 알려줌
    boolean canBuyAnyItem() {
        for (var item : inventoryStock.getPurchasbleitems())
            if (canBuyItem(item)) return true;
        return false;
    }

    public void debugPrint() {
        cashRegister.debugPrint();
        inventoryStock.debugPrint();
    }
}
