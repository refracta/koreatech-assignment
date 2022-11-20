import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.ListIterator;
import java.util.NoSuchElementException;

import org.junit.jupiter.api.Test;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진 
 * 배열 기반 비정렬 범용 리스트 테스트 프로그램
 */
class UnsortedArrayListTest {
	@Test
	void addTest() {
		UnsortedArrayList<Integer> list1 = new UnsortedArrayList<>();
		list1.pushBackAll(10,5,3,7,9,11);
		ArrayList<Integer> list2 = new ArrayList<>();
		list2.addAll(Arrays.asList(10,5,3,7,9,11)); 
		for(int i=0; i<list1.size(); i++) {
			assertEquals(list1.get(i), list2.get(i));
		}
		ListIterator<Integer> iterator1 = list1.listIterator();
		ListIterator<Integer> iterator2 = list2.listIterator();
		assertEquals(iterator1.next(), iterator2.next());
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		iterator1.add(4);
		iterator2.add(4);
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		for(int i=0; i<list1.size(); i++) {
			assertEquals(list1.get(i), list2.get(i));
		}
		assertEquals(iterator1.previous(), 4);
		assertEquals(iterator2.previous(), 4);
		assertEquals(iterator1.next(), iterator2.next());
		assertEquals(iterator1.previous(), 4);
		assertEquals(iterator2.previous(), 4);
		iterator1.add(6);
		iterator2.add(6);
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		assertEquals(iterator1.previous(), 6);
		assertEquals(iterator2.previous(), 6);
		while(iterator1.hasNext()) {
			iterator1.next();
			iterator2.next();
		}
		iterator1.add(20);
		iterator2.add(20);
		assertThrows(NoSuchElementException.class, ()->iterator1.next());
		assertThrows(NoSuchElementException.class, ()->iterator2.next());
	}
	@Test
	void removeTest() {
		UnsortedArrayList<Integer> list1 = new UnsortedArrayList<>();
		list1.pushBackAll(10,5,3,7,9,11);
		ArrayList<Integer> list2 = new ArrayList<>();
		list2.addAll(Arrays.asList(10,5,3,7,9,11)); 
		ListIterator<Integer> iterator1 = list1.listIterator();
		ListIterator<Integer> iterator2 = list2.listIterator();
		iterator1.next();
		iterator2.next();
		iterator1.remove();
		iterator2.remove();
		assertThrows(IllegalStateException.class, ()->iterator1.remove());
		assertThrows(IllegalStateException.class, ()->iterator2.remove());
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		for(int i=0; i<list1.size(); i++) {
			assertEquals(list1.get(i), list2.get(i));
		}
		assertEquals(iterator1.next(), 5);
		assertEquals(iterator2.next(), 5);
		assertEquals(iterator1.next(), 3);
		assertEquals(iterator2.next(), 3);
		assertEquals(iterator1.previous(), 3);
		assertEquals(iterator2.previous(), 3);
		iterator1.remove();
		iterator2.remove();
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		assertEquals(iterator1.next(), 7);
		assertEquals(iterator2.next(), 7);
	}
	@Test
	void setTest() {
		UnsortedArrayList<Integer> list1 = new UnsortedArrayList<>();
		list1.pushBackAll(10,5,3,7,9,11);
		ArrayList<Integer> list2 = new ArrayList<>();
		list2.addAll(Arrays.asList(10,5,3,7,9,11)); 
		for(int i=0; i<list1.size(); i++) {
			assertEquals(list1.get(i), list2.get(i));
		}
		ListIterator<Integer> iterator1 = list1.listIterator();
		ListIterator<Integer> iterator2 = list2.listIterator();
		assertEquals(iterator1.next(), iterator2.next());
		iterator1.add(4);
		iterator2.add(4);
		assertEquals(iterator1.next(), iterator2.next());
		assertEquals(iterator1.next(), iterator2.next());
		iterator1.set(6);
		iterator2.set(6);
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());
		for(int i=0; i<list1.size(); i++) {
			System.out.println(list1.get(i)+", "+list2.get(i));
		}
		assertEquals(iterator1.previous(), iterator2.previous());
		assertEquals(iterator1.previous(), iterator2.previous());
		iterator1.set(8);
		iterator2.set(8);
		assertEquals(iterator1.previousIndex(), iterator2.previousIndex());
		assertEquals(iterator1.nextIndex(), iterator2.nextIndex());		
	}
}
