import java.util.Iterator;

/**
 * @author refracta
 * 11장 내부 클래스
 * 단일 연결구조
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 */
public class UnsortedSingleLinkedList implements Iterable<String> {
    private static class Node {
        private String item = null;
        private Node next = null;

        private Node(String item) {
            this(item, null);
        }

        private Node(String item, Node next) {
            this.item = item;
            this.next = next;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "item='" + item + '\'' +
                    ", next=" + (next != null ? ("[" + next.item + ", " + next.hashCode() + "]") : "null") +
                    ", hash=" + this.hashCode() + '}';
        }
    }

    private class LinkedListIterator implements Iterator<String> {
        private Node curr = head;

        @Override
        public boolean hasNext() {
            return curr != null;
        }

        @Override
        public String next() {
            String value = curr.item;
            curr = curr.next;
            return value;
        }
    }

    private Node head = null;
    private Node tail = null;
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

    public void clear() {
        head = tail = null;
        size = 0;
    }

    public void pushFront(String item) {
        Node newNode = new Node(item, head);
        head = newNode;
        if (isEmpty()) tail = newNode;
        ++size;
    }

    public String popFront() {
        if (isEmpty()) throw new IllegalStateException();
        Node target = head;
        head = head.next;
        size--;
        return target.item;
    }

    public void pushBack(String item) {
        if (isEmpty()) {
            head = tail = new Node(item, null);
        } else {
            tail.next = tail = new Node(item, null);
        }
        size++;
    }

    public String popBack() {
        if (isEmpty()) throw new IllegalStateException();
        Node popNode = tail;
        Node dummy = new Node("", head);
        Node prev = dummy;
        while (prev.next != tail) prev = prev.next;
        prev.next = null;
        head = dummy.next;
        dummy.next = null; // 꼭 필요한 요소는 아님
        tail = (head == null) ? null : prev;
        --size;
        return popNode.item;
    }

    public String peekFront() {
        if (isEmpty()) throw new IllegalStateException();
        return head.item;
    }

    public String peekBack() {
        if (isEmpty()) throw new IllegalStateException();
        return tail.item;
    }

    public boolean find(String item) {
        if (isEmpty()) return false;
        Node curr = head;
        while (curr != null) {
            if (curr.item.equals(item)) return true;
            curr = curr.next;
        }
        return false;
    }

    private void removeNode(Node prev, Node current) {
        prev.next = current.next;
        if (current == head) {
            head = current.next;
        } else if (current == tail) {
            tail = prev;
        }
        size--;
    }

    // head부터 검색하여 item을 유지하는 첫 번째 노드를 삭제함
    public void removeFirst(String item) {
        if (isEmpty()) return;
        for (Node prev = new Node("", head); prev.next != null; prev = prev.next) {
            Node current = prev.next;
            if (item.equals(current.item)) {
                removeNode(prev, current);
                break;
            }
        }
    }

    // 리스트에서 item을 유지하는 모든 노드를 삭제함
    public void removeAll(String item) {
        if (isEmpty()) return;

        for (Node prev = new Node("", head); prev.next != null; prev = prev.next) {
            Node current = prev.next;
            if (item.equals(current.item)) {
                removeNode(prev, current);
                prev = new Node("", current);
            }
        }
    }

    @Override
    public Iterator<String> iterator() {
        return new LinkedListIterator();
    }
}
