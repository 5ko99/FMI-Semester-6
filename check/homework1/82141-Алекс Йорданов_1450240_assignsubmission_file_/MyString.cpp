#include "MyString.h"
#include <cstdlib>
#include <stdexcept>
#include <cstring>
#include <cassert>
#include <iostream>


MyString::MyString()
{
    this->str = new char[1];
    str[0]='\0';
}

MyString::MyString(const char* str)
{
    this->str = new char[strlen(str)+1];
    memcpy(this->str, str,strlen(str) + 1);
}
MyString::MyString(const MyString &s)
{
    str=nullptr;
    *this=s;
}

MyString& MyString::operator = (const MyString &s)
{

    delete[] str;
    this->str = new char[strlen(s.str)+1];
    memcpy(this->str,s.str, strlen(s.str) + 1);
    return *this;

}


char& MyString::at(std::size_t pos)
{
    if (pos>=strlen(str)) throw std::out_of_range("out of range");
    return str[pos];
}


const char& MyString::at(std::size_t pos) const
{
    if (pos>=strlen(str)) throw std::out_of_range("out of range");
    return str[pos];
}

char&  MyString::operator[](std::size_t pos)
{
    return at(pos);
}

const char& MyString::operator[](std::size_t pos) const
{
    return at(pos);
}

char&  MyString::front()
{
    return at(0);
}

const char& MyString::front() const
{
    return at(0);
}

char&  MyString::back()
{
    assert(strlen(str));
    return at(strlen(str)-1);
}

const char& MyString::back() const
{
    assert(strlen(str));
    return at(strlen(str)-1);
}
bool MyString::empty() const
{
    return strlen(str)==0;
}
std::size_t MyString::size() const
{
    return strlen(str);
}
void MyString::clear()
{
    *this=MyString("");
}
void MyString::push_back(char c)
{
    char* t=new char[strlen(str)+2];
    strcpy_s(t, strlen(str) + 2, str);
    delete[] str;
    str=t;
    str[strlen(str)]=c;
    str[strlen(str)+1]='\0';

}
void MyString::print()
{
    std::cout<<str<<std::endl;
}
void MyString::pop_back()
{
    assert(strlen(str));
    char* t=new char[strlen(str)];
    memcpy(t, str,strlen(str)-1);
    t[strlen(str)-1]=0;
    delete[] str;
    str=t;
}
MyString& MyString::operator+=(char c)
{
    push_back(c);
    return *this;
}
MyString& MyString::operator+=(const MyString& rhs)
{
    size_t size=strlen(str)+strlen(rhs.str);
    char* t=new char[size+1];
    memcpy(t,str,strlen(str));
    t[strlen(str)]='\0';
    strcat(t,rhs.str);
    delete[] str;
    str=t;
    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString s(*this);
    s+=c;
    return s;
}
MyString MyString::operator+(const MyString& rhs) const
{
    MyString s(*this);
    s+=rhs;
    return s;
}
const char* MyString::c_str() const
{
    return str;
}
bool MyString::operator==(const MyString &rhs) const
{
    return strcmp(str,rhs.str)==0;
}
bool MyString::operator<(const MyString &rhs) const
{
    return strcmp(str,rhs.str)<0;
}

MyString::~MyString()
{
    delete[] str;
}


