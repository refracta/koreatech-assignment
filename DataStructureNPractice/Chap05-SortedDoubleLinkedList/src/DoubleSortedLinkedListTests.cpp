/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file DoubleUnsortedLinkedListTests.cpp
 * 테스트 프로그램
 */

#include <string>
#include "gtest/gtest.h"
#include "DoubleSortedLinkedList.h"


TEST(DoubleSortedLinkedList_Duplicate, listEmptyInitializationTest)
{
    DoubleSortedLinkedList list{};
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.isEmpty());
    ASSERT_FALSE(list.isFull());
}

TEST(DoubleSortedLinkedList_Duplicate, addfindTest){
    DoubleSortedLinkedList list;
    list.add(3);
    list.add(5);
    list.add(7);
    list.add(3);
    list.add(9);
    list.add(9); // 3, 3, 5, 7, 9, 9
    ASSERT_EQ(list.size(),6);
    std::string output = "";
    for(auto n: list){
        output += std::to_string(n)+",";
    }
    ASSERT_EQ(output,"3,3,5,7,9,9,");

    ASSERT_TRUE(list.find(3));
    ASSERT_TRUE(list.find(5));
    ASSERT_TRUE(list.find(7));
    ASSERT_TRUE(list.find(9));
    ASSERT_FALSE(list.find(2));
    ASSERT_FALSE(list.find(4));
    ASSERT_FALSE(list.find(11));
}

TEST(DoubleSortedLinkedList_Duplicate, popTest)
{
    DoubleSortedLinkedList list;
    list.add(3);
    list.add(5);
    list.add(7);
    list.add(3);
    ASSERT_EQ(list.size(),4);
    std::string output = "";
    while(!list.isEmpty())
        output += std::to_string(list.popBack())+",";
    ASSERT_EQ(output,"7,5,3,3,");
    ASSERT_TRUE(list.isEmpty());

    list.add(5);
    list.add(5);
    ASSERT_EQ(list.size(),2);
    list.add(3);
    list.add(7);
    output = "";
    while(!list.isEmpty())
        output += std::to_string(list.popFront())+",";
    ASSERT_EQ(output,"3,5,5,7,");
}

TEST(DoubleSortedLinkedList_Duplicate, listInitializationTest)
{
    DoubleSortedLinkedList list1{3,5,7};
    list1.add(9);
    std::string output = "";
    while(!list1.isEmpty())
        output += std::to_string(list1.popFront())+",";
    ASSERT_EQ(output,"3,5,7,9,");

    DoubleSortedLinkedList list2{1,11,2,7,8,5,6,3,4,10,};
    output = "";
    while(!list2.isEmpty())
        output += std::to_string(list2.popFront())+",";
//	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,11,");
    ASSERT_EQ(output,"1,2,3,4,5,6,7,8,10,11,");
}

TEST(DoubleSortedLinkedList_Duplicate, findTest){
    DoubleSortedLinkedList list{3,3,5,7,9};
    ASSERT_TRUE(list.find(3));
    ASSERT_TRUE(list.find(5));
    ASSERT_TRUE(list.find(7));
    ASSERT_TRUE(list.find(9));
    ASSERT_FALSE(list.find(2));
    ASSERT_FALSE(list.find(4));
    ASSERT_FALSE(list.find(11));
}

TEST(DoubleSortedLinkedList_Duplicate, removeFirstTest){
    DoubleSortedLinkedList list{3,3,5,6,6,6,9};
    list.removeFirst(3);
    ASSERT_EQ(list.peekFront(), 3);
    ASSERT_EQ(list.size(),6);
    list.removeFirst(9);
    ASSERT_EQ(list.peekBack(), 6);
    ASSERT_EQ(list.size(),5);
    list.removeFirst(3);
    ASSERT_EQ(list.size(),4);
    list.removeFirst(6);
    ASSERT_EQ(list.size(),3);
    list.removeFirst(6);
    ASSERT_EQ(list.size(),2);
    list.removeFirst(6);
    ASSERT_EQ(list.size(),1);
    ASSERT_EQ(5,list.popFront());
    ASSERT_TRUE(list.isEmpty());
    list.add(7);
    list.add(3);
    list.add(5);
    ASSERT_EQ(list.size(),3);
    list.removeFirst(5);
    list.removeFirst(3);
    list.removeFirst(7);
    ASSERT_TRUE(list.isEmpty());
}

TEST(DoubleSortedLinkedList_Duplicate, removeAllTest){
    DoubleSortedLinkedList list{1,1,1,3,3,4,4,7,9,9};
    list.removeAll(3);
    ASSERT_EQ(list.size(),8);
    std::string output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"1,1,1,4,4,7,9,9,");
    list.removeAll(1);
    ASSERT_EQ(list.size(),5);
    output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"4,4,7,9,9,");
    list.removeAll(9);
    ASSERT_EQ(list.size(),3);
    output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"4,4,7,");
    list.removeAll(7);
    output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"4,4,");
    list.removeAll(4);
    ASSERT_TRUE(list.isEmpty());
    list.add(7);
    list.add(7);
    list.add(7);
    ASSERT_EQ(list.size(),3);
    list.removeAll(7);
    ASSERT_TRUE(list.isEmpty());
}

TEST(DoubleSortedLinkedList_Duplicate, iteratorTest){
    DoubleSortedLinkedList list;
    list.add(3);
    list.add(5);
    list.add(7);
    std::string output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"3,5,7,");
}

TEST(DoubleSortedLinkedList_Duplicate, IndexOperator){
    DoubleSortedLinkedList list;
    list.add(3);
    list.add(5);
    ASSERT_EQ(list[1], 5);
    list.add(7);
    std::string output = "";
    for(auto i: list)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"3,5,7,");
}

TEST(DoubleSortedLinkedList_Duplicate, clearTest){
    DoubleSortedLinkedList list{1,3,1,1,3,4,5,4,4,6};
    list.clear();
    ASSERT_TRUE(list.isEmpty());
    list.add(4);
    ASSERT_EQ(list.size(),1);
    ASSERT_EQ(4,list.popFront());
    ASSERT_TRUE(list.isEmpty());
}

TEST(DoubleSortedLinkedList_Duplicate, Big5)
{
    DoubleSortedLinkedList list1{1,2,3,4,5};
    DoubleSortedLinkedList list2{6,7,8,9,10};
    DoubleSortedLinkedList list3;
    DoubleSortedLinkedList list4(list2);
    // copy constructor test
    for(int i=0; i<list2.size(); i++)
        ASSERT_EQ(list2[i], list4[i]);
    list3 = list1;
    // copy assignment test
    for(int i=0; i<list1.size(); i++)
        ASSERT_EQ(list1[i], list3[i]);
    // move constructor test
    DoubleSortedLinkedList list5(std::move(list3));
    for(int i=0; i<list5.size(); i++)
        ASSERT_EQ(list5[i], list1[i]);
    // move assignment test
    list3 = std::move(list4);
    for(int i=0; i<list3.size(); i++)
        ASSERT_EQ(list3[i], list2[i]);
}

// removeRange 테스트
TEST(DoubleSortedLinkedList_Duplicate, removeRangeTest) {
    DoubleSortedLinkedList list1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_THROW(list1.removeRange(-1, 1), std::out_of_range);
    ASSERT_THROW(list1.removeRange(1, 11), std::out_of_range);
    list1.removeRange(1, 9);
    std::string output = "";
    for(auto i: list1)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"0,9,");

    DoubleSortedLinkedList list2{0, 1, 2};
    list2.removeRange(0, 2);
    output = "";
    for(auto i: list2)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"2,");

    DoubleSortedLinkedList list3{0, 1, 2};
    list3.removeRange(1, 3);
    output = "";
    for(auto i: list3)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"0,");

    DoubleSortedLinkedList list4{0, 1, 2};
    list4.removeRange(0, 3);
    output = "";
    for(auto i: list4)
        output += std::to_string(i)+",";
    ASSERT_EQ(output,"");
}

