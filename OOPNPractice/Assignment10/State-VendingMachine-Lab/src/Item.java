import javafx.scene.image.Image;

/**
 * @author 김상진
 * 상태 패턴
 * 자동판매기 판매 제품: 판매하고 있는 상품의 종류를 나타내는 열거형
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public enum Item {
    Cider(800), Cola(800), Pepsi(800),
    Pocari(1000), Top(1200), Max(800);
    private static String[] itemNames = {
            "사이다", "콜라", "펩시", "포카리", "티오피", "맥스"
    };

    private static class ItemImage {
        static String[] names = new String[]{"cider.jpg", "cola.jpeg", "pepsi.jpg", "pocari.jpg", "top.jpg", "max.jpg"};
    }

    public final int price;
    public final Image image;

    private Item(int price) {
        this.price = price;
        this.image = VendingMachineTest.isJUnitTest ? null : new Image(ItemImage.names[this.ordinal()]);
    }

    @Override
    public String toString() {
        return itemNames[this.ordinal()];
    }
}
