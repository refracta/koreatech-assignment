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

template <typename K, typename V>
class AVL {
	using Pair = std::pair<K,V>;
private:
	template <typename NodeType>
	class TreeIterator: public std::iterator<std::input_iterator_tag,Pair>{
		std::stack<NodeType*> stack;
		NodeType* curr;
		Pair* p;
		void next(){
			while(curr){
				stack.push(curr);
				curr = curr->left;
			}
			if(!stack.empty()){
				NodeType* top = stack.top();
				stack.pop();
				p = &top->entry;
				curr = top->right;
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
		Pair& operator*() noexcept {return *p;}
	};
	struct TreeNode{
		Pair entry;
		TreeNode* parent; // 추가
		TreeNode* left;
		TreeNode* right;
		long height{0};
		TreeNode(const K& key, const V& value, TreeNode* parent = nullptr,
			TreeNode* left = nullptr, TreeNode* right = nullptr):
			entry{std::make_pair(key, value)}, parent{parent}, left{left}, right{right}{}
	};

	TreeNode* root{nullptr};
	size_t numNodes{0};
public:
	AVL() = default;
	virtual ~AVL(){
		clear();
	}

	AVL(const AVL& other){
		std::vector<std::pair<K,V>> visitedOrder;
		visitedOrder.reserve(other.size());
		preorder(other.root, visitedOrder);
		for(auto& entry: visitedOrder) put(entry.first, entry.second);
	}

	AVL(AVL&& tmp){
		root = tmp.root;
		numNodes = tmp.numNodes;
		tmp.root = nullptr;
		tmp.numNodes = 0;
	}

	const AVL& operator=(const AVL& other){
		clear();
		std::vector<Pair> visitedOrder;
		visitedOrder.reserve(other.size());
		preorder(other.root, visitedOrder);
		for(auto& entry: visitedOrder) put(entry.first, entry.second);
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

	void put(const K& key, const V& value){
		TreeNode* newNode{new TreeNode{key, value}};
		if(isEmpty())
			root = newNode;
		else{
			TreeNode* parent{findNode(root, key)};
			if(parent->entry.first==key){
				delete newNode;
				parent->entry.second = value;
				return;
			}
			else if(parent->entry.first>key) parent->left = newNode;
			else parent->right = newNode;
			newNode->parent = parent; // 추가
			rebalance(newNode);
		}
		++numNodes;
	}

	bool find(const K& key) const noexcept{
		if(isEmpty()) return false;
		return findNode(root, key)->entry.first==key;
	}

	const V& get(const K& key) const{
		TreeNode* node{findNode(root, key)};
		if(node->entry.first==key) return node->entry.second;
		else throw std::runtime_error("없는 키를 검색하였음");
	}

	void remove(const K& key) noexcept{
		if(isEmpty()) return;
		TreeNode* delNode{findNode(root, key)};
		if(delNode->entry.first!=key) return;
		if(delNode->left&&delNode->right){
			TreeNode* prevNode{delNode->left};
			while(prevNode->right){
				prevNode = prevNode->right;
			}
  			delNode->entry = prevNode->entry;
			delNode = prevNode;
		}
		removeChild(delNode);
		rebalance(delNode->parent);
	}

	auto begin() const { return TreeIterator<TreeNode>(root); }
	auto end() const { return TreeIterator<TreeNode>(nullptr); }

	//debug
	void debugPrint(){
		std::vector<TreeNode*> nodes;
		preorder(root, nodes);
		for(auto node: nodes){
			std::cout << "key: " << node->entry.first
				<< ", value: " << node->entry.second
				<< ", height: " << node->height << '\n';
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
			if(P->entry.first>A->entry.first) P->left = A;
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
			if(P->entry.first>B->entry.first) P->left = B;
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

	TreeNode* findNode(TreeNode* currNode, const K& key) const noexcept{
		if(currNode->entry.first==key) return currNode;
		else{
			TreeNode* nextNode{(currNode->entry.first>key)? currNode->left: currNode->right};
			return nextNode? findNode(nextNode, key): currNode;
		}
	}

	void removeChild(TreeNode* node){
		TreeNode* child{node->left? node->left: node->right};
		TreeNode* parent{node->parent};
		if(parent){
			if(parent->entry.first>=node->entry.first) parent->left = child;
			else parent->right = child;
		}
		else root = child;
		if(child) child->parent = parent;
		delete node;
		--numNodes;
	}

	void preorder(TreeNode* curr, std::vector<TreeNode*>& nodes){
		nodes.push_back(curr->entry);
		if(curr->left) preorder(curr->left, nodes);
		if(curr->right) preorder(curr->right, nodes);
	}
};

#endif /* AVL_H_ */
