#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#pragma once

class MyString
{
private:
    char* str;
    size_t str_size;

public:
    ///Constructor
    MyString();

    ///Constructor with arguments
    MyString(char* value);

    MyString(const char* value);

    ///Copy-Constructor
    MyString(const MyString& source);

    ///Copy-assignment constructor
    MyString& operator=(const MyString& source);

    char& at(size_t pos);

    const char& at(size_t pos) const;

    char& operator[](size_t pos);

    const char& operator[](size_t pos) const;

    char& front();

    const char& front() const;

    char& back();

    const char& back() const;

    bool empty() const;

    ///Get length of MyString
    size_t size() const;

    void clear();

    void push_back(char c);

    void pop_back();

    MyString& operator+=(char c);

    MyString& operator+=(const MyString& source);

    MyString operator+(char c) const;

    MyString operator+(const MyString& source) const;

    const char* c_str() const;

    bool operator==(const MyString& rhs) const;

    bool operator<(const MyString& rhs) const;


    ///Move constructor
    /*
    MyString(MyString&& source)
    {
        str = source.str;
        source.str = nullptr;
    }*/

    ~MyString()
    {
        delete[] str;
    }

};

#endif // MYSTRING_H_INCLUDED
