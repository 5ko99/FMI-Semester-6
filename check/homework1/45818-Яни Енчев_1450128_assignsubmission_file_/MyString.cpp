#include "MyString.h"
#include <cstring>
#include <cassert>
#include <exception>
#include <stdexcept>

MyString::MyString()
{
    this->str = nullptr;
}

MyString::MyString(const MyString& source)
{ 
    if (&source != this)
    {
        CopyDynStr(source.str, this->str);
    }

}

MyString::~MyString()
{
    delete[] this->str;

    // this->str = nullptr;
}

const char* MyString::getStr() const
{
    return this->str;
}

void MyString::setStr(const char* newStr)
{
    //if (newStr)
    //Not checking if the newStr is nullptr, because i want to be able to delete my data if i want to;
    CopyDynStr(newStr, this->str);
}

void CopyDynStr(const char* source, char*& destination) 
{
    if (destination != source)
    {
        if (source == nullptr)
        {
            delete[] destination;
            destination = nullptr;
            return;
        }

        char* temp = createDynString(source); // acquiring strong exception guarantee

        delete[] destination;
        destination = temp;

         
    }
}

char* createDynString(const char* source)
{
    if (source == nullptr)
        return nullptr;

    std::size_t sourceLen = strlen(source);

    if (sourceLen == 0) // to make sure we can't make a string with only a terminating zero in it
        return nullptr;

    char* dynString = new char[sourceLen + 1];

    for (std::size_t i = 0; i < sourceLen; i++)
    {
        dynString[i] = source[i];
    }

    dynString[sourceLen] = 0;
    return dynString;
}


MyString& MyString::operator= (const MyString& source)
{
    if (this == &source)
        return *this;

  //  if (source.str)
        CopyDynStr(source.str, this->str);

   /* else
    {
        delete[] this->str;
        this->str = nullptr;
    }*/

    return *this;
}

MyString::MyString(const char* str)
{
    // if (str) - this is already made in the function CopyDynStr
    CopyDynStr(str, this->str);
}

char& MyString::at(std::size_t pos)
{
    std::size_t lenString = strlen(this->str);

    if (pos > lenString)
        throw std::out_of_range("Position wanted is outside the array");

    else return this->str[pos]; // dosta vuprosi tuk... * vs & kato return
    // value na function. exceptionite
}

const char& MyString::at(std::size_t pos) const
{
    std::size_t lenString; // kato e definirana v if-a ili v elsa, ne se vijda izvun skopa im

    if (this->str == nullptr)
        lenString = 0;

    else
        lenString = strlen(this->str);
    
    if (pos > lenString)
        throw std::out_of_range("Position wanted is outside the array");

    else return this->str[pos];
}

char& MyString::front()
{
    assert(this->str != nullptr); // tova podsigurqva li che ne e prazen
    return *(this->str);
}

const char& MyString::front() const
{
    assert(this->str != nullptr);
    return *(this->str);
}

char& MyString::back()
{
    assert(this->str != nullptr);

    std::size_t lenString = strlen(this->str);
    return this->str[lenString - 1];
}

const char& MyString::back() const
{
    assert(this->str != nullptr);
    
    std::size_t lenString = strlen(this->str);
    return this->str[lenString - 1];
}

bool MyString::empty() const
{
    if (this->str == nullptr) // with my realization of the code, there can't be a string with only a terminating
        // zero in it. There are either characters or the string is nullptr 
        return true;
    return false;
}

std::size_t MyString::size() const
{
    if (this->str == nullptr)
        return 0;

    return strlen(this->str);
}

void MyString::clear()
{
    delete[] this->str;
    this->str = nullptr;
}

void MyString::push_back(char c)
{
    if (c == 0)
        return;

    std::size_t lenString;
    if (this->str == nullptr)
        lenString = 0;
    else
        lenString = strlen(this->str);

    char* tempStr = new char[lenString + 2];

    for (std::size_t i = 0; i < lenString; i++)
        tempStr[i] = this->str[i];

    tempStr[lenString] = c;
    tempStr[lenString + 1] = 0;
    delete[] this->str;
    this->str = tempStr;


}

void MyString::pop_back()
{
    assert(!this->empty());

    std::size_t lenString = strlen(this->str);
    lenString--;

    if (lenString == 0)
    {
        this->str = nullptr;
        return;
    }

    char* tempArr = new(std::nothrow) char[lenString + 1];

    if (tempArr == nullptr)
        return;

    for (std::size_t i = 0; i < lenString; i++)
        tempArr[i] = this->str[i];

    tempArr[lenString] = 0;

    delete[] this->str;
    this->str = tempArr;
}

const char* MyString::c_str() const
{
    char* newString = createDynString(this->str);

    return newString;
}

char& MyString::operator[](std::size_t pos)
{
    assert(this->str != nullptr);
    std::size_t lenString = strlen(this->str);

    assert(lenString > pos);
    return this->str[pos];
}

const char& MyString::operator[](std::size_t pos) const
{
    assert(this->str != nullptr);
    std::size_t lenString = strlen(this->str);

    assert(lenString > pos);
    return this->str[pos];
}

MyString& MyString::operator+=(char c)
{
    this->push_back(c);
    return *this; 
}

MyString& MyString::operator+=(const MyString& rhs)
{
    if (rhs.str == nullptr)
        return *this; 

    if (this->str == nullptr)
    {
        MyString resString = rhs;
        return resString; // kato return-na taka tq se kopira po stojnost nali taka. taka bi trqbvalo, mislq si
    }


    std::size_t lenThis = strlen(this->str);

    //for (std::size_t i = 0; i < lenString; i++)
    //    this->str += rhs.str[i];
    // this would be too many useless operations done. allocating the memory one by one

    std::size_t lenRes = strlen(rhs.str) + lenThis;

    MyString Res;

    Res.str = new char[lenRes + 1];
    for (std::size_t i = 0; i < lenThis; i++)
        Res.str[i] = this->str[i];

    for (std::size_t i = lenThis; i < lenRes; i++)
        Res.str[i] = rhs.str[i];

    Res.str[lenRes] = 0;
    return Res;
}

MyString MyString::operator+(char c) const
{
    MyString newString = *this;
    newString += c;
    return newString;
}

MyString MyString::operator+(const MyString& rhs) const
{
    MyString newString = *this;
    newString += rhs;
    return newString;
}

bool MyString::operator==(const MyString& rhs) const
{
    if (this == &rhs)
        return true;

    if (rhs.str == nullptr) 
    {
        if (this->str == nullptr)
            return true;

        return false;
    }

    if (this->str == nullptr)
        return false; // if we're at this point of the code, we know rhs isn't a nullpointer

    std::size_t lenStringRhs = strlen(rhs.str); 
    std::size_t lenStringThis = strlen((*this).str);

    if (lenStringThis != lenStringRhs)
        return false;

    for (std::size_t i = 0; i < lenStringThis; i++)
        if (rhs.str[i] != this->str[i])
            return false;

    return true;
}

bool MyString::operator<(const MyString& rhs) const
{
    if (this == &rhs)
        return false;

    if (rhs.str == nullptr) 
    {
        if (this->str == nullptr)
            return false;

        return false;
    }

    if (this->str == nullptr) // not just this but this->str
        return true;

    std::size_t lenStringThis = strlen(this->str);
    std::size_t lenStringRhs = strlen(rhs.str);

    std::size_t smallerLen = lenStringRhs < lenStringThis ? lenStringRhs : lenStringThis;

    for (std::size_t i = 0; i < smallerLen; i++)
    {
        if (rhs.str[i] > this->str[i])
            return true;

        if (rhs.str[i] < this->str[i])
            return false;
    }
    return false;
}
