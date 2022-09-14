/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상
 * HashMapTest.cpp
 * 테스트 프로그램
 */

#include "HashMap.h"
#include "gtest/gtest.h"
#include <string>

size_t hashString(const std::string& key) noexcept{
	constexpr static size_t P{13875551L};
	constexpr size_t x{62057};
	size_t value{0};
	for(auto c: key)
		value = (value*x+c)%P;
	return value;
}

TEST(HashMap, addTest)
{
	HashMap<std::string, int> hMap{11, hashString};
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("mango", 5);
	hMap.put("strawberry", 7);
	hMap.put("banana", 6);
	ASSERT_TRUE(hMap.containsKey("banana"));
	ASSERT_TRUE(hMap.containsKey("orange"));
	hMap.put("apple", 6);
	ASSERT_EQ(hMap.size(), 7);
}


TEST(HashMap, getTest)
{
	HashMap<std::string, int> hMap{11, hashString};
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("apple", 6);
	ASSERT_EQ(6, hMap.get("apple"));
	ASSERT_EQ(10, hMap.get("orange"));
	ASSERT_EQ(hMap.size(), 4);
}

TEST(HashMap, removeTest)
{
	HashMap<std::string, int> hMap{11, hashString};
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("mango", 5);
	hMap.put("strawberry", 7);
	hMap.put("banana", 6);
	hMap.remove("banana");
	hMap.remove("orange");
	ASSERT_FALSE(hMap.containsKey("banana"));
	ASSERT_FALSE(hMap.containsKey("orange"));
	ASSERT_TRUE(hMap.containsKey("mango"));
	hMap.put("peach", 10);
	ASSERT_EQ(hMap.size(), 5);
}

TEST(HashMap, iteratorTest)
{
	HashMap<std::string, int> hMap{11, hashString};
	std::unordered_set<std::string> keySet;
	std::unordered_set<int> valueSet;
	hMap.put("apple", 3);
	keySet.insert("apple");
	valueSet.insert(3);
	hMap.put("peach", 5);
	keySet.insert("peach");
	valueSet.insert(5);
	hMap.put("grape", 2);
	keySet.insert("grape");
	valueSet.insert(2);
	hMap.put("orange", 10);
	keySet.insert("orange");
	valueSet.insert(10);
	hMap.put("mango", 5);
	keySet.insert("mango");
	hMap.put("coconut", 2);
	keySet.insert("coconut");
	hMap.put("strawberry", 10);
	keySet.insert("strawberry");

	ASSERT_EQ(valueSet, hMap.getValueSet());
	ASSERT_EQ(keySet, hMap.getKeySet());
}
