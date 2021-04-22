#pragma once
#include <iostream>

class MyString{
    char* string = nullptr; 
    unsigned short length = 0;

    void StringAllocateHelper(const MyString &other);   //functions to help 
    void PushBackHelper(const char &c);         //avoid dublicating code;

public:

    MyString();

    MyString(const char* str);
    
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);

    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;
    
    char& front();
    const char& front() const;
    
    char& back();
    const char& back() const;
    
    bool empty()const;

    std::size_t size() const;
    
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


    ~MyString();
    
};