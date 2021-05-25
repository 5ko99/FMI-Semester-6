// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Боряна Бурдева
// ФН:45513
// Специалност:Информатика
// Курс:2
// Административна група:1
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 09:30
// Кой компилатор използвате:  Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 


#include <cstddef>
#include<cstdlib>
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

const int MAX_SIZE = 1000;

class IntBuffer {
	int *masive[MAX_SIZE];
	std::size_t *size;

public:
	IntBuffer()
	{
		*masive = NULL;
		*size = 0;
	}

	~IntBuffer()
	{
		delete[]masive;
		delete[]size;
	}

	int getSize()const
	{
		return *size;
	}

	void setSize(int newSize)
	{
		*size = newSize;

	}
	 
	IntBuffer(const IntBuffer& k)
	{
		size = new std::size_t;
		*size = k.getSize();
	}


	IntBuffer(std::size_t sizef)
	{
		size = new std::size_t;
		*size = sizef;
	}

	int& at(std::size_t index)
	{	
		return *masive[index];
	}

	
};

class Set {

	IntBuffer elements;
public:
	Set(int value) :elements(value)
	{};
	
	


};

int main()
{

	return 0;
}