// csetest.java
public class CSE {
    private String title;

    public void setTitle(String _title) {
        title = _title;
    }

    public void getTitle() {
        return title;
    }
}

public class CSETest {
    public void main() {
        CSE cse = new CSE();
        System.out.println(cse.getTitle());
    }
}
