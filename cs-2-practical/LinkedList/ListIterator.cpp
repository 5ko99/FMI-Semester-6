#include "ListIterator.h"
using I = LinkedListIterator;
I::LinkedListIterator(Node *p): ptr(p) {}

I I::next() const {
    return I(ptr->next);
}

int I::get() const {
    return ptr->data;
}

int & I::get() {
    return ptr->data;
}

bool I::operator==(const I &it) const {
    return this->ptr == it.ptr;
}

bool I::operator!=(const I &it) const {
    return !(*this==it);
}

int I::operator*() const {
    return get();
}

I::operator bool() const {
    return ptr != nullptr;
}

I& I::operator++() {
    return *this=next();
}

I  I::operator++(int) {
    I prev = I(*this);
    ++(*this);
    return prev;
}