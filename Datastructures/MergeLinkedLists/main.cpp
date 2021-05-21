#include <iostream>
#include<vector>

template<class T>
struct Node {
    T data;
    Node *next;

    explicit Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
};

template<class T>
class LinkedList {
    Node<T> *head{}, *tail{};
public:
    explicit LinkedList(Node<T> *head = nullptr, Node<T> *tail = nullptr) : head(head), tail(tail) {}

    LinkedList(const LinkedList<T> &l) : head(l.head), tail(l.tail) {}

    LinkedList(LinkedList<T> &&l) noexcept: head(l.head), tail(l.tail) {
        l.head = nullptr;
        l.tail = nullptr;
    }

    LinkedList<T> &operator=(const LinkedList<T> &l) {
        if (this != &l) {
            ~LinkedList();
            head = l.head;
            tail = l.tail;
        }
        return (*this);
    }

    LinkedList<T> &operator=(LinkedList &&l) noexcept {
        if (this != &l) {
            ~LinkedList();
            head = l.head;
            tail = l.tail;
            l.head = nullptr;
            l.tail = nullptr;
        }
    }

    void push_back(const T &data) {
        auto *node = new Node<T>(data);
        if (head == nullptr) {
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    void pop_back() {
        if (head != nullptr) {
            Node<T> *cur = head, *oneBack;
            while (cur->next != nullptr) {
                oneBack = cur;
                cur = cur->next;
            }
            delete tail;
            tail = oneBack;
        }
    }

    [[nodiscard]] inline T getHeadData() const {
        return head->data;
    }

    [[nodiscard]] inline T getTailData() const {
        return tail->data;
    }

    [[nodiscard]] std::vector<T> toVector() const {
        std::vector<T> res;
        Node<T> *cur = head;
        while (cur != nullptr) {
            res.push_back(cur->data);
            cur = cur->next;
        }
    }

    [[nodiscard]] Node<T> *getHead() {
        return head;
    }

    [[nodiscard]]  Node<T> *getTail() {
        return tail;
    }
};

template<class T>
Node<T> *mergeLists(Node<T> *l1, Node<T> *l2) {
    Node<T> *dummyHead = nullptr, *cur = nullptr;
    auto *cur1 = l1, *cur2 = l2;
    if (cur1->data <= cur2->data) {
        cur = cur1;
        cur1 = cur1->next;
    } else {
        cur = cur2;
        cur2 = cur2->next;
    }
    while (cur1 != nullptr && cur2 != nullptr) {
        if (cur1->data <= cur2->data) {
            cur->next = cur1;
            cur1 = cur1->next;
        } else {
            cur->next = cur2;
            cur2 = cur2->next;
        }
        if (dummyHead == nullptr)
            dummyHead = cur;
        cur = cur->next;
    }
    if (cur1 != nullptr) {
        cur->next = cur1;
    }
    if (cur2 != nullptr) {
        cur->next = cur2;
    }
    return dummyHead;
}

int main() {
    LinkedList<int> l1, l2,l3;
    l1.push_back(5);
    l1.push_back(8);
    l1.push_back(11);
    l1.push_back(87);
    l1.push_back(99);
    l2.push_back(-3);
    l2.push_back(45);
    l2.push_back(87);
    l2.push_back(88);
    l2.push_back(98);
    l2.push_back(100);
    l2.push_back(120);
    auto *head = mergeLists(l1.getHead(), l2.getHead());
    while (head != nullptr) {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
    return 0;
}
