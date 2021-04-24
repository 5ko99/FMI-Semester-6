// #ifdef NDEBUG
// #define assert(condition) ((void)0)
// #else
// #define assert(condition) /*implementation defined*/
// #endif


#include <cstring>
#include <iostream>
#include <cassert>
#pragma once
class String
{
private:
    ///Array of characters. Dynamically allocated.
    char *characters;

    ///How long is the string
    std::size_t length;

    ///How long is the array in the memory
    std::size_t memSize;

    ///Copy with given String
    void copy(const String &other);

    ///Free the memory and erase the characters array
    void erase();

    ///Check if the length is more than the size.
    void checkLenght();

public:
    ///Default constructor
    String();

    ///Constructor which gets another object of the class String
    String(const String &other);

    ///Overload of the operator =
    String &operator=(const String &other);

    ///Creates a new object and copies the contents of str.
    String(const char *chars);

    ///Deconstructor
    ~String();

    ///Adds a character to the end of the String.
    ///Operation must give strong exception guarantee.
    void push_back(const char character);

    ///Removes the last character of the String.
    void pop_back();

    ///Removes the last N characters of the String. @param n How many characters to remove.
    char &front();

    ///Like front() but for constantsa
    const char &front() const;

    ///Access the last character in the string.
    char &back();

    ///Like back() but for constants
    const char &back() const;

    ///Check if the string is empty.
    bool empty() const;

    ///Returns the lenght of the String.
    std::size_t size() const;

    ///Operator which returns the combination of two Strings.
    String operator+(const String &other) const;

    ///Returns a new string which is combination of the current + the new char
    String operator+(char c) const;

    ///Operator which combines two Strings and writes it to the String at the left.
    String &operator+=(const String &other);

    ///Operator which adds a char to the end of the array
    ///Gives strong exception guarantee
    ///Returns *this
    String &operator+=(char c);

    ///Operator which checks if the two Strings are identical.
    bool operator==(const String &other) const;

    ///Check if the current string is shorter than the other
    bool operator<(const String &other) const;

    ///Access to the item located in position pos.
    ///The function should not check for correctness if pos is a valid position.
    ///(In debug mode, assert whether pos is a valid position).
    char &operator[](std::size_t pos);

    ///Like operator[] but for constants.
    const char &operator[](std::size_t pos) const;

    ///Access to the element located in position pos.
    ///If not, throw an exception std :: out_of_range.
    char &at(std::size_t pos);

    ///Like at() but for constants.
    const char &at(std::size_t pos) const;

    ///Clear the array. Default set to ""
    void clear();

    ///Returns pointer to null-terminated char[],
    ///which has a copy of the current string.
    const char *c_str() const;

    ///print the string
    void print();
};
