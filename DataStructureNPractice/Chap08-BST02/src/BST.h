/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file BST.h
 * 이진 검색 트리: 부모에 대한 포인터를 유지하지 않음, 재귀적으로 구현
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

class BST {
public:
    enum class TreeTraversal {
        INORDER, PREORDER, POSTORDER
    };
private:
    struct TreeNode {
        int key;
        TreeNode *left;
        TreeNode *right;
        TreeNode *parent;

        TreeNode(int key = -1, TreeNode *left = nullptr, TreeNode *right = nullptr, TreeNode *parent = nullptr) :
                key{key}, left{left}, right{right}, parent{parent} {}
    };

    TreeNode *root{nullptr};
    size_t numNodes{0};

    std::vector<int> visitedOrder;
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
        preorder(other.root);
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
        visitedOrder.clear();
        preorder(other.root);
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
            ++numNodes;
        } else {
            TreeNode *parent{findNode(root, key)};
            if (parent->key == key) {
                delete newNode;
                return;
            } else if (parent->key > key) {
                parent->left = newNode;
                newNode->parent = parent;
                // 새로 생성한 노드에 부모 노드 할당
            } else {
                parent->right = newNode;
                newNode->parent = parent;
                // 새로 생성한 노드에 부모 노드 할당
            }
            ++numNodes;
        }
    }

    bool find(int key) const noexcept {
        if (isEmpty()) { return false; }
        return findNode(root, key)->key == key;
    }

    int next(int key) const {
        if (isEmpty()) { throw std::runtime_error("빈 트리"); }
        TreeNode *currNode{findNode(root, key)};
        // parents stack을 이용하지 않도록 변경
        if (currNode->key != key) { throw std::invalid_argument("키가 존재하지 않음"); }
        return getNext(currNode);
    }

    int prev(int key) const {
        if (isEmpty()) { throw std::runtime_error("빈 트리"); }
        TreeNode *currNode{findNode(root, key)};
        // parents stack을 이용하지 않도록 변경
        if (currNode->key != key) { throw std::invalid_argument("키가 존재하지 않음"); }
        return getPrev(currNode);
    }

    void remove(int key) noexcept {
        if (isEmpty()) { return; }
        // parents stack을 이용하지 않도록 변경
        TreeNode *delNode{findNode(root, key)};
        if (delNode->key != key) { return; }

        if (delNode->left && delNode->right) {
            TreeNode *parent{delNode};
            TreeNode *prevNode{delNode->left};
            while (prevNode->right) {
                parent = prevNode;
                prevNode = prevNode->right;
            }
            delNode->key = prevNode->key;
            removeChild(parent, prevNode);
        } else {
            TreeNode *parent{!delNode->parent ? nullptr : delNode->parent};
            removeChild(parent, delNode);
        }
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
            TreeNode dummy = {-1, nullptr, nullptr, currNode};
            currNode = &dummy;
            // 더미 노드를 통한 순회 처리
            while (currNode->parent && !(nextFound && prevFound)) {
                TreeNode *parent{currNode->parent};
                if (!nextFound && parent->key > key) {
                    result.second = parent->key;
                    nextFound = true;
                }
                if (!prevFound && parent->key < key) {
                    result.first = parent->key;
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
        visitedOrder.clear();
        inorder(root);
        clear();
        balanceTree(0, visitedOrder.size() - 1);
    }

    void setIteratorType(BST::TreeTraversal traversalMethod) noexcept {
        this->traversalMethod = traversalMethod;
    }

    std::vector<int>::iterator begin() {
        traversal();
        return visitedOrder.begin();
    }

    std::vector<int>::iterator end() {
        return visitedOrder.end();
    }

private:
    size_t size(TreeNode *currNode) const noexcept {
        return currNode ? 1 + size(currNode->left) + size(currNode->right) : 0;
    }

    long height(TreeNode *currNode) const noexcept {
        return currNode ? 1 + std::max(height(currNode->left), height(currNode->right)) : 0L;
    }

    void traversal() {
        visitedOrder.clear();
        switch (traversalMethod) {
            case TreeTraversal::INORDER:
                inorder(root);
                break;
            case TreeTraversal::PREORDER:
                preorder(root);
                break;
            default:
                postorder(root);
        }
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

    void removeChild(TreeNode *parent, TreeNode *child) {
        // parents stack을 이용하지 않도록 변경
        TreeNode *descendant{child->left ? child->left : child->right};
        if (!parent) { root = descendant; }
        else {
            if (parent->key > child->key) { parent->left = descendant; }
            else { parent->right = descendant; }
        }
        delete child;
        --numNodes;
    }

    int getNext(TreeNode *currNode) const {
        // parents stack을 이용하지 않도록 변경
        TreeNode *originalNode = currNode;
        if (currNode->right) {
            currNode = currNode->right;
            while (currNode->left) { currNode = currNode->left; }
            return currNode->key;
        } else {
            while (currNode->parent) {
                TreeNode *parent = currNode->parent;
                if (parent->key > currNode->key) {
                    return parent->key;
                }
                currNode = currNode->parent;
            }
        }
        return originalNode->key;
    }

    int getPrev(TreeNode *currNode) const {
        // parents stack을 이용하지 않도록 변경
        TreeNode *originalNode = currNode;
        if (currNode->left) {
            currNode = currNode->left;
            while (currNode->right) { currNode = currNode->right; }
            return currNode->key;
        } else {
            while (currNode->parent) {
                TreeNode *parent = currNode->parent;
                if (parent->key < currNode->key) {
                    return parent->key;
                }
                currNode = currNode->parent;
            }
        }
        return originalNode->key;
    }


    void inorderRangeSearch(int left, int right, TreeNode *curr, std::vector<int> &result) const {
        if (curr->left && curr->left->key >= left) { inorderRangeSearch(left, right, curr->left, result); }
        if (curr->key >= left && curr->key <= right) { result.push_back(curr->key); }
        if (curr->right && curr->right->key <= right) { inorderRangeSearch(left, right, curr->right, result); }
    }

    void balanceTree(size_t lo, size_t hi) {
        if (lo == hi) { add(visitedOrder[lo]); }
        else if (lo + 1 == hi) {
            add(visitedOrder[hi]);
            add(visitedOrder[lo]);
        } else {
            size_t mid{lo + (hi - lo) / 2};
            add(visitedOrder[mid]);
            balanceTree(lo, mid - 1);
            balanceTree(mid + 1, hi);
        }
    }

    void preorder(TreeNode *curr) {
        visitedOrder.push_back(curr->key);
        if (curr->left) { preorder(curr->left); }
        if (curr->right) { preorder(curr->right); }
    }

    void inorder(TreeNode *curr) {
        if (curr->left) { inorder(curr->left); }
        visitedOrder.push_back(curr->key);
        if (curr->right) { inorder(curr->right); }
    }

    void postorder(TreeNode *curr) {
        if (curr->left) { postorder(curr->left); }
        if (curr->right) { postorder(curr->right); }
        visitedOrder.push_back(curr->key);
    }
};

#endif /* BST_H_ */
