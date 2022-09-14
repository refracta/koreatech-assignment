/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file SingleUnsortedLinkedList.h
 * 중복 허용, 단일 연결구조를 이용한 비정렬 정수 리스트
 * 두 개의 포인터를 이용하여 popBack, remove 연산 구현
 * head와 tail을 유지, dummy 노드 사용, 코드 중복 제거
 */

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleUnsortedLinkedList {
private:
    struct Node {
        int item{0};
        Node *next{nullptr};

        Node() = default;

        Node(int item, Node *next = nullptr) : item{item}, next{next} {}
    };

    template<typename U>
    class ListIterator : public std::iterator<std::input_iterator_tag, U> {
        Node *p;
    public:
        explicit ListIterator(Node *p) : p{p} {}

        const ListIterator &operator++() noexcept {
            p = p->next;
            return *this;
        }

        ListIterator operator++(int) noexcept {
            auto retval{*this};
            p = p->next;
            return retval;
        }

        bool operator==(const ListIterator &other) const noexcept { return p == other.p; }

        bool operator!=(const ListIterator &other) const noexcept { return p != other.p; }

        U &operator*() noexcept { return p->item; }
    };

    Node *head{nullptr};
    Node *tail{nullptr};
    // tail Node 포인터 추가
    size_t numItems{0};

    Node* getTail() const {
        return tail;
    }

    void copyList(const SingleUnsortedLinkedList &other) {
        Node *dest{nullptr};
        Node *src{other.head};
        while (src) {
            Node *newNode{new Node{src->item}};
            if (dest) {
                dest->next = newNode;
                dest = newNode;
            } else head = dest = newNode;
            src = src->next;
            ++numItems;
        }
        tail = dest;
        // tail을 복사한 노드로 설정한다.
    }

    void moveList(SingleUnsortedLinkedList &tmp) {
        numItems = tmp.numItems;
        head = tmp.head;
        tail = tmp.tail;
        tmp.head = nullptr;
        tmp.tail = nullptr;
        // tail 관련 이동 코드 추가
        tmp.numItems = 0;
    }

    int &getItem(int index) const {
        Node *curr{head};
        for (int i = 0; i < index; ++i) curr = curr->next;
        return curr->item;
    }

    void removeNode(Node *prev, Node *curr) {
        prev->next = curr->next;
        delete curr;
        --numItems;
    }

public:
    explicit SingleUnsortedLinkedList() = default;

    explicit SingleUnsortedLinkedList(const std::initializer_list<int> &initList) {
        Node *curr{nullptr};
        for (auto item: initList) {
            Node *newNode{new Node{item}};
            if (curr) {
                curr->next = newNode;
                curr = newNode;
            } else head = curr = newNode;
            ++numItems;
        }
        tail = curr;
        // 마지막 요소의 Node wrapper를 tail로 추가한다.
    }

    virtual ~SingleUnsortedLinkedList() {
        clear();
    }

    SingleUnsortedLinkedList(const SingleUnsortedLinkedList &other) {
        copyList(other);
    }

    SingleUnsortedLinkedList(SingleUnsortedLinkedList &&tmp) {
        moveList(tmp);
    }

    const SingleUnsortedLinkedList &operator=(const SingleUnsortedLinkedList &other) {
        clear();
        copyList(other);
        return *this;
    }

    const SingleUnsortedLinkedList &operator=(SingleUnsortedLinkedList &&tmp) {
        clear();
        moveList(tmp);
        return *this;
    }

    bool isEmpty() const noexcept {
        return !head;
    }

    bool isFull() const noexcept {
        return false;
    }

    size_t size() const noexcept {
        return numItems;
    }

    void clear() noexcept {
        Node *curr{head};
        while (curr) {
            Node *deleteNode{curr};
            curr = curr->next;
            delete deleteNode;
        }
        head = nullptr;
        tail = nullptr;
        // tail 포인터 초기화
        numItems = 0;
    }

    int operator[](int index) const {
        if (index >= 0 && index < numItems) return getItem(index);
        else throw std::out_of_range("Index ERROR: [] const");
    }

    int &operator[](int index) {
        if (index >= 0 && index < numItems) return getItem(index);
        else throw std::out_of_range("Index ERROR: []");
    }

    void pushBack(int item) {
        Node *newNode{new Node(item)};
        if (isEmpty()) {
            head = tail = newNode;
            // 비어있으면 tail도 같이 초기화
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++numItems;
    }

    int popBack() {
        if (isEmpty()) throw std::runtime_error("popBack: empty state");
        Node dummy{-1, head};
        Node *prev{&dummy};
        Node *curr{head};
        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }
        int ret{curr->item};
        prev->next = nullptr;
        head = dummy.next;
        tail = head != nullptr ? prev : nullptr;
        // tail을 마지막 prev로 설정
        delete curr;
        --numItems;
        return ret;
    }

    void pushFront(int item) {
        Node *newNode{new Node(item)};
        newNode->next = head;
        if (isEmpty()) {
            tail = newNode;
            // 비어있는 경우에만 tail 초기화
        }
        head = newNode;
        ++numItems;
    }

    int popFront() {
        if (isEmpty()) throw std::runtime_error("popFront: empty state");
        int ret{head->item};
        Node *deleteNode{head};
        head = head->next;
        delete[] deleteNode;
        --numItems;
        return ret;
    }

    int peekFront() const {
        if (isEmpty()) throw std::runtime_error("peekFront: empty state");
        return head->item;
    }

    int peekBack() const {
        if (isEmpty()) throw std::runtime_error("peekBack: empty state");
        return tail->item;
    }

    bool find(int item) const noexcept {
        if (isEmpty()) return false;
        Node *curr{head};
        while (curr) {
            if (curr->item == item) return true;
            curr = curr->next;
        }
        return false;
    }

    void removeFirst(int item) noexcept {
        if (isEmpty()) return;
        Node dummy{-1, head};
        Node *prev{&dummy};
        Node *curr{head};
        while (curr) {
            if (curr->item == item) {
                removeNode(prev, curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        head = dummy.next;
    }

    void removeAll(int item) noexcept {
        if (isEmpty()) return;
        Node dummy{-1, head};
        Node *prev{&dummy};
        Node *curr{head};
        while (curr) {
            if (curr->item == item) {
                Node *next{curr->next};
                removeNode(prev, curr);
                curr = next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        head = dummy.next;
    }

    auto begin() { return ListIterator<int>(head); }

    auto end() { return ListIterator<int>(nullptr); }

    auto cbegin() const { return ListIterator<const int>(head); }

    auto cend() const { return ListIterator<const int>(nullptr); }
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
