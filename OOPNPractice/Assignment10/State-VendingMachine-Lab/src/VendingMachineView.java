import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴
 * 자동 판매기 뷰
 */
public class VendingMachineView extends Application {
	private Button[] itemButtons = new Button[6];
	private Button insertCoinButton = new Button("돈 투입");
	private Button cancelButton = new Button("취소");
	private TextField currentUserBalanceField = new TextField();
	private VendingMachine vendingMachine = new VendingMachine();
	
	// 뷰의 메뉴 생성 
	private MenuBar createMenuBar() {
		MenuItem stockSetupItem = new MenuItem("재고 정리");
		MenuItem balanceSetupItem = new MenuItem("돈 정리");
		stockSetupItem.setOnAction(e->manageStock());
		balanceSetupItem.setOnAction(e->manageBalance());	
		Menu setupMenu = new Menu("자판기 설정");
		setupMenu.getItems().addAll(stockSetupItem, balanceSetupItem);
		MenuBar menuBar = new MenuBar();
		menuBar.getMenus().add(setupMenu);
		return menuBar;
	}
	
	// 제품 선택 뷰 생성
	private GridPane createItemsPane() {
		GridPane centerPane = new GridPane();
		centerPane.setAlignment(Pos.CENTER);
		TextField[] prices = new TextField[itemButtons.length];
		for(int i=0; i<itemButtons.length; i++) {
			Item currentItem = Item.values()[i];
			prices[i] = new TextField();
			itemButtons[i] = new Button();
			itemButtons[i].setOnAction(e->processItemSelect(currentItem));
			itemButtons[i].setGraphic(new ImageView(currentItem.image));
			itemButtons[i].setDisable(true);
			prices[i].setMaxWidth(120d);
			prices[i].setEditable(false);
			prices[i].setText(String.format("%,d원", currentItem.price));
			prices[i].setAlignment(Pos.CENTER);
			centerPane.add(prices[i], i%3, (i/3==0)?1:3);
			centerPane.add(itemButtons[i], i%3, (i/3==0)?0:2);
		}
		return centerPane;
	}

	private HBox createButtonPane() {
		HBox buttonPane = new HBox();
		buttonPane.setAlignment(Pos.CENTER);
		buttonPane.setPadding(new Insets(10d));
		buttonPane.setSpacing(10d);
		currentUserBalanceField.setEditable(false);
		currentUserBalanceField.setText(String.format("%,d원", vendingMachine.getBalance()));
		currentUserBalanceField.setAlignment(Pos.BASELINE_RIGHT);
		
		insertCoinButton.setOnAction(e->processInsertCash());
		cancelButton.setOnAction(e->processCancel());
		
		buttonPane.getChildren().addAll(
			currentUserBalanceField, insertCoinButton, cancelButton);
		return buttonPane;
	}
	
	private void processItemSelect(Item item) {
		try {
			vendingMachine.selectItem(item);
		} 
		catch (ChangeNotAvailableException exception) {
			String msg = exception.changeReturned?
				"거스름을 드릴 수 없어 상품을 구매할 수 없습니다. 다른 종류의 동전/지폐를 이용해 주세요.":
				"거스름을 드릴 수 없어 이 상품을 구매할 수 없습니다. 다른 상품은 구매 가능합니다.";		
			VendingMachineUtility.showInfoDialog(msg);
		}
		currentUserBalanceField.setText(
			String.format("%,d원", vendingMachine.getInsertedBalance()));
		enableDisableButtons();
		insertCoinButton.requestFocus();
	}
	
	private void processInsertCash() {
		CashRegister cashRegister = new CashRegister();
		VendingMachineUtility.showBalanceSetupDialog(cashRegister, false);
		for(var currency: Currency.values()) {
			int amount = cashRegister.getAmount(currency);
			if(amount>0) vendingMachine.insertCash(currency, amount);
		}
		enableDisableButtons();
		currentUserBalanceField.setText(
			String.format("%,d원", vendingMachine.getInsertedBalance()));
	}
	
	private void processCancel() {
		vendingMachine.cancel();
		enableDisableButtons();
		currentUserBalanceField.setText(
			String.format("%,d원", vendingMachine.getInsertedBalance()));
	}
	
	// 상품 구매 가능 여부 활성화
	private void enableDisableButtons(){
		Item[] items = Item.values();
		boolean flag = false;
		for(int i=0; i<items.length; i++) {
			boolean buyable = vendingMachine.getNumberOfItems(items[i])>0&&
				vendingMachine.getInsertedBalance()>0 && vendingMachine.canBuyItem(items[i]);
			if(buyable) flag = true;
			itemButtons[i].setDisable(!buyable);
		}
		if(!flag) {
			for(var item: Item.values()) {
				if(vendingMachine.getNumberOfItems(item)>0 &&
					vendingMachine.getInsertedBalance()>=item.price) {
					VendingMachineUtility.showInfoDialog(
						"거스름을 드릴 수 없어 상품을 구매할 수 없습니다. 다른 종류의 동전/지폐를 이용해 주세요.");
					break;
				}
			}
			vendingMachine.cancel();
		}
	}
	
	private void manageStock() {
		VendingMachineUtility.showStockSetupDialog(vendingMachine);
		enableDisableButtons();
	}
	
	private void manageBalance() {
		CashRegister cashRegister = new CashRegister();
		for(var currency: Currency.values()) {
			int amount = vendingMachine.getAmount(currency);
			if(amount>0) cashRegister.set(currency, amount);
		}
		VendingMachineUtility.showBalanceSetupDialog(cashRegister, true);
		for(var currency: Currency.values()) {
			int amount = cashRegister.getAmount(currency);
			if(amount>0) vendingMachine.setCash(currency, amount);
		}
		enableDisableButtons();
	}
	
	@Override
	public void start(Stage mainStage) throws Exception {
		BorderPane mainPane = new BorderPane();
		mainPane.setTop(createMenuBar());
		mainPane.setCenter(createItemsPane());
		mainPane.setBottom(createButtonPane());
		mainStage.setTitle("KoreaTech Vending Machine App");
		mainStage.setScene(new Scene(mainPane));
		mainStage.show();
		insertCoinButton.requestFocus();
	}

	public static void main(String[] args) {
		Application.launch(args);
	}
}
