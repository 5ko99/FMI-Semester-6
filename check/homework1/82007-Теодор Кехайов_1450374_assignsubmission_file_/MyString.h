#ifndef HOMEWORK1_MYSTRING_H
#define HOMEWORK1_MYSTRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>


class MyString
{
private:
    char* str;
    std::size_t lenght;

public:
    MyString();
    MyString(const char* str);
    ~MyString();
    MyString(const MyString& str);
    MyString& operator= (const MyString& str);
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

    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator== (const char* str) const;
    bool operator<(const MyString &rhs) const;
    bool operator>(const MyString &rhs) const;

    friend std::ostream& operator<< (std::ostream& os, const MyString& str);
    friend std::istream& operator>> (std::istream& is, MyString &str);


};




#endif //HOMEWORK1_MYSTRING_H
