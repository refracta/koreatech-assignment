/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author: refracta
 * TreeMap.h
 */

#ifndef TREEMAP_H_
#define TREEMAP_H_
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <utility>
#include <set>
#include "AVL.h"

template <typename K, typename V>
class TreeMap {
private:
	using Pair = std::pair<K,V>;
	AVL<K,V> tree{};
public:
	TreeMap() = default;
	virtual ~TreeMap() = default;

	TreeMap(TreeMap<K,V>&& tmp) = default;
	TreeMap<K,V>& operator=(TreeMap<K,V>&& tmp) = default;

	bool isEmpty() const noexcept{
		return tree.isEmpty();
	}
	bool isFull() const noexcept{
		return false;
	}
	size_t size() const noexcept{
		return tree.size();
	}

	void put(const K& key, const V& value){
		// 완성
        tree.put(key, value);
	}

	bool containsKey(const K& key) const noexcept{
		// 완성
        return tree.find(key);
	}
	const V& get(const K& key) const{
		if(isEmpty()) throw std::runtime_error("HashMap: get, empty");
		return tree.get(key);
	}
	void remove(const K& key) noexcept{
		// 완성
        tree.remove(key);
	}
	std::set<K> getKeySet() const noexcept{
		std::set<K> set;
		for(auto& entry: tree){
			set.insert(entry.first);
		}
		return set;
	}
	std::set<V> getValueSet() const noexcept{
		std::set<V> set;
		for(auto& entry: tree){
			set.insert(entry.second);
		}
		return set;
	}

	auto begin() const {return tree.begin();}
	auto end() const {return tree.end();}
};

#endif /* TREEMAP_H_ */
