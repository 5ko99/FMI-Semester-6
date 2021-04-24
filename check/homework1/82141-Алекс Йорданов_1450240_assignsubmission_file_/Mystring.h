#ifndef  MYSTRING_H
#define  MYSTRING_H
#include<cstdlib>


class MyString
{
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString &s);
    MyString& operator = (const MyString &s);
    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    char& front() ;
    const char& front() const;
    char& back() ;
    const char& back() const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    void push_back(char c);
    void print();
    void pop_back();
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const ;
    bool operator<(const MyString &rhs) const;

    ~MyString();


private:
    char* str;

};

#endif // MYSTRING_H
