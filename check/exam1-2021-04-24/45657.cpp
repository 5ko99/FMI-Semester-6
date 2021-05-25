// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Светослав Богданов
// ФН: 45657
// Специалност: Информатика
// Курс: 2.
// Административна група: 4.
// Ден, в който се явявате на контролното: 24.04.2021г.
// Начален час на контролното: 9:30 ч.
// Кой компилатор използвате: Visual C++
//
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

using std::cout;
using std::cin;
using std::endl;
using std::string;

size_t min(size_t a, size_t b);

bool moddedBinarySearch(const IntBuffer& arr, size_t size, int key);

class IntBuffer
{
private:
	size_t size;
	int* arr;
public:
	IntBuffer(size_t size) : size(size)
	{
		try
		{
			arr = new int[size];
		}
		catch (const std::bad_alloc& e)
		{
			cout << e.what();
		}
	}

	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		try
		{
			arr = new int[size];
		}
		catch (const std::bad_alloc& e)
		{
			cout << e.what();
		}

		size_t n = min(size, other.size);

		for (size_t i = 0; i < n; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	~IntBuffer()
	{
		delete[] arr;
	}

	int& at(size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("invalid index");
		}
		return arr[index];
	}

	const int& at(size_t index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("invalid index");
		}
		return arr[index];
	}

	int& operator[](size_t index)
	{
		assert(index >= size);
		return arr[index];
	}

	const int& operator[](size_t index) const
	{
		assert(index >= size);
		return arr[index];
	}

	size_t getSize() const //size_t size() const
	{
		return size;
	}

	void copy_from(const IntBuffer& other, size_t count)
	{
		if (size < count || other.size < count)
		{
			throw std::out_of_range(" ");
		}
		for (size_t i = 0; i < count; ++i)
		{
			arr[i] = other.arr[i];
		}
	}

	bool operator==(const IntBuffer& other) const
	{
		if (this->size == other.size)
		{
			for (size_t i = 0; i < size; ++i) {
				if (arr[i] != other.arr[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool operator<(const IntBuffer& other) const
	{
		size_t minSize = min(size, other.size);
		for (size_t i = 0; i < minSize; ++i)
		{
			if (arr[i] > other.arr[i])
			{
				return false;
			}
		}
		return true;
	}
};

class Set
{
private:
	size_t capacity;
	size_t used;
	IntBuffer elements;
public:
	Set(IntBuffer& elements, size_t size) : elements(elements), capacity(2)
	{

	}

	bool contains(int value) const
	{
		return moddedBinarySearch(elements, used, value);
	}

	void insert(int value)
	{
		bool isValueContained = contains(value);

		if (!isValueContained || used < capacity - 1)
		{
			for (size_t i = 0; i < used; ++i)
			{
				if (value > elements[i])
				{
					for (size_t j = i; i < used; ++j)
					{
						elements[j + 1] = elements[j];
					}
					elements[i] = value;
					break;
				}
			}
		}

		++used;
	}

	size_t size() const
	{
		return used;
	}
};

int main()
{

	return 0;
}

size_t min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

bool moddedBinarySearch(const IntBuffer& arr, size_t size, int key)
{
	int l = 0;
	int h = size - 1;
	while (h - l > 0)
	{
		int mid = (l + h) / 2;
		if (arr[mid] == key)
		{
			return true;
		}
		else if (arr[mid] > key)
		{
			h = mid;
		}
		else
		{
			l = mid;
		}
	}
	if (arr[l] == key || arr[h] == key)
	{
		return true;
	}

	return false;
}