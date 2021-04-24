
// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Филип Емилов Карастоянов
// ФН: 45757
// Специалност: Информатика
// Курс:1
// Административна група:2
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
#include <stdexcept>
#include <cstddef>
class Registration
{
public:
	Registration(const char* _regNum)
	{
		if (checkValidation(_regNum))
		{
			strcpy(regNum, _regNum);
		}
		else throw std::exception("invalid registration");
		
	}
	
	Registration& operator=(const char* _regNum)
	{
		
		if (checkValidation(_regNum) && strcmp(regNum, _regNum) != 0)
		{
			strcpy(regNum, _regNum);
		}
		else throw std::exception("invalid registration");
			
		return *this;
	}
	bool operator == (const char* str) const
	{
		return !strcmp(regNum, str);
	}
	const char* toString() const
	{
		return this->regNum;
	}
private:
	char regNum[9];
	bool checkValidation(const char* _regNum)
	{
		for (unsigned i = 0; i < 9; i++)
		{
			switch (i)
			{
			case 0: if (!isalpha(_regNum[i])) return false; break;
			case 1:  if (!isalpha(_regNum[i]) && !isdigit(_regNum[i])) return false; break;
			case 2: if (!isdigit(_regNum[i])) return false; break;
			case 3: if (!isdigit(_regNum[i])) return false; break;
			case 4: if (!isdigit(_regNum[i])) return false; break;
			case 5:if (!isalpha(_regNum[i]) && !isdigit(_regNum[i])) return false; break;
			case 6:if (!isalpha(_regNum[i])) return false; break;
			case 7:if (!isalpha(_regNum[i])) return false; break;
			case 8: return false;
			}
		}
		return true;
	}

};

class Vehicle
{
public:
	Vehicle(const char* _regnum, const char* _description)
	{
		
		regnum = _regnum;
		description = _description;

	}

private:
	Registration regnum{"aa0000aa"};
	std::string description;
};
class VehicleList
{
public:
	VehicleList(size_t _capacity) : ListCapacity(_capacity), carCount(0)
	{
		cars = new Vehicle*[_capacity];
		
	}
	~VehicleList()
	{
		freeMemory();
		
	}
	VehicleList(VehicleList& other)
	{
		copyList(other);
	}
	VehicleList operator=(VehicleList& other)
	{
		if (this != &other)
		{
			copyList(other);
		}
		return *this;
	}
	bool empty() const
	{
		return carCount;
	}
	size_t capacity() const
	{
		return ListCapacity;
	}
	size_t size() const
	{
		return carCount;
	}
	const Vehicle& at(size_t pos) const
	{
		if (pos > carCount) throw std::out_of_range("No car at this index");
		return *cars[pos];
	}
	const Vehicle& operator[](size_t pos) const
	{
		assert(pos < carCount);
		return at(pos);
	}
	void insert(const char* regnum, const char* description)
	{
		if (carCount == ListCapacity) throw std::exception("Limit reached!");
		if (find(regnum) != nullptr) throw std::exception("Car already in the list");
		
			
	}
	const Vehicle* find(const char* regnum)
	{
		if (empty()) return nullptr;

		return nullptr;
	}

private:
	size_t ListCapacity;
	Vehicle** cars;
	size_t carCount;
	void copyList(VehicleList& other)
	{
		ListCapacity = other.capacity();
		freeMemory();
		cars = new Vehicle * [other.capacity()];

		for (unsigned i = 0; i < ListCapacity; i++)
		{
			
			
		}

	}
	void freeMemory()
	{
		
		delete[] cars;
	}
};
int main()
{
	size_t n;
	std::cout << "Input the size of the Vehicle list" << std::endl;
	std::cin >> n;
	VehicleList list{ n };
	
	return 0;
}