#ifndef MYSTRING_HPP
#define MYSTRING_HPP

#include <assert.h>
#include <cstring>
#include <iostream>

const int MAX_STRING_SIZE = 128;

class MyString {
   private:
    std::size_t sizeOfStr;
    char* string;

   public:
    //! Constructor
    MyString();

    //! Copy constructor
    MyString(const MyString& other);

    //! Copy assignment operator
    MyString& operator=(const MyString& other);

    //! Create new object with string
    MyString(const char* str);

    //! Access symbol by position
    char& at(std::size_t pos);

    //! Access symbol by position for conatant
    const char& at(std::size_t pos) const;

    //! Access symbol by position operator []
    char& operator[](std::size_t pos);

    //! Access symbol by position operator [] for constant
    const char& operator[](std::size_t pos) const;

    //! Access first symbol
    char& front();

    //! Access first symbol for constant
    const char& front() const;

    //! Access last symbol
    char& back();

    //! Access last symbol for constant
    const char& back() const;

    //! Empty string verification
    bool empty() const;

    //! String size
    std::size_t size() const;

    //! Clear the string
    void clear();

    //! Add new symbol in the end
    void push_back(char c);

    //! Remove the last symbol
    void pop_back();

    //! String concatenation with c symbol
    MyString& operator+=(char c);

    //! String concatenation with rhs string
    MyString& operator+=(const MyString& rhs);

    //! Returns string concatenation with c symbol
    MyString operator+(char c) const;

    //! Returns string concatenation with rhs string
    MyString operator+(const MyString& rhs) const;

    //! Returns char array of string
    const char* c_str() const;

    //! Comparing strings operators
    bool operator==(const MyString& rhs) const;
    bool operator<(const MyString& rhs) const;

    //! Destructor
    ~MyString();
};

#endif