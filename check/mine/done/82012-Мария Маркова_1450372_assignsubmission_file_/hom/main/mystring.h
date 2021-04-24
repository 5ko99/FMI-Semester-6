#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <cstddef> // I need this library for std::size_t

class MyString
{
private:
    char* data;
    std::size_t length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    void push_back(char c);
    void pop_back();

    MyString& operator=(const MyString& other);
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& other);
    MyString operator+(char c) const;
    MyString operator+(const MyString& other) const;
    const char* c_str() const;
    bool operator==(const MyString& other) const;
    bool operator<(const MyString& other) const;


};

#endif