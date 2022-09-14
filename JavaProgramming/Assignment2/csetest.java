package com;

/**
 * Name: CSETest.java
 * Author: refracta
 * Version: 2020년도 2학기 과제2
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Description: CSETest 클래스
 */

// CSETest.java
// 통상적으로 사용하는 Java naming convention에 따르면 클래스 파일명의 이름은 PascalCase가 되어야 한다.
// CSE = Computer Science & Engineering이므로 CSETest.java가 파일명으로 권장되는 이름이다.
class CSE {
    // 파일 하나에서는 한개의 public class만을 사용할 수 있다.
// csetest.java
public class CSE {
    private String title;

    public void setTitle(String title) {
        this.title = title;
        // this 키워드를 사용하여 현재 함수 스코프에서 매개변수로 인해 은닉된 클래스 멤버 변수에 접근할 수 있다.
    public void setTitle(String _title) {
        title = _title;
    }

    public String getTitle() {
        // String title의 getter에는 void가 아닌 반환형 String을 명시해야 한다.
    public void getTitle() {
        return title;
    }
}

public class CSETest {
    public static void main(String[] args) {
        // Entry point로 main 함수가 사용되기 위해서는 기존 선언 대비 static 키워드와 String[] args 매개변수가 추가적으로 요구된다.
    public void main() {
        CSE cse = new CSE();
        cse.setTitle("Computer Science & Engineering");
        System.out.println(cse.getTitle());
    }
}