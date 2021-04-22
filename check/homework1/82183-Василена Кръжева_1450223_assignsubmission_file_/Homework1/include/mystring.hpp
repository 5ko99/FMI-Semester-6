#ifndef MYSTRING_H
#define MYSTRING_H

//the smallest library(that i found) that includes size_t
#include <cstddef>

/**
* \brief Class for working with strings;
* \author V. Krazheva
*/

class MyString
{
private:
    char* string;   //!< stores a pointer to the string
    int length;     //!< stores the length of the string
    int capacity;   //!< stores the capacity of the string

    ///delete the current content and copy the new one
	void copy(const char* string, int length, int capacity);

    ///extends the current capacity of the string, the information stored remains the same
    void extendCapacity(int newCapaciy);

    //! Function for validating a position in the string
    void validatePos(std::size_t pos) const;
public:
    static const size_t DEFAULT_CAPACITY = 10;

    ///Default constructor for creatind a MyString
    MyString();

    ///Constructor for creating a MyString object with initial values
    MyString(const char* str);

    ///Constructor creating a copy of the object other
    MyString(const MyString& other);

    ///Destructor
    ~MyString();

    /**
     * Overloads operator=.
     * Works in a similar way as the constructor taking char*
     * 
     * @see MyString(const char* str)
     * @param str contains the string to be copied
     * @return Returns a pointer to the MyString object
     */
    MyString& operator=(const char* str);

    /**
     * Overloads operator=.
     * Assings the values of the other object
     * 
     * @param other is the object whose values we are assigning to our object
     * @return Returns a pointer to the MyString object
     */
    MyString& operator=(const MyString& other);

    /**
     * Overloads operator+=.
     * Takes a char and appends it to the end of the string
     * 
     * @param c is the parameter that is appended
     * @return Returns a pointer to the MyString object
     */
    MyString& operator+=(char c);

    /**
     * Overloads operator+=
     * @param rhs is appended to the end of the string
     * @return Returns a pointer to the MyString object
     * @exceptsafe The arguments are unchanged in the event of an exception.
     */
    MyString& operator+=(const MyString& rhs);

    /**
     * Overloads operator +=
     * @param a is appended to the end of the string
     * @return Returns a new MyString containing a copy of the current string with the appended char
     */
    MyString operator+(char c) const;
    
    /**
     * Overloads operator+
     * @param rhs is appended to the end of the string
     * @return Returns a new MyString containing a copy of the current one with the appended string
     */
    MyString operator+(const MyString& rhs) const;

    /**
     * Overloads operator==
     * Compares two strings
     * @return Returns true if the strings are equal and false if the strings are different 
     */
    bool operator==(const MyString &rhs) const;

    /**
     * Overloads operator==
     * Compares string and const char*
     * @return Returns true if the strings are equal and false if the strings are different 
     */
    bool operator==(const char* str) const;

    /**
     * Overloads operator<
     * Compares two strings lexicographically 
     * @return Returns true if rhs is larger and false otherwise
     */
    bool operator<(const MyString &rhs) const;

    /**
     * Overloads operator>
     * Compares two strings lexicographically 
     * @return Returns true if rhs is smaller and false otherwise
     */
    bool operator>(const MyString &rhs) const;

    /**
     * Overloads operator[]
     * Provides access to the element on position pos.
     * @param pos the position of the char
     * @return Returns a reference to the char at pos
     */
    char& operator[](std::size_t pos);

    ///Returns a const reference to the char at pos
    const char& operator[](std::size_t pos) const;

    ///reference to the char on position pos
    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;

    ///reference to the first element of the string
    char& front();
    const char& front() const;

    ///reference to the last element of the string
    char& back();
    const char& back() const;

    ///checks whether the string is empty
    bool empty() const;

    ///gets the size of the string
    std::size_t size() const;

    ///clears the content of the string
    void clear();

    ///appends a char to the end of the string, strong exception guarantee
    void push_back(char c);

    ///removes the last element of the string
    void pop_back();

    ///returns a pointer to null-terminated char array with the same content as the string
    const char* c_str() const;
};

#endif