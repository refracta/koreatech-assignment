/*
 * AllTests.cpp
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2021년도 2학기
 * Author: 김상진
 */
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

