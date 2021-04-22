#include "mystring.h"
#include <iostream>
#include <cassert>  

//Rule of 3
MyString::MyString()
{
   string = nullptr; 
   length = 0;
   allocated = 0;
}

MyString::MyString(const MyString& other)
{
    string = new char [other.length+1];
    
    length = other.length;
    allocated = length + 1; 

    for (size_t i=0; i<length; i++){
        string[i] = other.string[i];
    }
    string[length] = '\0';   
}

MyString::MyString(const char* str)
{
    length = strlen(str);
    
    this->string = new char [length+1];

    for (size_t i=0; i<length; i++){
        string[i] = str[i];
    }
    string[length] = '\0'; 
    allocated = length + 1;
}

MyString& MyString::operator= (const MyString& other)
{
    if (this == &other){
        return *this;
    }
    
    if (this->allocated <= other.length){
        char* newString;
        try {
            newString = new char [other.length+1];
        } catch (const std::exception& e){
            std::cerr << e.what() << std::endl;
            return *this; //strong exception guarantee
        }
        delete [] string;
        string = newString;
        newString = nullptr;
        allocated = other.length + 1;
    }

    this->length = other.length;
    for (size_t i=0; i<length; i++){
        this->string[i] = other.string[i];
    }
    this->string[length] = '\0'; 
    return *this;
}

MyString::~MyString()
{
    delete [] string;
    string = nullptr;
    length = 0;
    allocated = 0;
}

//Other methods
size_t MyString::size()const {return length;}

void MyString::printString() const {std::cout << string << std::endl;}

char& MyString::at(size_t pos) 
{
    if (pos >= length){
        throw std::out_of_range ("Invalid position!");    
    }
    return string[pos];
}

const char& MyString::at(size_t pos) const
{
    if (pos >= length){
        throw std::out_of_range ("Invalid position!"); 
    }
    return string[pos];
}

char& MyString::operator[](size_t pos)
{
    assert(pos < length);
    return at(pos);
}

const char& MyString::operator[](size_t pos) const
{
    assert(pos < length);
    return at(pos);
}

char& MyString::front()
{
    assert(string != nullptr && string[0] != '\0');
    return string[0];
}

const char& MyString::front() const
{
    assert(string != nullptr && string[0] != '\0');
    return string[0];
}

char& MyString::back()
{
    assert(string != nullptr && string[0] != '\0');
    return string [length - 1];
}

const char& MyString::back() const
{
    assert(string != nullptr && string[0] != '\0');
    return string [length - 1];
}

bool MyString::empty() const {return !(length);}

void MyString::clear()
{
    for (size_t i=0; i<length; i++){
        string[i] = '\0';
    }
    length = 0;
}

void MyString::push_back(char c)
{
    //allocated must be always >= length+1
    if (allocated < length + 2){
        char* newString;
        try {
            newString = new char[length+2];
        } catch (const std::exception& e){
            std::cerr << e.what() << std::endl;
            return;
        }
        for (size_t i=0; i<length; i++){
            newString[i] = string[i];
        }
        allocated = length + 2;
        delete [] string;
        string = newString;    
    }
    length++;
    string[length-1] = c;
    string[length] = '\0';
}

void MyString::pop_back()
{
    assert(string != nullptr && string[0] != '\0');
    string[length-1] = '\0';
    length--;
}

MyString& MyString::operator+=(char c)
{
    push_back(c);
    return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
    if (this == &rhs){
        MyString copy(*this);
        return *this += copy;
    }

    //the string after concatenation will have lenght=length+rhs.length
    if (allocated < length + rhs.length + 1){
        char* newString;
        try {
            newString = new char[length + rhs.length + 1];    
        } catch (const std::exception& e){
            std::cerr << "ERROR: Not enough memory to concatenate strings" << std::endl;
            return *this;
        }
        allocated = length + rhs.length + 1;
        for (size_t i=0; i<length; i++){
            newString[i] = string[i];
        }
        newString[length] = '\0';
        delete [] string;
        string = newString;
    }

    for (size_t i=0; i<rhs.size(); i++){
        *this += rhs[i];
    }

    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString result(*this);
    result += c;
    return result;
}

MyString MyString::operator+(const MyString& rhs) const
{
    MyString result(*this);
    result += rhs;
    return result;
}

const char* MyString::c_str() const
{
    char* arr;
    try {
        arr = new char[length+1];
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
    for (size_t i=0; i<length; i++){
        arr[i] = string[i];
    }
    arr[length] = '\0';
    return arr;
}

bool MyString::operator==(const MyString &rhs) const
{
    if (this->length != rhs.length){
        return false;
    }
    for (size_t i=0; i<this->length; i++){
        if (string[i] != rhs[i]){
            return false;
        }
    }
    return true;
}

bool MyString::operator<(const MyString &rhs) const
{
    size_t i=0;
    for (i; string[i] != '\0'; i++){
        if (string[i] > rhs.string[i]){
            return false;
        }
        else if (string[i] < rhs.string[i]){
            return true;
        }
    }
    return (rhs.string[i]);
}

bool MyString::operator>(const MyString &rhs) const
{
    size_t i=0;
    for (i; string[i] != '\0'; i++){
        if (string[i] < rhs.string[i]){
            return false;
        }
        else if (string[i] > rhs.string[i]){
            return true;
        }
    }
    return (string[i]);
}

//Helper Method
size_t MyString::strlen(const char* string) const
{
    if (string == nullptr) {
        return 0;
    }
    size_t len = 0;
    while (*string){
        len++;
        string++;
    }
    return len;
}