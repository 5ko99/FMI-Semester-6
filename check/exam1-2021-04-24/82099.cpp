// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Християн Ангелов
// ФН: 82099
// Специалност: КН
// Курс: 2
// Административна група: 3
// Ден, в който се явявате на контролното: 24.04.2021г.
// Начален час на контролното: 09:30
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>

int main()
{
	std::size_t n;
	std::cin >> n;

	Set generated;
	for (size_t i = 0; i < n; i++)
	{
		generated.insert(std::rand());
	}

	Set G;
	int matches = 0;
	int number;
	while (matches < n)
	{
		std::cin >> number;

		if (G.contains(number))
		{
			std::cout << "Already used";
			continue;
		}
		
		if (generated.contains(number))
		{
			std::cout << "Yes";
			matches++;
		}

		std::cout << "No";
	}

	return 0;
}

class IntBuffer {
public:
	IntBuffer(std::size_t size) : size(size)
	{
		try
		{
			data = new int[size];
		}
		catch (std::bad_alloc)
		{
			delete[] data;
			throw;
		}
	}

	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		std::size_t n = size;
		if (n > other.size())
		{
			n = other.size();
		}

		for (int i = 0; i < n; i++)
		{
			data[i] = other[i];
		}
	}

	IntBuffer(const IntBuffer& rhs) : data(rhs.data), size(rhs.size())
	{

	}

	~IntBuffer()
	{
		delete[] data;
	}

	IntBuffer& operator=(const IntBuffer& rhs)
	{
		if (this == &rhs)
			return *this;
		
		std::size_t size = rhs.size();
		int* new_data = new int[size];
		std::memcpy(new_data, rhs.data, size);
		delete[] data;
		data = new_data;
		return *this;
	}

	int& at(std::size_t index)
	{
		if (index > size)
		{
			throw std::out_of_range("Out of range");
		}

		return data[index];
	}

	const int& at(std::size_t index) const
	{
		if (index > size)
		{
			throw std::out_of_range("Out of range");
		}

		return data[index];
	}

	int& operator[](std::size_t index)
	{
		return data[index];
	}

	const int& operator[](std::size_t index) const
	{
		return data[index];
	}

	std::size_t size() const
	{
		return sizeof(data);
	}

	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if (count > other.size())
		{
			throw std::out_of_range("Out of range");
		}

		for (int i = 0; i < count; i++)
		{
			data[i] = other[i];
		}
	}

	bool operator==(const IntBuffer& other) const
	{
		return size == other.size();
	}

	bool operator<(const IntBuffer& other) const
	{
		// TODO
	}

private:
	int* data;
	std::size_t size;
};

class Set
{
public:
	Set()
	{

	}

	void insert(int value)
	{
		if (used >= elements->size())
		{
			elements = new IntBuffer(used * 2, elements);
		}

		used++;
	}

	bool contains(int value) const
	{
		if (binarySearch(0, used, value) != -1)
		{
			return true;
		}

		return false;
	}

	std::size_t size() const
	{
		return used;
	}

private:
	IntBuffer* elements = new IntBuffer(2);
	std::size_t used = 0;

	int binarySearch(int l, int r, int x) const
	{
		if (r >= l) {
			int mid = l + (r - l) / 2;

			if (elements->at(mid) == x)
				return mid;

			if (elements->at(mid) > x)
				return binarySearch(l, mid - 1, x);

			return binarySearch(mid + 1, r, x);
		}

		return -1;
	}
};