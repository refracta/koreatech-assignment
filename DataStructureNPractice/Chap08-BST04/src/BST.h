/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file BST.h
 * 이진 검색 트리: 부모에 대한 포인터를 유지, 재귀적으로 구현
 * 코드 중복 제거
 */

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>

class BST {
public:
    enum class TreeTraversal {
        INORDER, PREORDER, POSTORDER
    };
private:
    struct TreeNode {
        int key;
        TreeNode *parent;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int key = -1, TreeNode *parent = nullptr, TreeNode *left = nullptr, TreeNode *right = nullptr) :
                parent{parent}, key{key}, left{left}, right{right} {}
    };

    template<typename U>
    class TreeIterator : public std::iterator<std::input_iterator_tag, U> {
        typename std::vector<U> visitedOrder;
        U *p{nullptr};
    public:
        explicit TreeIterator(const BST *bst) {
            if (bst) {
                bst->traversal(visitedOrder);
                p = &visitedOrder[0];
            }
        }

        const TreeIterator &operator++() noexcept {
            ++p;
            if (p == &visitedOrder[visitedOrder.size()]) { p = nullptr; }
            return *this;
        }

        TreeIterator operator++(int) noexcept {
            auto retval{*this};
            ++p;
            if (p == &visitedOrder[visitedOrder.size()]) { p = nullptr; }
            return retval;
        }

        bool operator==(const TreeIterator &other) const noexcept { return p == other.p; }

        bool operator!=(const TreeIterator &other) const noexcept { return p != other.p; }

        U &operator*() noexcept { return *p; }
    };

    TreeNode *root{nullptr};
    size_t numNodes{0};
    TreeTraversal traversalMethod{TreeTraversal::INORDER};

public:
    BST() = default;

    BST(const std::initializer_list<int> &initList) {
        for (auto key: initList) { add(key); }
    }

    virtual ~BST() {
        clear();
    }

    BST(const BST &other) {
        std::vector<int> visitedOrder;
        preorder(other.root, visitedOrder);
        for (auto key: visitedOrder) { add(key); }
    }

    BST(BST &&tmp) {
        root = tmp.root;
        numNodes = tmp.numNodes;
        tmp.root = nullptr;
        tmp.numNodes = 0;
    }

    const BST &operator=(const BST &other) {
        clear();
        std::vector<int> visitedOrder;
        preorder(other.root, visitedOrder);
        for (auto key: visitedOrder) { add(key); }
        return *this;
    }

    const BST &operator=(BST &&tmp) {
        root = tmp.root;
        numNodes = tmp.numNodes;
        tmp.root = nullptr;
        tmp.numNodes = 0;
        return *this;
    }


    bool isEmpty() const noexcept {
        return numNodes == 0;
    }

    size_t size() const noexcept {
        //return numNodes;
        return size(root);
    }

    long height() const noexcept {
        return height(root) - 1;
    }

    void clear() {
        deleteNodes(root);
        root = nullptr;
        numNodes = 0;
    }

    void add(int key) {
        TreeNode *newNode{new TreeNode{key}};
        if (isEmpty()) {
            root = newNode;
        } else {
            TreeNode *parent{findNode(root, key)};
            if (parent->key == key) {
                delete newNode;
                return;
            } else if (parent->key > key) { parent->left = newNode; }
            else { parent->right = newNode; }
            newNode->parent = parent;
        }
        ++numNodes;
    }

    bool find(int key) const noexcept {
        if (isEmpty()) { return false; }
        return findNode(root, key)->key == key;
    }

    int next(int key) const {
        if (isEmpty()) { throw std::runtime_error("빈 트리"); }
        TreeNode *currNode{findNode(root, key)};
        if (currNode->key != key) { throw std::invalid_argument("키가 존재하지 않음"); }
        return getNext(currNode);
    }

    int prev(int key) const {
        if (isEmpty()) { throw std::runtime_error("빈 트리"); }
        TreeNode *currNode{findNode(root, key)};
        if (currNode->key != key) { throw std::invalid_argument("키가 존재하지 않음"); }
        return getPrev(currNode);
    }

    void remove(int key) noexcept {
        if (isEmpty()) { return; }
        TreeNode *delNode{findNode(root, key)};
        if (delNode->key != key) { return; }

        if (delNode->left && delNode->right) {
            TreeNode *prevNode{delNode->left};
            while (prevNode->right) {
                prevNode = prevNode->right;
            }
            delNode->key = prevNode->key;
            delNode = prevNode;
        }
        removeChild(delNode);
    }

    std::vector<int> rangeSearch(int left, int right) const {
        if (left > right) { throw std::out_of_range("범위 오류"); }
        std::vector<int> result;
        if (isEmpty()) { return result; }
        inorderRangeSearch(left, right, root, result);
        return result;
    }

    std::pair<int, int> nearestNeighbor(int key) const noexcept {
        std::pair<int, int> result;

        TreeNode *currNode{findNode(root, key)};
        if (currNode->key == key) {
            result.first = getPrev(currNode);
            result.second = getNext(currNode);
        } else {
            bool prevFound{false};
            bool nextFound{false};
            while (currNode && !(nextFound && prevFound)) {
                if (!nextFound && currNode->key > key) {
                    result.second = currNode->key;
                    nextFound = true;
                }
                if (!prevFound && currNode->key < key) {
                    result.first = currNode->key;
                    prevFound = true;
                }
                currNode = currNode->parent;
            }
            if (!prevFound) { result.first = result.second; }
            if (!nextFound) { result.second = result.first; }
        }
        return result;
    }

    void balanceTree() {
        std::vector<int> visitedOrder;
        inorder(root, visitedOrder);
        clear();
        balanceTree(0, visitedOrder.size() - 1, visitedOrder);
    }

    void setIteratorType(BST::TreeTraversal traversalMethod) noexcept {
        this->traversalMethod = traversalMethod;
    }

    auto begin() const { return TreeIterator<int>(this); }

    auto end() const { return TreeIterator<int>(nullptr); }

private:
    size_t size(TreeNode *currNode) const noexcept {
        return currNode ? 1 + size(currNode->left) + size(currNode->right) : 0;
    }

    long height(TreeNode *currNode) const noexcept {
        return currNode ? 1 + std::max(height(currNode->left), height(currNode->right)) : 0L;
    }

    void deleteNodes(TreeNode *currNode) {
        if (currNode) {
            deleteNodes(currNode->left);
            deleteNodes(currNode->right);
            delete currNode;
        }
    }

    TreeNode *findNode(TreeNode *currNode, int key) const noexcept {
        if (currNode->key == key) { return currNode; }
        else {
            TreeNode *nextNode{(currNode->key > key) ? currNode->left : currNode->right};
            return nextNode ? findNode(nextNode, key) : currNode;
        }
    }

    void removeChild(TreeNode *node) {
        TreeNode *parent{node->parent};
        TreeNode *child{node->left ? node->left : node->right};
        if (!parent) { root = child; }
        else {
            if (parent->key >= node->key) { parent->left = child; }
            else { parent->right = child; }
        }
        if (child) { child->parent = parent; }
        delete node;
        --numNodes;
    }

    int getNext(TreeNode *currNode) const {
        if (currNode->right) {
            currNode = currNode->right;
            while (currNode->left) { currNode = currNode->left; }
            return currNode->key;
        } else {
            int key = currNode->key;
            while (currNode->parent) {
                currNode = currNode->parent;
                if (currNode->key > key) { return currNode->key; }
            }
            return key; // 주어진 키가 BST에서 가장 큰 값 (next가 없는 경우)
        }
    }

    int getPrev(TreeNode *currNode) const {
        if (currNode->left) {
            currNode = currNode->left;
            while (currNode->right) { currNode = currNode->right; }
            return currNode->key;
        } else {
            int key = currNode->key;
            while (currNode->parent) {
                currNode = currNode->parent;
                if (currNode->key < key) { return currNode->key; }
            }
            return key; // 주어진 키가 BST에서 가장 작은 값 (prev가 없는 경우)
        }
    }


    void inorderRangeSearch(int left, int right, TreeNode *curr, std::vector<int> &result) const {
        if (curr->left && curr->left->key >= left) { inorderRangeSearch(left, right, curr->left, result); }
        if (curr->key >= left && curr->key <= right) { result.push_back(curr->key); }
        if (curr->right && curr->right->key <= right) { inorderRangeSearch(left, right, curr->right, result); }
    }

    void balanceTree(size_t lo, size_t hi, const std::vector<int> &visitedOrder) {
        if (lo == hi) { add(visitedOrder[lo]); }
        else if (lo + 1 == hi) {
            add(visitedOrder[hi]);
            add(visitedOrder[lo]);
        } else {
            size_t mid{lo + (hi - lo) / 2};
            add(visitedOrder[mid]);
            balanceTree(lo, mid - 1, visitedOrder);
            balanceTree(mid + 1, hi, visitedOrder);
        }
    }

    void traversal(std::vector<int> &visitedOrder) const {
        switch (traversalMethod) {
            case TreeTraversal::INORDER:
                inorder(root, visitedOrder);
                break;
            case TreeTraversal::PREORDER:
                preorder(root, visitedOrder);
                break;
            default:
                postorder(root, visitedOrder);
        }
    }

    void preorder(TreeNode *curr, std::vector<int> &visitedOrder) const {
        visitedOrder.push_back(curr->key);
        if (curr->left) { preorder(curr->left, visitedOrder); }
        if (curr->right) { preorder(curr->right, visitedOrder); }
    }

    void inorder(TreeNode *curr, std::vector<int> &visitedOrder) const {
        if (curr->left) { inorder(curr->left, visitedOrder); }
        visitedOrder.push_back(curr->key);
        if (curr->right) { inorder(curr->right, visitedOrder); }
    }

    void postorder(TreeNode *curr, std::vector<int> &visitedOrder) const {
        if (curr->left) { postorder(curr->left, visitedOrder); }
        if (curr->right) { postorder(curr->right, visitedOrder); }
        visitedOrder.push_back(curr->key);
    }
};

#endif /* BST_H_ */
