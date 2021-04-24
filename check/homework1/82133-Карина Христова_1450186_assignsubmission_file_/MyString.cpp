#include "MyString.h"
#include <stdexcept>
#include <cassert>

//Length of the string will be with 1 less than the 
//number of elements of the data array because of the '\0'

MyString::MyString()
{
	this->length = 0;
	this->data = new char[1];
	this->data[0] = '\0';
}

MyString::MyString(const char* str)
{
	if (str) {
		int strLength = 0;
		while (str[strLength] != '\0') strLength++; //Gets the length of str

		char* newData = new char[strLength + 1];
		if (newData != nullptr)
		{
			for (int i = 0; i < strLength; i++)
				newData[i] = str[i];
			newData[strLength] = '\0';

			if (this->length != 0)
				delete[] this->data;
			this->data = newData;
			this->length = strLength;
		}
		else
			throw std::exception("Could not allocate enough memory!");
	}
}

MyString::~MyString()
{
	if (length != 0)
		delete[] data;
	this->length = 0;
}

char& MyString::at(std::size_t pos)
{
	if (pos < 0 || pos >= this->length)
		throw std::out_of_range("Index out of range!");

	char& p = this->data[pos];
	return p;
}

const char& MyString::at(std::size_t pos) const
{
	if (pos < 0 || pos >= this->length)
		throw std::out_of_range("Index out of range!");

	const char& p = this->data[pos];
	return p;
}

char& MyString:: operator[](std::size_t pos)
{
	assert(pos >= 0 && pos < this->length); //Assert in debug mode that the position is valid
	char& p = this->data[pos];
	return p;
}

const char& MyString:: operator[](std::size_t pos) const
{
	assert(pos >= 0 && pos < this->length); //Assert in debug mode that the position is valid
	const char& p = this->data[pos];
	return p;
}

char& MyString::front()
{
	assert(this->data[0] != '\0'); //Assert in debug mode that the string is not empty
	char& p = this->data[0];
	return p;
}

const char& MyString::front() const
{
	assert(this->data[0] != '\0'); //Assert in debug mode that the string is not empty
	const char& p = this->data[0];
	return p;
}

char& MyString::back()
{
	assert(this->data[0] != '\0'); //Assert in debug mode that the string is not empty
	char& p = this->data[length - 1];
	return p;
}

const char& MyString::back() const
{
	assert(this->data[0] != '\0'); //Assert in debug mode that the string is not empty
	const char& p = this->data[length - 1];
	return p;
}

bool MyString::empty() const
{
	return data[0] == '\0';
	//return length == 0;
}

std::size_t MyString::size() const
{
	return length;
}

void MyString::clear()
{
	this->length = 0;
	if (this->length != 0)
		delete[] data;
	this->data = new char[1];
	this->data[0] = '\0';
}

void MyString::push_back(char c)
{
	size_t newLen = this->length + 1;
	char* newData = new char[newLen + 1];

	if (newData == nullptr)
		throw std::exception("Could not allocate enough memory");

	for (int i = 0; i < length; i++)
		newData[i] = data[i];
	newData[length] = c;
	newData[newLen] = '\0';

	if (this->length != 0)
		delete[] data;
	length = newLen;
	data = newData;
}

void MyString::pop_back()
{
	assert(this->data[0] != '\0'); 	//Assert in debug mode that the string is not empty

	size_t newLen = this->length - 1;
	char* newData = new char[newLen + 1];
	if (newData == nullptr)
		throw std::exception("Could not allocate enough memory");

	this->length = newLen;
	for (int i = 0; i < newLen; i++)
		newData[i] = data[i];
	newData[newLen] = '\0';

	if (this->length != 0)
		delete[] data;
	length = newLen;
	data = newData;
}

MyString& MyString::operator+=(char c)
{
	size_t newLen = this->length + 1;
	char* newData = new char[newLen + 1];

	if (newData == nullptr)
		throw std::exception("Could not allocate enough memory");

	for (int i = 0; i < length; i++)
		newData[i] = data[i];

	newData[length] = c;
	newData[newLen] = '\0';

	if (this->length != 0)
		delete[] data;
	length = newLen;
	data = newData;
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	size_t rhsLen = rhs.size();
	size_t newLen = rhsLen;
	newLen += this->length;

	char* newData = new char[newLen + 1];

	if (newData == nullptr)
		throw std::exception("Could not allocate enough memory");

	for (int i = 0; i < length; i++)
		newData[i] = data[i];

	for (int j = 0; j < rhsLen; j++)
		newData[length + j] = rhs[j];

	newData[newLen] = '\0';

	if (this->length != 0)
		delete[] data;
	length = newLen;
	data = newData;
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString st = *this;
	MyString str = (st += c);
	return str;
}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString st = *this;
	MyString str = (st += rhs);
	return str;
}

const char* MyString::c_str() const
{
	size_t len = this->length + 1;
	char* p = new char[len];
	if (p == nullptr)
		throw std::exception("Could not allocate enough memory");

	for (int i = 0; i < length; i++)
		p[i] = this->data[i];

	*(p + length) = '\0';

	return p;
	//const char* p = this->data;
	//return p;
	////return this->data;
}

bool MyString::operator==(const MyString& rhs) const
{
	if (this->length != rhs.length)
		return false;

	bool equal = true;
	for (int i = 0; i < rhs.length; i++)
		if (this->data[i] != rhs.data[i])
			equal = false;

	return equal;
}

bool MyString::operator<(const MyString& rhs) const
{
	if (this->length != rhs.length) //If one is shorter it is first
		return (this->length < rhs.length);
	else { //In case they have the same length the first different character will show which is first
		for (int i = 0; i < rhs.length; i++) {
			if (this->data[i] < rhs.data[i]) //First is before the second 
				return true;

			if (this->data[i] > rhs.data[i]) //Second is before the first
				return false;
		}

		return false;
	}
}