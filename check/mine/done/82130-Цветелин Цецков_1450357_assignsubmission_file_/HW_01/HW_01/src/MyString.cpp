#include "MyString.h"
#include <cstring>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <cassert>

static const int NULL_TERMINATOR = 1;

/*
Allocates the size of the array and fills with zeroes
*/
static char* allocateCharPrtOfZeroes(const std::size_t len)
{
	char* raw = new char[len];
	memset(raw, 0, len * sizeof(char)); // most of the time the for loop is optimized to this
	return raw;
}

MyString::MyString()
{
	rawStr = allocateCharPrtOfZeroes(NULL_TERMINATOR);
	usedSize = NULL_TERMINATOR;
	rawSize = NULL_TERMINATOR;
}

MyString::MyString(const char* str)
{
	if (str == nullptr)
	{
		//throw std::invalid_argument("Cannot initialize with nullptr!");
		rawStr = allocateCharPrtOfZeroes(NULL_TERMINATOR);
		rawSize = usedSize = NULL_TERMINATOR;
		return;
	}

	const std::size_t inputLen = strlen(str);
	rawStr = allocateCharPrtOfZeroes(inputLen + NULL_TERMINATOR);
	strcpy(rawStr, str);
	rawSize = usedSize = inputLen + NULL_TERMINATOR;
}

MyString::MyString(const MyString & other)
{
	const std::size_t inputLenRaw = other.size() + NULL_TERMINATOR;
	char* newBuf = allocateCharPrtOfZeroes(inputLenRaw);
	strcpy(newBuf, other.rawStr);
	rawStr = newBuf;
	rawSize = usedSize = inputLenRaw;
}

MyString::~MyString()
{
	if (rawStr != nullptr)
	{
		delete[] rawStr;
		rawStr = nullptr;
	}
	this->usedSize = 0;
	this->rawSize = 0;
}

MyString & MyString::operator=(const MyString & other)
{
	const std::size_t inputLenRaw = other.size() + NULL_TERMINATOR;
	if (inputLenRaw > this->rawSize)
	{
		char* newBuf = allocateCharPrtOfZeroes(inputLenRaw);
		strcpy(newBuf, other.rawStr);
		delete[] rawStr;
		rawStr = newBuf;
		rawSize = usedSize = inputLenRaw;
	}
	else {
		strcpy(this->rawStr, other.rawStr);
		usedSize = inputLenRaw;
	}
	return *this;
}

char & MyString::at(std::size_t pos)
{
	if (pos >= this->size()) // cannot access the null terminator
	{
		throw std::out_of_range("Requested character after the end of the string!");
	}
	return rawStr[pos];
}

const char & MyString::at(std::size_t pos) const
{
	if (pos >= this->size()) // cannot access the null terminator
	{
		throw std::out_of_range("Requested character after the end of the string!");
	}
	return rawStr[pos];
}

char & MyString::operator[](std::size_t pos)
{
	assert(pos < this->usedSize);
	return this->rawStr[pos];
}

const char & MyString::operator[](std::size_t pos) const
{
	assert(pos < this->usedSize);
	return this->rawStr[pos];
}

char & MyString::front()
{
	assert(this->size() > 0);
	return this->rawStr[0];
}

const char & MyString::front() const
{
	assert(this->size() > 0);
	return this->rawStr[0];
}

char & MyString::back()
{
	assert(this->size() > 0);
	return this->rawStr[this->usedSize - NULL_TERMINATOR - 1];
}

const char & MyString::back() const
{
	assert(this->size() > 0);
	return this->rawStr[this->usedSize - NULL_TERMINATOR - 1];
}

bool MyString::empty() const
{
	return this->size() == 0;
}

std::size_t MyString::size() const
{
	return this->usedSize - NULL_TERMINATOR;
}

void MyString::clear()
{
	memset(rawStr, 0, rawSize * sizeof(char));
	this->usedSize = NULL_TERMINATOR;
}

void MyString::push_back(char c)
{
	if (this->usedSize >= this->rawSize)
	{
		this->expandBuffer();
	}

	rawStr[usedSize - 1] = c;
	usedSize++;
}

void MyString::pop_back()
{
	assert(this->size() > 0);
	this->back() = 0;
	this->usedSize -= (this->size() > 0); // boolean conversion ftw
}

MyString & MyString::operator+=(char c)
{
	this->push_back(c);
	return *this;
}

MyString & MyString::operator+=(const MyString & rhs)
{
	for (std::size_t i = 0; i < rhs.size(); i++)
	{
		this->push_back(rhs[i]);
	}
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString res = *this;
	res += c;
	return res;
}

MyString MyString::operator+(const MyString & rhs) const
{
	MyString res = *this;
	res += rhs;
	return res;
}

const char * MyString::c_str() const
{
	return rawStr;
}

bool MyString::operator==(const MyString & rhs) const
{
	if (this->size() != rhs.size())
		return false;

	for (std::size_t i = 0; i < this->size(); i++)
	{
		if (this->at(i) != rhs.at(i))
			return false;
	}
	return true;
}

bool MyString::operator!=(const MyString & rhs) const
{
	if (this->size() != rhs.size())
		return true;

	for (std::size_t i = 0; i < this->size(); i++)
	{
		if (this->at(i) != rhs.at(i))
			return true;
	}
	return false;
}

bool MyString::operator<(const MyString & rhs) const
{
	return strcmp(this->c_str(), rhs.c_str());
}

MyString::operator const char*() const
{
	return this->c_str();
}

void MyString::expandBuffer()
{
	const std::size_t newSize = expansionFunction(this->rawSize);
	char* newBuf = allocateCharPrtOfZeroes(newSize);
	strcpy(newBuf, rawStr);
	delete[] this->rawStr;
	this->rawStr = newBuf;
	this->rawSize = newSize;
}

std::size_t MyString::expansionFunction(const std::size_t oldSize)
{
	if (oldSize == 0)
		return 2;
	const std::size_t newSize = oldSize * 2;
	//const std::size_t newSize = oldSize + ;
	assert(oldSize < newSize);
	return newSize;
}

std::ostream & operator<<(std::ostream & os, const MyString & str)
{
	os << str.rawStr;
	return os;
}

std::istream& getline(std::istream & is, MyString & str)
{
	str.clear();
	char ch = is.get();
	while (is && ch != '\n')
	{
		str += ch;
		ch = is.get();
	}

	return is;
}
