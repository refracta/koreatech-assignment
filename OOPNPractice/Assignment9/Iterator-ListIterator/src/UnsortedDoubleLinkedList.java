import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * @author 김상진, refracta
 * 이중 연결구조 기반 비정렬 범용 리스트
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class UnsortedDoubleLinkedList<T> implements Iterable<T> {
    private static class Node<T> {
        private T item = null;
        private Node<T> prev = null;
        private Node<T> next = null;

        public Node(T item) {
            this.item = item;
        }
    }

    private class LinkedListIterator implements ListIterator<T> {
        @SuppressWarnings("unused")
        /**
         * 현재 요소
         */
        private Node<T> current = head;
        /**
         * 마지막 반환 요소
         */
        private Node<T> last = null;
        /**
         * 현재 요소 위치
         */
        private int currentIndex = 0;
        /**
         * 마지막 반환 요소 위치
         */
        private int lastIndex = -1;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                // 다음 요소가 없는 경우 예외 던지기
                throw new NoSuchElementException();
            }

            lastIndex = currentIndex++;
            // 마지막 반환 위치를 현재 요소 위치로 설정, 현재 요소 위치를 증가
            current = (last = current).next;
            // 마지막 반환 요소를 현재 요소로 설정, 현재 요소를 현재 요소의 다음 요소로 설정
            return last.item;
        }

        @Override
        public boolean hasPrevious() {
            return current != head;
        }

        @Override
        public T previous() {
            if (!hasPrevious()) {
                // 이전 요소가 없는 경우 예외 던지기
                throw new NoSuchElementException();
            }

            lastIndex = --currentIndex;
            // 현재 요소 위치를 이전 요소 위치로 설정, 마지막 반환 위치를 이전 요소 위치로 설정
            last = current = current.prev;
            // 마지막 반환 요소, 현재 요소를 이전 요소로 설정
            return current.item;
        }

        @Override
        public int nextIndex() {
            return currentIndex;
        }

        @Override
        public int previousIndex() {
            return currentIndex - 1;
        }

        @Override
        public void remove() {
            if (last == null) {
                // 마지막 반환 요소가 없는 경우 예외를 던지기
                throw new IllegalStateException();
            }

            current = last.next;
            // 현재 요소를 마지막 반환 요소의 다음 요소로 설정
            currentIndex = lastIndex;
            // 현재 요소 위치를 마지막 반환 요소 위치로 설정 (지웠으므로 현재 요소 위치는 lastIndex가 됨)
            if (last == head) {
                // 마지막 반환 요소(지울 대상)이 맨 앞 요소인 경우
                head = last.next;
                // 마지막 반환 요소의 다음 요소로 head를 설정
            }

            if (last.prev != null) {
                last.prev.next = current;
            }
            if (last.next != null) {
                last.next.prev = last.prev;
            }
            // 마지막 반환 요소를 지운 후, 연결 리스트 봉합

            last = null;
            lastIndex = -1;
            size--;
            // 변수 처리
        }

        @Override
        public void set(T e) {
            if (last == null) {
                // 마지막 반환 요소가 없는 경우 예외를 던지기
                throw new IllegalStateException();
            }
            last.item = e;
            // 마지막 반환 요소의 item 섲렁
        }

        @Override
        public void add(T e) {
            Node<T> newNode = new Node<T>(e);

            if (!hasNext()) {
                // 맨 마지막 에다가 요소를 추가하는 경우
                current = new Node<>(null);
                // current를 이용하여 일반화된 추가 구현을 위해, current를 Dummy로 설정
                tail.next = current;
                current.prev = tail;
                tail = current;
                // current를 tail로 설정
            }

            if (hasPrevious()) {
                current.prev.next = newNode;
                // 이전 요소를 가지는 경우, 새 노드를 현재 요소의 이전 요소가 가지는 다음 요소로 설정함
            }

            newNode.next = current;
            newNode.prev = current.prev;
            current.prev = newNode;
            // 새 요소 추가한 후, 연결 리스트 봉합

            if (tail == current) {
                newNode.next = current = null;
                // 맨 마지막 에다가 요소를 추가하는 경우에 대한 후처리
                // 임시로 끝 요소로 설정했던 dummy current를 삭제
            }

            last = null;
            lastIndex = -1;
            currentIndex++;
            size++;
            // 변수 처리
        }
    }

    private Node<T> head = null;
    private Node<T> tail = null;
    private int size = 0;

    public boolean isFull() {
        return false;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    public T get(int index) {
        if (index < 0 || index >= size) throw new IndexOutOfBoundsException();
        Node<T> curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }
        return curr.item;
    }

    public void pushFront(T item) {
        Node<T> newNode = new Node<>(item);
        newNode.next = head;
        if (head != null) head.prev = newNode;
        else tail = newNode;
        head = newNode;
        ++size;
    }

    public T popFront() {
        if (isEmpty()) throw new IllegalStateException();
        Node<T> popNode = head;
        head = head.next;
        if (head != null) head.prev = null;
        else tail = null;
        --size;
        return popNode.item;
    }

    public T peekFront() {
        if (isEmpty()) throw new IllegalStateException();
        return head.item;
    }

    public void pushBack(T item) {
        Node<T> newNode = new Node<>(item);
        if (tail == null) head = tail = newNode;
        else {
            tail.next = newNode;
            newNode.prev = tail;
            tail = newNode;
        }
        ++size;
    }

    public T popBack() {
        if (isEmpty()) throw new IllegalStateException();
        Node<T> popNode = tail;
        tail = tail.prev;
        if (tail != null) tail.next = null;
        else head = null;
        --size;
        return popNode.item;
    }

    public T peekBack() {
        if (isEmpty()) throw new IllegalStateException();
        return tail.item;
    }

    @SuppressWarnings("unchecked")
    public void pushBackAll(T... items) {
        for (var item : items) pushBack(item);
    }

    public boolean find(T item) {
        if (isEmpty()) return false;
        Node<T> curr = head;
        while (curr != null) {
            if (curr.item.equals(item)) return true;
            curr = curr.next;
        }
        return false;
    }

    public void removeFirst(T item) {
        if (isEmpty()) return;
        Node<T> dummy = new Node<>(null);
        dummy.next = head;
        head.prev = dummy;
        Node<T> curr = head;
        while (curr != null) {
            if (curr.item.equals(item)) {
                curr.prev.next = curr.next;
                if (curr.next != null) curr.next.prev = curr.prev;
                if (curr == tail) tail = tail.prev;
                --size;
                break;
            } else curr = curr.next;
        }
        head = dummy.next;
        if (head == null) tail = null;
        else head.prev = null;
    }

    @Override
    public Iterator<T> iterator() {
        return new LinkedListIterator();
    }

    public ListIterator<T> listIterator() {
        return new LinkedListIterator();
    }
}
