// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Искендер Чавдаров Чобаанов
// ФН: 45508
// Специалност: Информатика
// Курс:3-ти
// Административна група:-
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: Visual C++
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
#include <cstring>
#include <iostream>
#include <string>

class IntBuffer
{
private:
	int* arr;
//	size_t curr;
	size_t cap;
public:
	IntBuffer(std::size_t size=2);
	IntBuffer(const IntBuffer&);
	IntBuffer& operator=(const IntBuffer&);
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
	arr = new int[size];
	for (std::size_t i = 0; i < size; i++)
		arr[i] = 0;
	//curr = 0;
	cap = size;
}
IntBuffer& IntBuffer::operator=(const IntBuffer& other)
{
	if (this != &other)
	{
		if (cap >= other.cap)
		{
          int* buffer = new int[cap];
		  for (std::size_t i = other.cap; i < cap; i++)
			  arr[i] = 0;
		for (std::size_t i = 0; i < other.cap; i++)
	    buffer[i] = other.arr[i];

		delete[] arr;
		arr = buffer;
		}
		else
		{
			int* buffer = new int[other.cap];
			for (std::size_t i = cap; i < other.cap; i++)
				buffer[i] = 0;
			for (std::size_t i = 0; i < cap; i++)
				buffer[i] = other.arr[i];

			delete[] arr;
			arr = buffer;
		}
		

		return *this;
		
	}
	return *this;
}
/*IntBuffer::IntBuffer(const IntBuffer& other)
{
	if (cap > other.cap)
	{
		int* buffer = new int[cap];
		for (std::size_t i = 0; i < cap; i++)
			buffer[i] = 0;
		for (std::size_t i = 0; i < other.cap; i++)
			buffer[i] = other.arr[i];

		delete[] arr;
		arr = buffer;
	}
	if(cap<other.cap)
	{
		int* buffer = new int[other.cap];
		for (std::size_t i = 0; i < cap; i++)
			buffer[i] = 0;
		for (std::size_t i = 0; i < cap; i++)
			buffer[i] = other.arr[i];

		delete[] arr;
		arr = buffer;
	}
	if (cap = other.cap)
	{
		for (std::size_t i = 0; i < cap; i++)
			arr[i] = other.arr[i];
	}
}
*/
IntBuffer::~IntBuffer()
{
	delete[] arr;
}
IntBuffer::IntBuffer(std::size_t size, const IntBuffer& other)
{
	if (size >= other.cap)
	{
		for (std::size_t i = 0; i < other.cap; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	else {
		for (std::size_t i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}
}
int& IntBuffer::at(std::size_t index)
{
	if (index >= cap)
		throw std::out_of_range("Index out of range");
	return arr[index];
}
const int& IntBuffer::at(std::size_t index) const
{
	if (index >= cap)
		throw std::out_of_range("Index out of range");
	return arr[index];

}
std::size_t IntBuffer::size() const
{
	return cap;
}
void IntBuffer::copy_from(const IntBuffer& other, std::size_t count)
{
	if (count >= cap)
		throw std::out_of_range("Index out of range");
	for (size_t i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
}

bool IntBuffer::operator==(const IntBuffer& other) const
{
	if (cap == other.cap)
	{
		bool equal = 1;
		for (std::size_t i = 0; i < cap; i++)
		{
			if (arr[i] != other.arr[i])
				equal = 0;

		}
		return equal;
	}
	return false;
}
bool IntBuffer::operator<(const IntBuffer& other) const
{
	if (cap < other.cap)
		return true;
	if (cap > other.cap)
		return false;
	
	for (std::size_t i = 0; i < cap; i++)
	{
		if (arr[i] > other.arr[i])
			return false;
	}
	return true;
}
int& IntBuffer::operator[](std::size_t index)
{
	if (index >= cap)
		throw std::out_of_range("Index out of range");
	return arr[index];
}
const int& IntBuffer::operator[](std::size_t index) const
{
	if (index >= cap)
		throw std::out_of_range("Index out of range");
	return arr[index];
}



class Set {
private:
	IntBuffer elements;
	std::size_t curr;
	std::size_t cap;
	public:
		Set();
		void insert(int value);
		bool contains(int value) const;
		std::size_t size() const;
};

Set::Set()
{

	IntBuffer elementSet(2);
	elements = elementSet;
	std::size_t curr;
	std::size_t cap ;
}
void Set::insert(int value)
{
	if (curr+1 < cap)
	{
		if (elements[curr] == value)
		{
			return;
		}
		curr++;
		elements[curr] = value;
	}
	else {
		IntBuffer buffer(2 * cap);
		elements = buffer;
		cap *= 2;
		curr++;
		elements[curr] = value;

	}
	for (int i = 0; i < curr; i++)
	{
		for (int j = 0; j < curr; j++)
		{
			if (elements[i] > elements[j])
			{
				int buff = elements[j];
				elements[j] = elements[i];
				elements[i] = buff;
			}

		}
	}

}
std::size_t Set::size() const
{
	return cap;
}
//bool Set::contains(int value) const
//{

//}
int main()
{


	
	return 0;
}