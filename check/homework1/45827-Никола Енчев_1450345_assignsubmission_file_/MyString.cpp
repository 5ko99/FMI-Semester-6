
#include "MyString.h"
#include <exception>
#include <cassert>
#include <cstring>
#include <iostream>

void createDynCopy(char*& destination, const char* source)
{
	if (source)
	{
		destination = new char[strlen(source) + 1];
		int pos = 0;
		while (source[pos]) {
			destination[pos] = source[pos];
			++pos;
		}
		destination[pos] = '\0';
	}
	else
	{
		destination = nullptr;
	}
}
MyString::MyString()
{
	str = new char[1];
	str[0] = '\0';
	used = 0;
	capacity = 0;
}

MyString::~MyString()
{
	delete str;
	str = nullptr;
	used = 0;
	capacity = 0;
}

MyString::MyString(const char* source)
{
	createDynCopy(this->str, source);
	this->capacity = strlen(source);
	this->used = strlen(source);
}

MyString::MyString(const MyString& source)
{
	createDynCopy(this->str, source.str);
	this->capacity = source.capacity;
	this->used = source.used;
}

MyString& MyString::operator=(const MyString& rhs)
{
	if (this == &rhs)
		return *this;
	createDynCopy(this->str, rhs.str);
	this->capacity = rhs.capacity;
	this->used = rhs.used;
	return *this;
}

char& MyString::at(size_t pos)
{
	if (pos >= 0 && pos < used)
	{

		return this->str[pos];
	}
	throw std::out_of_range("Something is out of range!");
}

const char& MyString::at(size_t pos) const
{
	if (pos >= 0 && pos < used)
	{

		return this->str[pos];
	}
	else
		throw std::out_of_range("Something is out of range!");
}

char& MyString::operator[](size_t pos)
{
	assert(pos < used);
	return this->str[pos];
}

const char& MyString::operator[](size_t pos) const
{
	assert(pos < used);
	return this->str[pos];
}

char& MyString::front()
{
	assert(used > 0);
	return this->str[0];
}

const char& MyString::front() const
{
	assert(used > 0);
	return this->str[0];
}

char& MyString::back()
{

	assert(used > 0);
	return str[used - 1];
}

const char& MyString::back() const
{

	assert(used > 0);
	return str[used - 1];
}

bool MyString::empty() const
{
	if (used > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

size_t MyString::size() const
{
	return this->used;
}

void MyString::clear()
{
	this->used = 0;
}

void MyString::push_back(char c)
{
	if (used == capacity)
	{
		size_t newSize = ((capacity == 0) ? 2 : capacity * 2);


		char* newStr = new char[newSize];

		for (size_t i = 0; i < used; i++)
		{
			newStr[i] = str[i];
		}
		newStr[newSize - 1] = '\0';

		delete[] str;
		str = newStr;
		newStr = nullptr;
	}

	this->used++;
	this->str[used - 1] = c;
}

void MyString::pop_back()
{
	assert(used > 0);

	-- this->used;
}

MyString& MyString::operator+=(char c)
{
	if (used == capacity)
	{
		size_t newSize = ((capacity == 0) ? 2 : (capacity * 2));

		char* newStr = new char[newSize];

		for (size_t i = 0; i < used; i++)
		{
			newStr[i] = str[i];
		}
		newStr[newSize - 1] = '\0';

		delete[] str;
		str = newStr;
		newStr = nullptr;
	}
	this->str[used] = c;
	this->used++;

	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{

	size_t newSize = 0;
	newSize = used + rhs.size();

	char* newStr = new char[newSize + 1];

	for (int i = 0; i < used; i++)
	{
		newStr[i] = str[i];
	}
	int index = 0;
	for (int i = used; i < newSize; i++)
	{
		newStr[i] = rhs[index];
		index++;
	}
	newStr[newSize] = '\0';

	delete[] str;
	str = newStr;
	newStr = nullptr;

	this->used = newSize;
	this->capacity = newSize;

	return *this;


}

MyString MyString::operator+(char c) const
{
	size_t newSize = used + 2;
	char* newStr = new char[newSize];

	for (size_t i = 0; i < used; i++)
	{
		newStr[i] = str[i];
	}

	newStr[newSize - 2] = c;
	newStr[newSize - 1] = '\0';

	MyString concatenatedStr{ newStr };

	delete[] newStr;
	newStr = nullptr;

	return concatenatedStr;
}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString concatenatedStr{};

	concatenatedStr += str;
	concatenatedStr += rhs;

	return concatenatedStr;
}

const char* MyString::c_str() const
{
	if (str)
	{
		char* newStr = new char[used + 1];

		for (size_t i = 0; i < used; i++)
		{
			newStr[i] = str[i];
		}
		newStr[used] = '\0';

		return newStr;
	}
	else
	{
		return nullptr;
	}
}

bool MyString::operator==(const MyString& rhs) const
{
	if (used != rhs.used)
		return false;

	for (size_t i = 0; i < used; i++)
	{
		if (str[i] != rhs.str[i])
			return false;
	}

	return true;
}

bool MyString::operator<(const MyString& rhs) const
{
	size_t index = (used < rhs.used ? used : rhs.used);

	for (size_t i = 0; i < index; i++)
	{
		if (str[i] > rhs.str[i])
			return false;

		if (str[i] < rhs.str[i])
			return true;
	}

	if (used >= rhs.used)
		return false;

	return true;
}
