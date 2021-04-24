#include <iostream>
#include <cstring>
#include <cassert>
#include "MyString.h"


bool MyString::allocateMemory(size_t newCapacity, char*& arr) const
{
	try {
		arr = new char[newCapacity];
	}
	catch (std::exception& e)
	{
		return false; //could not allocate
	}
	return true; //successful
}

void MyString::stringCpy(char*& destination, const char* source, const size_t quantity) const {
	for (size_t i = 0; i < quantity; i++)
	{
		destination[i] = source[i];
	}
}

MyString::MyString()
{
	arrSize = 0;
	if (!allocateMemory(2, string)) {
		capacity = 0;
		string = nullptr;
		throw - 1;
		return;
	}
	capacity = 2;
}

MyString::MyString(size_t newCapacity) {
	arrSize = 0;
	if (allocateMemory(newCapacity, string))
	{
		capacity = newCapacity;
	}
	else {
		if (allocateMemory(2, string)) //we will continue with less memory and try allocating more if needed later
		{
			capacity = 2;
		}
		else
		{
			capacity = 0;
			string = nullptr;
			throw - 1;
		}
	}

}

MyString::MyString(const char* str) {
	if (allocateMemory(strlen(str), string)) {
		capacity = strlen(str);
		arrSize = capacity;
		stringCpy(string, str, strlen(str));
		return;
	}
	capacity = 0;
	arrSize = 0;
	string = nullptr;
	throw - 1; //could not copy
}

MyString::MyString(MyString&& other) noexcept {

	capacity = other.capacity;
	arrSize = other.arrSize;
	string = other.string;

	other.string = nullptr;
	other.arrSize = other.capacity = 0;

}

MyString::MyString(const MyString& newString) {

	if (allocateMemory(newString.capacity, string))
	{
		capacity = newString.capacity;
		arrSize = newString.arrSize;
		stringCpy(string, newString.string, newString.capacity);
		return;
	}
	string = nullptr;
	arrSize = 0;
	capacity = 0;
	throw - 1; //could not copy
}

MyString::~MyString() {
	if (string != nullptr) {
		delete[] string;
	}
	arrSize = 0;
	capacity = 0;
}

char& MyString::at(std::size_t pos) {
	if (arrSize <= pos)
	{
		throw std::out_of_range("Position out of range");
	}
	return string[pos];
}

const char& MyString::at(std::size_t pos) const
{
	if (arrSize <= pos)
	{
		throw std::out_of_range("Position out of range");
	}
	return string[pos];
}

char& MyString::front() {
	assert(arrSize > 0);
	return string[0];
}

const char& MyString::front() const {
	assert(arrSize > 0);
	return string[0];
}

char& MyString::back() {
	assert(arrSize > 0);
	return string[arrSize - 1];
}

const char& MyString::back() const {
	assert(arrSize > 0);
	return string[arrSize - 1];
}

bool MyString::empty() const {

	return (arrSize == 0);
}

size_t MyString::size() const {
	return arrSize;
}

void MyString::clear() { //We can clear it and keep it's capacity but why would we ? We might need that memory

	delete[] string;
	string = nullptr;
	capacity = 0;
	arrSize = 0;
}

void MyString::push_back(char c)//TBD
{
	if (arrSize >= capacity) //it's full
	{
		char* newStr = nullptr;
		size_t newCapacity;
		
		if (!allocateMemory(capacity + 1, newStr))
		{
			throw - 1; //could not add
		}
		newCapacity = capacity + 1;
		
		stringCpy(newStr, string, capacity);
		newStr[capacity] = c;
		delete[] string;
		string = newStr;
		capacity = newCapacity;
		arrSize++;
	}
	else
	{
		string[arrSize++] = c;
	}
}

void MyString::pop_back()
{
	assert(arrSize > 0);
	string[--arrSize] = '\0';
}

MyString& MyString::operator=(MyString&& other) noexcept {

	if (this != &other)
	{
		delete[] string;
		arrSize = other.arrSize;
		capacity = other.capacity;
		string = other.string;

		other.arrSize = other.capacity = 0;
		other.string = nullptr;
	}
	return *this;
}


MyString& MyString::operator=(const MyString& newString) {
	if (this != &newString)
	{

		if (newString.arrSize > arrSize)
		{
			char* newStr = nullptr;
			if (allocateMemory(newString.arrSize, newStr)) //just as much as we need .
			{
				delete[] string;
				string = newStr;
				arrSize = newString.arrSize;
				stringCpy(string, newString.string, arrSize);
				capacity = arrSize;
				return *this;
			}
			throw - 1;//could  not copy

		}
		else
		{
			stringCpy(string, newString.string, newString.arrSize);
			arrSize = newString.arrSize;
			//we don't really need to change the capacity now as it fits 
		}
	}
	return *this;
}

char& MyString::operator[](std::size_t pos)
{
	assert(pos < arrSize);
	return string[pos];
}


const char& MyString::operator[](std::size_t pos) const
{
	assert(pos < arrSize);
	return string[pos];
}

MyString& MyString::operator+=(char c) {
	push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	//can be done with push_back but it will be slower
	if (arrSize + rhs.arrSize >= capacity) //it's full
	{
		char* newStr = nullptr;
		size_t newCapacity;
		if (!allocateMemory(capacity + rhs.capacity, newStr))
		{
			if (!allocateMemory(capacity + rhs.arrSize, newStr))
			{
				//failed to add
				return *this;
			}
			newCapacity = capacity + rhs.arrSize;
		}
		else //we could allocate that much memory in newStr
		{
			newCapacity = capacity + rhs.capacity;
		}
		stringCpy(newStr, string, arrSize);
		delete[] string;
		string = newStr;
		for (size_t i = arrSize; i < arrSize + rhs.arrSize; i++)
		{
			string[i] = rhs.string[i - arrSize]; //concat
		}
		capacity = newCapacity;
	}

	for (size_t i = arrSize; i < arrSize + rhs.arrSize; i++)
	{
		string[i] = rhs.string[i - arrSize]; //concat
	}
	arrSize += rhs.arrSize;

	return *this;
}

MyString MyString::operator+(char c) const {
	MyString newStr(*this);
	newStr.push_back(c);
	return newStr;
}

MyString MyString::operator+(const MyString& rhs) const {
	MyString newStr(*this);
	newStr += rhs;
	return newStr;
}

const char* MyString::c_str() const {
	char* newArr = nullptr;
	if (allocateMemory(arrSize + 1, newArr))
	{
		stringCpy(newArr, string, arrSize);
		newArr[arrSize] = '\0';
		return newArr;
	}
	throw - 1;
	//could not get memory here
	
}

bool MyString::operator==(const MyString& rhs) const {
	if (rhs.arrSize != arrSize)
	{
		return false;
	}
	for (size_t i = 0; i < arrSize; i++)
	{
		if (string[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

bool MyString::operator==(const char* rhs) const {
	if (strlen(rhs) != arrSize)
	{
		return false;
	}
	for (size_t i = 0; i < arrSize; i++)
	{
		if (string[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}


bool MyString::operator<(const MyString& rhs) const {
	size_t i = 0;
	while (i < arrSize && i < rhs.arrSize)
	{
		if (string[i] < rhs[i])
		{
			return true;
		}
		else if (string[i] > rhs[i])
		{
			return false;
		}
		i++;
	}

	return (arrSize < rhs.arrSize);
}

bool MyString::operator<=(const MyString& rhs) const {
	size_t i = 0;
	while (i < arrSize && i < rhs.arrSize)
	{
		if (string[i] < rhs[i])
		{
			return true;
		}
		else if (string[i] > rhs[i])
		{
			return false;
		}
		i++;
	}

	return (arrSize <= rhs.arrSize);
}

bool MyString::operator>(const MyString& rhs) const {
	size_t i = 0;
	while (i < arrSize && i < rhs.arrSize)
	{
		if (string[i] > rhs[i])
		{
			return true;
		}
		else if (string[i] < rhs[i])
		{
			return false;
		}
		i++;
	}

	return (arrSize > rhs.arrSize);
}

bool MyString::operator>=(const MyString& rhs) const {
	size_t i = 0;
	while (i < arrSize && i < rhs.arrSize)
	{
		if (string[i] > rhs[i])
		{
			return true;
		}
		else if (string[i] < rhs[i])
		{
			return false;
		}
		i++;
	}

	return (arrSize >= rhs.arrSize);
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
	const char* arr = str.c_str();
	os <<arr;
	delete[] arr;
	return os;
}
