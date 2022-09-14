/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2021년도 2학기
 * @author 김상
 * 테스트 프로그램
 */

#include "gtest/gtest.h"
#include <string>
#include "TreeMap.h"

TEST(TreeMap, addTest)
{
	TreeMap<std::string, int> map;
	map.put("apple", 3);
	map.put("peach", 5);
	map.put("grape", 2);
	map.put("orange", 10);
	map.put("mango", 5);
	map.put("strawberry", 7);
	map.put("banana", 6);
	ASSERT_TRUE(map.containsKey("banana"));
	ASSERT_TRUE(map.containsKey("orange"));
	map.put("apple", 6);
	ASSERT_EQ(map.size(), 7);
}

TEST(TreeMap, getTest)
{
	TreeMap<std::string, int> map;
	map.put("apple", 3);
	map.put("peach", 5);
	map.put("grape", 2);
	map.put("orange", 10);
	map.put("apple", 6);
	ASSERT_EQ(6, map.get("apple"));
	ASSERT_EQ(10, map.get("orange"));
	ASSERT_EQ(map.size(), 4);
}

TEST(TreeMap, removeTest)
{
	TreeMap<std::string, int> map;
	map.put("apple", 3);
	map.put("peach", 5);
	map.put("grape", 2);
	map.put("orange", 10);
	map.put("mango", 5);
	map.put("strawberry", 7);
	map.put("banana", 6);
	map.remove("banana");
	map.remove("orange");
	ASSERT_FALSE(map.containsKey("banana"));
	ASSERT_FALSE(map.containsKey("orange"));
	ASSERT_TRUE(map.containsKey("mango"));
	map.put("peach", 10);
	ASSERT_EQ(map.size(), 5);
}

TEST(TreeMap, iteratorTest)
{
	TreeMap<std::string, int> map;
	std::set<std::string> keySet;
	std::set<int> valueSet;
	map.put("apple", 3);
	keySet.insert("apple");
	valueSet.insert(3);
	map.put("peach", 5);
	keySet.insert("peach");
	valueSet.insert(5);
	map.put("grape", 2);
	keySet.insert("grape");
	valueSet.insert(2);
	map.put("orange", 10);
	keySet.insert("orange");
	valueSet.insert(10);
	map.put("mango", 5);
	keySet.insert("mango");
	map.put("coconut", 2);
	keySet.insert("coconut");
	map.put("strawberry", 10);
	keySet.insert("strawberry");

	ASSERT_EQ(valueSet, map.getValueSet());
	ASSERT_EQ(keySet, map.getKeySet());
}
