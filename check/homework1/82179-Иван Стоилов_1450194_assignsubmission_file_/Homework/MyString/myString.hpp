#ifndef MY_STRING_H
#define MY_STRING_H
#include<iostream>

class MyString
{
private:
    char* string;
    size_t lenght;

public:
    //constructors
    MyString();
    MyString(const char *string);
    ~MyString();

    //copy assignment operator
    MyString& operator=(const MyString &source);

    //access element at specific index operator
    char &operator[](std::size_t pos);
    const char &operator[](std::size_t pos) const;

    //concatenate operators
    MyString &operator+=(char c);
    MyString &operator+=(const MyString &rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString &rhs) const;

    //identity operator
    bool operator==(const MyString &rhs) const;

    //lexicographically compare operator
    bool operator<(const MyString &rhs) const;

    //access element at specific index
    char &at(std::size_t pos);
    const char &at(std::size_t pos) const;

    //access first element
    char &front();
    const char &front() const;

    //access last element
    char &back();
    const char &back() const;

    //check if string is empty
    bool empty() const;

    //retrun string lenght
    std::size_t size() const;

    //clear string
    void clear();

    //add char at last index
    void push_back(char c);

    //remove last element
    void pop_back();

    //return pointer to string in new array
    const char *c_str() const;
};

#endif