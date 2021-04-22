#include <iostream>
#include <cassert>
#include <cstring> 
#include "mystring.h"

// Ще съм много благодарна, ако получа обратна връзка с коментар за решението
// Благодаря предварително :)
// Използвам VS Code, компилатор MinGW



MyString::MyString()
{
	data = nullptr;
	length = 0;
}

MyString::MyString(const char* str)
{
	std::size_t len = strlen(str);
	length = len;

	data = new char[len + 1];

	for (std::size_t i = 0; i < len; ++i)
		data[i] = str[i];

	data[len] = '\0';
}

MyString::MyString(const MyString& other)
{

	this->data = new char[other.length + 1];
	this->length = other.length;

	for (std::size_t i = 0; i < other.length; ++i)
		this->data[i] = other.data[i];

	this->data[this->length] = '\0';
}



MyString::~MyString()
{
	//std::cout << "delete";
	delete[] data;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		delete[] this->data;
		this->data = new char[other.length + 1];
		for (std::size_t i = 0; i < other.length; ++i)
			this->data[i] = other.data[i];
		this->length = other.length;

		this->data[this->length] = '\0';
	}
	return *this;
}

char& MyString::at(std::size_t pos)
{
	if (pos >= length)
	{
		throw std::out_of_range("Too big index!");
	}

	return data[pos];
}

const char& MyString::at(std::size_t pos) const
{
	if (pos >= length)
	{
		throw std::out_of_range("Too big index!");
	}
	return data[pos];
}

char& MyString::operator[](std::size_t pos)
{
	//#define DEBUG

#ifdef DEBUG
	assert(pos >= 0 && pos < length);
#endif

	return data[pos];
}

const char& MyString::operator[](std::size_t pos) const
{
#ifdef DEBUG
	assert(pos >= 0 && pos < length);
#endif
	return data[pos];
}

char& MyString::front()
{
#ifdef DEBUG
	assert(length != 0);
#endif
	return at(0);
}

const char& MyString::front() const
{
#ifdef DEBUG
	assert(length != 0);
#endif
	return at(0);
}

char& MyString::back()
{
#ifdef DEBUG
	assert(length != 0);
#endif

	return at(this->length - 1);
}

const char& MyString::back() const
{
#ifdef DEBUG
	assert(length != 0);
#endif
	return at(this->length - 1);
}

bool MyString::empty() const
{
	return this->length == 0;
}

std::size_t MyString::size() const
{
	return this->length;
}

void MyString::clear()
{
	delete[] this->data;
	this->data = nullptr;
	this->length = 0;
}

void MyString::push_back(char c)
{
	char* buffer = new char[length + 2];
	for (std::size_t i = 0; i < length; ++i)
		buffer[i] = data[i];

	buffer[length] = c;
	buffer[length + 1] = '\0';
	delete[] data;
	data = buffer;
	this->length++;
}

void MyString::pop_back()
{
#ifdef DEBUG
	assert(length != 0);
#endif

	char* buffer = new char[length];

	for (std::size_t i = 0; i < length - 1; ++i)
		buffer[i] = data[i];
	buffer[length - 1] = '\0';
	delete[] data;
	data = buffer;
	this->length--;
}

MyString& MyString::operator+= (char c)
{
	push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
	char* buffer = new char[this->length + other.length + 1];
	for (std::size_t i = 0; i < this->length; ++i)
		buffer[i] = data[i];
	for (std::size_t i = 0; i < other.length; ++i)
		buffer[this->length + i] = other.data[i];
	buffer[this->length + other.length] = '\0';

	this->length += other.length;
	delete[] data;
	data = buffer;

	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString newStr(*this);
	newStr += c;
	return newStr;
}

MyString MyString::operator+(const MyString& other) const
{
	MyString newStr(*this);

	newStr += other;

	return newStr;
}

const char* MyString::c_str() const
{
	/*char* buffer = new char[this->length + 1];
	for (std::size_t i = 0; i < length; ++i)
		buffer[i] = data[i];
	buffer[length] = '\0';
	return buffer;*/
	return this->data;
}

bool MyString::operator==(const MyString& other) const
{
	bool areEmty = this->empty() && other.empty();
	if (areEmty)
		return true;
	return strcmp(this->data, other.data) == 0;
}

bool MyString::operator<(const MyString& other) const
{
	return strcmp(this->data, other.data) < 0;
}


