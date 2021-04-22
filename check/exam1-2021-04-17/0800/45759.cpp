// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Кристиян Костадинов Даскалов
// ФН: 45759
// Специалност: Информатика
// Курс: първи
// Административна група: 2-ра
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
#include <cctype>


class Registration
{
	char reg[9];
	void copy(const char* str) {
		for (int i = 0; i < 8; ++i) {
			reg[i] = str[i];
		}
	}
	bool type(const char* str)
	{
		return (strlen(str) < 9 && ((isalpha(str[0]) == 1 && isalpha(str[1]) == 1 && isdigit(str[2]) && isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5]) && isalpha(str[6]) == 1 && isalpha(str[7]) == 1) ||
			(isalpha(str[0]) == 1 && isdigit(str[1]) && isdigit(str[2]) && isdigit(str[3]) && isdigit(str[4]) && isalpha(str[5]) == 1 && isalpha(str[6]) == 1) ));
	}

public:
	Registration() = delete;
	Registration(const char* str)
	{
		if(type(str))
		{
			copy(str);
		}
		else {
			throw std::exception("Not Valid registration type");
		}
	}
	Registration& operator=(const char* str)
	{
		if (type(str))
		{
			copy(str);
		}
		else {
			throw std::exception("Not Valid registration type");
		}
	}
	bool operator==(const char* str) const
	{
		bool equal = true;
		for (int i = 0; i < 8; ++i) {
			if (reg[i] != str[i])
			{
				equal = false;
				break;
			}
		}
		return equal;
	}
	const char* toString() const
	{
		return reg;
	}
};

class Vehicle
{
	Registration* regnum;
	std::string description;

public:
	Vehicle() = delete;
	Vehicle(const char* regnum, const char* description)
	{
		this->regnum =new Registration(regnum);
		this->description = description;
	}
};

class VehicleList
{
	Vehicle** list;
	const std::size_t* capacity;
	unsigned taken = 0;

public:
	VehicleList(std::size_t capacity) {
		list = new Vehicle * [capacity];
		this->capacity = new std::size_t(capacity);
	}
	VehicleList(const Vehicle& other) {
		//taken++;
		*list[taken++] = other;
	}
	
	VehicleList& operator=(const VehicleList& other)
	{
		Vehicle** buffer = new Vehicle * [*(other.capacity) + 1];
		delete[] *list;
		list = buffer;
		capacity = other.capacity;
		taken = other.taken;

	}

	~VehicleList()
	{
		for (unsigned i = 0; i < *capacity; ++i)
		{
			delete[] list[i];
		}
		delete[] list;
		delete[] capacity;
	}

	void insert(const char* regnum, const char* description)
	{
		if (taken++ >= *capacity)
		{
			throw std::exception("the vehicle list reached its capasity");
		}
		else {
			Vehicle a(regnum, description);
			*list[taken - 1] = a;
		}
	}
	const Vehicle& at(std::size_t index) const
	{
		if (index > taken)
			throw std::out_of_range("there is no element at this position");
		return *list[index];
	}
	const Vehicle& operator[](std::size_t index) const
	{
		assert(index < taken);
		return *list[index];
	}
	bool empty() const
	{
		return taken == 0;
	}
	std::size_t capacity() const
	{
		return *capacity;
	}
	std::size_t size() const
	{
		return taken;
	}
	/*
	
	const Vehicle* find(const char* regnum) const
	{
		for (int i = 0; i < taken; ++i)
		{
			if(list[i])
		}
		return nullptr;
	}
	*/

};

int main()
{
	int N;
	std::cin >> N;
	VehicleList myList(N);
	for (int i = 0; i <= N; ++i)
	{
		char helpArr[9];
		std::cout << "Registration: ";
		std::cin >> helpArr;
		Registration helpReg(helpArr);
		std::string helpDescription;
		std::cout << "Description: ";
		std::cin >> helpDescription;
		myList.insert(helpArr, helpDescription);
	}



	return 0;
}