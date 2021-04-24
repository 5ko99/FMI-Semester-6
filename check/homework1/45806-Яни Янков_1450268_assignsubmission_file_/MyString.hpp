#pragma once
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

class MyString {
private:
	char* string=nullptr;
	unsigned lenght=0;
	unsigned capacity=0;
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& copy) noexcept;
	void resize();
	MyString& operator=(const MyString& copy) noexcept;
	char& at(size_t pos);
	const char& at(size_t pos) const;
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	bool empty() const;
	size_t size() const;
	void clear();
	void push_back(char c);
	void pop_back();
	MyString& operator+=(char c);
	MyString& operator+=(const MyString& rhs);
	MyString operator+(char c) const;
	MyString operator+(const MyString& rhs) const;
	const char* c_str() const;
	bool operator==(const MyString& rhs) const;
	bool operator<(const MyString& rhs) const;
	const char* get_string() const;
	unsigned get_lenght() const;
	unsigned get_capacity() const;
	
	~MyString();//destructor
};