#pragma once
#include <cstddef>

// This implementation doesn't allow a string to have only a termination zero in it
// and makes that a nullptr instead
// Doesn't give access to the terminating zero through the function 'at' and through
// the operator '[]'

class MyString {
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& source); // the & is important to avoid
    // the recursion with the copy constructors
    ~MyString();
    MyString& operator= (const MyString& source); // evala tuk ne bqh slojil ampersanta i mi davashe greshka sumati vreme
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;
    bool operator==(const MyString& rhs) const;
    bool operator<(const MyString& rhs) const;

    const char* getStr() const;
    void setStr(const char* newStr);
    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    void push_back(char c);
    void pop_back();
    const char* c_str() const;


private:
    char* str;
};

void CopyDynStr(const char* source, char*& destination);
char* createDynString(const char* source);