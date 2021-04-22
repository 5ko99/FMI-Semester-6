#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>

MyString::MyString()
{
	str = nullptr;
	len = 0;
	buf_len = 0;
}

MyString::~MyString()
{
	delete[] str;
	len = 0;
	buf_len = 0;
}

MyString::MyString(const char* original)
{
	len = strlen(original);
	buf_len = len + 1;
	str = new char[buf_len];
	strcpy(this->str, original);
}

MyString::MyString(const MyString& original) 
{
	len =original.size();
	buf_len = len + 1;
    str = new char[buf_len];
	strcpy(this->str, original.str);
}

char& MyString::at(std::size_t pos)
{
	if (pos < 0 || pos > len)
		throw std::out_of_range("There is no such position!");

	return str[pos];
}

const char& MyString::at(std::size_t pos) const
{
	if (pos < 0 || pos > len)
		throw std::out_of_range("There is no such position!");

	return str[pos];
}

char& MyString::operator[](std::size_t pos)
{
	assert(pos >= 0 && pos <= len);
		return str[pos];
}

const char& MyString::operator[](std::size_t pos) const
{
	assert(pos >= 0 && pos <= len);
	return str[pos];
}

char& MyString::front()
{
	assert(len > 0);
	return str[0];
}

const char& MyString::front() const
{
	assert(len > 0);
	return *(str+1);
}

char& MyString::back()
{
	assert(len > 0);
	return str[len - 1];
}

const char& MyString::back() const
{
	assert(len > 0);
	return str[len - 1];
}

bool MyString::empty() const
{
	return len == 0;
}

std::size_t MyString::size() const
{
	return len;
}

void MyString::clear()
{
	for (size_t i = 0; i < buf_len; i++)
		str[i] = '\0';
}

void MyString::push_back(char c)
{
	try
	{
		char* temp = new char[buf_len + 1];
		for (size_t i = 0; i < len; i++)
			temp[i] = str[i];
		temp[buf_len - 1] = c;
		temp[buf_len] = '\0';
		buf_len++;
		len++;
		if (strlen(temp) == len)
			throw std::invalid_argument("invalid");
		delete[] str;
		str = new char[buf_len];
		for (size_t i = 0; i <= len; i++)
			str[i] = temp[i];
		delete[] temp;
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}

void MyString::pop_back()
{
	try 
	{
		char* temp = new char[buf_len - 1];
		for (size_t i = 0; i < buf_len - 2; i++)
			temp[i] = str[i];

		temp[buf_len - 2] = '\0';

		buf_len--;
		len--;
		if (strlen(temp) == len)
			throw std::invalid_argument("invalid");
		
		delete[] str;
		str = new char[buf_len];
		for (size_t i = 0; i < buf_len - 1; i++)
			str[i] = temp[i];

		delete[] temp;
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}

MyString& MyString::operator+=(char c)
{
	push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	size_t new_buf = this->buf_len + rhs.buf_len -1;
	size_t counter = 0;
	char* temp = new char[new_buf];
	for (size_t i = 0; i < this->len; i++)
	{
		temp[counter] = str[i];
		counter++;
	}
	for (size_t i = 0; i < rhs.len; i++)
	{
		temp[counter] = rhs[i];
		counter++;
	}
	if(counter<=new_buf) temp[counter] = '\0';
	counter++;
	this->len = new_buf - 1;
	this->buf_len = new_buf;

	if (strlen(temp) == len)
	{
		delete[] str;
		 str = new char[buf_len];
		 for (size_t i = 0; i <= len; i++)
			 str[i] = temp[i];
	}

	delete[] temp;
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString newArray=this->str;
	newArray.push_back(c);
	
	return newArray.str;
}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString newArray = this->str;
	newArray += rhs;

	return newArray.str;
}

const char* MyString::c_str() const
{
	
	return  const_cast<const char*>(str);

}

bool MyString::operator==(const MyString& rhs) const
{
	return !strcmp(this->c_str(), rhs.c_str());
}

bool MyString::operator<(const MyString& rhs) const
{
	size_t i = 0;
	int flag = strcmp(this->c_str(), rhs.c_str());
	if (flag > 0) return true;
	return false;

}

std::ostream& operator <<(std::ostream& os, const MyString& obj)
{
	os << obj.c_str();
	return os;
}

MyString& MyString::operator=(const MyString& rhs)
{
	this->buf_len = rhs.buf_len;
	delete[] str;
	str = new char[buf_len];
	this->len = rhs.len;
	for (size_t i = 0; i <= len; i++)
		str[i] = rhs.str[i];

	return *this;
}
