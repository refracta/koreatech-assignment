/*
 * HashTableIterator.h
 *
 *  Created on: 2021. 11. 3.
 *      Author: sangjin
 */

#ifndef HASHTABLEITERATOR_H_
#define HASHTABLEITERATOR_H_

#include <iterator>
#include <list>
#include <vector>

template <typename E>
class TableIterator: public std::iterator<std::input_iterator_tag,E>{
	using TableIterType = typename std::vector<std::list<E>>::iterator;
	using BucketIterType = typename std::list<E>::iterator;
	TableIterType table_iter;
	TableIterType table_end;
	BucketIterType list_iter;
	static inline typename std::list<E> emptyList{};
public:
	explicit TableIterator(TableIterType begin_it, TableIterType end_it):
	table_iter{begin_it}, table_end{end_it}{
		while(table_iter!=table_end && table_iter->empty()){
			++table_iter;
		}
		list_iter = table_iter!=table_end ? table_iter->begin(): emptyList.end();
	}
	void moveToNextItem(){
		++list_iter;
		if(list_iter==table_iter->end()){
			do{
				++table_iter;
			} while(table_iter!=table_end && table_iter->empty());
			list_iter = table_iter!=table_end ? table_iter->begin(): emptyList.end();
		}
	}
	const TableIterator& operator++() noexcept {
		moveToNextItem();
		return *this;
	}
	TableIterator operator++(int) noexcept {
		TableIterator retval(*this);
		moveToNextItem();
		return retval;
	}
	bool operator==(const TableIterator& other) const noexcept {
		return table_iter == other.table_iter && list_iter==other.list_iter; }
	bool operator!=(const TableIterator& other) const noexcept {return !operator==(other);}
	E& operator*() noexcept { return *list_iter; }
};

template <typename E>
class TableConstIterator: public std::iterator<std::input_iterator_tag,E>{
	using TableIterType = typename std::vector<std::list<E>>::const_iterator;
	using BucketIterType = typename std::list<E>::const_iterator;
	TableIterType table_iter;
	TableIterType table_end;
	BucketIterType list_iter;
	static inline typename std::list<E> emptyList{};
public:
	explicit TableConstIterator(TableIterType begin_it, TableIterType end_it):
	table_iter{begin_it}, table_end{end_it}{
		while(table_iter!=table_end && table_iter->empty()){
			++table_iter;
		}
		list_iter = table_iter!=table_end ? table_iter->cbegin(): emptyList.cend();
	}
	void moveToNextItem(){
		++list_iter;
		if(list_iter==table_iter->cend()){
			do{
				++table_iter;
			} while(table_iter!=table_end && table_iter->empty());
			list_iter = table_iter!=table_end ? table_iter->cbegin(): emptyList.cend();
		}
	}
	const TableConstIterator& operator++() noexcept {
		moveToNextItem();
		return *this;
	}
	TableConstIterator operator++(int) noexcept {
		TableConstIterator retval(*this);
		moveToNextItem();
		return retval;
	}
	bool operator==(const TableConstIterator& other) const noexcept {
		return table_iter == other.table_iter && list_iter==other.list_iter; }
	bool operator!=(const TableConstIterator& other) const noexcept {return !operator==(other);}
	const E& operator*() noexcept { return *list_iter; }
};


#endif /* HASHTABLEITERATOR_H_ */
