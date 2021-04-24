#include "MyString.hpp"

MyString::MyString() {
	this->data = new char[1];
}

void MyString::copyFrom(const char* other_str) {
	this->data = new char[strlen(other_str) + 1];
	strcpy_s(this->data, strlen(other_str) + 1, other_str);
}

MyString::MyString(const MyString& other) {
	copyFrom(other.data);
}

void MyString::del() {
	delete[] this->data;
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		del();
		this->data = nullptr;

		copyFrom(other.data);
	}

	return *this;
}

MyString::MyString(const char* str) {
	this->data = new char[strlen(str) + 1];
	strcpy_s(this->data, strlen(str) + 1, str);
}

char& MyString::at(size_t pos) {
	if (pos >= strlen(this->data) || pos < 0) {
		throw out_of_range("Position is out of range!");
	}

	return this->data[pos];
}

const char& MyString::at(size_t pos) const {
	if (pos >= strlen(this->data) || pos < 0) {
		throw out_of_range("Position is out of range!");
	}

	return this->data[pos];
}

char& MyString::operator[](size_t pos) {
	return at(pos);
}

const char& MyString::operator[](size_t pos) const {
	return at(pos);
}

char& MyString::front() {
	return at(0);
}

const char& MyString::front() const {
	return at(0);
}

char& MyString::back() {
	return at(strlen(this->data) - 1);
}

const char& MyString::back() const {
	return at(strlen(this->data) - 1);
}

bool MyString::empty() const {
	if (strlen(this->data) == 0) {
		return true;
	}
	else {
		return false;
	}
}

size_t MyString::size() const {
	return strlen(this->data);
}

void MyString::clear() {
	del();
	this->data = nullptr;
}

void MyString::push_back(char c) {
	char* newStr = new char[size() + 2];
	if (!newStr) {
		throw exception("Not enough memory!");
	}

	for (size_t i = 0; i < size(); i++) {
		newStr[i] = this->data[i];
	}

	newStr[size()] = c;
	newStr[size() + 1] = '\0';

	copyFrom(newStr);

	delete[] newStr;
}

void MyString::pop_back() {
	char* newStr = new char[size()];

	for (size_t i = 0; i < size() - 1; i++) {
		newStr[i] = this->data[i];
	}

	newStr[size() - 1] = '\0';

	copyFrom(newStr);

	delete[] newStr;
}

MyString& MyString::operator+=(char c) {
	push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	for (size_t i = 0; i < rhs.size(); i++) {
		push_back(rhs.data[i]);
	}

	return *this;
}

MyString MyString::operator+(char c) const {
	MyString temp(this->data);
	temp += c;

	return temp;
}

MyString MyString::operator+(const MyString& rhs) const {
	MyString temp(this->data);
	temp += rhs;

	return temp;
}

const char* MyString::c_str() const {
	return this->data;
}

bool MyString::operator==(const MyString& rhs) const {
	if (strcmp(this->data, rhs.data) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator<(const MyString& rhs) const {
	if (strcmp(rhs.data, this->data) < 0) {
		return true;
	}
	else {
		return false;
	}
}

MyString::~MyString() {
	del();
}
