#include <iostream>
#include "helpers.h"
#pragma once

class MyString
{
private:
    char *string;

public:
    MyString();
    MyString(const char *string);
    MyString(const MyString &other);
    MyString(MyString && other) noexcept;

    ~MyString();
    MyString &operator=(const MyString &other);
    MyString &operator=(const char* other);
    MyString& operator=(MyString &&other) noexcept;


    MyString& operator+=(const char c);
    MyString operator+(const char c) const;

    MyString& operator+=(const MyString &other);
    MyString operator+(const MyString &other) const;

    bool operator==(const MyString &other) const;
    bool operator<(const MyString &other) const;

    char &at(std::size_t index);
    const char& at(std::size_t index) const;

    char &operator[](std::size_t index);
    const char& operator[](std::size_t index) const;

    char &front();
    const char& front() const;

    char &back();
    const char& back() const;

    std::size_t size() const;
    bool isEmpty() const;

    void clear(); 
    void push_back(const char c);
    void pop_back();

    const char* c_str() const; 
    void print() const;

private:
    void copy(const MyString &other);
    void destroy();
    
};