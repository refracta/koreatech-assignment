/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file SortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 정렬 정수 리스트
 * 코드 중복 제거
 */

#ifndef SORTEDARRAYLIST_H_
#define SORTEDARRAYLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SortedArrayList {
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
	// 동적 확장을 위해 capacity 멤버 변수 선언
	size_t capacity;
	int* items;
	size_t numItems{0};

	void shiftLeft(size_t startIdx){
		for(size_t i{startIdx}; i<numItems-1; ++i)
			items[i] = items[i+1];
		--numItems;
	}
	// 이진 탐색
	// @return 있으면 해당 요소가 있는 색인, 없으면 해당 요소를 삽입할 위치
	size_t search(int item) const noexcept{
		size_t lo{0};
		size_t hi{numItems-1};
		while(lo<=hi){
			size_t mid{lo+(hi-lo)/2};
			if(items[mid]==item) return mid;
			else if(items[mid]>item){
				if(mid==0) return lo;
				hi = mid-1;
			}
			else lo = mid+1;
		}
		return lo;
	}

	bool isNeedExpand(){
        return numItems==capacity;
	}

	// 동적 할당과 복사를 이용한 capacity 확장 구현
    void increaseCapacity(){
        capacity *= 2;
        int* tmp{new int[capacity]};
        std::copy(items, items+numItems, tmp);
        if(items) delete [] items;
        items = tmp;
    }
public:
    // 생성자로 capacity를 받아 빈 리스트를 생성할 수 있도록 생성자 추가
    explicit SortedArrayList(size_t capacity = 5):
    capacity{capacity}, items{new int[capacity]}{}

    // 배열을 받아 두배의 capacity로 리스트 초기화
    explicit SortedArrayList(const std::initializer_list<int>& initList):
            SortedArrayList(initList.size() * 2){
        auto it{initList.begin()};
        for(size_t i{0}; i<initList.size(); ++i){
            add(*it);
            ++it;
        }
    }
    // ↓ 소멸자와 Big5 처리 ↓
    virtual ~SortedArrayList(){
        if(items) delete [] items;
    }

    SortedArrayList(const SortedArrayList& other):
            SortedArrayList(other.capacity){
        numItems = other.numItems;
        std::copy(other.items, other.items+numItems, items);
    }

    SortedArrayList(SortedArrayList&& tmp):
    capacity{tmp.capacity}, numItems{tmp.numItems}{
        items = tmp.items;
        tmp.items = nullptr;
    }

    const SortedArrayList& operator=(const SortedArrayList& other){
        capacity = other.capacity;
        numItems = other.numItems;
        if(items) delete [] items;
        items = new int[capacity];
        std::copy(other.items, other.items+numItems, items);
        return *this;
    }

    const SortedArrayList& operator=(SortedArrayList&& tmp){
        capacity = tmp.capacity;
        numItems = tmp.numItems;
        if(items) delete [] items;
        items = tmp.items;
        tmp.items = nullptr;
        return *this;
    }

	bool isEmpty() const noexcept {
		return numItems==0;
	}

	bool isFull() const noexcept {
		return false;
	}

	size_t size() const noexcept{
		return numItems;
	}

	// 현재 capacity를 반환하는 함수
    int currentCapacity(){
        return capacity;
    }

	void clear() noexcept{
		numItems = 0;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems) return items[index];
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		--numItems;
		return items[numItems];
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{items[0]};
		shiftLeft(0);
		return ret;
	}

	void add(int item){
        if(isNeedExpand()) increaseCapacity();
        // 확장이 필요한 경우 확장 시도
		if(isEmpty()||items[numItems-1]<=item)
			items[numItems] = item;
		else{
			size_t insertLoc{search(item)};
			for(size_t i{numItems}; i>insertLoc; --i)
				items[i] = items[i-1];
			items[insertLoc] = item;
		}
		++numItems;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return items[0];
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: empty state");
		return items[numItems-1];
	}

	bool find(int item) const noexcept{
		if(isEmpty()) return false;
		return items[search(item)]==item;
	}

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(items[itemLoc]==item) shiftLeft(itemLoc);
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(items[itemLoc]==item){
			size_t lo{itemLoc};
			while(lo-1>=0 && items[lo-1]==item){
				--lo;
				if(lo==0) break;
			}
			size_t hi{itemLoc};
			while(hi+1<=numItems-1 && items[hi+1]==item) ++hi;
			for(size_t i{hi+1}, j{lo}; i<numItems; ++i, ++j)
				items[j] = items[i];
			numItems -= (hi-lo+1);
		}
	}

    void removeRange(int first, int last) {
        if (!((0 <= first && first < numItems) && (0 <= last - 1) && (last - 1 < numItems)) || first > last)
            throw std::out_of_range("Index ERROR: out of range");

        for (int i = first; i < last; i++)
            shiftLeft(first);
    }

	auto begin() {return ListIterator<int>(items);}
	auto end() {return ListIterator<int>(items+numItems);}
	auto cbegin() const {return ListIterator<const int>(items);}
	auto cend() const {return ListIterator<const int>(items+numItems);}
};

#endif /* SORTEDARRAYLIST_H_ */
