#include "MyString.h"

MyString::MyString()
{
	if (str)
	{
		str = new (nothrow) char[1];
		strcpy(str, "");
	}
}

MyString::MyString(const char* str)
{
	this->str = new (nothrow) char[strlen(str) + 1];
	strcpy(this->str, str);
}

MyString::MyString(const MyString& src)
{
	str = new (nothrow) char[strlen(src.str) + 1];
	strcpy(this->str, src.str);
}

MyString& MyString::operator=(const MyString& other)
{
	if (&other != this)
	{
		str = new (nothrow) char[strlen(other.str) + 1];
		strcpy(this->str, other.str);
	}
	return *this;
}

char& MyString::at(size_t pos)
{
	if (pos >= size() || pos < 0)
	{
		throw out_of_range("Out of range.");
	}
	else
	{
		return str[pos];
	}
}

const char& MyString::at(size_t pos) const
{
	if (pos >= size() || pos < 0)
	{
		throw out_of_range("Out of range.");
	}
	else
	{
		return str[pos];
	}
}

char& MyString::operator[](size_t pos)
{
	return str[pos];
}

const char& MyString::operator[](size_t pos) const
{
	return str[pos];
}

char& MyString::front()
{
	return str[0];
}

const char& MyString::front() const
{
	return str[0];
}

char& MyString::back()
{
	return str[size()];
}

const char& MyString::back() const
{
	return str[size()];
}

bool MyString::empty() const
{
	return size() == 0;
}

size_t MyString::size() const
{
	return strlen(str);
}

void MyString::clear()
{
	delete[] str;
}

void MyString::push_back(char c)
{
	char* temp = new (nothrow) char[size()+1];
	if (temp) 
	{
		strcpy(temp, str);
		temp[size() + 1] = c;
		clear();
		str = temp;
	}
}

void MyString::pop_back()
{
	str[strlen(str)-1] = '/0';
}

MyString& MyString::operator+=(char c)
{
	push_back(c);

	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	char* temp = new (nothrow) char[strlen(str) + strlen(rhs.str) + 1];
	if (temp)
	{
		strcpy(temp, str);
		strcat(temp, rhs.str);
		clear();
		str = temp;
	}
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString copystr(*this);
	copystr += c;
	return copystr;
}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString copystr(*this);
	copystr += rhs;
	return copystr;
}

const char* MyString::c_str() const
{
	return str;
}

bool MyString::operator==(const MyString& rhs) const
{
	return !strcmp(str, rhs.str);
}

bool MyString::operator<(const MyString& rhs) const
{
	return strcmp(str,rhs.str) < 0;
}
