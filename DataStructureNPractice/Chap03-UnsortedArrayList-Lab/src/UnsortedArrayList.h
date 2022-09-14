/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file UnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하는 방법으로 pushFront, popFront, remove를 구현함
 */

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class UnsortedArrayList {
    template <typename U>
    class ListIterator: public std::iterator<std::input_iterator_tag,U>{
        U *p;
    public:
        explicit ListIterator(U *p): p{p} {}
        const ListIterator& operator++() noexcept {++p; return *this;}
        ListIterator operator++(int) noexcept {auto retval{*this}; ++p; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        U& operator*() const noexcept {return *p;}
    };
private:
    // 검사 목적으로 용량을 작게 설정
    const static inline size_t MAX{10};
    int items[MAX];
    size_t numItems{0};

    // index가 유효한 자리인지 검사
    bool isValidIndex(int index) const noexcept {
        return 0 <= index && index < numItems;
    }

    // 매개변수로 받은 시작 인덱스 ~ 끝 인덱스 까지의 요소를 왼쪽으로 한칸씩 밀음
    void shiftLeft(int startIdx) {
        for(int i = startIdx; i < numItems-1; i++) {
            items[i] = items[i+1];
        }
        numItems--;
    }

    // 매개변수로 받은 시작 인덱스 ~ 끝 인덱스 까지의 요소를 오른쪽으로 한칸씩 밀음
   void shiftRight(int startIdx) {
        for(int i = numItems-1; i >= startIdx; i--){
            items[i + 1] = items[i];
        }
        numItems++;
    }

    // 매개변수 요소를 검색해서 해당 index를 반환함, 찾지 못할 경우에는 MAX가 반환됨
    size_t search(int item) const noexcept {
        for(int i = 0; i <= numItems; i++){
            if(items[i] == item){
                return i;
            }
        }
        return MAX;
    }
public:
    explicit UnsortedArrayList() = default;
    explicit UnsortedArrayList(const std::initializer_list<int>& initList) {
        numItems = std::min(initList.size(), MAX);
        auto it{initList.begin()};
        for(int i = 0; i <numItems; i++){
            items[i] = *it;
            ++it;
        }
    }

    virtual ~UnsortedArrayList() = default;

    bool isEmpty() const noexcept {
        return numItems == 0;
    }

    bool isFull() const noexcept {
        return numItems >= MAX;
    }

    size_t size() const noexcept {
        return numItems;
    }

    void clear() noexcept{
        numItems = 0;
    }

    int operator[](int index) const {
        if(!isValidIndex(index)) throw std::out_of_range("Index ERROR: [] const");
        return items[index];
    }

    int& operator[](int index) {
        if(!isValidIndex(index)) throw std::out_of_range("Index ERROR: [] const");
        return items[index];
    }

    void pushBack(int item) {
        if(isFull()) throw std::runtime_error("pushBack: full state");
        items[numItems++] = item;
    }

    int popBack() {
        if(isEmpty()) throw std::runtime_error("popBack: full state");
        return items[--numItems];
    }

    void pushFront(int item) {
        if(isFull()) throw std::runtime_error("pushFront: full state");
        shiftRight(0);
        items[0] = item;
    }

    int popFront() {
        if(isEmpty()) throw std::runtime_error("pushFront: empty state");
        int value = items[0];
        shiftLeft(0);
        return value;
    }

    int peekFront() const {
        if(isEmpty()) throw std::runtime_error("pushFront: empty state");
        return items[0];
    }

    int peekBack() const {
        if(isEmpty()) throw std::runtime_error("pushFront: empty state");
        return items[numItems - 1];
    }

    bool find(int item) const noexcept {
        return search(item) != MAX;
    }

    void removeFirst(int item) noexcept {
        if(isEmpty()) return;
        for(int i = 0; i < numItems; i++){
            if(items[i] == item){
                shiftLeft(i);
                break;
            }
        }
    }

    void removeAll(int item) noexcept {
        if (isEmpty()) return;
        for (int i = 0; i < numItems; items[i] == item ? (shiftLeft(i), 0) : i++);
    }

    void insert(int index, int value) {
        if(isFull()) throw std::runtime_error("insert: full state");
        if(!isValidIndex(index) && index != numItems) throw std::out_of_range("Index ERROR");
        // index == numItems일 때는 요소를 맨 뒤에 추가함
        shiftRight(index);
        items[index] = value;
    }

    auto begin() {return ListIterator<int>(items);}
    auto end() {return ListIterator<int>(items+numItems);}
    auto cbegin() const {return ListIterator<const int>(items);}
    auto cend() const {return ListIterator<const int>(items+numItems);}
};

#endif /* UNSORTEDARRAYLIST_H_ */
