import javafx.geometry.Insets;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonBar;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 상태 패턴
 * 자동판매기 뷰에서 실행되는 각종 dialog
 * 1) showStockSetupDialog: 재고 관리
 * 2) showBalanceSetupDialog: 현금 관리, 동전/지패 투입 관리
 * 3) showInfoDialog
 */
public class VendingMachineUtility {
	public static void showStockSetupDialog(VendingMachine vendingMachine) {
		Dialog<Boolean> dialog = new Dialog<>();
		dialog.setTitle("자판기 재고 관리");
		
		ButtonType setupButtonType = new ButtonType("설정", ButtonBar.ButtonData.OK_DONE);
		dialog.getDialogPane().getButtonTypes().addAll(setupButtonType, ButtonType.CANCEL);
		
		GridPane contentsPane = new GridPane();
		contentsPane.setHgap(10d);
		contentsPane.setVgap(10d);
		contentsPane.setPadding(new Insets(10d));
		
		Item[] items = Item.values();
		TextField[] itemLabels = new TextField[items.length];
		TextField[] inputs = new TextField[items.length];
		for(int i=0; i<itemLabels.length; i++) {
			itemLabels[i] = new TextField();
			inputs[i] = new TextField();
			itemLabels[i].setEditable(false);
			itemLabels[i].setMaxWidth(100d);
			inputs[i].setMaxWidth(100d);
			itemLabels[i].setText(items[i].toString());
			inputs[i].setText(vendingMachine.getNumberOfItems(items[i])+"");
			contentsPane.add(itemLabels[i], 0, i);
			contentsPane.add(inputs[i], 1, i);
		}
		dialog.getDialogPane().setContent(contentsPane);
		dialog.setResultConverter(dialogButton -> {
		    if (dialogButton == setupButtonType) {
		    	vendingMachine.clearItems();
		        for(int i=0; i<items.length; i++) {
		        	int amount = Integer.valueOf(inputs[i].getText());
		        	if(amount>0)
		        		vendingMachine.setItems(items[i], amount);
		        }
		    }
		    return false;
		});
		dialog.showAndWait();
	}
	
	public static void showBalanceSetupDialog(CashRegister cashRegister, boolean flag) {
		Dialog<Boolean> dialog = new Dialog<>();
		dialog.setTitle(flag? "자판기 돈 설정": "돈 투입");
		String buttonText = flag? "설정": "투입";
		ButtonType setupButtonType = new ButtonType(buttonText, ButtonBar.ButtonData.OK_DONE);
		dialog.getDialogPane().getButtonTypes().addAll(setupButtonType, ButtonType.CANCEL);
		
		GridPane contentsPane = new GridPane();
		contentsPane.setHgap(10d);
		contentsPane.setVgap(10d);
		contentsPane.setPadding(new Insets(10d));
		
		Currency[] moneys = Currency.values();
		TextField[] itemLabels = new TextField[moneys.length];
		TextField[] inputs = new TextField[moneys.length];
		for(int i=0; i<itemLabels.length; i++) {
			itemLabels[i] = new TextField();
			inputs[i] = new TextField();
			itemLabels[i].setEditable(false);
			itemLabels[i].setMaxWidth(100d);
			inputs[i].setMaxWidth(100d);
			itemLabels[i].setText(String.format("%,d원", moneys[i].value));
			inputs[i].setText(cashRegister.getAmount(moneys[i])+"");
			contentsPane.add(itemLabels[i], 0, i);
			contentsPane.add(inputs[i], 1, i);
		}
		dialog.getDialogPane().setContent(contentsPane);
		dialog.setResultConverter(dialogButton -> {
		    if (dialogButton == setupButtonType) {
		        for(int i=0; i<moneys.length; i++) {
		        	cashRegister.set(moneys[i], Integer.valueOf(inputs[i].getText()));
		        }
		    }
		    return false;
		});
		dialog.showAndWait();
	}
	
	public static void showInfoDialog(String content){
		Alert alert = new Alert(AlertType.INFORMATION);
		alert.setTitle("Koreatech 자판기 App");
		alert.setHeaderText(null);
		alert.setContentText(content);
		ImageView icon = new ImageView(new Image("soda.png"));
		icon.setFitHeight(80);
		icon.setPreserveRatio(true);
		alert.setGraphic(icon);
		alert.showAndWait();
	}
}
