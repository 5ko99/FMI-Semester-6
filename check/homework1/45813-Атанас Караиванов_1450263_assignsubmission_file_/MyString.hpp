#pragma once
#include <iostream>
using namespace std;

class MyString {
private:
	char* data;

	void del();
	void copyFrom(const char* other_str);

public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& oldString);
	MyString& operator=(const MyString& other);
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
	~MyString();
};