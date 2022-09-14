/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * 집합: HashTable을 이용한 구현
 */

#ifndef SET_H_
#define SET_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <list>
#include <iterator>
#include <string>
#include <functional>
#include "HashTable.h"

template <typename T>
class Set;

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B);

template <typename T>
class Set {
private:
	HashTable<T> hTable;
public:
	Set(size_t tableSize, const std::function<size_t(T)>& hash):
		hTable{tableSize, hash}{}
	virtual ~Set() = default;
	Set(Set<T>&& tmp) = default;
	Set<T>& operator=(Set<T>&& tmp) = default;

	bool isEmpty() const noexcept{
		return hTable.isEmpty();
	}
	bool isFull() const noexcept{
		return hTable.isFull();
	}
	size_t size() const noexcept{
		return hTable.size();
	}
	size_t capacity() const noexcept{
		return hTable.capacity();
	}
	const std::function<size_t(T)>& hash_function() const noexcept{
		return hTable.hash_function();
	}

	void add(const T& key){
		hTable.add(key);
	}
	bool contains(const T& key) const{
		return hTable.contains(key);
	}
	void remove(const T& key){
		hTable.remove(key);
	}

	void debugPrint(){
		hTable.debugPrint();
	}

	auto begin() { return hTable.begin(); }
	auto end() { return hTable.end(); }
	auto begin() const { return hTable.begin(); }
	auto end() const { return hTable.end(); }

	friend Set<T> operator+<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> operator-<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> intersection<>(const Set<T>& A, const Set<T>& B);
};

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B){
	Set<T> set{A.capacity()+B.capacity(), A.hash_function()};
	for(auto s: A) set.add(s);
	for(auto s: B) set.add(s);
	return set;
}

template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B){
	Set<T> set(A.capacity(), A.hash_function());
	for(auto s: A){
		if(!B.contains(s)) set.add(s);
	}
	return set;
}

template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B){
	Set<T> set(A.capacity(), A.hash_function());
	for(auto s: A){
		if(B.contains(s)) set.add(s);
	}
	return set;
}


#endif /* SET_H_ */
