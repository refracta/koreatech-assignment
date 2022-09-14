/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author: refracta
 * HashTable.h
 * 용량 고정 단일 버켓, key = 문자열
 * Linear Probing(+1), 해댕 위치 없을 때 delete flag 사용하지 않고 전체 탐색
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <string>

enum class BucketState {EMPTY, DELETED, OCCUPIED};

class HashTable {
	struct Bucket{
		std::string key;
//		bool empty{true};
        BucketState state{BucketState::EMPTY};
	};
	template <typename BucketType, typename ElementType>
	class TableIterator: public std::iterator<std::input_iterator_tag,ElementType>{
		BucketType *p;
		BucketType *end;
    public:
        explicit TableIterator(BucketType *p) : p{p}, end{p+MAX} {}
        const TableIterator& operator++() noexcept {
        	++p;
        	while(p->state!=BucketState::OCCUPIED&&p!=end) ++p;
        	return *this;
        }
        TableIterator operator++(int) noexcept {
        	TableIterator retval(*this);
        	while(p->state!=BucketState::OCCUPIED&&p!=end) ++p;
        	return retval;
        }
        bool operator==(const TableIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const TableIterator& other) const noexcept {return !(p == other.p);}
        ElementType& operator*() noexcept {
        	return p->key;
        }
    };
private:
	const static size_t MAX{7};
	Bucket table[MAX];
	size_t numItems{0};
public:
	HashTable() = default;
	virtual ~HashTable() = default;
	bool isEmpty() const noexcept{
		return numItems==0;
	}
	bool isFull() const noexcept{
		return numItems==MAX;
	}
	size_t size() const noexcept{
		return numItems;
	}
	void add(const std::string& key){
		if(isFull()) throw std::runtime_error("");
		if(contains(key)) return;
		size_t index{hashString(key)};
		for(size_t i=0; i<MAX; ++i){
			if(table[index].state==BucketState::EMPTY){
				table[index].key = key;
				table[index].state = BucketState::OCCUPIED;
				++numItems;
				break;
			}
			index = (index+1) % MAX;
		}
	}
	bool contains(const std::string& key) const noexcept{
		if(isEmpty()) return false;
		size_t index{hashString(key)};
		for(size_t i=0; i<MAX; ++i){
			if(table[index].state==BucketState::OCCUPIED && table[index].key==key)
				return true;
            else if(table[index].state==BucketState::EMPTY) return false;
			index = (index+1) % MAX;
		}
		return false;
	}
	void remove(const std::string& key) noexcept{
		if(isEmpty()) return;
		size_t index{hashString(key)};
		for(size_t i=0; i<MAX; ++i){
            if(table[index].state==BucketState::OCCUPIED && table[index].key==key) {
				table[index].state = BucketState::DELETED;
				--numItems;
				break;
			} else if(table[index].state==BucketState::EMPTY) return;
			index = (index+1) % MAX;
		}
	}
	void debugPrint(){
		for(size_t i=0; i<MAX; ++i){
			std::cout << i << ": ";
			if(table[i].state!=BucketState::OCCUPIED)
				std::cout << (table[i].state==BucketState::EMPTY) ? "empty\n" : "deleted\n";
			else
				std::cout << table[i].key << " > "<< hashString(table[i].key) <<'\n';
		}
	}
	auto begin() {return TableIterator<Bucket,std::string>(table);}
	auto end() {return TableIterator<Bucket,std::string>(table+MAX);}
	auto cbegin() const {return TableIterator<const Bucket,const std::string>(table);}
	auto cend() const {return TableIterator<const Bucket,const std::string>(table+MAX);}
private:
	size_t hashString(const std::string& key) const noexcept{
		constexpr static size_t P{13875551L};
		constexpr size_t x{62057};
		size_t value{0};
		for(auto c: key)
			value = (value*x+c)%P;
		return hashInteger(value);
	}
	size_t hashInteger(size_t x) const noexcept{
		constexpr static size_t P{4210098769L};
		constexpr size_t a{42283};
		constexpr size_t b{44267};
		size_t value = (a*x + b) % P;
		return value % MAX;
	}
};

#endif /* HASHTABLE_H_ */
