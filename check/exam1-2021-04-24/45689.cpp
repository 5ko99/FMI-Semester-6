// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Шазие Ходжова
// ФН: 45689
// Специалност: Информатика
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното:  24.04.2021г.
// Начален час на контролното: 9:30
// Кой компилатор използвате: MSVC
//

#define _CRT_SECURE_NO_WARNING

class IntBuffer
{
private:
	int* f_array;
	size_t f_size;

private:
	int min(int a, int b)
	{
		if (a > b)
		{
			return b;
		}
		else
			return a;
	}

	void clean()
	{
		delete[] f_array;
	}

	void copy(const IntBuffer& other)
	{
		f_size = other.f_size;

		int* f_array = new int[f_size];

		for (int i = 0; i < f_size; i++)
		{
			f_array[i] = other.f_array[i];
		}

	}


public:
	IntBuffer(const int* array, size_t size) : f_size(size)
	{

	}

	/*IntBuffer& (const IntBuffer& other)
	{
		if (this != &other)
		{
			copy(other);
		}

		return *this;
	}
	*/
	IntBuffer& operator=(const IntBuffer& other)
	{
		if (this != &other)
		{
			clean();
			copy(other);
		}

		return *this;
	}

	~IntBuffer()
	{
		clean();
	}

	 IntBuffer(std::size_t size)
	{
		int* arr = new int[size];
	}
	
	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		int* arr = new int[size];

		unsigned int n;

		n = min(size, other.f_size);

		for (int i = 0; i < n; i++)
		{
			arr[i] = other[i];
		}

	}

	int& at(std::size_t index)
	{
		for (int i = 0; i < f_size; i++)
		{
			if (i == index)
			{
				return f_array[index];
			}
		}
	}

	const int& at(std::size_t index) const
	{
		for (int i = 0; i < f_size; i++)
		{
			if (i == index)
			{
				return f_array[index];
			}
		}
	}

	int& operator[](std::size_t index)
	{
		for (int i = 0; i < f_size; i++)
		{
			if (i == index)
			{
				return f_array[index];
			}
		}
	}

	const int& operator[](std::size_t index) const
	{
		for (int i = 0; i < f_size; i++)
		{
			if (i == index)
			{
				return f_array[index];
			}
		}
	}

	std::size_t size() const
	{
		int sizeOfArray = 0;
		for (int i = 0; i < f_size; i++)
		{
			sizeOfArray++;
		}
		
		std::cout << "The size of the array is: " << sizeOfArray;

		return sizeOfArray;
	}

	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if (f_size > count && other.f_size > count)
		{
			for (int i = 0; i < count; i++)
			{
				f_array[i] = other.f_array[i];
			}
		}

		//std::out_of_range

	}

	bool operator==(const IntBuffer& other) const
	{
		bool flag = false;

		if (f_size == other.f_size)
		{
			for (int i = 0; i < f_size; i++)
			{
				if (f_array[i] == other.f_array[i])
				{
					flag = true;
				}
				else
					flag = false;
			}

			flag = false;
		}
		
		return flag;
	}

	bool operator<(const IntBuffer& other) const
	{

	}

};

class Set
{
private:

	IntBuffer elements;
	int f_capacity;


	void resize(const Set& other, int newCapacity)
	{
		newCapacity = f_capacity * 2;

		int* buff = new int[newCapacity];

		for (int i = 0; i < newCapacity; i++)
		{
			
		}

		
	}

public:
	Set()
	{
	
	}

	~Set()
	{

	}

	void insert(int value)
	{

	}

	bool contains(int value) const
	{

	}

	std::size_t size() const
	{

	}

};








#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>

int main()
{

	return 0;
}