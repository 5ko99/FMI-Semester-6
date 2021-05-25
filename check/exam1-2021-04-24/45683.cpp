// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Димитър Венциславов Колев
// ФН: 45683
// Специалност: Информатика
// Курс: Втори
// Административна група: Първа
// Ден, в който се явявате на контролното: 24.04.2021г.
// Начален час на контролното: <9:30>
// Кой компилатор използвате: <Visual C++>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

class IntBuffer
{
public:
	//Constructors
	IntBuffer() = delete;
	IntBuffer(std::size_t size);
	IntBuffer(std::size_t size, const IntBuffer& other);
	IntBuffer& operator=(const IntBuffer& other);
	~IntBuffer();

	//Methods
	int& at(std::size_t index);
	const int& at(std::size_t index) const;
	int& operator[](std::size_t index);
	const int& operator[](std::size_t index) const;
	std::size_t size() const;
	bool operator==(const IntBuffer& other) const;
	bool operator<(const IntBuffer& other) const;
	void copy_from(const IntBuffer& other, std::size_t count);

private:
	int* m_buffer;
	size_t m_count;
	size_t m_capacity;

	//Helpers
	void clear();
	void copy(const IntBuffer& other);
};

class Set
{
public:
	//Constructors
	Set();
	~Set();

	//Methods
	bool hasSameElements(int elem);
	void sortElements();
	void insert(int value);
	std::size_t size() const;
	bool contains(int value) const;
	void print() const;

private:
	IntBuffer** elements;
	size_t m_count;
	size_t m_capacity;

	//Helper
	void resize();
};

int main()
{
	IntBuffer buffer{ 4 };
	Set set;
	set.insert(4);
	set.insert(2);
	set.insert(5);
	set.print();
	return 0;
}

IntBuffer::IntBuffer(std::size_t size)
{
	m_capacity = size;
	m_count = 0;
	m_buffer = new int [m_capacity];
	if (!m_buffer)
		throw std::bad_alloc();
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer& other)
{
	m_count = other.m_count;
	m_capacity = other.m_capacity;

	int newCap = (other.m_count < size) ? other.m_count : size;

	m_buffer = new int[newCap];
	if (!m_buffer)
		throw std::bad_alloc();

	for (size_t i = 0; i < m_count; ++i)
		m_buffer[i] = other.m_buffer[i];
}

IntBuffer& IntBuffer::operator=(const IntBuffer& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

IntBuffer::~IntBuffer()
{
	clear();
}

int& IntBuffer::at(std::size_t index)
{
	if (index > m_count)
		throw std::out_of_range("Index is out of range!");

	return m_buffer[index];
}

const int& IntBuffer::at(std::size_t index) const
{
	if (index > m_count)
		throw std::out_of_range("Index is out of range!");

	return m_buffer[index];
}

int& IntBuffer::operator[](std::size_t index)
{
	assert(index <= m_count);
	return m_buffer[index];
}

const int& IntBuffer::operator[](std::size_t index) const
{
	assert(index <= m_count);
	return m_buffer[index];
}

std::size_t IntBuffer::size() const
{
	return m_capacity;
}

bool IntBuffer::operator==(const IntBuffer& other) const
{
	bool flag = true;
	for (size_t i = 0; i < m_count; ++i)
	{
		if (m_buffer[i] != other.m_buffer[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}

bool IntBuffer::operator<(const IntBuffer& other) const
{
	bool flag = true;
	for (size_t i = 0; i < m_count; ++i)
	{
		if (m_buffer[i] > other.m_buffer[i])
		{
			flag = false;
			break;
		}
		else if (m_buffer[i] == other.m_buffer[i])
			continue;
	}
	return flag;
}

void IntBuffer::copy_from(const IntBuffer& other, std::size_t count)
{
	m_count = other.m_count;
	m_capacity = other.m_capacity;

	if (m_capacity < count || other.m_capacity < count)
		throw std::out_of_range("Out of range!");

	m_buffer = new int[other.m_count];
	for (size_t i = 0; i < other.m_count; ++i)
		m_buffer[i] = other.m_buffer[i];
}

void IntBuffer::clear()
{
	delete[] m_buffer;
	m_buffer = nullptr;
}

void IntBuffer::copy(const IntBuffer& other)
{
	m_capacity = other.m_capacity;
	m_count = other.m_count;

	m_buffer = new int[m_capacity];
	for (size_t i = 0; i < m_count; ++i)
		m_buffer[i] = other.m_buffer[i];
}

Set::Set()
{
	m_capacity = 2;
	m_count = 0;
	elements = new IntBuffer*[m_capacity];
}

Set::~Set()
{
	for (size_t i = 0; i < m_count; ++i)
		delete elements[i];

	delete[] elements;
}

bool Set::hasSameElements(int elem)
{
	for (size_t i = 0; i < m_count; ++i)
	{
		if (elements[i]->at(i) == elem)
		{
			return true;
			break;
		}
	}
	return false;
}

void Set::sortElements()
{
	for (size_t i = 0; i < m_count - 1; ++i)
	{
		for (size_t j = 0; j = m_count - i - 1; ++j)
		{
			if (elements[j]->at(j) > elements[j + 1]->at(j + 1))
			{
				std::swap(elements[j], elements[j + 1]);
			}
		}
	}
}

void Set::insert(int value)
{
	if (m_count == m_capacity)
		resize();

	int* newElem = new int(value);
	if (!hasSameElements(*newElem))
		elements[m_count++]->operator[](m_count++) = *newElem;

	if (m_count > 1)
		sortElements();
}

std::size_t Set::size() const
{
	return m_count;
}

bool Set::contains(int value) const
{
	for (size_t i = 0; i < m_count; ++i)
	{
		if (elements[i]->operator[](i) == value)
		{
			return true;
			break;
		}
	}
	return false;
}

void Set::print() const
{
	for (size_t i = 0; i < m_count; ++i)
		std::cout << elements[i]->at(i) << '\n';
}

void Set::resize()
{
	m_capacity *= 2;

	IntBuffer** newElements = new IntBuffer * [m_capacity];
	if (!newElements)
		throw std::bad_alloc();

	for (size_t i = 0; i < m_count; ++i)
	{
		newElements[i] = elements[i];
	}

	delete[] elements;
	elements = newElements;
}
