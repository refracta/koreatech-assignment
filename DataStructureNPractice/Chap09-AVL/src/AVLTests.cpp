/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * TreeTest.cpp
 * AVL 트리
 * 테스트 프로그램
 */

#include "gtest/gtest.h"
#include "AVL.h"
#include <string>
#include <random>

#include <iostream>

std::random_device rd;
std::mt19937_64 mtRand(rd());

int getRandomInt(int n) {
    std::uniform_int_distribution<std::int64_t> dist(1, n);
    return dist(mtRand);
}

TEST(AVL_recursiveimpl_parentlink, initTest) {
    AVL tree;
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.isEmpty());
}

TEST(AVL_recursiveimpl_parentlink, addTest_singleRotation_rebalanceRight) {
    AVL tree;
    tree.add(10);
    tree.add(5);
    tree.add(2);
    ASSERT_EQ(tree.height(), 1);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "5,2,10,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}

TEST(AVL_recursiveimpl_parentlink, addTest_singleRotation_rebalanceLeft) {
    AVL tree;
    tree.add(2);
    tree.add(5);
    tree.add(10);
    ASSERT_EQ(tree.height(), 1);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "5,2,10,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}


TEST(AVL_recursiveimpl_parentlink, doubleRotation_rebalanceRight) {
    AVL tree;
    tree.add(10);
    tree.add(5);
    tree.add(12);
    tree.add(2);
    tree.add(8);
    tree.add(6);
    ASSERT_EQ(tree.height(), 2);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "8,5,2,6,10,12,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}


TEST(AVL_recursiveimpl_parentlink, addTest_doubleRotation_rebalanceLeft) {
    AVL tree;
    tree.add(10);
    tree.add(5);
    tree.add(17);
    tree.add(13);
    tree.add(21);
    tree.add(11);
    ASSERT_EQ(tree.height(), 2);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "13,10,5,11,17,21,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}


TEST(AVL_recursiveimpl_parentlink, removeLeafNodeTest) {
    AVL tree;
    tree.add(5);
    tree.add(3);
    tree.add(9);
    tree.add(4);
    tree.add(7);
    tree.add(12);
    tree.add(6);
    tree.remove(4);
    ASSERT_EQ(tree.height(), 2);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "7,5,3,6,9,12,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}


TEST(AVL_recursiveimpl_parentlink, removeSingleChildNodeTest) {
    AVL tree;
    tree.add(5);
    tree.add(3);
    tree.add(9);
    tree.add(4);
    tree.add(7);
    tree.add(12);
    tree.add(6);
    tree.remove(3);
    ASSERT_EQ(tree.height(), 2);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "7,5,4,6,9,12,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}

TEST(AVL_recursiveimpl_parentlink, removeTwoChildNodeTest) {
    AVL tree{5, 3, 9, 4, 7, 12, 6};
    tree.remove(5);
    ASSERT_EQ(tree.height(), 2);
    std::string output = "";
    tree.setIteratorType(AVL::TreeTraversal::PREORDER);
    for (auto i: tree) {
        output += std::to_string(i) + ",";
    }
    ASSERT_EQ(output, "7,4,3,6,9,12,");

    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}

TEST(AVL_recursiveimpl_parentlink, randomTest) {
    AVL tree;
    int size = 0;
    while (size < 32) {
        int key{getRandomInt(100)};
        tree.add(key);
        size = tree.size();
    }
    std::vector<AVL::TreeNode *> list(tree.getAllNodes());
    for (auto node: list) {
        long leftHeight{(node->left) ? node->left->height : -1};
        long rightHeight{(node->left) ? node->left->height : -1};
        ASSERT_TRUE(std::abs(rightHeight - leftHeight) <= 1);
    }
}

