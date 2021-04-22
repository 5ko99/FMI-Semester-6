#pragma once

#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>

class MyString {
private:
	char* strPtr;
	size_t length;

public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& str);

	~MyString();

	char& at(std::size_t pos);
	const char& at(std::size_t pos) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	bool empty() const;
	std::size_t size();
	void clear();
	void push_back(char c);
	void pop_back();
	const char* c_str() const;

	char& operator[](std::size_t pos);
	const char& operator[](std::size_t pos) const;
	MyString& operator=(const char* otherstr);
	MyString& operator=(const MyString& otherstr);
	MyString& operator+=(char c);
	MyString& operator+=(const MyString& otherstr);
	MyString operator+(char c) const;
	MyString operator+(const MyString& otherstr) const;
	bool operator==(const MyString& otherstr) const;
	bool operator<(const MyString& otherstr) const;
};