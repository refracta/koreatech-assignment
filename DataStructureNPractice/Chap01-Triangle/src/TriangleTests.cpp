/*
 * TriangleTests.cpp
 * 삼각형 테스트 프로그램
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2021년도 2학기
 * Author: 김상진
 */
#include "gtest/gtest.h"
#include "Triangle.h"

TEST(Triangle, initTest)
{
	ASSERT_THROW(Triangle(Point{15, 15}, Point{15, 20}, Point{15, 30}), std::runtime_error);
}


TEST(Triangle, areaTest)
{
	Triangle a{Point{15, 15}, Point{23, 30}, Point{50, 25}};
	ASSERT_EQ(a.area(), 222.5);
	Triangle b{Point{15, 15}, Point{23, 30}, Point{35, 10}};
	ASSERT_EQ(b.area(), 170);
}

TEST(Triangle, isInsideTest)
{
	Triangle a{Point{15, 15}, Point{23, 30}, Point{50, 25}};
	Triangle b{Point{15, 15}, Point{23, 30}, Point{35, 10}};

	ASSERT_TRUE(a.isInside(Point{25,20}));
	ASSERT_TRUE(b.isInside(Point{25,20}));
	ASSERT_FALSE(a.isInside(Point{10,25}));
	ASSERT_FALSE(b.isInside(Point{10,25}));
}


