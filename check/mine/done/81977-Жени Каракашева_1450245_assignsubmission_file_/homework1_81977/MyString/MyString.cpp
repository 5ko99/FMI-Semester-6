#include<iostream>
#include<cassert>
#include<cstring>
#include<exception>

#include "MyString.h"

void MyString::copy(const MyString& other) {
    sizeString = other.sizeString;
    capacityString = other.capacityString;

    data = new (std::nothrow) char[capacityString]; 
   
    if (data == nullptr) {
        sizeString = 0;
        capacityString = 0;
        data[sizeString] = '\0';
    } else {
        strcpy(data, other.data);
    }
}

void MyString::deleteString() {
    delete [] data;
    data = nullptr;

    sizeString = 0;
    capacityString = 0;
}

MyString::MyString(): data(nullptr), sizeString(0), capacityString(0) {}

MyString::MyString(const char* other): sizeString(strlen(other)), capacityString(sizeString*2) {
    if (sizeString == 0) {
        data = nullptr;
    } else {
        data = new char[capacityString];
        strcpy(data, other);
    }
}
 
MyString::MyString(const MyString& other) {
    copy(other); 
}

MyString& MyString::operator=(const MyString& other) {
    if(this != &other) {
        deleteString();
        copy(other);
    }

    return *this;
}

MyString::~MyString() {
    deleteString();
}

char& MyString::at(std::size_t pos) {
    if (pos < 0 || pos >= sizeString || empty()) {
        throw std::out_of_range("The position is out of range!");
    }
    
    return data[pos];
}

const char& MyString::at(std::size_t pos) const{
    if (pos < 0 || pos >= sizeString || empty()) {
        throw std::out_of_range("The position is out of range!");
    }

    return data[pos];
};

char& MyString::operator[] (std::size_t pos) { 
    assert(pos >= 0 && pos < size());
    return data[pos]; 
}

const char& MyString::operator[] (std::size_t pos) const {
    assert(pos >= 0 && pos < size());
    return data[pos];
}

char& MyString::front() {
    assert(sizeString > 0);
    return at(0);
}

const char& MyString::front() const{
    assert(sizeString == 0);
    return at(0);
}

char& MyString::back() {
    assert(sizeString > 0);
    return at(sizeString-1);
}

const char& MyString::back() const{
    assert(sizeString == 0);
    return at(0);
}

bool MyString::empty() const{
    return sizeString == 0; 
}

std::size_t MyString::size() const{
    return sizeString;
} 

void MyString::push_back(char c) {
    if(capacityString > sizeString + 1) {
        char* newData = new char[sizeString+1];
        strcpy(newData,data);

        newData[sizeString] = c;
        newData[sizeString+1] = 0;
        sizeString++; 

        delete [] data;
        data = newData; 
    } else {
        resize(sizeString+1);

        char* newData = new char[sizeString+1];
        strcpy(newData,data);

        newData[sizeString] = c;
        newData[sizeString+1] = 0;

        sizeString++; 
        delete [] data;
        data = newData;
    }
} 

void MyString::pop_back() {
    assert(sizeString > 0); 

    data[sizeString] = '\0';
    sizeString -= 1;
} 

MyString& MyString::operator+=(char c) {
    MyString temp;
    temp.push_back(c);

    return *this;
}

MyString& MyString::operator += (const MyString& rhs) {
    this->append(rhs);

    return *this;
}

MyString MyString::operator+(char c) const {
    MyString result;
    result.append(data);

    std::size_t length = strlen(result.data);
    result.data[length] = c;
    result.data[length+1] = 0;   
    return result;
}

MyString MyString::operator +(const MyString& rhs) const {
    MyString result(*this);
    result.append(rhs);

    return result;
}

const char* MyString::c_str() const {
    char* newData = new char[sizeString + 1];
    strcpy(newData,data);

    return newData;
}  

bool MyString::operator==(const MyString &rhs) const {
    return strcmp (data, rhs.data) == 0;
}

bool MyString::operator<(const MyString &rhs) const {
    return strcmp (data, rhs.data) < 0;
}

std::size_t MyString::capacity() const{
    return capacityString;
}

void MyString::resize(std::size_t n) {
    if (n < sizeString + 1) {
        sizeString = n;
    }

    capacityString = n;
    char* newData = new char[capacityString];
    strcpy(newData, data);
    delete[] data;
    data = newData;  
}

void MyString::append(const MyString& addEnd) {
    if (capacityString < sizeString + addEnd.sizeString) {
        resize((sizeString+addEnd.sizeString)*2); 
    }

    for(int i = 0; i < addEnd.sizeString; i++) {
        data[i+sizeString] = addEnd.data[i];
    } 
    
    data[sizeString + addEnd.sizeString] = '\0';
    sizeString = sizeString + addEnd.sizeString;
}

std::ostream& operator <<(std::ostream& out, const MyString& element) {
   if (element.sizeString != 0 || element.capacityString != 0) {
        out<< element.data;
    }
    return out;
}