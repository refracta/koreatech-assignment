/**
 * @author 김상진, refracta
 * 상태 패턴
 * 상태 interface
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */

public enum VendingMachineState {
    /**
     * 매진 상태, addItems 등을 통해 SOLD 상태로 전이되어야 자판기가 작동함
     * 매진 상태에서는 insertCash로 금액 투입시 충전되지 않음 (빈 메소드로 모델링)
     */
    SOLD_OUT {
    },

    /**
     * 판매 상태, 취소와 금액 투입을 처리함
     */
    SOLD {
        @Override
        public void cancel(VendingMachine vendingMachine) {
            vendingMachine.returnChange();
        }

        @Override
        public void insertCash(VendingMachine vendingMachine, Currency currency, int amount) {
            vendingMachine.addCash(currency, amount);
        }
    },

    /**
     * 거스름 돈이 없어 금액을 거슬러줄 수 없는 상태
     * 살 수 있는 물건도 없으면 취소하고 ChangeNotAvailableException를 던짐
     */
    NO_CHANGE {
        @Override
        public void cancel(VendingMachine vendingMachine) {
            vendingMachine.returnChange();
        }

        @Override
        public void selectItem(VendingMachine vendingMachine, Item item) throws ChangeNotAvailableException {
            boolean canBuyAnyItem = vendingMachine.canBuyAnyItem();
            if (!canBuyAnyItem) {
                vendingMachine.cancel();
            }
            throw new ChangeNotAvailableException(!canBuyAnyItem);
        }

        @Override
        public void insertCash(VendingMachine vendingMachine, Currency currency, int amount) {
            vendingMachine.addCash(currency, amount);
        }
    },

    /**
     * 물건이 나오기 직전의 상태
     */
    DISPENSE {
        @Override
        public void cancel(VendingMachine vendingMachine) {
            vendingMachine.returnChange();
        }

        @Override
        public void selectItem(VendingMachine vendingMachine, Item item) throws ChangeNotAvailableException {
            vendingMachine.removeItem(item);

            int changeAmount = vendingMachine.getInsertedBalance() - item.price;
            CashRegister changeRegister = vendingMachine.getChange(changeAmount);
            vendingMachine.setUserCashRegister(changeRegister);
            // 사용자가 투입한 돈에 거스름 돈 반영

            if (!vendingMachine.canBuyAnyItem()) {
                vendingMachine.cancel();
                if (!vendingMachine.isEmpty()) {
                    throw new ChangeNotAvailableException(true);
                }
            }
            // 더 살수 있는 물건이 없으면 거스름 돈 반환 처리

            vendingMachine.setDispenseItem(item);
            // 내보낼 물건 설정

            vendingMachine.changeState(vendingMachine.isEmpty() ? SOLD_OUT : SOLD);
            // 재고 상태에 따라 상태 전이
        }

        @Override
        public void dispenseItem(Item item) {
            System.out.println(item + "(이)가 자판기에서 나왔습니다.");
        }
    };

    public void insertCash(VendingMachine vendingMachine, Currency currency, int amount) {}

    public void selectItem(VendingMachine vendingMachine, Item item) throws ChangeNotAvailableException {}

    public void cancel(VendingMachine vendingMachine) {}

    public void dispenseItem(Item item) {}

    // 상태 변경을 유발하는 관리자용 함수들. State 클래스에서 모든 상태 관제를 맡기 위해서 아래와 같이 설계
    public void clearItems(VendingMachine vendingMachine, InventoryStock inventoryStock) {
        inventoryStock.clear();
        vendingMachine.changeState(VendingMachineState.SOLD_OUT);
    }

    public void setItems(VendingMachine vendingMachine, InventoryStock inventoryStock, Item item, int amount) {
        inventoryStock.setItem(item, amount);
        if (amount > 0) {
            vendingMachine.changeState(VendingMachineState.SOLD);
        }
    }

    public void removeItem(VendingMachine vendingMachine, InventoryStock inventoryStock, Item item) {
        inventoryStock.removeItem(item);
        if (inventoryStock.isEmpty() && vendingMachine.getCurrentState() != VendingMachineState.DISPENSE) {
            vendingMachine.changeState(VendingMachineState.SOLD_OUT);
        }
    }

    /**
     * 거슬러 줄 수 있는지 확인하고, 다음 상태로 상태 전이하는 함수
     */
    public void checkChange(VendingMachine vendingMachine, Item item) {
        int changeAmount = vendingMachine.getInsertedBalance() - item.price;
        CashRegister changeRegister = vendingMachine.getChange(changeAmount);
        if (changeRegister.getBalance() != changeAmount) {
            vendingMachine.changeState(NO_CHANGE);
        } else {
            vendingMachine.changeState(DISPENSE);
        }
    }
}
