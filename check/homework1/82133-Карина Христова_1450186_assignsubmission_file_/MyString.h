#ifndef MYSTRING_H
#define MYSTRING_H
#include <cstddef>

class MyString
{
	char* data;
	size_t length = 0;

public:

	MyString(); //Default constructor
	MyString(const char* str); //Copy constructor
	~MyString(); //Destructor

	char& at(std::size_t pos); //Access to element on position 'pos'. Throws exeption (std::out_of_range.) if there's no such element
	const char& at(std::size_t pos) const; //Same as above but for constants

	char& operator[](std::size_t pos); //Access to element on position 'pos'.
	const char& operator[](std::size_t pos) const; //Same as above but for constants 

	char& front(); //Acess to first element 
	const char& front() const; //Same as above but for constants

	char& back(); //Access to last element
	const char& back() const; //Same as above but for constants

	bool empty() const; //Checks if the string is empty

	std::size_t size() const; //Gets the lenght of the string

	void clear(); //Clears the string 

	void push_back(char c); //Adds the symbol 'c' at the end of the string //STRONG EXCEPTION GUARANTEE

	void pop_back(); //Removes the last element of the string

	MyString& operator+=(char c); //Adds the symbol 'c' at the end of the string //STRONG EXCEPTION GUARANTEE //Returns *this

	MyString& operator+=(const MyString& rhs); //Concatenates the content of str to the current string //STRONG EXCEPTION GUARANTEE //Returns *this

	MyString operator+(char c) const; //Returns a new string which is a result of the concatenation of the current string and the symbol 'c'

	MyString operator+(const MyString& rhs) const; //Returns a new string which is a result of the concatenation of the current string and the rhs string

	const char* c_str() const; //Returns a pointer of a null-terminated array of type char with identical content of that of the string

	bool operator==(const MyString& rhs) const; //Checks if two strings are identical (1:1)

	bool operator<(const MyString& rhs) const; //Check if the current string is lexicografically smaller than thr rhs string

};

#endif MYSTRING_H