// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Йоанна Сиркова
// ФН: 82037
// Специалност: КН
// Курс: 2
// Административна група: 1
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате:  Visual C++
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib> 

class IntBuffer
{
	std::size_t mySize=0;
	int* myArray=nullptr;
public:
	IntBuffer(std::size_t size)
	{
		this->mySize = size;
		myArray = new int[this->mySize];
		
	}
	~IntBuffer()
	{
		delete[] myArray;
		mySize = 0;
	}
	IntBuffer(const IntBuffer& other)
	{
		delete[] myArray;
		myArray = new int[other.mySize];
		if (myArray == nullptr)
			throw std::bad_alloc();
		mySize = other.mySize;
		for (std::size_t i = 0; i < mySize; i++)
			myArray[i] = other[i];
	}
	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		myArray = new int[size];
		if (myArray == nullptr)
			throw std::bad_alloc();
		size_t N = (size <= other.mySize) ? size : other.mySize;
		for (std::size_t i = 0; i < N; i++)
			myArray[i] = other.myArray[i];

	}
	int& at(std::size_t index)
	{
		if (index < 0 || index > mySize)
			throw std::out_of_range("This index is out of range");
		return myArray[index];
	}
	int& at(std::size_t index) const
	{
		if (index < 0 || index > mySize)
			throw std::out_of_range("This index is out of range");
		return myArray[index];
	}
	int& operator[](std::size_t index)
	{
		assert(index < 0 || index > mySize);
		return myArray[index];
	}
	int& operator[](std::size_t index) const
	{
		assert(index < 0 || index > mySize);
		return myArray[index];
	}
	std::size_t size() const
	{
		return mySize;
	}
	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if(count>mySize || count>other.mySize)
		 throw std::out_of_range("This count is out of range");
		for (std::size_t i = 0; i < count; i++)
			myArray[i] = other.myArray[i];
		
	}
	bool operator==(const IntBuffer& other) const
	{
		if (mySize != other.mySize) return 0;
		for (std::size_t i = 0; i < mySize; i++)
		{
			if (myArray[i] != other[i]) return 0;
		}
		return 1;
	}

	bool operator<(const IntBuffer& other) const
	{
		if (mySize < other.mySize) return 1;
		if (mySize > other.mySize) return 0;
		for (std::size_t i = 0; i < mySize; i++)
		{
			if ((char)myArray[i] < (char)other[i]) return 1;
			if ((char)myArray[i] > (char)other[i]) return 0;
		}
		return 0;
	}
	

};

class Set
{
	std::size_t usedCells;
	IntBuffer elements;
	
public:
	Set() : elements{ 2 }
	{
		elements[0] = INT_MAX;
		elements[1] = INT_MAX;
		usedCells = 0;
	}
	void insert(int value)
	{
		usedCells++;
		if (usedCells > elements.size())
		{
			IntBuffer helper{ usedCells * 2 };
			for (std::size_t i = 0; i < usedCells; i++)
			{
				helper[i] = elements[i];
			}

			elements = helper;

		}
		if (!contains(value))
		{
			for (size_t i = 0; i < usedCells; i++)
			{
				if (elements[i] > value)
				{
					int helper = elements[i];
					elements[i] = value;
					value = helper;
				}
			}
		}
	}
	bool contains(int value) const
	{
		for (size_t i = 0; i < elements.size(); i++)
		{
			if (elements[i] == value) return 1;
		}
		return 0;
	}
	std::size_t size() const
	{
		return usedCells;
	}

};


int main()
{

	size_t N;
	std::cin >> N;
	Set generated;
	for (size_t i = 0; i < N; i++)
		generated.insert(rand());

	Set G;
	while (G.size() != N)
	{
		int n;
		std::cin >> n;
		if (generated.contains(n)) std::cout << "Yes, generated contains " << n << "\n";
		else std::cout << "No, generated doesnt contains " << n << "\n";
		G.insert(n);
	}


	return 0;
}