#include "Headers/MyString.hpp"

#include <assert.h>

#include <cstring>
#include <iostream>

//! Constructor
MyString::MyString() {
    string = nullptr;
    sizeOfStr = 0;
}

//! Copy constructor
MyString::MyString(const MyString& other) {
    std::size_t length = strlen(other.string) + 1;
    try {
        string = new char[length];
    } catch (std::bad_alloc& e) {
        throw;
    }
    for (size_t i = 0; i <= other.sizeOfStr; i++) {
        string[i] = other.string[i];
    }
    sizeOfStr = strlen(other.string);
}

//! Copy assignment operator
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        std::size_t length = strlen(other.string) + 1;
        try {
            string = new char[length];
        } catch (std::bad_alloc& e) {
            throw;
        }
        for (size_t i = 0; i <= other.sizeOfStr; i++) {
            string[i] = other.string[i];
        }
        sizeOfStr = strlen(other.string);
    }
    return *this;
}

//! Create new object with string
MyString::MyString(const char* str) {
    std::size_t length = strlen(str) + 1;
    try {
        string = new char[length];
    } catch (std::bad_alloc& e) {
        throw;
    }
    sizeOfStr = length - 1;
    strcpy(string, str);
}

//! Access symbol by position
char& MyString::at(std::size_t pos) {
    if (pos < 0 || pos >= sizeOfStr) {
        throw std::out_of_range("Out of range! Error of class MyString!");
    } else {
        return string[pos];
    }
}

//! Access symbol by position for conatant type
const char& MyString::at(std::size_t pos) const {
    if (pos < 0 || pos >= sizeOfStr) {
        throw std::out_of_range("Out of range! Error of class MyString!");
    } else {
        return string[pos];
    }
}

//! Access symbol by position operator []
char& MyString::operator[](std::size_t pos) {
    assert(pos >= 0 && pos < sizeOfStr);
    return string[pos];
}

//! Access symbol by position operator [] for constant
const char& MyString::operator[](std::size_t pos) const {
    assert(pos >= 0 && pos < sizeOfStr);
    return string[pos];
}

//! Access first symbol
char& MyString::front() {
    assert(sizeOfStr > 0 && string != nullptr);
    return string[0];
}

//! Access first symbol for constant
const char& MyString::front() const {
    assert(sizeOfStr > 0 && string != nullptr);
    return string[0];
}

//! Access last symbol
char& MyString::back() {
    assert(sizeOfStr > 0 && string != nullptr);
    return string[sizeOfStr - 1];
}

//! Access last symbol for constant
const char& MyString::back() const {
    assert(sizeOfStr > 0 && string != nullptr);
    return string[sizeOfStr - 1];
}

//! Empty string verification
bool MyString::empty() const { return (string == nullptr || sizeOfStr == 0); }

//! String size
std::size_t MyString::size() const { return sizeOfStr; }

//! Clear the string
void MyString::clear() {
    for (std::size_t i = 0; i < sizeOfStr; i++) {
        string[i] = ' ';  //! Filling the string with spaces
    }
}

//! Add element in the end
void MyString::push_back(char c) {
    char* newStr = nullptr;
    try {
        newStr = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        throw;
    }
    strcpy(newStr, string);
    delete[] string;
    ++sizeOfStr;
    try {
        string = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        delete[] newStr;
        throw;
    }
    strcpy(string, newStr);
    string[sizeOfStr - 1] = c;
    string[sizeOfStr] = '\0';
    delete[] newStr;
}

//! Remove the last symbol
void MyString::pop_back() {
    assert(sizeOfStr > 0 && string != nullptr);
    char* newStr = nullptr;
    try {
        newStr = new char[sizeOfStr];
    } catch (std::bad_alloc& e) {
        throw;
    }
    for (int i = 0; i < sizeOfStr; i++) {
        newStr[i] = string[i];
    }
    delete[] string;
    --sizeOfStr;
    try {
        string = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        delete[] newStr;
        throw;
    }
    strcpy(string, newStr);
    string[sizeOfStr] = '\0';
    delete[] newStr;
}

//! String concatenation with c symbol
MyString& MyString::operator+=(char c) {
    char* newStr = nullptr;
    try {
        newStr = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        throw;
    }
    strcpy(newStr, string);
    delete[] string;
    ++sizeOfStr;
    try {
        string = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        delete[] newStr;
        throw;
    }
    strcpy(string, newStr);
    string[sizeOfStr - 1] = c;
    string[sizeOfStr] = '\0';
    delete[] newStr;
    return *this;
}

//! String concatenation with rhs string
MyString& MyString::operator+=(const MyString& rhs) {
    char* newStr = nullptr;
    try {
        newStr = new char[sizeOfStr + 1];
    } catch (std::bad_alloc& e) {
        throw;
    }
    strcpy(newStr, string);
    delete[] string;
    try {
        string = new char[sizeOfStr + rhs.size() + 1];
    } catch (std::bad_alloc& e) {
        delete[] newStr;
        throw;
    }
    strcpy(string, newStr);
    for (size_t i = 0; i < rhs.size(); i++) {
        string[sizeOfStr + i] = rhs[i];
    }
    sizeOfStr += rhs.size();
    string[sizeOfStr] = '\0';
    delete[] newStr;
    return *this;
}

//! Returns string concatenation with c symbol
MyString MyString::operator+(char c) const {
    MyString newMyString(string);
    newMyString += c;
    return newMyString;
}

//! Returns string concatenation with rhs string
MyString MyString::operator+(const MyString& rhs) const {
    MyString newMyString(string);
    newMyString += rhs;
    return newMyString;
}

//! Returns char array of string
const char* MyString::c_str() const { return string; }

//! Comparing strings operators
bool MyString::operator==(const MyString& rhs) const {
    bool flag = false;
    if (sizeOfStr == rhs.size()) {
        flag = true;
        for (unsigned int i = 0; i < sizeOfStr; i++) {
            if (string[i] != rhs[i]) {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool MyString::operator<(const MyString& rhs) const {
    bool flag = false;
    if (sizeOfStr < rhs.size()) {
        flag = true;
    } else {
        if (sizeOfStr == rhs.size()) {
            for (unsigned int i = 0; i < sizeOfStr; i++) {
                if (string[i] < rhs[i]) {
                    flag = true;
                    break;
                }
            }
        }
    }
    return flag;
}

// Destructor
MyString::~MyString() {
    delete[] string;
    string = nullptr;
    sizeOfStr = 0;
}