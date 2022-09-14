/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file AVL.h
 * AVL 트리: 재귀적으로 구현
 * 코드 중복 제거
 */

#ifndef AVL_H_
#define AVL_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>

template <typename T>
class AVL {
private:
	template <typename NodeType, typename ElementType>
	class TreeIterator: public std::iterator<std::input_iterator_tag,ElementType>{
		std::stack<NodeType*> stack;
		NodeType* curr;
		NodeType* p;
		void next(){
			while(curr){
				stack.push(curr);
				curr = curr->left;
			}
			if(!stack.empty()){
				p = stack.top();
				stack.pop();
				curr = p->right;
			}
			else p = nullptr;
		}
	public:
		explicit TreeIterator(NodeType* root): curr{root} {
			next();
		}
		const TreeIterator& operator++() noexcept { next(); return *this; }
		TreeIterator operator++(int) noexcept { auto retval{*this}; next(); return retval; }
		bool operator==(const TreeIterator& other) const noexcept {return p == other.p;}
		bool operator!=(const TreeIterator& other) const noexcept {return p != other.p;}
		ElementType& operator*() noexcept {return p->key;}
	};
	struct TreeNode{
		T key;
		TreeNode* parent; // 추가
		TreeNode* left;
		TreeNode* right;
		long height{0};
		TreeNode(const T& key, TreeNode* parent = nullptr,
			TreeNode* left = nullptr, TreeNode* right = nullptr):
			key{key}, parent{parent}, left{left}, right{right}{}
	};

	TreeNode* root{nullptr};
	size_t numNodes{0};
public:
	AVL() = default;
	AVL(const std::initializer_list<T>& initList){
		for(auto key: initList) add(key);
	}
	virtual ~AVL(){
		clear();
	}

	AVL(const AVL& other){
		std::vector<T> visitedOrder;
		visitedOrder.reserve(other.size());
		preorder(other.root, visitedOrder);
		for(auto key: visitedOrder) add(key);
	}

	AVL(AVL&& tmp){
		root = tmp.root;
		numNodes = tmp.numNodes;
		tmp.root = nullptr;
		tmp.numNodes = 0;
	}

	const AVL& operator=(const AVL& other){
		clear();
		std::vector<T> visitedOrder;
		visitedOrder.reserve(other.size());
		preorder(other.root, visitedOrder);
		for(auto key: visitedOrder) add(key);
		return *this;
	}

	const AVL& operator=(AVL&& tmp){
		root = tmp.root;
		numNodes = tmp.numNodes;
		tmp.root = nullptr;
		tmp.numNodes = 0;
		return *this;
	}


	bool isEmpty() const noexcept{
		return numNodes==0;
	}

	size_t size() const noexcept{
		return numNodes;
	}

	long height() const noexcept{
		return height(root)-1;
	}

	void clear(){
		deleteNodes(root);
		root = nullptr;
		numNodes = 0;
	}

	void add(const T& key){
		TreeNode* newNode{new TreeNode{key}};
		if(isEmpty()){
			root = newNode;
			++numNodes;
		}
		else{
			TreeNode* parent{findNode(root, key)};
			if(parent->key==key){
				delete newNode;
				return;
			}
			else if(parent->key>key) parent->left = newNode;
			else parent->right = newNode;
			++numNodes;
			newNode->parent = parent; // 추가
			rebalance(newNode);
		}
	}

	bool find(const T& key) const noexcept{
		if(isEmpty()) return false;
		return findNode(root, key)->key==key;
	}

	void remove(const T& key) noexcept{
		if(isEmpty()) return;
		TreeNode* delNode{findNode(root, key)};
		if(delNode->key!=key) return;
		if(delNode->left&&delNode->right){
			TreeNode* prevNode{delNode->left};
			while(prevNode->right){
				prevNode = prevNode->right;
			}
  			delNode->key = prevNode->key;
			delNode = prevNode;
		}
		removeChild(delNode);
		rebalance(delNode->parent);
	}

	auto begin() const { return TreeIterator<TreeNode, const T>(root); }
	auto end() const { return TreeIterator<TreeNode, const T>(nullptr); }

	//debug
	void debugPrint(){
		std::vector<TreeNode*> nodes;
		preorder(root, nodes);
		for(auto node: nodes){
			std::cout << "key: " << node->key << ", height: " << node->height << '\n';
		}
	}

private:

	std::pair<long, long> getChildHeight(TreeNode* node){
		return std::make_pair(
			node->left? node->left->height: -1,
			node->right? node->right->height: -1
		);
	}

	void rebalance(TreeNode* node){
		TreeNode* parent{node->parent};
		auto [leftHeight, rightHeight]{getChildHeight(node)};
		if(std::abs(rightHeight-leftHeight)==2){
			if(leftHeight>rightHeight) rebalanceRight(node);
			else rebalanceLeft(node);
		}
		adjustHeight(node);
		if(parent) rebalance(parent);
	}

	void adjustHeight(TreeNode* node){
		auto [leftHeight, rightHeight]{getChildHeight(node)};
		node->height = 1+std::max(leftHeight, rightHeight);
	}

	void rebalanceRight(TreeNode* node){
		TreeNode* left{node->left};
		if(left){
			auto [leftHeight, rightHeight]{getChildHeight(left)};
			if(rightHeight>leftHeight) rotateLeft(left);
		}
		rotateRight(node);
	}

	void rebalanceLeft(TreeNode* node){
		TreeNode* right{node->right};
		if(right){
			auto [leftHeight, rightHeight]{getChildHeight(right)};
			if(leftHeight>rightHeight) rotateRight(right);
		}
		rotateLeft(node);
	}

	void rotateLeft(TreeNode* node){
		TreeNode* P{node->parent};
		TreeNode* A{node->right};
		TreeNode* T2{A->left};
		if(P){
			if(P->key>A->key) P->left = A;
			else P->right = A;
		}
		else root = A;
		A->parent = P;
		A->left = node;
		node->right = T2;
		if(T2) T2->parent = node;
		node->parent = A;
		adjustHeight(node);
		if(node->parent) adjustHeight(node->parent);
	}

	void rotateRight(TreeNode* node){
		TreeNode* P{node->parent};
		TreeNode* B{node->left};
		TreeNode* T2{B->right};
		if(P){
			if(P->key>B->key) P->left = B;
			else P->right = B;
		}
		else root = B;
		B->parent = P;
		B->right = node;
		node->left = T2;
		if(T2) T2->parent = node;
		node->parent = B;
		adjustHeight(node);
		if(node->parent) adjustHeight(node->parent);
	}

	long height(TreeNode* currNode) const noexcept{
		return currNode? 1+std::max(height(currNode->left), height(currNode->right)): 0L;
	}

	void deleteNodes(TreeNode* currNode){
		if(currNode){
			deleteNodes(currNode->left);
			deleteNodes(currNode->right);
			delete currNode;
		}
	}

	TreeNode* findNode(TreeNode* currNode, const T& key) const noexcept{
		if(currNode->key==key) return currNode;
		else{
			TreeNode* nextNode{(currNode->key>key)? currNode->left: currNode->right};
			return nextNode? findNode(nextNode, key): currNode;
		}
	}

	void removeChild(TreeNode* node){
		TreeNode* child{node->left? node->left: node->right};
		TreeNode* parent{node->parent};
		if(parent){
			if(parent->key>=node->key) parent->left = child;
			else parent->right = child;
		}
		else root = child;
		if(child) child->parent = parent;
		delete node;
		--numNodes;
	}

	void preorder(TreeNode* curr, std::vector<TreeNode*>& nodes){
		nodes.push_back(curr);
		if(curr->left) preorder(curr->left, nodes);
		if(curr->right) preorder(curr->right, nodes);
	}
};

#endif /* AVL_H_ */
