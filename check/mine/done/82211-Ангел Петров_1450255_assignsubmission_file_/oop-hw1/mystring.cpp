#include<iostream>
#include<cstring>
#include<cassert>
#include "myString.h"

MyString::MyString () {

    string = new char [4];
    strcpy(string, "N/A");
    setSize();
}

void MyString::setSize() {

    sizeOfString = strlen(string);
}

MyString::MyString (const char* str) {

    string = new char [strlen(str) + 1];
    strcpy (string, str);
    setSize();
}   

MyString::~MyString() {

    delete [] string;
}

MyString::MyString(const MyString& other) {

    string = new char [other.sizeOfString + 1];
    strcpy (string, other.string);
    setSize();
}

MyString& MyString::operator=(const MyString& other) {

    if (this != &other) {

        delete [] string;
        string = new char [other.sizeOfString + 1];
        strcpy (string, other.string);
        setSize();
    }
    return *this;
}

char& MyString::at(std::size_t pos) {

    try {
        if (pos >= sizeOfString) {
            throw std::out_of_range("Inavalid index!");
        }
    }
    catch (const char* e) {
        std::cout << e << std::endl;
    }

    char* el = &string[pos];

    return *el;
}

const char& MyString::at(std::size_t pos) const {

    try {
        if (pos >= sizeOfString) {
            throw std::out_of_range("Inavalid index!");
        }
    }
    catch (const char* e) {
        std::cout << e << std::endl;
    }

    const char* el = &string[pos];

    return *el;
}

char& MyString::operator[](std::size_t pos) {

    assert (pos < sizeOfString);

    char* el = &string[pos];

    return *el;
}

const char& MyString::operator[](std::size_t pos) const {

    assert (pos < sizeOfString);

    const char* el = &string[pos];

    return *el;
}

char& MyString::front() {

    assert (sizeOfString > 0);

    char* el = &string[0];

    return *el;
}

const char& MyString::front() const {

    assert (sizeOfString > 0);

    const char* el = &string[0];

    return *el;
}

char& MyString::back() {

    assert (sizeOfString > 0);
    
    char* el = &string[sizeOfString - 1];

    return *el;
}

const char& MyString::back() const {

    assert (sizeOfString > 0);
    
    const char* el = &string[sizeOfString - 1];

    return *el;
}

bool MyString::empty () const {

    return sizeOfString == 0;
}

std::size_t MyString::size() const {

    return sizeOfString;
}

void MyString::clear () {

    if (string != nullptr) {
        delete [] string;
        string = nullptr;
    }
}

void MyString::push_back (char c) {

    char* buffer = nullptr;
    try {
        buffer = new char (sizeOfString + 2);
    }
    catch (std::bad_alloc& e) {
        std::cout << e.what();
        return;
    }

    strcpy(buffer,string);
    buffer[sizeOfString] = c;
    buffer[sizeOfString + 1] = '\0';
    clear ();
    string = buffer;
    ++sizeOfString;
}

void MyString::pop_back () {

    assert (sizeOfString > 0);

    string[sizeOfString - 1] = '\0';
    --sizeOfString;
}

MyString& MyString::operator+=(char c) {

    push_back(c);

    return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {

    for (int i = 0; i < rhs.sizeOfString; ++i) {
        push_back(rhs[i]);
    }

    return *this;
}

MyString MyString::operator+(char c) const {

    MyString other;
    
    other.string = new char [sizeOfString + 1];
    strcpy(other.string, string);
    other.setSize();
    other.push_back(c);
    
    return other;
}

MyString MyString::operator+(const MyString& rhs) const {

    MyString other;
    
    other.string = new char [sizeOfString];
    strcpy(other.string, string);
    other.setSize();
    for (int i = 0; i < strlen(rhs.string); ++i) {

        other += rhs[i];
    }

    return other;
}

const char* MyString::c_str() const {

    char* other = new char [sizeOfString + 1];

    strcpy(other, string);
    other[sizeOfString + 1] = '\0';

    return other;
}

bool MyString::operator==(const MyString &rhs) const {

    return !strcmp(string, rhs.string) ? true : false;
}

bool MyString::operator<(const MyString &rhs) const {

    return strcmp(string, rhs.string) < 0 ? true : false;
}