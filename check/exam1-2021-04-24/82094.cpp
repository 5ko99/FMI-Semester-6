//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: София Ивова Захариева
// ФН: 82094
// Специалност: КН
// Курс: 2
// Административна група: 1
// Ден, в който се явявате на контролното: 24.04.21
// Начален час на контролното: 09:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <stdexcept>

class IntBuffer
{
private:
	int *arr;
	std::size_t sizeOfArray;

public:
	IntBuffer(std::size_t size);
	IntBuffer(int *, std::size_t);
	IntBuffer(const IntBuffer &);
	IntBuffer(std::size_t size, const IntBuffer &other);
	IntBuffer &operator=(const IntBuffer &);
	~IntBuffer();

	int &at(std::size_t index);
	const int &at(std::size_t index) const;
	int &operator[](std::size_t index);
	const int &operator[](std::size_t index) const;
	std::size_t size() const;
	void copy_from(const IntBuffer &other, std::size_t count);
	bool operator==(const IntBuffer &other) const;
	bool operator<(const IntBuffer &other) const;
};

IntBuffer::IntBuffer(std::size_t size)
{
	this->arr = new int[size];
	this->sizeOfArray = size;
}
IntBuffer::IntBuffer(int *arr, std::size_t size)
{
	this->arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		this->arr[i] = arr[i];
	}
	this->sizeOfArray = size;
}
IntBuffer::IntBuffer(const IntBuffer &other)
{
	this->arr = new int[other.sizeOfArray];
	for (int i = 0; i < other.sizeOfArray; ++i)
	{
		this->arr[i] = other.arr[i];
	}
	this->sizeOfArray = other.sizeOfArray;
}
IntBuffer::IntBuffer(std::size_t size, const IntBuffer &other)
{
	int n = (size < other.sizeOfArray ? size : other.sizeOfArray);
	this->arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		this->arr[i] = other.arr[i];
	}
	this->sizeOfArray = n;
}
IntBuffer &IntBuffer::operator=(const IntBuffer &other)
{
	if (this != &other)
	{
		delete[] this->arr;
		this->arr = new int[other.sizeOfArray];
		for (int i = 0; i < other.sizeOfArray; ++i)
		{
			this->arr[i] = other.arr[i];
		}
		this->sizeOfArray = other.sizeOfArray;
	}
	return *this;
}
IntBuffer::~IntBuffer()
{
	delete[] this->arr;
	this->arr = nullptr;
}

int &IntBuffer::at(std::size_t index)
{
	if (index < 0 || index > this->sizeOfArray - 1)
	{
		throw std::out_of_range("This is not a valid index");
	}
	return this->arr[index];
}
const int &IntBuffer::at(std::size_t index) const
{
	if (index < 0 || index > this->sizeOfArray - 1)
	{
		throw std::out_of_range("This is not a valid index");
	}
	return this->arr[index];
}
int &IntBuffer::operator[](std::size_t index)
{
	assert(index > 0 && index < this->sizeOfArray - 1);
	return this->arr[index];
}
const int &IntBuffer::operator[](std::size_t index) const
{
	assert(index > 0 && index < this->sizeOfArray - 1);
	return this->arr[index];
}
std::size_t IntBuffer::size() const
{
	return this->sizeOfArray;
}
void IntBuffer::copy_from(const IntBuffer &other, std::size_t count)
{
	if (this->sizeOfArray - 1 > count || other.sizeOfArray - 1 > count)
	{
		std::out_of_range("");
	}
	for (int i = 0; i < count; ++i)
	{
		this->arr[i] = other.arr[i];
	}
}
bool IntBuffer::operator==(const IntBuffer &other) const
{
	if (this->sizeOfArray != other.sizeOfArray)
		return false;
	for (int i = 0; i < this->sizeOfArray; ++i)
	{
		if (this->arr[i] != other.arr[i])
			return false;
	}
	return true;
}
bool IntBuffer::operator<(const IntBuffer &other) const
{
	if (this->sizeOfArray > other.sizeOfArray)
		return false;

	for (int i = 0; i < this->sizeOfArray; ++i)
	{
		if (this->arr[i] > other.arr[i])
			return false;
	}
	return true;
}

class Set
{
private:
	IntBuffer elements;
	std::size_t elementsInSet;

public:
	Set();
	void insert(int value);
	bool contains(int value) const;
	std::size_t size() const;

private:
	bool binarySearch(int, int) const;
	void insertHelper(int);
};

Set::Set() : elements(2), elementsInSet(0)
{
}
void Set::insert(int value)
{
	int counter = 0;

	for (int i = 0; i < elementsInSet; ++i)
	{
		if (elements[i] != value)
		{
			++counter;
		}
	}
	if (counter == elementsInSet)
	{
		insertHelper(value);
	}
	if (counter < elementsInSet)
	{
		std::cout << "This element is already here";
	}
}
void Set::insertHelper(int value)
{
	int indexWhereIsAValue = 0;
	int *helperBuffer = new int[elementsInSet + 1];
	for (int i = 0; i < elementsInSet;)
	{
		if (this->elements[i] < value)
		{
			helperBuffer[i] = this->elements[i];
			++i;
		}
		else
		{
			helperBuffer[i] = value;
			indexWhereIsAValue = i;
			i += elementsInSet;
		}
	}
	if (indexWhereIsAValue == 0)
	{
		helperBuffer[elementsInSet] = value;
	}
	else
	{
		for (int i = indexWhereIsAValue; i < elementsInSet; ++i)
		{
			helperBuffer[i + 1] = elements[i];
		}
	}
	IntBuffer h(helperBuffer, this->elementsInSet + 1);
	elements = h;
}
bool Set::contains(int value) const
{
	return binarySearch(value, elementsInSet);
}
bool Set::binarySearch(int value, int helper) const
{
	int index;
	index = helper / 2;
	if (elements[index] == value)
		return true;
	if (value < elements[index])
	{
		return binarySearch(value, index);
	}
	else
	{
		return binarySearch(value, index + helper - 1);
	}
}
std::size_t Set::size() const
{
	return elementsInSet;
}

int main()
{

	return 0;
}