#include "MyString.h"
#include <cstring>
#include <assert.h>

MyString::MyString(): str(nullptr)
{
    str = new char[1];
    str[0] = '\0';
}

MyString::MyString(const char* newStr)
{
    if (newStr == nullptr)
    {
        this->str = new char[1];
        this->str[0] = '\0';
    }
    else
    {
        str = new char[strlen(newStr) + 1];
        strcpy(this->str, newStr);
        str[strlen(newStr)] = '\0';
    }
}

MyString::MyString(const MyString& source)
{
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
}

char* MyString::getString()
{
    return str;
}

MyString::~MyString()
{
    delete str;
}

char& MyString::at(std::size_t pos){

    if(strlen(str) > pos)
    {
        return str[pos];
    }

    throw std::out_of_range("index out of range");
}

const char& MyString::at(std::size_t pos) const
{
    if(strlen(str) > pos)
    {
        const char a = str[pos];
        return a;
    }

    throw std::out_of_range("index out of range");
}

char& MyString::operator[](std::size_t pos)
{
    bool exceptionThrown = false;

    try
    {
        at(pos);
    }
    catch(std::out_of_range&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    return at(pos);
}

const char& MyString::operator[](std::size_t pos) const
{
    const char a = at(pos);
    return a;
}

char& MyString::front()
{
    if (str && !str[0])
    {
        throw std::out_of_range("No first element");
    }
    else
    {
        return str[0];
    }
}

const char& MyString::front() const
{
    const char a = front();
    return a;
}

char& MyString::back()
{
    bool emptyString = false;
    if (str && !str[std::strlen(str) - 1])
    {
        emptyString = true;
        throw std::out_of_range("No last element");
    }
    else
    {
        return str[std::strlen(str) - 1];
    }
}

const char& MyString::back() const
{
    const char a = back();
    return a;
}



bool MyString::empty() const
{
    return str && !str[0];
}

std::size_t MyString::size() const
{
    size_t size = std::strlen(str);
    return size;
}

void MyString::clear()
{
    delete[] str;
    str = nullptr;
}

void MyString::push_back(char c)
{
    char* safetyStr = new char[strlen(str) + 1];

    if(str != nullptr)
    {
        strcpy(safetyStr, str);
    }
    try
    {
        int size = strlen(safetyStr);
        delete[] str;
        str = new char[size + 2];
        strcpy(str, safetyStr);
        str[size] = c;
        str[size+1] = '\0';
    }
    catch (...)
    {
        str = safetyStr;
    }
}

void MyString::pop_back() {
    if(!empty()) {
        str[strlen(str)-1] = '\0';
    }
}

MyString& MyString::operator+=(char c){
    push_back(c);
    return *this;
}

MyString& MyString::operator+=(MyString& hello){
    for(size_t i = 0; i < hello.size(); i++) {
           push_back(hello.at(i));
    }
    return *this;
}

MyString MyString::operator+(char c) const{
    MyString newString(this->str);
    newString.push_back(c);
    return newString;
}

/*MyString MyString::operator+(const MyString& rhs) const{
    MyString* newObj = new MyString(str);
    for(size_t i = 0; i < rhs.size(); i++) {
           newObj->push_back(rhs.at(i));
    }
    return *newObj;
}
*/

const char* MyString::c_str() const {
    char* returner = new char[size()+1];
    returner[size()] = '\0';
    return returner;
}

bool MyString::operator==(const MyString &rhs) const{
    if(size() != rhs.size()) {
        return false;
    }

    for(int i = 0 ; i < size(); i++) {
        if(str[i] != rhs.at(i))
            return false;
    }
    return true;
}

 bool MyString::operator<(const MyString &rhs) const{
     for(int i = 0; i < size(); i++) {
        if(str[i] > rhs.at(i)){
            return false;
        }
     }

     return size() < rhs.size();
 }



