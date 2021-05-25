// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Деян Борисов Цветков
// ФН: 45625
// Специалност: Информатика
// Курс: II
// Административна група: II
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

class IntBuffer
{
public:
	IntBuffer(const IntBuffer& other)
	{
		copy(other);
	}
	IntBuffer& operator=(const IntBuffer& other)
	{
		if (this != &other)
		{
			clear();
			copy(other);
		}
		return *this;
	}
	~IntBuffer()
	{
		clear();
	}

	IntBuffer(std::size_t size)
	{
		m_arr = new int[size];
		if (!m_arr)
		{
			throw bad_alloc();
		}
		m_size = size;
		//m_reserved = 0;
	}

	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		m_arr = new int[size];
		if (!m_arr)
		{
			throw bad_alloc();
		}
		size_t n = size < other.m_size ? size : other.m_size;
		for (size_t i = 0; i < n; i++)
		{
			m_arr[i] = other.m_arr[i];
		}
		m_size = size;
	}

	int& at(std::size_t index)
	{
		if (index <= m_size)
		{
			throw out_of_range("Index out of range!");
		}
		return m_arr[index];
	}

	int& operator[](std::size_t index)
	{
		assert(index < m_size);
		return m_arr[index];
	}

	const int& operator[](std::size_t index) const
	{
		assert(index < m_size);
		return m_arr[index];
	}

	std::size_t size() const
	{
		return m_size;
	}

	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if (m_size < count || other.m_size < count)
		{
			throw out_of_range("Invalid argument!");
		}

		for (size_t i = 0; i < count; i++)
		{
			m_arr[i] = other.m_arr[i];
		}
	}

	bool operator==(const IntBuffer& other) const
	{
		if (m_size != other.m_size)
		{
			return false;
		}

		for (size_t i = 0; i < m_size; i++)
		{
			if (m_arr[i] != other.m_arr[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator<(const IntBuffer& other) const
	{
		if (m_size < other.m_size)
			return true;
		else if (m_size > other.m_size)
			return false;
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_arr[i] < other.m_arr[i])
			{
				return true;
			}
		}

		return false;
	}

private:
	void copy(const IntBuffer& other)
	{
		int* newArr = new int[other.m_size];
		for (size_t i = 0; i < m_size; i++)
		{
			newArr[i] = other.m_arr[i];
		}
		m_arr = newArr;
		m_size = other.m_size;
	}
	void clear()
	{
		delete[] m_arr;
	}

	int* m_arr;
	size_t m_size;
	//size_t m_reserved;
};

class Set
{
public:
	Set()
		: m_elements(IntBuffer(2))
		, m_reserved(0)
	{}


	void insert(int value)
	{
		for (size_t i = 0; i < m_reserved; i++)
		{
			if (m_elements[i] == value)
			{
				return;
			}
		}

		if (m_reserved + 1 >= m_elements.size())
		{
			size_t newSize = m_elements.size() * 2;
			IntBuffer newElements(newSize, m_elements);
			m_elements = newElements;
			int ind = 0;
			while (ind < m_reserved && value > m_elements[ind])
			{
				ind++;
			}

			for (int i = m_reserved; i > ind; i--)
			{
				m_elements[i] = m_elements[i - 1];
			}
			m_elements[ind] = value;

			m_reserved++;
		}
		else
		{
			int ind = 0;
			while (ind < m_reserved && value > m_elements[ind])
			{
				ind++;
			}
			
			for (int i = m_reserved; i > ind; i--)
			{
				m_elements[i] = m_elements[i - 1];
			}
			m_elements[ind] = value;

			m_reserved++;
		}
	}

	bool contains(int value) const
	{
		if (m_reserved == 0)
		{
			return false;
		}

		int l = 0;
		int r = m_reserved - 1;
		while (l < r)
		{
			int mid = r - (l + r) / 2;
			if (value == m_elements[mid])
			{
				return true;
			}
			else if (value > m_elements[mid])
			{
				l += mid;
			}
			else
			{
				r -= mid;
			}
		}
		return m_elements[l] == value || m_elements[r] == value;
	}

	std::size_t size() const
	{
		return m_reserved;
	}
private:
	IntBuffer m_elements;
	size_t m_reserved;
};

int main()
{
	srand(time(0));
	size_t n;
	cout << "Enter count of numbers: ";
	cin >> n;

	Set generated, G;
	for (size_t i = 0; i < n; i++)
	{
		int num = rand();
		if (generated.contains(num))
		{
			i--;
			continue;
		}
		generated.insert(num);
	}

	while (G.size() < n)
	{
		cout << "Enter number to see is it in the set: ";
		int num;
		cin >> num;
		if (generated.contains(num))
		{
			G.insert(num);
		}
	}

	return 0;
}