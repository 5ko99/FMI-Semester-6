#pragma once
#include <cstddef>
using std::size_t;

class MyString {

private:
    char* string;
    size_t length;
    size_t allocated; //must be always >= length+1

public:
    MyString();
    MyString(const MyString& other);
    MyString(const char* str);
    MyString& operator= (const MyString& other);
    ~MyString();

public:
    size_t size() const; 
    void printString() const;
    char& at(size_t pos);
    const char& at(size_t pos) const;
    char& operator[](size_t pos);
    const char& operator[](std::size_t pos) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    bool empty() const;
    void clear();
    void push_back(char c);
    void pop_back();
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator<(const MyString &rhs) const;
    bool operator>(const MyString &rhs) const;

private:
    size_t strlen(const char* string) const;
};