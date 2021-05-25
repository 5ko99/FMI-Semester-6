// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Костадин Маринов Нарлиев
// ФН: 81975
// Специалност: Компютърни науки
// Курс: Втори
// Административна група: Втора
// Ден, в който се явявате на контролното: 24.04.2021г.
// Начален час на контролното: 9:30
// Кой компилатор използвате: GCC
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
#include <cstddef>
#include <algorithm>
#include <cstdlib>

class IntBuffer
{
public:
	int* array_of_numbers = nullptr;
	int allocated = 0;
	int used = 0;
public:
	IntBuffer(); // Заради грешка на 148 ред
	IntBuffer(std::size_t size)
	{
		int* array_of_numbers = new int[size];
		allocated=size;
		used=0;
	}
	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		int* array_of_numbers = new int[size];
		allocated=size;
		used=0;
		if(this->allocated>=other.allocated)
		{
			for (int i = 0; i < other.allocated; i++)
			{
				this->array_of_numbers[i]=other.array_of_numbers[i];
				used++;
			}
		}
		else
		{
			for (int i = 0; i < this->allocated; i++)
			{
				array_of_numbers[i]=other.array_of_numbers[i];
				used++;
			}
		}
	}
	int& at(std::size_t index)
	{
		if(index<used)
		{
			return array_of_numbers[index];
		}
	}
	const int& at(std::size_t index)const
	{
		if(index<used)
		{
			return array_of_numbers[index];
		}
	}
	int& operator[](std::size_t index)
	{
		return array_of_numbers[index];
	}
	const int& operator[](std::size_t index)const
	{
		return array_of_numbers[index];
	}
	std::size_t size() const
	{
		return used;
	}
	void copy_from(const IntBuffer& other, std::size_t count)
	{
		if(this->allocated>=count && other.allocated>=count)
		{
			for (int i = 0; i < count; i++)
			{
				this->array_of_numbers[i]=other.array_of_numbers[i];
			}
			
		}
	}
	bool operator==(const IntBuffer& other)const
	{
		if(this->allocated!=other.allocated) return false;
		if(this->used!=other.used) return false;
		for (int i = 0; i < this->used; i++)
		{
			if(this->array_of_numbers[i]!=other.array_of_numbers[i]) return false;
		}
		return true;
	}
	bool operator<(const IntBuffer& other)const
	{
		if(this->allocated>other.allocated) return false;
		if(this->used>other.used) return false;
		for (int i = 0; i < this->used; i++)
		{
			if(this->array_of_numbers[i]>other.array_of_numbers[i]) return false;
		}
		return true;
	}
	void clear()
	{
		array_of_numbers=nullptr;
		allocated=0;
		used=0;
	}
	~IntBuffer()
	{
		delete[] array_of_numbers;
		clear();
	}
};

class Set
{
public:
	IntBuffer elements;

	Set()
	{
		elements(2);
	}
	void sorting_and_add(const int value, IntBuffer arr)
	{
	
		if(arr.used==0)
		{
			arr.array_of_numbers[0]=value;
			arr.used++;
		}
		else
		{
			bool contains=false;
			for (int i = 0; i < arr.used; i++)
			{
				if(arr.array_of_numbers[i]==value)
				{
					contains=true;
					break;
				}
			}
			if(contains==false && arr.allocated>arr.used)
			{
				arr.used++;
				int index=arr.used-1;
				arr.array_of_numbers[index]=value;
				for (int i = 0; i < arr.used-1; i++)
				{
					if(value<arr.array_of_numbers[i])
					{
						index=i;
						break;
					}
					else if(value>arr.array_of_numbers[i] && value<arr.array_of_numbers[i+1])
					{
						index=i+1;
						break;
					}
				}
				if(index!=arr.used-1)
				{
					for (int i = arr.used-1; i >= index; i--)
					{
						if(i!=index)
						{
							arr.array_of_numbers[i]=arr.array_of_numbers[i-1];
						}
						else
						{
							arr.array_of_numbers[i]=value;
						}
					}
				}
			}
			else if(contains==false && arr.allocated==arr.used)
			{
				IntBuffer buffer(2*arr.allocated);
				for (int i = 0; i < arr.used; i++)
				{
					buffer.array_of_numbers[i]=arr.array_of_numbers[i];
					buffer.used++;
				}
				buffer.used++;
				int index=buffer.used-1;
				buffer.array_of_numbers[index]=value;
				for (int i = 0; i < buffer.used-1; i++)
				{
					if(value<buffer.array_of_numbers[i])
					{
						index=i;
						break;
					}
					else if(value>buffer.array_of_numbers[i] && value<buffer.array_of_numbers[i+1])
					{
						index=i+1;
						break;
					}
				}
				if(index!=buffer.used-1)
				{
					for (int i = buffer.used-1; i >= index; i--)
					{
						if(i!=index)
						{
							buffer.array_of_numbers[i]=buffer.array_of_numbers[i-1];
						}
						else
						{
							buffer.array_of_numbers[i]=value;
						}
					}
				}
				arr.clear();
				arr(buffer.allocated,buffer);
			}
		}
	}
	void insert(int value)
	{
		sorting_and_add(value, elements);
	}
	bool contains(int value)const
	{
		for (int i = 0; i < elements.used; i++)
		{
			if(elements.array_of_numbers[i]==value) return true;
		}
		return false;
	}
	std::size_t size()const
	{
		return elements.used;
	}
};

int main()
{
	std::size_t N;
	std::cout << "Input N:";
	std::cin >> N;
	Set generated;
	for (int i = 0; i < N; i++)
	{
		generated.insert(std::rand());
	}
	Set guessed;
	int guessed_number=0;
	while(guessed.size()!=generated.size())
	{
		std::cout << "Input suggested number:";
		std::cin >> guessed_number;
		if(generated.contains(guessed_number))
		{
			guessed.insert(guessed_number);
			std::cout << "Good guess!" << std::endl;
		} 
		else std::cout << "Sorry! Try again." << std::endl;
	}
	return 0;
}