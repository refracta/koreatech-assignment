/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * 테스트 프로그램
 */

#include "Set.h"
#include "gtest/gtest.h"
#include <string>
#include <set>

TEST(AVL, DISABLED_iteratorTest){
	AVL<std::string> avl;
	std::vector<std::string> vec;
	avl.add("apple");
	vec.push_back("apple");
	avl.add("banana");
	vec.push_back("banana");
	avl.add("blackberry");
	vec.push_back("blackberry");
	avl.add("coconut");
	vec.push_back("coconut");
	avl.add("grape");
	vec.push_back("grape");
	avl.add("kiwi");
	vec.push_back("kiwi");
	avl.add("lemon");
	vec.push_back("lemon");
	avl.add("mango");
	vec.push_back("mango");
	avl.add("melon");
	vec.push_back("melon");
	avl.add("orange");
	vec.push_back("orange");
	avl.add("peach");
	vec.push_back("peach");
	avl.add("strawberry");
	vec.push_back("strawberry");
	avl.add("tomato");
	vec.push_back("tomato");

	size_t idx{0};
	for(auto& fruit: avl){
		ASSERT_EQ(fruit, vec[idx]);
		++idx;
	}
}

TEST(AVL, DISABLED_removeTest)
{
	AVL<std::string> avl;
	avl.add("apple");
	avl.add("peach");
	avl.add("orange");
	avl.add("mango");
	avl.add("grape");
	avl.add("strawberry");
	avl.add("banana");
	avl.add("melon");
	avl.add("kiwi");
	avl.add("tomato");
	avl.add("blackberry");
	ASSERT_EQ(avl.size(), 11);
	avl.remove("orange");
	ASSERT_EQ(avl.size(), 10);
	avl.remove("banana");
	ASSERT_EQ(avl.size(), 9);
	avl.remove("apple");
	ASSERT_EQ(avl.size(), 8);
}

TEST(Set_HashTable_Chaining, addTest)
{
	Set<std::string> set;
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
	Set<std::string> set;
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
	ASSERT_EQ(set.size(), 10);
	set.remove("banana");
	ASSERT_EQ(set.size(), 9);
	set.remove("apple");
	ASSERT_EQ(set.size(), 8);
	ASSERT_FALSE(set.contains("banana"));
	ASSERT_FALSE(set.contains("orange"));
	ASSERT_FALSE(set.contains("apple"));
	ASSERT_TRUE(set.contains("mango"));
	set.add("peach");
	ASSERT_EQ(set.size(), 8);
}

TEST(Set_HashTable_Chaining, iteratorTest)
{
	Set<std::string> set;
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
	Set<std::string> set1;
	Set<std::string> set2;
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
	Set<std::string> set1;
	Set<std::string> set2;
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
	Set<std::string> set1;
	Set<std::string> set2;
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
