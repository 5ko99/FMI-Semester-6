//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Здравко Младенов
// ФН: 45555
// Специалност: Информатика
// Курс: 2
// Административна група: 2
// Ден, в който се явявате на контролното: 24.04.2021г.
// Начален час на контролното: 9:30
// Кой компилатор използвате: Visual C++

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class IntBuffer
{
private:
	int* data;
	size_t capacity;

public:
	IntBuffer(size_t size);
	~IntBuffer();
	IntBuffer(const IntBuffer& other);
	IntBuffer& operator=(const IntBuffer& other);
	IntBuffer(size_t size, const IntBuffer& other);

	int& at(size_t index);
	const int& at(size_t index) const;
	int& operator[](size_t index);
	const int& operator[](size_t index) const;
	size_t size() const;
	void copy_from(const IntBuffer& other, size_t count);
	bool operator==(const IntBuffer& other) const;
	/*bool operator<(const IntBuffer& other) const;*/

private:
	void clean();
	void copyAllFrom(const IntBuffer& other);
};

IntBuffer::IntBuffer(size_t size) : capacity(size)
{
	try
	{
		data = new int[capacity];
	}
	catch (const std::exception&)
	{
		throw std::bad_alloc();
	}
}

IntBuffer::~IntBuffer()
{
	clean();
}

IntBuffer::IntBuffer(const IntBuffer & other)
{
	if (this != &other)
	{
		copyAllFrom(other);
	}
}

IntBuffer& IntBuffer::operator=(const IntBuffer & other)
{
	if (this != &other)
	{
		clean();
		copyAllFrom(other);
	}
	return *this;
}

IntBuffer::IntBuffer(size_t size, const IntBuffer & other)
{
	try
	{
		capacity = size;
		data = new int[capacity];

		if (size >= other.capacity)
		{
			for (size_t i = 0; i < other.capacity; i++)
			{
				data[i] = other.data[i];
			}
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				data[i] = other.data[i];
			}
		}
	}
	catch (std::exception&)
	{
		throw std::bad_alloc();
	}

}

int& IntBuffer::at(size_t index)
{
	if (index >= capacity)
	{
		throw std::out_of_range("The index is bigger than the array's size!");
	}
	else
	{
		return data[index];
	}
}

const int& IntBuffer::at(size_t index) const
{
	if (index >= capacity)
	{
		throw std::out_of_range("The index is bigger than the array's size!");
	}
	else
	{
		return data[index];
	}
}

int& IntBuffer::operator[](size_t index)
{
	return data[index];
}

const int& IntBuffer::operator[](size_t index) const
{
	assert(index < capacity);

	return data[index];
}

size_t IntBuffer::size() const
{
	return capacity;
}

void IntBuffer::copy_from(const IntBuffer & other, size_t count)
{
	if (capacity < count || other.capacity < count)
	{
		throw std::out_of_range("The wanted number is bugger than the size of the arrays!");
	}
	else
	{
		for (size_t i = 0; i < count; i++)
		{
			data[i] = other.data[i];
		}
	}
}

bool IntBuffer::operator==(const IntBuffer & other) const
{
	if (capacity != other.capacity)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < other.capacity; i++)
		{
			if (data[i] != other.data[i])
			{
				return false;
			}
		}
	}
	return true;
}

//bool IntBuffer::operator<(const IntBuffer &other) const
//{
//
//}

void IntBuffer::clean()
{
	delete[] data;
	capacity = 0;
}

void IntBuffer::copyAllFrom(const IntBuffer & other)
{
	capacity = other.capacity;
	data = new int[capacity];

	for (size_t i = 0; i < capacity; i++)
	{
		data[i] = other.data[i];
	}
}


class Set
{
private:
	IntBuffer elements;
	size_t count;
public:
	Set();
	
	void insert(int value);
	bool contains(int value) const;
	size_t size() const;

private:
	void sortElements();
};

Set::Set() : elements(2), count(0)
{
}

void Set::insert(int value)
{
	if (!contains(value))
	{
		try
		{
			if (count < elements.size())
			{
				elements[count] = value;
				count++;
				sortElements();
			}
			else
			{
				IntBuffer temp(elements.size() * 2, elements);
				elements = temp;
				elements[count] = value;
				count++;
				sortElements();
			}
		}
		catch (const std::exception&)
		{
			throw bad_alloc();
		}
	}
}

bool Set::contains(int value) const
{
	size_t left = 0;
	size_t right = elements.size() - 1;
	size_t mid;
	mid = (left + right) / 2;

	while (mid > 0)
	{
		if (elements[mid] == value)
		{
			return true;
		}
		else if (elements[mid] > value)
		{
			right = mid - 1;
		}
		else if (elements[mid] < value)
		{
			left = mid + 1;
		}
		mid = (left + right) / 2;
	}
	return false;
}

size_t Set::size() const
{
	return elements.size();
}

void Set::sortElements()
{
	for (size_t i = 0; i < count - 1; i++)
	{
		for (size_t j = 0; j < count - i - 1; j++)
		{
			if (elements[j] > elements[j+1])
			{
				swap(elements[j], elements[j + 1]);
			}
		}
	}
}


int main()
{
	size_t n;
	cout << "Input your set size" << endl;
	cin >> n;

	Set generated;
	size_t temp;
	for (size_t i = 0; i < n; i++)
	{
		temp = rand();
		if (generated.contains(temp))
		{
			while (generated.contains(temp))
			{
				temp = rand();
			}
			generated.insert(temp);
		}
		else
		{
			generated.insert(temp);
		}
	}

	Set userSet;
	size_t guessedNumber;
	do
	{
		cout << "Not it's your turn, find all numbers." << endl;
		cin >> guessedNumber;

		if (generated.contains(guessedNumber))
		{
			userSet.insert(guessedNumber);
		}

	} while (generated.size() != userSet.size());


	return 0;
}


