#include <iostream>
#include <cstring>
#include <assert.h>
#include "../include/mystring.hpp"


void MyString::extendCapacity(int newCapaciy)
{
    if(newCapaciy <= capacity){ //added in case of misuse of the function
        throw std::invalid_argument("New capacity is smaller than the current one");
    }
    
    char* tmp = new char[newCapaciy];

    strcpy_s(tmp, length+1, string);
    
    if(string != nullptr) delete[] string;
    
    string = tmp;
    capacity = newCapaciy;
}

void MyString::copy(const char* str, int length, int capacity)
{
    if(string == nullptr || this->capacity <= length)
    {
        //modifying the parameter not this->capacity
        capacity += DEFAULT_CAPACITY;   //default capacity is used so that we don't allocate new memory for every added character
        char* tmp = new char[capacity];

        if(string != nullptr) delete[] string;
        
        string = tmp;
        this->capacity = capacity;
    }

    strcpy_s(string, capacity, str);
    this->length = length;
    
}

//helper function
void MyString::validatePos(std::size_t pos) const
{
    if(pos >= length)
    {
        throw std::out_of_range("Pos is out of range");
    }
}

MyString::MyString() 
            : string(nullptr), length(0), capacity(DEFAULT_CAPACITY)   
{
    copy("", length, capacity); //creates a string containing '\0' with default length
}

MyString::MyString(const char* str) 
            : string(nullptr), length(0), capacity(0)
{
    length = strlen(str);
    copy(str, length, length+1);//added 1 for the terminating symbol
}

MyString::MyString(const MyString& other)
{
    copy(other.string, other.length, other.capacity);
}

MyString::~MyString()
{
    if(string != nullptr)
    {
        delete[] string;
    }
}

MyString& MyString::operator=(const char* str)
{
    length = strlen(str);
    copy(str, length, length+1);//added 1 for the terminating symbol

    return *this;
}

MyString& MyString::operator=(const MyString& other)
{
    if(this != &other)
    {
        copy(other.string, other.length, other.capacity);
    }

    return *this;
}

MyString& MyString::operator+=(char c)
{
    push_back(c);
    return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
    int tmpLen = length + rhs.length;

    if(tmpLen + 1 >= capacity)
    {
        //default capacity is added so we don't allocate new memory every time we want to add a char
        extendCapacity(capacity + rhs.length + DEFAULT_CAPACITY); 
    }
    
    strcat_s(string, capacity, rhs.string);
    length = tmpLen;
    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString str(this->string);
    str+=c;
    
    return str;
}

MyString MyString::operator+(const MyString& rhs) const
{
    MyString str(this->string);
    str+=rhs;

    return str;
}

bool MyString::operator<(const MyString &rhs) const
{
    return (strcmp(this->string, rhs.string) < 0);
}

bool MyString::operator>(const MyString &rhs) const
{
    return (strcmp(this->string, rhs.string) > 0);
}

bool MyString::operator==(const MyString &rhs) const
{
    return strcmp(this->string, rhs.string) == 0;
}

bool MyString::operator==(const char* str) const
{
    return strcmp(this->string, str) == 0;
}

char& MyString::operator[](std::size_t pos)
{
    assert(pos>=0 && pos < length);
    return string[pos];
}

const char& MyString::operator[](std::size_t pos) const
{
    assert(pos>=0 && pos < length);
    return string[pos];
}

char& MyString::at(std::size_t pos)
{
    validatePos(pos);
    return string[pos];
}

const char& MyString::at(std::size_t pos) const
{
    validatePos(pos);
    return string[pos];
}

std::size_t MyString::size() const
{
    return length;
}

char& MyString::front()
{
    assert(length > 0);
    return string[0];
}

const char& MyString::front() const
{
    assert(length > 0);
    return string[0];
}

char& MyString::back()
{
    assert(length > 0);
    return string[length-1];
}

const char& MyString::back() const
{
    assert(length > 0);
    return string[length-1];
}

bool MyString::empty() const
{
    return !length;
}

void MyString::clear()
{
    if(string != nullptr)//could have written if(string) but this is easier to read
    {
        string[0] = '\0';   //no need to clear all the elements
        length = 0;
    }
}

void MyString::push_back(char c)
{
    if(length + 1 >= capacity)
    {
        extendCapacity(capacity + DEFAULT_CAPACITY);
    }

    string[length++] = c;
    string[length] = '\0';
}

void MyString::pop_back()
{
    assert(length > 0);
    string[--length] = '\0';
}

const char* MyString::c_str() const
{
    return string;  //string is null-terminated
}