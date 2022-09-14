/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author: refracta
 * HashTable.h
 * chaining 기법, key = 문자열
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <functional>
#include "HashTableIterator.h"

template <typename T>
class HashTable {
private:
	size_t tableSize;
	std::vector<std::list<T>> table;
	size_t numItems{0};
	std::function<size_t(T)> hash;
public:
	HashTable(size_t tableSize, const std::function<size_t(T)>& hash):
		tableSize{tableSize}, table(tableSize), hash{hash}{}
	virtual ~HashTable() = default;

	HashTable(HashTable<T>&& tmp) = default;
	HashTable<T>& operator=(HashTable<T>&& tmp) = default;

	bool isEmpty() const noexcept{
		return numItems==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	size_t size() const noexcept{
		return numItems;
	}
	size_t capacity() const noexcept{
		return tableSize;
	}
	const std::function<size_t(T)>& hash_function() const noexcept{
		return hash;
	}

	void add(const T& key){
		if(needCapacityExpansion()) increaseCapacity();
		if(contains(key)) return;
		size_t index{getIndex(key)};
		table[index].push_front(key);
		++numItems;
		if(table[index].size()>=3) increaseCapacity();
	}
	bool contains(const T& key) const noexcept{
		if(isEmpty()) return false;
		size_t index{getIndex(key)};
		auto it{std::find(table[index].begin(), table[index].end(), key)};
		return it!=table[index].end();
	}
	void remove(const T& key) noexcept{
		if(isEmpty()) return;
		size_t index{getIndex(key)};
		auto it{std::find(table[index].begin(), table[index].end(), key)};
		if(it!=table[index].end()){
			table[index].erase(it);
			--numItems;
		}
	}
	void debugPrint(){
		for(size_t i=0; i<tableSize; ++i){
			std::cout << i << ": ";
			if(table[i].empty()) std::cout << "empty\n";
			else{
				for(auto& key: table[i])
					std::cout << key << ", ";
				std::cout << '\n';
			}
		}
	}

	auto begin() {return TableIterator<T>(table.begin(), table.end());}
	auto end() {return TableIterator<T>(table.end(), table.end());}
	auto begin() const {return TableConstIterator<T>(table.cbegin(), table.cend());}
	auto end() const {return TableConstIterator<T>(table.cend(), table.cend());}
private:
	bool needCapacityExpansion() const noexcept{
		return static_cast<double>(numItems)/tableSize>0.7;
	}

	std::vector<T> getKeyList(){
		std::vector<T> keyList;
		keyList.reserve(numItems);
		for(auto list: table){
			if(!list.empty())
				for(auto key: list) keyList.push_back(key);
		}
		return keyList;
	}

	void increaseCapacity(){
		std::vector<T> keyList{getKeyList()};
		tableSize = tableSize*2+1;
		numItems = 0;
		for(auto& list: table) list.clear();
		table.clear();
		table.resize(tableSize);
		for(auto key: keyList) add(key);
	}
	size_t getIndex(const T& key) const noexcept{
		return hashInteger(hash(key));
	}
	size_t hashInteger(size_t x) const noexcept{
		constexpr static size_t P{4210098769L};
		constexpr size_t a{42283};
		constexpr size_t b{44267};
		size_t value = (a*x + b) % P;
		return value % tableSize;
	}
};

#endif /* HASHTABLE_H_ */
