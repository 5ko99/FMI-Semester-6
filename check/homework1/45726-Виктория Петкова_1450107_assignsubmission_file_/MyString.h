#pragma once
#include<iostream>
#include<cstring>

using namespace std;

class MyString
{
private:
	char* str;

public:
	MyString();
	MyString(const char*);
	MyString& operator=(const MyString& other);
	MyString(const MyString& src);
	~MyString() { clear(); }
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

};

