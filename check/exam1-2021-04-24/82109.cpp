// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Христо Тихомиров Христов
// ФН: 82109
// Специалност: Компютърни науки
// Курс: 2
// Административна група: 3
// Ден, в който се явявате на контролното: 24.04.21
// Начален час на контролното: 9:30
// Кой компилатор използвате: C++
//

#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <stdexcept> 

class IntBuffer {
	size_t size;
	int* arr;

public:
	IntBuffer(size_t size)
	{
		this->size = size;
		try {
			arr = new int[size];
		}
		catch (std::bad_alloc ecvt)
		{
			throw(ecvt);
		}
	}

	IntBuffer(IntBuffer& other)
	{
		delete[] this->arr;
		this->size = other.size;
		this->arr = new int[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}

	IntBuffer(std::size_t size_, const IntBuffer& other)
	{
		try
		{
			if (size_ > other.size)
			{
				this->size = other.size;
				this->arr = new int[size];
				for (int i = 0; i < size; i++)
				{
					arr[i] = other.arr[i];
				}
			}
			else
			{
				this->size = size_;
				this->arr = new int[size];
				for (int i = 0; i < size; i++)
				{
					arr[i] = other.arr[i];
				}
			}
		}
		catch (const std::bad_alloc ecvt)
		{
			throw(ecvt);
		}
	}

	int& at(std::size_t index)
	{
		if (index >= this->size)
		{
			throw "std::out_of_range";
		}
		else
		{
			return arr[index];
		}
	}

	const int& at(std::size_t index) const
	{
		if (index >= this->size)
		{
			throw "std::out_of_range";
		}
		else
		{
			return arr[index];
		}
	}

	int &operator[](std::size_t index)
	{
		assert(index < this->size);
		return arr[index];
	}

	const int &operator[](std::size_t index) const
	{
		assert(index < this->size);
		return arr[index];
	}

	std::size_t get_size() const
	{
		size_t const_copy = this->size;
		return const_copy;
	}

	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if (count > other.size || count > this->size)
		{
			throw "std::out_of_range";
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				arr[i] = other.arr[i];
			}
		}
	}

	bool operator==(const IntBuffer& other) const
	{
		if (this->size != other.size)
		{
			return false;
		}
		else
		{
			bool temp = true;
			for (int i = 0; i < size; i++)
			{
				if (arr[i] != other.arr[i])
				{
					temp = false;
				}
			}
			return temp;
		}
	}

	bool operator<(const IntBuffer& other) const
	{
		int cnt;
		if (this->size > other.size)
		{
			cnt = other.size;
		}
		else
		{
			cnt = this->size;
		}

		for (int i = 0; i < size; i++)
		{
			if (arr[i] > other.arr[i])
			{
				return false;
			}
		}
		
		return true;
	}

	~IntBuffer()
	{
		this->size = 0;
		delete[] arr;
	}
};

class Set {
	size_t size;
	int* arr;

public:
	Set()
	{
		this->size = 0;		
	}

	void insert(int value)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == value)
			{
				return;
			}
		}

		int *newArr = new int[size++];
		int index;
		for (int i = 0; i < size; i++)
		{
			if (value > arr[i])
			{			
			}
			else
			{
				index = 1;
			}
		}

		for (int i = 0; i < index; i++)
		{
			newArr[i] = this->arr[i];
		}
		for (int i = index; i > 0; i--)
		{
			newArr[i] = this->arr[i - 1];
		}
		newArr[index] = value;
	}

	bool binary_search(int l, int r, int value) const
	{
		if (r>=l)
		{
			int mid = l + (r - l) / 2;
			if (arr[mid] == value)
			{
				return true;
			}
			else if (arr[mid] > value)
			{
				return binary_search(l, mid - 1, value);
			}
			else
			{
				return binary_search(mid + 1, r, value);
			}
		}
		return false;
	}

	bool contains(int value) const
	{
	   return binary_search(0, size, value);
	}

	std::size_t get_size() const
	{
		return this->size;
	}

	~Set()
	{
		delete[] arr;
		this->size = 0;
	}
};

int main()
{
	std::size_t n;
	std::cin >> n;





	return 0;
}