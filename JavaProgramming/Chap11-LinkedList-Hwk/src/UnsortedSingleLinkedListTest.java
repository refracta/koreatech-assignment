import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2021년도 2학기
 * @author refracta
 * 단일 연결구조 기반 비정렬 문자열 리스트 테스트 프로그램
 */
class UnsortedSingleLinkedListTest {
	@Test
	void pushFront_popFrontTest() {
		UnsortedSingleLinkedList list = new UnsortedSingleLinkedList();
		list.pushFront("grape");
		list.pushFront("banana");
		list.pushFront("apple");
		assertEquals(list.peekFront(), "apple");
		String output = "";
		while(!list.isEmpty()) {
			output += list.popFront()+",";
		}
		assertEquals(output,"apple,banana,grape,");
	}
	@Test
	void pushBack_popBackTest() {
		UnsortedSingleLinkedList list = new UnsortedSingleLinkedList();
		list.pushBack("grape");
		list.pushBack("banana");
		list.pushBack("apple");
		assertEquals(list.peekFront(), "grape");
		assertEquals(list.peekBack(), "apple");
		String output = "";
		while(!list.isEmpty()) {
			output += list.popBack()+",";
		}
		assertEquals(output,"apple,banana,grape,");
	}
	@Test
	void removeFirstTest() {
		UnsortedSingleLinkedList list = new UnsortedSingleLinkedList();
		list.pushBack("apple");
		list.pushBack("banana");
		list.pushBack("grape");
		list.removeFirst("banana");
		assertEquals("apple",list.peekFront());
		assertEquals("grape",list.peekBack());
		list.pushBack("melon");
		list.removeFirst("apple");
		assertEquals("grape",list.peekFront());
		assertEquals("melon",list.peekBack());
		assertEquals(2,list.size());
		list.removeFirst("grape");
		assertEquals(list.peekFront(),list.peekBack());
	}
	@Test
	void removeAllTest() {
		UnsortedSingleLinkedList list = new UnsortedSingleLinkedList();
		list.pushBack("grape");
		list.pushBack("banana");
		list.pushBack("grape");
		list.pushBack("grape");
		list.pushBack("banana");
		list.pushBack("apple");
		list.pushBack("grape");
		list.removeAll("grape");
		assertEquals(3,list.size());
		assertEquals("banana",list.peekFront());
		assertEquals("apple",list.peekBack());
		list.removeAll("apple");
		list.removeAll("banana");
		assertTrue(list.isEmpty());
	}
	@Test
	void iteratorTest() {
		UnsortedSingleLinkedList list = new UnsortedSingleLinkedList();
		list.pushFront("kiwi");
		list.pushFront("mango");
		list.pushFront("melon");
		String output = "";
		for(var n: list)
			output += n+",";
		assertEquals(3,list.size());
		assertEquals(output,"melon,mango,kiwi,");
	}

}
