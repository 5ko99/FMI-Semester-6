// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Александра Пенева
// ФН: 45354
// Специалност: Информатика
// Курс: 3
// Административна група: 1
// Ден, в който се явявате на контролното: 24.04.2021
// // Начален час на контролното: 9:30
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

class IntBuffer {
private:
	int* buffer{ nullptr };
	std::size_t buffSize{ 0 };

public:
	IntBuffer(std::size_t size);
	IntBuffer(const IntBuffer& other);
	IntBuffer& operator=(const IntBuffer& other);
	~IntBuffer();

	IntBuffer(std::size_t size, const IntBuffer& other);
	int& at(std::size_t index);
	const int& at(std::size_t index) const;
	int& operator[](std::size_t index);
	const int& operator[](std::size_t index) const;
	std::size_t size() const;
	void copy_from(const IntBuffer& other, std::size_t count);
	bool operator==(const IntBuffer& other) const;
	bool operator<(const IntBuffer& other) const;

};

IntBuffer::IntBuffer(std::size_t size)
{
	try
	{
		buffer = new int[size];
		buffSize = size;
	}
	catch (const std::bad_alloc&)
	{
		throw;
	}
}

IntBuffer::IntBuffer(const IntBuffer& other)
{
	this->buffSize = other.buffSize;
	copy_from(other, buffSize);
}

IntBuffer& IntBuffer::operator=(const IntBuffer& other)
{
	int* temp = new int[other.buffSize];
	try
	{
		for (size_t i = 0; i < other.buffSize; i++)
			temp[i] = other.buffer[i];
	}
	catch (const std::exception&)
	{
		delete[] temp;
		throw;
	}

	delete[] this->buffer;
	this->buffer = new int[other.buffSize];
	this->buffSize = other.buffSize;
	this->buffer = temp;
	return *this;
}

IntBuffer::~IntBuffer()
{
	delete[] buffer;
	buffer = nullptr;
	buffSize = 0;
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer& other)
{
	try
	{
		buffer = new int[size] {0};
	}
	catch (const std::exception&)
	{
		throw new std::bad_alloc();
	}

	std::size_t N = (size < other.buffSize) ?
		size : other.buffSize;
	for (size_t i = 0; i < N; i++)
		this->buffer[i] = other.buffer[i];
	this->buffSize = size;
}

int& IntBuffer::at(std::size_t index)
{
	if (index < 0 || index >= buffSize)
		throw std::out_of_range("Index is out of range!");

	return this->buffer[index];
}

const int& IntBuffer::at(std::size_t index) const
{
	if (index < 0 || index >= buffSize)
		throw std::out_of_range("Index is out of range!");

	return this->buffer[index];
}

int& IntBuffer::operator[](std::size_t index)
{
	assert(index >= 0 && index < buffSize);
	return this->buffer[index];
}

const int& IntBuffer::operator[](std::size_t index) const
{
	assert(index >= 0 && index < buffSize);
	return this->buffer[index];
}

std::size_t IntBuffer::size() const
{
	return this->buffSize;
}

void IntBuffer::copy_from(const IntBuffer& other, std::size_t count)
{
	if (this->buffSize < count || other.buffSize < count)
		throw std::out_of_range("Count is out of range!");

	for (size_t i = 0; i < count; i++)
		this->buffer[i] = other.buffer[i];
}

bool IntBuffer::operator==(const IntBuffer& other) const
{
	if (this->buffSize != other.buffSize)
		return false;

	for (size_t i = 0; i < buffSize; i++)
	{
		if (this->buffer[i] != other.buffer[i])
			return false;
	}

	return true;
}

bool IntBuffer::operator<(const IntBuffer& other) const
{
	std::size_t size = (this->buffSize < other.buffSize) ?
		this->buffSize : other.buffSize;
	for (size_t i = 0; i < size; i++)
	{
		if (this->buffer[i] >= other.buffer[i])
			return false;
	}

	if (size == this->buffSize)
		return true;

	return false;
}

class Set {
private:
	size_t capacity{ 0 };
	const IntBuffer empty = *new IntBuffer(0);
	IntBuffer elements{ empty };
	size_t numElems{ 0 };
	void resize();
	bool binarySearch(size_t minIndex, size_t maxIndex, int value) const;

public:
	Set();
	void insert(int value);
	bool contains(int value) const;
	size_t size() const;
};

void Set::resize()
{
	try
	{
		IntBuffer temp = *new IntBuffer(capacity * 2);
		for (size_t i = 0; i < numElems; i++)
		{
			temp[i] = this->elements[i];
		}
		elements = temp;
		this->capacity *= 2;
	}
	catch (const std::exception&)
	{
		throw new std::bad_alloc;
	}
}

bool Set::binarySearch(size_t minIndex, size_t maxIndex, int value) const
{	

	return false;
}

Set::Set() : capacity(2), numElems(0), elements(empty)
{}

void Set::insert(int value)
{
	try
	{

		for (size_t i = 0; i < numElems; i++)
		{
			if (elements[i] == value)
			{
				return;
			}
			if (value > elements[i] && value < elements[i+1])
			{
				if (numElems + 1 == capacity)
					this->resize();
				int temp = elements[i + 1];
				elements[i + 1] = value;
				for (size_t j = i; i < numElems; j++)
				{
					temp = elements[i + 1];
					elements[i + 1] = elements[i];
				}
			}

		}
	}
	catch (const std::exception& ex)
	{
		throw ex.what();
	}
}

bool Set::contains(int value) const
{
	return binarySearch(0, numElems, value);
}

std::size_t Set::size() const
{
	return this->numElems;
}


int main()
{
	return 0;
}