#include <iostream>
#ifndef MYSTRING_H
#define MYSTRING_H
class MyString {
    char* str;

public:
    MyString();
    MyString(const char*);
    MyString(const MyString&);
    ~MyString();
    char* getString();
    char& at(std::size_t);
    const char& at(std::size_t) const;
    char& operator[](std::size_t);
    const char& operator[](std::size_t) const;
    char& front();

    const char& front() const;
    char& back();
    const char& back() const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    void push_back(char c);
    void pop_back();
    MyString& operator+=(char c);
    MyString& operator+=(MyString& rhs);
    MyString operator+(char c) const;
    //MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator<(const MyString &rhs) const;
};

#endif // MYSTRING_H
