/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author: refracta
 * HashTable.h
 * 용량 고정 단일 버켓, key = 문자열
 * Linear Probing, 해댕 위치 없을 때 delete flag 사용하지 않고 전체 탐색
 * 테스트 프로그램
 */
#include "gtest/gtest.h"
#include "HashTable.h"
#include <string>
#include <set>

TEST(HashTable_LinearProbing, addTest)
{
	HashTable hTable;
	hTable.add("peach"); 	//
	hTable.add("grape");	//
	hTable.add("orange");	//
	ASSERT_EQ(hTable.size(), 3);
	ASSERT_TRUE(hTable.contains("peach"));
	ASSERT_FALSE(hTable.contains("melon"));
	hTable.add("kiwi");		//
	hTable.add("mango");	//
	hTable.add("tomato");	//
	hTable.add("melon");	//

	//hTable.add("cherry");	//
	//hTable.add("lemon");	//

	ASSERT_EQ(hTable.size(), 7);
	ASSERT_FALSE(hTable.contains("cherry"));
	ASSERT_TRUE(hTable.contains("tomato"));
	ASSERT_TRUE(hTable.contains("melon"));
	hTable.debugPrint();
}

TEST(HashTable_LinearProbing, removeTest)
{
	HashTable hTable;
	hTable.add("peach");
	hTable.add("grape");
	hTable.add("orange");
	hTable.add("kiwi");
	hTable.add("mango");
	hTable.add("cherry");
	hTable.add("tomato");
	hTable.debugPrint();
	hTable.remove("peach");
	hTable.add("mango");

	hTable.remove("kiwi");
	ASSERT_EQ(hTable.size(), 5);
	ASSERT_TRUE(hTable.contains("tomato"));
	hTable.remove("cherry");
	hTable.remove("tomato");
	hTable.debugPrint();
	hTable.add("melon");
	ASSERT_EQ(hTable.size(), 4);
	ASSERT_FALSE(hTable.contains("kiwi"));
	ASSERT_FALSE(hTable.contains("cherry"));
	ASSERT_TRUE(hTable.contains("melon"));

}

TEST(HashTable_LinearProbing, DISABLED_iteratorTest)
{
	HashTable hTable;
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

	for(auto fruit: hTable){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
