import java.util.Arrays;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * @author 김상진, refracta
 * 배열 기반 비정렬 범용 리스트
 * @version 2022년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 */
public class UnsortedArrayList<T> implements Iterable<T> {
    private int capacity = 5;
    @SuppressWarnings("unchecked")
    private T[] items = (T[]) (new Object[capacity]);
    private int size = 0;

    private class ArrayListIterator implements ListIterator<T> {
        /**
         * 다음 요소를 가리키는 커서
         */
        private int cursor = 0;
        /**
         * 마지막 반환 요소를 가리키는 커서
         */
        private int lastCursor = -1;

        @Override
        public boolean hasNext() {
            return cursor < size;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                // 다음 요소가 없는 경우 예외 던지기
                throw new NoSuchElementException();
            }
            lastCursor = cursor;
            // 마지막 반환 커서를 현재 요소 색인으로 설정
            return items[cursor++];
            // 다음 요소 커서 위치를 하나 올리고 현재 요소 반환
        }

        @Override
        public boolean hasPrevious() {
            return cursor > 0;
        }

        @Override
        public T previous() {
            if (!hasPrevious()) {
                // 이전 요소가 없는 경우 예외 던지기
                throw new NoSuchElementException();
            }
            return items[lastCursor = --cursor];
            // 마지막 반환 커서를 반환할 이전 요소의 위치(다음 요소 - 1)로 설정하고, 이전 요소를 반환
        }

        @Override
        public int nextIndex() {
            return cursor;
        }

        @Override
        public int previousIndex() {
            return cursor - 1;
        }

        @Override
        public void remove() {
            if (lastCursor < 0) {
                // 마지막 반환 위치가 없는 경우 예외를 던지기
                throw new IllegalStateException();
            }

            size--;

            for (int i = lastCursor; i < size; i++)
                items[i] = items[i + 1];
            // 왼쪽으로 한칸 시프팅

            cursor = lastCursor;
            // 다음 위치를 삭제한 요소의 다음 위치로 설정
            lastCursor = -1;
        }

        @Override
        public void set(T e) {
            if (lastCursor < 0) {
                // 마지막 반환 위치가 없는 경우 예외를 던지기
                throw new IllegalStateException();
            }

            items[lastCursor] = e;
            // 마지막 반환 위치에 요소를 설정
        }

        @Override
        public void add(T e) {
            if (size == capacity) {
                // 용적까지 사이즈가 다다른 경우, 확장
                increaseCapacity();
            }

            for (int i = size; i > cursor; i--) {
                items[i] = items[i - 1];
            }
            // 오른쪽으로 한칸 시프팅
            items[cursor] = e;
            // 원래의 다음 요소 색인에 요소 설정

            size++;
            cursor++;
            lastCursor = -1;
            // 변수 처리
        }
    }

    public boolean isFull() {
        return false;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    public T peekBack() {
        if (isEmpty()) throw new IllegalStateException();
        return items[size - 1];
    }

    private void increaseCapacity() {
        capacity *= 2;
        items = Arrays.copyOf(items, capacity);
    }

    public void pushBack(T item) {
        if (size == capacity) increaseCapacity();
        items[size++] = item;
    }

    public T popBack() {
        if (isEmpty()) throw new IllegalStateException();
        return items[--size];
    }

    public T get(int index) {
        if (index < 0 || index >= size) throw new IndexOutOfBoundsException("유효하지 않은 색인 사용");
        return items[index];
    }

    public void remove(T item) {
        for (int i = 0; i < size; i++)
            if (items[i].equals(item)) {
                for (int j = i + 1; j < size; j++)
                    items[j - 1] = items[j];
                --size;
                break;
            }
    }

    @SuppressWarnings("unchecked")
    public void pushBackAll(T... items) {
        for (var item : items) pushBack(item);
    }

    @Override
    public Iterator<T> iterator() {
        return new ArrayListIterator();
    }

    public ListIterator<T> listIterator() {
        return new ArrayListIterator();
    }
}
