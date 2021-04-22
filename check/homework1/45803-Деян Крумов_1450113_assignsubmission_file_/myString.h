#pragma once
#include <cstring>
#include <cassert>
#include <iostream>

class MyString
{
    char* data = nullptr;
    size_t length = 0;

/*
    Allocates memory for char array
    @param size the size of the array
    @exception - if new fails to allocate memory
    @return pointer to the allocated array
*/
    char* memoryAlloc(const size_t &size);

/*
    Only executes if the strings are different, allocates enough memory
    and copies the content of one string to the other
    @param string to be copied
    @exception - if new fails to allocate memory
*/
    void copyFrom(const MyString& other);

public:

    MyString() = default;

/*
    Constructor: Creates new object and copies the contents of str
    @param str string to be copied
    @exception if new faills to allocate memory
    @note due to different problems I had to set the '\0' symbol myself
*/
    MyString(const char* str);

/*
    Copy constuctor: calls copyFrom func
    @param other string to be copied
*/
    MyString(const MyString& other);

/*
    Deletes the old string and calls copyFrom func
    @param other string to be copied
    @note if copyFrom func fails the old data is lost
*/
    MyString& operator=(const MyString& s);

/*
    Access to the element at a certain possition
    @param pos element to be accessed
    @exception out_of_range - if pos is invalid
*/
    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;

/*
    Access to the element at a certain possition 
    @param pos element to be accessed
    @note due to performance the index is not checked if it is in bounds

*/
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;

/*
    Access to the first element in the string
    @note due to performance the index is not checked if it is in bounds
*/
    char& front();
    const char& front() const;

/*
    Access to the last element in the string
    @note due to performance the index is not checked if it is in bounds
*/
    char& back();
    const char& back() const;

/*
    Checks if the string is empty, returns true if data is null and length
    = 0
*/
    bool empty() const;

/*
    Returns the length of the string
    @return length
*/
    std::size_t size() const;

/*
    Deletes all string content and sets it to 0
*/
    void clear();

/*
    Adds a char to the end of the string, allocates an array with + 1 size
    and copies the old sring and char into it, when done frees the old data
    Nandles 2 cases - string is empty - not empty
    Provides strong exception guarantee
    @param char to be inserted
    @exception if new fails to allocate memory
    @note due to different problems I had to set the '\0' symbol myself
*/
    void push_back(char c);

/*
    Calls push_back func
    @param char to be inserted
*/
    MyString& operator+=(char c);

/*
    Removes the last element, reallocates and reduces the length of the str
    @exception if it fails to allocate memory
    @note due to performance the index is not checked if it is in bounds
*/
    void pop_back();

/*
    Concatenates rhs to the end of the string, allocates new memory enough
    for both of them, copies and updates length
    Nandles 2 cases - string is empty - not empty
    Provides Strong exception guarantee
    @param string to be inserted
    @exception if new fails to allocate memory
*/
    MyString& operator+=(const MyString& rhs);

/*
    Returns new string, concatenates a char to the end of the string
    Calls Copy constructor then uses += operator to insert the char
    @param char to be inserted
    @return new class MyString
*/
    MyString operator+(char c) const;

/*
    Returns new string, concatenates other string to the end of the string
    Calls Copy constructor then uses += operator to insert the string
    @param string to be inserted
    @return new class MyString
*/
    MyString operator+(const MyString& rhs) const;

/*
    Returns pointer to a copy of the array of the string
    @exception if new fails to allocate memory
*/
    const char* c_str() const;

/*
    Checks if two strings are equal
*/
    bool operator==(const MyString &rhs) const;

/*
    Compares two strings based on lexicographic order
    The first mismatching element defines which 
    is lexicographically less or greater than the other
    compared element by element, shorter strings are less than longer ones
*/
    bool operator<(const MyString &rhs) const;

    ~MyString();

    char* getData() const;
};