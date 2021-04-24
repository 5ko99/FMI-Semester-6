#pragma once
#include <cstddef> //size_t

class  MyString {
private:
	size_t capacity;
	size_t arrSize;
	char* string;

	bool allocateMemory(size_t newCapacity,char* &arr) const;
	void stringCpy(char*& destination, const char* source, const size_t quantity) const;

public:
	MyString();
	MyString(size_t newCapacity);
	MyString(const char* str); //copy str value 
    MyString(const MyString& newString); //Rule of 5 copy
	MyString(MyString&& other) noexcept; //Rule of 5 move
	~MyString(); //Rule of 5 deconstr
	char& at(std::size_t pos);//return element at pos
	const char& at(std::size_t pos) const; //same
	char& front();//first element
	const char& front() const;
	char& back();//last
	const char& back() const;
	bool empty() const;
	std::size_t size() const; //returns size
	void clear();//removes everything in the array
	void push_back(char c);//adds at the end
	void pop_back();//removes last

	MyString& operator=(const MyString& newString);//Rule of 5 copy assignment
	MyString& operator=(MyString&& other) noexcept; //Rule of 5 move assign
	char& operator[](std::size_t pos);
	const char& operator[](std::size_t pos) const;
	MyString& operator+=(char c); //returns *this . Adds c to the end of the array
	MyString& operator+=(const MyString& rhs);//return *this , concat 2 arrays
	MyString operator+(char c) const; //conc array and c , returns new array
	MyString operator+(const MyString& rhs) const; //return new array conc with str
	const char* c_str() const;//returns pointer to an array , that's a copy of ours
	bool operator==(const MyString& rhs) const;
	bool operator==(const char* rhs) const;
	bool operator<(const MyString& rhs) const; //check if our array is < rhs
	bool operator<=(const MyString& rhs) const;
	bool operator>(const MyString& rhs) const; //check if our array is > rhs
	bool operator>=(const MyString& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};
