#include "MyString.hpp"

#include <cstring>
#include <iostream>

MyString::MyString() {

}

MyString::MyString(const char* str) {
	this->str = (char*)str;
}

char& MyString::at(std::size_t pos) {
	std::size_t n = this->size();
	if (pos < 0 || pos >= n) {
		throw std::out_of_range("The given position is out of the range of this string!");
	}

	return this->str[pos];
}

const char& MyString::at(std::size_t pos) const {
	std::size_t n = this->size();

	if (pos < 0 || pos >= n) {
		throw std::out_of_range("The given position is out of the range of this string!");
	}

	return this->str[pos];
}

char& MyString::operator[](std::size_t pos) {
	return this->str[pos];
}

const char& MyString::operator[](std::size_t pos) const {
	return this->str[pos];
}

char& MyString::front() {
	return this->str[0];
}

const char& MyString::front() const {
	return this->str[0];
}

char& MyString::back() {
	std::size_t n = this->size();
	return this->str[n-1];
}

const char& MyString::back() const {
	std::size_t n = this->size();
	return this->str[n - 1];
}

bool MyString::empty() const {
	if (this->str == 0 || this->size() == 0) {
		return true;
	}

	return false;
}

std::size_t MyString::size() const {
	if (this->str == 0 || str == "") {
		return 0;
	}
	return 	std::strlen(this->str);
}

void MyString::clear() {
	this->str = 0;
}

void MyString::push_back(char c) {
	try 
	{
		std::size_t n = this->size();
		const std::size_t size = n + 2;
		char* newStr = new char[size];

		for (int i = 0; i < n; i++) {
			newStr[i] = this->str[i];
		}

		newStr[n] = c;
		newStr[n + 1] = '\0';
		this->str = newStr;
	}
	catch(...)
	{
		throw std::out_of_range("Exception has been thrown!");
	}
}

void MyString::pop_back() {
	int n = this->size();
	int size = n - 1;
	char* newStr = new char [size];

	for (int i = 0; i < n - 1; i++) {
		newStr[i] = this->str[i];
	}
	
	newStr[n - 1] = '\0';
	this->str = newStr;
}

MyString& MyString::operator+=(char c) {
	this->push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	std::size_t size = rhs.size();

	for (int i = 0; i < size; i++) {
		this->push_back(rhs[i]);
	}
	
	return *this;
}

MyString MyString::operator+(char c) const {
	MyString newStr(this->str);
	newStr.push_back(c);
	return newStr;
}

MyString MyString::operator+(const MyString& rhs) const {
	MyString newStr(this->str);

	std::size_t size = rhs.size();

	for (int i = 0; i < size; i++) {
		newStr.push_back(rhs[i]);
	}
	return newStr;
}

const char* MyString::c_str() const {
	std::size_t n = this->size();
	char* arr = new char[n];

	for (int i = 0; i < this->size(); i++) {
		arr[i] = this->str[i];
	}
	arr[n] = '\0';

	return arr;
}

bool MyString::operator==(const MyString& rhs) const {
	std::size_t n = rhs.size();
	
	if (n != this->size()) {
		false;
	}

	const char* toCompare = rhs.c_str();

	for (int i = 0; i < n; i++) {
		if (toCompare[i] != this->str[i]) {
			return false;
		}
	}

	return true;
}

bool MyString::operator<(const MyString& rhs) const {

	if (this->size() < rhs.size()) {
		return true;
	}

	return false;
}

void MyString::print() {
	std::cout << this->str << std::endl;
}