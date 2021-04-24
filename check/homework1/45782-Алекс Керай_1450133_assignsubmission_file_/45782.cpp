// 45782.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstring>
#include <cassert>
using namespace std;

class MyString
{
private:
    char* str{};
public:
    MyString() = default;
    MyString(const char* _str)
    {
        str = new char[strlen(_str) + 1];
        strcpy_s(str, strlen(_str) + 1, _str);
    }
    ~MyString()
    {
        delete[]str;
    }
    MyString(const MyString& other)
    {
        str = new char[strlen(other.str) + 1];
        strcpy_s(str, strlen(other.str) + 1, other.str);
    }
    MyString& operator=(const MyString& other)
    {
        delete[]str;
        str = new char[strlen(other.str) + 1];
        strcpy_s(str, strlen(other.str) + 1, other.str);
    }
    char& at(size_t pos)
    {
        int count = strlen(this->str);
        assert(pos - 1 != count);
        return this->str[pos - 1];
    }
    const char& atConst(std::size_t pos)
    {
        int count = strlen(this->str);
        assert(pos-1 != count);
        return this->str[pos-1];
    }
    char& operator[](size_t pos)
    {
        int count = strlen(this->str);
        assert(pos-1 != count);
        return this->str[pos-1];
    }
    char& front()
    {
        return this->str[0];
    }
    const char& front() const
    {
        return this->str[0];
    }
    char& back()
    {
        int count = strlen(this->str);
        return this->str[count-1];
    }
    const char& back() const
    {
        int count = strlen(this->str);
        return this->str[count - 1];
    }
    bool empty() const
    {
        if(strlen(this->str)==0)
        {
            return true;
        }
        else { return false; }
    }
    size_t size() const
    {
        return strlen(this->str);
    }
    void clear()
    {
        char none[1]{'\0'};
        this->str = none;
    }
    void push_back(char c)
    {
        int count = strlen(this->str);
        char* buffer;
        buffer = new char[count+1];
        strcpy_s(buffer, strlen(this->str), this->str);
        buffer[strlen(this->str)] = c;
        buffer[strlen(this->str)+1] = '\0';
        delete[]str;
        str = new char[strlen(this->str) + 1];
        strcpy_s(str, strlen(buffer), buffer);
        delete[]buffer;
    }
    void print()
    {
        int count = strlen(this->str);
        for (int i = 0; i < count; i++)
        {
            cout << this->str[i];
        }
    }
    void pop_back()
    {
        int count = strlen(this->str);
        char* buffer;
        buffer = new char[count-1];
        strcpy_s(buffer, strlen(this->str), this->str);
        buffer[strlen(this->str)] = '\0';
        delete[]str;
        str = new char[strlen(this->str) -1];
        strcpy_s(str, strlen(buffer), buffer);
        delete[]buffer;
    }

};

