/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author refracta
 * @file DoubleSortedLinkedList.h
 * 중복 허용, 이중 연결구조를 이용한 비정렬 정수 리스트
 * head, tail 유지, dummy 노드 사용, 코드 중복 제거
 */

#ifndef DOUBLEUNSORTEDLINKEDLIST_H_
#define DOUBLEUNSORTEDLINKEDLIST_H_

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class DoubleSortedLinkedList {
private:
    struct Node {
        int item{0};
        Node *prev{nullptr};
        Node *next{nullptr};

        Node() = default;

        Node(int item, Node *prev = nullptr, Node *next = nullptr) :
                item{item}, prev{prev}, next{next} {}
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
    size_t numItems{0};

    void copyList(const DoubleSortedLinkedList &other) {
        Node *dest{nullptr};
        Node *src{other.head};
        while (src) {
            Node *newNode{new Node{src->item}};
            if (dest) {
                dest->next = newNode;
                newNode->prev = dest;
                dest = newNode;
            } else head = dest = newNode;
            src = src->next;
            ++numItems;
        }
        tail = dest;
    }

    void moveList(DoubleSortedLinkedList &tmp) {
        numItems = tmp.numItems;
        head = tmp.head;
        tail = tmp.tail;
        tmp.head = tmp.tail = nullptr;
        tmp.numItems = 0;
    }

    int &getItem(int index) const {
        Node *curr{head};
        for (size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->item;
    }

    void removeNode(Node *curr) {
        Node *prev{curr->prev};
        if (curr == tail) tail = (curr == head) ? nullptr : prev;
        prev->next = curr->next; // dummy를 사용하므로 prev가 nullptr인 경우는 발생하지 않음
        if (curr->next) curr->next->prev = prev;
        delete curr;
        --numItems;
    }

public:
    explicit DoubleSortedLinkedList() = default;

    explicit DoubleSortedLinkedList(const std::initializer_list<int> &initList) {
        for (auto item: initList)
            add(item);
    }

    virtual ~DoubleSortedLinkedList() {
        clear();
    }

    DoubleSortedLinkedList(const DoubleSortedLinkedList &other) {
        copyList(other);
    }

    DoubleSortedLinkedList(DoubleSortedLinkedList &&tmp) {
        moveList(tmp);
    }

    const DoubleSortedLinkedList &operator=(const DoubleSortedLinkedList &other) {
        clear();
        copyList(other);
        return *this;
    }

    const DoubleSortedLinkedList &operator=(DoubleSortedLinkedList &&tmp) {
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
        head = tail = nullptr;
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

    void add(int item) {
        // 확장이 필요한 경우 확장 시도
        Node *newNode{new Node(item)};
        if (isEmpty()) {
            head = tail = newNode;
            // 빈 경우 head, tail 초기화
        } else if (tail->item <= item) {
            Node *last = tail;
            last->next = newNode;
            tail = newNode;
            tail->prev = last;
            // 뒤 쪽에 위치 할 값인 경우 뒤에 추가
        } else if (item <= head->item) {
            Node *first = head;
            head->prev = newNode;
            head = newNode;
            head->next = first;
            // 앞 쪽에 위치할 값인 경우 앞에 추가
        } else {
            Node *curr{head};
            while (curr) {
                if (item <= curr->item) {
                    Node *prev = curr->prev;
                    curr->prev = newNode;
                    newNode->next = curr;
                    newNode->prev = prev;
                    prev->next = newNode;
                    break;
                }
                curr = curr->next;
            }
            // 중간에 위치할 값인 경우 처리
        }
        ++numItems;
    }

    int popBack() {
        if (isEmpty()) throw std::runtime_error("popBack: empty state");
        int ret{tail->item};
        Node *prev{tail->prev};
        delete tail;
        if (prev) {
            prev->next = nullptr;
            tail = prev;
        } else head = tail = nullptr; // 노드가 하나만 있는 경우
        --numItems;
        return ret;
    }


    int popFront() {
        if (isEmpty()) throw std::runtime_error("popFront: empty state");
        int ret{head->item};
        Node *deleteNode{head};
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr; // 노드가 하나밖에 없는 경우
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
        if (isEmpty()) {
            return false;
        }
        Node *curr{head};
        while (curr) {
            if (curr->item == item) {
                return true;
            } else if (curr->item > item) {
                // 리스트에 값이 없는 것이 확실하므로 중단과 함께 false 반환
                return false;
            }
            curr = curr->next;
        }
        return false;
    }


    void removeFirst(int item) noexcept {
        if (isEmpty()) { return; }
        Node dummy{-1, nullptr, head};
        head->prev = &dummy;
        Node *curr{head};
        while (curr) {
            if (curr->item == item) {
                removeNode(curr);
                break;
            } else if (curr->item > item) {
                // 리스트에 값이 없는 것이 확실하므로 중단
                return;
            }
            curr = curr->next;
        }
        head = dummy.next;
        if (head) {
            head->prev = nullptr;
        }
    }

    void removeAll(int item) noexcept {
        if (isEmpty()) return;
        Node dummy{-1, nullptr, head};
        head->prev = &dummy;
        Node *curr{head};
        while (curr) {
            if (curr->item == item) {
                Node *next{curr->next};
                removeNode(curr);
                curr = next;
            } else if (curr->item > item) {
                // 리스트에 값이 없는 것이 확실하므로 중단
                break;
            } else {
                curr = curr->next;
            }
        }
        head = dummy.next;
        if (head) head->prev = nullptr; // 단일 연결구조와 차이
    }

    void removeRange(int first, int last) {
        if (!((0 <= first && first < numItems) && (0 <= last - 1) && (last - 1 < numItems)) || first > last)
            throw std::out_of_range("Index ERROR: out of range");

        Node *leftNode;
        Node *rightNode;
        Node *curr = head;

        for (int i = 0; i < first; i++) {
            curr = curr->next;
        }
        leftNode = curr->prev;
        // 좌측 끝 노드 구하기

        for (int i = first; i < last; i++) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
            numItems--;
        }
        // 노드 삭제 처리

        rightNode = curr;
        // 우측 끝 노드 설정

        if (leftNode && rightNode) {
            leftNode->next = rightNode;
            rightNode->prev = leftNode;
            // 리스트 봉합
        } else if (!leftNode && rightNode) {
            head = rightNode;
            // 좌측 끝 노드가 존재하지 않으면 head 재설정
        } else if (leftNode && !rightNode) {
            tail = leftNode;
            tail->next = nullptr;
            // 우측 끝 노드가 존재하지 않으면 tail 재설정
        } else {
            head = tail = nullptr;
            // 모든 범위를 없애는 경우
        }
    }

    auto begin() { return ListIterator<int>(head); }

    auto end() { return ListIterator<int>(nullptr); }

    auto cbegin() const { return ListIterator<const int>(head); }

    auto cend() const { return ListIterator<const int>(nullptr); }
};

#endif /* DOUBLEUNSORTEDLINKEDLIST_H_ */
