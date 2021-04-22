#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <cassert>

class MyString
{
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
    ~MyString();

	// check again;
	char& at(std::size_t pos);
	const char& at(std::size_t pos) const;
	// check again
	char& operator[](std::size_t pos);
	const char& operator[](std::size_t pos) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	bool empty() const;
	std::size_t size() const;
	// the same as Free() ?
	void push_back(char c);
	void pop_back();

	MyString& operator+=(char c);
	MyString& operator+=(const MyString& rhs);
	MyString operator+(char c) const;
	MyString operator+(const MyString& rhs) const;

	const char* c_str() const;
	bool operator==(const MyString& rhs) const;
	bool operator<(const MyString& rhs) const;


	char* getStr() const;
	std::size_t getSize() const;
	std::size_t getCapacity() const;

	void setStr(const char* str);



private:
	void Free();
	void expand();


private:
	char* str = nullptr;
	// size is the number of elements in my string
	// capacity is the maximal number of elements my string can contain
	size_t my_size;
	size_t my_capacity;
};


#endif // MYSTRING_H
