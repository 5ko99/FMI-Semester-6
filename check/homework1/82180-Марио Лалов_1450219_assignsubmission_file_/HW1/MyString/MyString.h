#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>

class MyString
{
private:
    char *string;
    std::size_t lenght;

public:
    MyString();//default constructor
    MyString(const char *str);//parameter constructor
    MyString(const MyString &other);//copy constructor
    char &at(std::size_t pos);//get at position
    const char &at(std::size_t pos) const;//get at position for constant
    char &operator[](std::size_t pos);//get at position operator
    const char &operator[](std::size_t pos) const;//get at position operator for constant
    char &front();//get first letter
    const char &front() const;//get first letter for constant
    char &back();//get last letter
    const char &back() const;//get last letter for constant
    bool empty() const;//check if empty
    std::size_t size() const;//get string lenght
    void clear();//empty string
    void push_back(char c);//add symbol to the back
    void pop_back();//remove last symbol
    MyString &operator=(const MyString &other);//assign another string
    MyString &operator+=(char c);//add symbol to back operator
    MyString &operator+=(MyString &rhs);//concatenate current string with another
    MyString operator+(char c) const;//additon operator for string+char
    MyString operator+(const MyString &rhs) const;//concatenate two strings
    const char *c_str() const;//get string as char*
    bool operator==(const MyString &rhs) const;
    bool operator<(const MyString &rhs) const;
    ~MyString();
};

#endif