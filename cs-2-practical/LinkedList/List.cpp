#include "List.h"
#include<iostream>

using I = LinkedListIterator;

//private helper functions
void List::copyList(const List &l) {
    front = back = nullptr;
    for (I it = l.begin(); it; ++it)
        insertEnd(*it);
}

void List::deleteList() {
    while (!isEmpty()) {
        deleteBegin();
    }
}

I List::findPrev(const I &it) {
    I result = begin();
    while (result && result.ptr->next != it.ptr)
        result++;
    return result;
}

//Public part

List::List() : front(nullptr), back(nullptr) {}

List::~List() {
    deleteList();
}

List::List(const List &l) {
    copyList(l);
}

List &List::operator=(const List &l) {
    if (this != &l) {
        deleteList();
        copyList(l);
    }
    return *this;
}

int& List::operator[](size_t idx) {
    size_t count = 0;
    for (I it = begin(); it; ++it) {
        if (count == idx) return getAt(it);
        if(count>idx) {
            std::cerr << "Idx out of list bounds!" << '\n';
            exit(1);
        }
    }
    std::cerr << "Idx out of list bounds!" << '\n';
    exit(1);
}

int List::operator[](size_t idx) const {
    int count = 0;
    for (I it = begin(); it; ++it) {
        if (count == idx) return getAt(it);
        ++count;
    }
    std::cerr << "Idx out of list bounds!" << '\n';
    exit(1);
}

I List::begin() const {
    return I(front);
}

I List::end() const {
    return I(back);
}

bool List::isEmpty() const {
    return front == nullptr;
}

int List::getAt(const I &it) const {
    return it.get();
}

int &List::getAt(I &it) {
    return it.get();
}

bool List::insertBefore(int x, const I &it) {
    if (!it && !isEmpty())
        return false;
    if (it == begin()) {
        Node *p = new Node(x, front);
        if (front == nullptr) {
            back = p;
        }
        front = p;
        return true;
    }
    return insertAfter(x, findPrev(it));
}

bool List::insertAfter(int x, const I &it) {
    if (isEmpty()) {
        front = back = new Node(x);
        return true;
    }

    if (!it) {
        return false;
    }

    I temp = it.next();
    Node *p = new Node(x, it.ptr->next);
    it.ptr->next = p;
    if (back == it) back = p;
    return true;
}

void List::insertBegin(int x) {
    insertBefore(x, begin());
}

void List::insertEnd(int x) {
    insertAfter(x, end());
}

bool List::deleteAt(const I &it) {
    if (!it || isEmpty())
        return false;
    if (it == begin()) {
        int x = front->data;
        Node *p = front;
        front = front->next;
        if (front == nullptr)
            back = nullptr;

        delete p;
        return true;
    }

    return deleteAfter(findPrev(it));
}

bool List::deleteBefore(const I &it) {
    if (isEmpty() || !it || it == begin())
        return false;

    return deleteAt(findPrev(it));
}

bool List::deleteBegin() {
    return deleteAt(begin());
}

bool List::deleteEnd() {
    return deleteAt(end());
}

bool List::deleteAfter(const I &it) {
    if (isEmpty() || !it || it == end())
        return false;

    Node *p = it.ptr->next; // it next
    it.ptr->next = p->next; // it next next
    int x = p->data;

    if (back == p)
        back = it.ptr;

    delete p;

    return true;
}

void List::print() const {
    for (I it = begin(); it; ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
}


