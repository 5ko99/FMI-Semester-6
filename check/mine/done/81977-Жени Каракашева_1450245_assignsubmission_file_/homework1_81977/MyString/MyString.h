#ifndef __MYSTRING_HH__
#define __MYSTRING_HH__
#include<iostream>
#include<cstring>

class MyString {
    char* data; //the string itself
    std::size_t sizeString; //the size of the string
    std::size_t capacityString; //the capacity of the string

    //private methods which have a helping role
    void copy(const MyString& other); //a function for copying a string
    void deleteString(); //a function for deleting a string
    void resize(std::size_t); //a function for resizing a string
    
    public:
    friend std::ostream& operator <<(std::ostream&, const MyString&); //serialization

    MyString(); //a default constructor 
    MyString(const char* str); //creates a new object and copies the data from str
    MyString(const MyString& other); //copy constructor
    MyString& operator =(const MyString& other); //operator =
    ~MyString(); //destructor

    //required methods and predefined operators
    char& at(std::size_t pos); //access to the element at pos, throws an exception if pos is invalid
    const char& at(std::size_t pos) const; //the same as at() but for const objects
    char& operator[] (std::size_t pos); //access to the element at pos without check for a correct position
    const char& operator[] (std::size_t) const; //the same as operator [] but for const objects
    char& front(); //access to the first element of the string without check for existence of such an element
    const char& front() const; //the same as front() but for const objects
    char& back(); //access to the last element of the string without check for existence of such an element
    const char& back() const; //the same as back() but for const objects
    bool empty() const; //checks if a string is empty
    std::size_t size() const; //returns the length of the string
    void push_back(char c); //adds an element at the back of the string
    void pop_back(); //removes the last element of the string without check for existence of such an element
    MyString& operator+=(char c); 
    MyString& operator += (const MyString& rhs); //concats the str to the current string
    MyString operator+(char c) const; //returns a new string which is made from the current one concat with c
    MyString operator +(const MyString& rhs) const; //returns a new string which is made from the current one concat with rhs
    const char* c_str() const; //returns a pointer to a null-terminated char array with the same content as the string
    bool operator==(const MyString &rhs) const; //checks if two strings are identical
    bool operator<(const MyString &rhs) const; //checks if the current string is before rhs lexicographically

    void append(const MyString&); //a helping function for some of the required methods
    std::size_t capacity() const; //a selector for the capacity
};

#endif