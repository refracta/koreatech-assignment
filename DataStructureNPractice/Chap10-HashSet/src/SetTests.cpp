/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2021년도 2학기
 * @author refracta
 * 집합: HashTable을 이용한 구현
 */

#include "Set.h"
#include "gtest/gtest.h"
#include <string>
#include <set>

size_t hashString(const std::string& key) noexcept{
	constexpr static size_t P{13875551L};
	constexpr size_t x{62057};
	size_t value{0};
	for(auto c: key)
		value = (value*x+c)%P;
	return value;
}

TEST(HashTable_LinearProbing, addTest)
{
	HashTable<std::string> hTable{7, hashString};
	hTable.add("peach"); 	//
	hTable.add("grape");	//
	hTable.add("orange");	//
	hTable.add("kiwi");		//
	hTable.add("mango");	//
	hTable.debugPrint();
	hTable.add("tomato");	//
	hTable.add("melon");	//
	hTable.add("cherry");	//
	hTable.add("lemon");	//
	hTable.add("plum");
	hTable.debugPrint();
}

void test(const HashTable<std::string>& hTable, const std::set<std::string>& fruits){
	for(auto fruit: hTable){
		std::cout << fruit << "\n";
		ASSERT_EQ(1, fruits.count(fruit));
	}
}

TEST(HashTable_LinearProbing, iteratorTest)
{
	HashTable<std::string> hTable{7, hashString};
	std::set<std::string> fruits;
	hTable.add("apple");
	fruits.insert("apple");
	hTable.add("peach");
	fruits.insert("peach");
	hTable.add("grape");
	fruits.insert("grape");
	hTable.add("orange");
	fruits.insert("orange");
	hTable.add("mango");
	fruits.insert("mango");
	hTable.add("lemon");
	fruits.insert("lemon");
	hTable.add("cherry");
	fruits.insert("cherry");
	hTable.remove("grape");
	fruits.erase("grape");

	hTable.debugPrint();
	test(hTable, fruits);
}


TEST(Set_HashTable_Chaining, addTest)
{
	Set<std::string> set{11, hashString};
	set.add("apple");
	set.add("peach");
	set.add("orange");
	set.add("mango");
	set.add("grape");
	set.add("strawberry");
	set.add("banana");
	set.add("melon");
	set.add("kiwi");
	set.add("tomato");
	set.add("blackberry");
	ASSERT_EQ(set.size(), 11);
	ASSERT_TRUE(set.contains("banana"));
	ASSERT_TRUE(set.contains("orange"));
	ASSERT_TRUE(set.contains("peach"));
	set.add("apple");
	ASSERT_EQ(set.size(), 11);
}

TEST(Set_HashTable_Chaining, removeTest)
{
	Set<std::string> set{11, hashString};
	set.add("apple");
	set.add("peach");
	set.add("orange");
	set.add("mango");
	set.add("grape");
	set.add("strawberry");
	set.add("banana");
	set.add("melon");
	set.add("kiwi");
	set.add("tomato");
	set.add("blackberry");
	ASSERT_EQ(set.size(), 11);
	set.remove("orange");
	set.remove("banana");
	set.remove("apple");
	ASSERT_FALSE(set.contains("banana"));
	ASSERT_FALSE(set.contains("orange"));
	ASSERT_FALSE(set.contains("apple"));
	ASSERT_TRUE(set.contains("mango"));
	set.add("peach");
	ASSERT_EQ(set.size(), 8);
}

TEST(Set_HashTable_Chaining, iteratorTest)
{
	Set<std::string> set{11, hashString};
	std::set<std::string> fruits;
	set.add("apple");
	fruits.insert("apple");
	set.add("peach");
	fruits.insert("peach");
	set.add("grape");
	fruits.insert("grape");
	set.add("orange");
	fruits.insert("orange");
	set.add("mango");
	fruits.insert("mango");
	set.add("coconut");
	fruits.insert("coconut");
	set.add("strawberry");
	fruits.insert("strawberry");

	set.remove("grape");
	fruits.erase("grape");

	for(auto& fruit: set){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}


TEST(Set_HashTable_Chaining, unionTest)
{
	Set<std::string> set1{11, hashString};
	Set<std::string> set2{11, hashString};
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	fruits.insert("peach");
	set1.add("grape");
	fruits.insert("grape");
	set2.add("orange");
	fruits.insert("orange");
	set2.add("mango");
	fruits.insert("mango");
	set2.add("coconut");
	fruits.insert("coconut");
	set2.add("strawberry");
	fruits.insert("strawberry");

	Set<std::string> set(set1 + set2);

	for(auto& fruit: set){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}

TEST(Set_HashTable_Chaining, DifferenceTest)
{
	Set<std::string> set1{11, hashString};
	Set<std::string> set2{11, hashString};
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	set1.add("mango");
	fruits.insert("mango");
	set1.add("grape");
	fruits.insert("grape");
	set2.add("peach");
	set2.add("grape");
	set2.add("strawberry");

	Set<std::string> set(set1 - set2);

	for(std::string fruit: set){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}

TEST(Set_HashTable_Chaining, IntersectionTest)
{
	Set<std::string> set1{11, hashString};
	Set<std::string> set2{11, hashString};
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	set1.add("mango");
	set2.add("apple");
	set2.add("grape");
	set2.add("strawberry");

	Set<std::string> set(intersection(set1, set2));

	for(auto& fruit: set){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
