#pragma once

#include "MyString.h"
#include <cstring>
#include <iostream>
#include <cassert>


MyString::MyString()
{
	SomeString = nullptr;
}

MyString::MyString(const char* str)
{
	int len = strlen(str);
	assert(len > 0);

	this->SomeString = new char[len + 1];
	strncpy(this->SomeString, str, len + 1);
}

char& MyString::at(size_t pos)
{
	if (strlen(this->SomeString) >= pos)
	{
		return this->SomeString[pos - 1];
	}
	else
	{
		throw std::out_of_range("Out of range");
	}
}

const char& MyString::at(size_t pos) const
{
	if (strlen(this->SomeString) > pos)
	{
		return this->SomeString[pos];
	}
	else
	{
		throw std::out_of_range("Out of range");
	}
}

char& MyString::operator[](size_t pos)
{
	assert(pos > 0);
	return this->SomeString[pos - 1];
}


const char& MyString::operator[](size_t pos) const
{
	assert(pos > 0);
	return  this->SomeString[pos - 1];

}

char& MyString::front()
{
	assert(this->SomeString != nullptr);

	return  this->SomeString[0];
}

const char& MyString::front() const
{
	assert(this->SomeString != nullptr);

	return  this->SomeString[0];
}

char& MyString::back()
{
	assert(this->SomeString != nullptr);
	size_t len  = strlen(this->SomeString);
	char& NeededElement = this->SomeString[len - 1];
	return NeededElement;
}

const char& MyString::back() const
{
	assert(this->SomeString != nullptr);
	size_t len = strlen(this->SomeString);
	return this->SomeString[len - 1];
}

bool MyString::empty() const
{
	if (this->SomeString == nullptr)
	{
		return 1;
	}
	return 0;
}

size_t MyString::size() const
{
    if(this->SomeString == nullptr)
    {
        return 0;
    }
	size_t len = strlen(this->SomeString);
	return len;
}

void MyString::clear()
{
	delete [] this->SomeString;
    this->SomeString = nullptr;
}

void MyString::push_back(char c)
{
	int len = strlen(this->SomeString);	
	assert(len > 0);
	try {
		char* String2 = new char[len + 1];
		strncpy(String2, this->SomeString, len);
		String2[len] = c;
		String2[len + 1] = '\0';
		this->SomeString = String2;
	}
	catch (std::bad_alloc& e)
	{
		std:: cerr << "bad alloc";
	}
}

void MyString::pop_back()
{
	assert(this->SomeString != nullptr);
	int len = strlen(this->SomeString);
	this->SomeString[len - 1] = '\0';
	this->SomeString[len] = NULL;
}

MyString &MyString::operator+=(char c)
{
	int len = strlen(this->SomeString);
	assert(len > 0);
	char* String2 = new char[len + 1];
	strncpy(String2, this->SomeString, len);
	String2[len] = c;
	String2[len + 1] = '\0';
	this->SomeString = String2;
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	strcat(this->SomeString, rhs.SomeString);
	return *this;
}

MyString MyString::operator+(char c) const
{
	const char* cc = &c;
	strcat(this->SomeString, cc);
	return *this;
}

MyString MyString::operator+(const MyString& rhs) const
{
	strcat(this->SomeString, rhs.SomeString);
	return this->SomeString;
}

const char* MyString::c_str() const
{
	int len = this->size();
	assert(len > 0);
	char* identicalString = new char [len + 1];
	strncpy(identicalString, this->SomeString, len);
	identicalString[len] = '\0';
	return identicalString;
}


bool MyString::operator==(const MyString& rhs) const
{
	bool equal = 0;

	if (strcmp(this->SomeString, rhs.SomeString) == 0)
	{
		equal = 1;
		return equal;
	}
	return equal;
}

bool MyString::operator<(const MyString& rhs) const
{
	bool equal = 0;

	if (strcmp(this->SomeString, rhs.SomeString) < 0)
	{
		equal = 1;
		return equal;
	}
	return equal;
}

