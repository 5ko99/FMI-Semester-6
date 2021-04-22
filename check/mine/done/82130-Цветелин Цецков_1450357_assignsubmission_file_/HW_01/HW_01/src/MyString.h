#pragma once

#include <cstddef>
#include <ostream>
#include <istream>

class MyString
{
public:
	/*
	Constructs an empty string
	*/
	MyString();

	/*
	Constructs a string that has the same charactes as str
	*/
	MyString(const char* str);

	MyString(const MyString& other);

	~MyString();

	MyString& operator=(const MyString& other);

	/*
	Returns the char at the supplied index,
	if it is outside the bounds of the string,
	then an std::out_of_range exception is thrown
	*/
	char& at(std::size_t pos);

	/*
	Returns a constant char at the supplied index,
	if it is outside the bounds of the string,
	then an std::out_of_range exception is thrown
	*/
	const char& at(std::size_t pos) const;

	char& operator[](std::size_t pos);
	const char& operator[](std::size_t pos) const;

	/*
	Returns the char at the front of the string.
	It does NOT check if the string is not empty.
	In debug that check is asserted.
	*/
	char& front();

	/*
	Returns a constant reference to the char at the front of the string.
	It does NOT check if the string is not empty.
	In debug that check is asserted.
	*/
	const char& front() const;

	/*
	Returns the last char of the string.
	It does NOT check if the string is not empty.
	In debug that check is asserted.
	*/
	char& back();

	/*
	Returns a constant reference to the last char of the string.
	It does NOT check if the string is not empty.
	In debug that check is asserted.
	*/
	const char& back() const;

	/*
	Checks if the string is empty:
	MyString().empty() == true
	MyString("").empty() == true
	MyString("Hello World").empty() == false
	*/
	bool empty() const;

	/*
	The size of the string
	MyString().size() == 0
	MyString("").size() == 0
	MyString("abcd").size() == 4
	*/
	std::size_t size() const;

	/*
	Clears the contents of the string
	MyString().clear().empty() == true
	MyString("").clear().empty() == true
	MyString("Hello").clear().empty() == true
	*/
	void clear();

	/*
	Appends the char c at the end of the string
	Has strong exception guarantee
	*/
	void push_back(char c);

	/*
	Removes the last char of the string
	*/
	void pop_back();

	/*
	Appends the char at the end of the string
	Has strong exception guarantee
	Modifies the left-hand-side
	*/
	MyString& operator+=(char c);

	/*
	Appends the string at the end of the string
	Has strong exception guarantee.
	Modifies the left-hand-side
	*/
	MyString& operator+=(const MyString& rhs);

	/*
	Constructs a new string from the current one and appended character
	*/
	MyString operator+(char c) const;

	/*
	Constructs a new string from the current one and appended the other string
	*/
	MyString operator+(const MyString& rhs) const;

	/*
	Returns a null-terminated c-style string
	*/
	const char* c_str() const;

	/*
	Checks if the contents of 2 strings match
	*/
	bool operator==(const MyString &rhs) const;

	/*
	Checks if the contents of 2 strings аре дифферент
	*/
	bool operator!=(const MyString &rhs) const;

	/*
	Compares two strings for lexicographical order
	*/
	bool operator<(const MyString &rhs) const;

	/*
	Casts to a null terminated string
	*/
	operator const char*() const;

	// Although we do not need private access in the operator,
	// Being inside the class makes it a lot more readable and understandable,
	// that it is coupled to this class, specifically
	// This can also be made not to be a friend and use the c_str method
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
	/*
	Expands the raw buffer and copies the data from the old one
	Strong exception guarantee
	*/
	void expandBuffer();

	/*
	Generates the next size, which the buffer should expand to
	*/
	std::size_t expansionFunction(const std::size_t oldSize);
private:
	char* rawStr;
	std::size_t usedSize;
	std::size_t rawSize;
};

/*
Reads to the \n character and puts the contents in the string
*/
std::istream& getline(std::istream & is, MyString & str);
// This function on the other hand is not that tightly coupled to the class
//( at least in my opinion operators are more connected with the class)
// This function just reads from the stream and produces a MyString value
