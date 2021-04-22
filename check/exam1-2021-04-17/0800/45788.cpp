// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: 
// ФН: 45788
// Специалност: Информатика
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
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
using namespace std;

class Registration
{
private:
	char* reg;
public:
	Registration(const char* str)
	{
		reg = new char[9];

		reg[0] = 'A' - 'Z';
		reg[1] = ('A' - 'Z') || ('0' - '9');
		reg[2] = '0' - '9';
		reg[3] = '0' - '9';
		reg[4] = '0' - '9';
		reg[5] = ('0' - '9') || ('A' - 'Z');
		reg[6] = 'A' - 'Z';
		reg[7] = 'A' - 'Z';

		if ((strlen(str) > 9 || strlen(str) < 8) && strcmp(reg, str))
		{
			throw exception("Invalid Registration");
		}
	}

	~Registration()
	{
		delete[] reg;
	}

	Registration& operator=(const char* str)
	{
		if ((strlen(str) > 9 || strlen(str) < 8) && strcmp(reg, str))
		{
			throw exception("Invalid Registration!");
		}
	}

	bool operator == (const char* str) const
	{
		if (strcmp(reg, str) == 0)
		{
			return true;
		}
	}

	const char* toString() const
	{
		return reg;
	};
};


class Vehicle
{
public:
	const Registration regnum;
	const string description;

	void copyFrom(Registration regNum, string Description)
	{
		regNum = regnum;
		Description = description;
	}

	Vehicle(const char* regnum, const char* description)
	{
		copyFrom(regnum, description);
	}
};

class VehicleList
{
public:
	size_t* capacity;
	VehicleList()
	{
		capacity = 0;
	}

	~VehicleList()
	{
		delete[] capacity;
	}

	void copyFrom(size_t* Capacity)
	{
		Capacity = capacity;
	}

	VehicleList(size_t capacity)
	{
		copyFrom(&capacity);
		VehicleList list;
		list.capacity = &capacity;
	}

	void insert(const char* regnum, const char* description)
	{
		VehicleList list;
		Vehicle vehicle;

		if ((strlen(regnum) < 8 || strlen(regnum) > 9) || strcmp(vehicle.regnum, regnum) == 0 || capacity > list.capacity)
		{
			throw exception("Invalid Registration or no Capacity!");
		}
	}

	const Vehicle& at(std::size_t index) const
	{

	}

	const Vehicle& operator[](std::size_t index) const
	{

	}

	bool empty() const
	{

	}

	size_t capacity() const
	{
		size_t capacity;
		copyFrom(&capacity);
		return capacity;
	}

	size_t size() const
	{

	}

	const Vehicle* find(const char* regnum) const
	{
		Vehicle vehicle;
		if(vehicle.regnum == regnum)
		{
			return ;
		}
		else 
		{
			return nullptr;
		}
	}
};


int main()
{

	return 0;
}
