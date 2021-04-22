// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Яни Енчев
// ФН: 45818
// Специалност: Информатика
// Курс: 1
// Административна група: 6 
// Ден, в който се явявате на контролното: 17.4.2021
// Начален час на контролното: 8
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
#include <cstddef>
#include <string>
#include <stdexcept>


bool isValidRegistration(const char* str);
void clearVehicleList(Vehicle** arr, size_t size);

class Registration
{
public:
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;
private:
	char symbols[9];

};

class Vehicle
{
public:
	Vehicle(const char* regnum, const char* description);
	const Registration regnum;
	std::string description;
};



Vehicle::Vehicle(const char* regnum, const char* description)
	: regnum(regnum), description(description)
{
}

class VehicleList
{
public:
	VehicleList(std::size_t capacity);
	VehicleList(VehicleList& other);
	~VehicleList();
	VehicleList& operator= (VehicleList& other);
	//void insert(const char* regnum, const char* description);
	const Vehicle& at(std::size_t index) const;
	const Vehicle& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t Capacity() const;
	std::size_t size() const;
	const Vehicle* find(const char* regnum) const;

private:
	size_t capacity;
	size_t vehiclesNumber;
	size_t capacityLeft;
	Vehicle** vehicles;
};

const Vehicle* VehicleList::find(const char* regnum) const
{
	for (size_t i = 0; i < this->vehiclesNumber; i++)
		{
			const char* tempReg = this->vehicles[i][0].regnum.toString();
			if (strcmp(tempReg, regnum) == 0)
			{
				delete[] tempReg;
				return &(this->vehicles[i][0]);
			}
		}

	return nullptr;
}

std::size_t VehicleList::size() const
{
	return this->vehiclesNumber;
}

std::size_t VehicleList::Capacity() const
{
	return this->capacity;
}

bool VehicleList::empty() const
{
	if (this->vehiclesNumber == 0)
		return true;

	return false;
}

const Vehicle& VehicleList::operator[](std::size_t index) const
{
	assert(this->vehiclesNumber <= index);
		
	return this->vehicles[index][0];
}

const Vehicle& VehicleList::at(std::size_t index) const
{
	if (this->vehiclesNumber <= index)
		throw std::out_of_range("Index wanted is out of range");

	return this->vehicles[index][0];
}

//void VehicleList::insert(const char* regnum, const char* description)
//{
//	for (size_t i = 0; i < this->vehiclesNumber; i++)
//	{
//		const char* tempReg = this->vehicles[i][0].regnum.toString();
//		if (strcmp(tempReg, regnum) == 0)
//		{
//			delete[] tempReg;
//			throw std::exception("Registration number is already in");
//		}
//	}
//
//	if (this->capacityLeft == 0)
//		throw std::exception("No more space left!");
//
//	Vehicle** temp = new Vehicle * [this->vehiclesNumber + 1]{ nullptr };
//	try
//	{
//		for (size_t i = 0; i < this->vehiclesNumber; i++)
//		{
//			temp[i][0] = this->vehicles[i][0];
//		}
//	}
//
//	catch (std::bad_alloc& e)
//	{
//		std::cout << "Error appeared while allocating memory!" << std::endl;
//		clearVehicleList(temp, this->vehiclesNumber);
//		throw;
//	}
//
//
//}

VehicleList& VehicleList::operator= (VehicleList& other)
{
	if (this == &other)
		return other;

	Vehicle** temp = new Vehicle * [other.vehiclesNumber]{ nullptr };
	try
	{
		for (size_t i = 0; i < other.vehiclesNumber; i++)
		{
			const char* tempDesc = other.vehicles[i][0].description.c_str();
			const char* tempRegNum = other.vehicles[i][0].regnum.toString();
			temp[i] = new Vehicle(tempRegNum, tempDesc);
			delete[] tempDesc;
			delete[] tempRegNum;
		}
	}

	catch (std::bad_alloc& e)
	{
		std::cout << "Error appeared while allocating memory!" << std::endl;
		clearVehicleList(temp, other.vehiclesNumber);
		throw;
	}

	this->vehicles = temp;
	this->capacity = other.capacity;
	this->vehiclesNumber = other.vehiclesNumber;
	this->capacityLeft = other.capacityLeft;

}

VehicleList::VehicleList(VehicleList& other)
{
	//if(this == &other)
	Vehicle** temp = new Vehicle * [other.vehiclesNumber]{nullptr};
	try
	{
		for (size_t i = 0; i < other.vehiclesNumber; i++)
		{
			const char* tempDesc = other.vehicles[i][0].description.c_str();
			const char* tempRegNum = other.vehicles[i][0].regnum.toString();
			temp[i] = new Vehicle(tempRegNum, tempDesc);
			delete[] tempDesc;
			delete[] tempRegNum;
		}
	}

	catch (std::bad_alloc& e)
	{
		std::cout << "Error while allocating memory appeared!" << std::endl;
		clearVehicleList(temp, other.vehiclesNumber);
		throw;
	}

	this->vehicles = temp;
	this->capacity = other.capacity;
	this->vehiclesNumber = other.vehiclesNumber;
	this->capacityLeft = other.capacityLeft;
}

VehicleList::~VehicleList()
{
	clearVehicleList(this->vehicles, this->vehiclesNumber);
}

VehicleList::VehicleList(std::size_t capacity)
	:capacity(capacity), capacityLeft(capacity) ,vehiclesNumber(0)
{
	vehicles = nullptr;
}

const char* Registration::toString() const
{
	size_t regLen = strlen(this->symbols);

	char* temp = new char[regLen + 1];

	strcpy(temp, this->symbols);
	temp[regLen] == 0;
	return temp;
}

bool Registration::operator==(const char* str) const
{
	if (str == nullptr)
		return false;

	if (strcmp(this->symbols, str) == 0)
		return true;

	else return false;
}

Registration& Registration::operator=(const char* str)
{
	if (isValidRegistration(str))
	{
		size_t strLen = strlen(str);
		strcpy(this->symbols, str);
	}


	else throw std::exception("Invalid registration number!");
}

Registration::Registration(const char* str)
{
	if (isValidRegistration(str))
	{
		size_t strLen = strlen(str);
		strcpy_s(this->symbols, str);
	}
		

	else throw
		std::exception("Invalid registration number!");
}

bool isValidRegistration(const char* str)
{
	if (!isalpha(str[0]))
		return false;

	if (isalpha(str[1]))
	{
		for(size_t i=2; i<6; i++)
			if(!isdigit(str[i]))
				return false;

		for(size_t i=6; i<8; i++)
			if(!isalpha(str[i]))
				return false;

		if (str[8] != 0)
			return false;
	}

	else
	{
		for (size_t i = 1; i < 5; i++)
			if (!isdigit(str[i]))
				return false;

		for (size_t i = 5; i < 7; i++)
			if (!isalpha(str[i]))
				return false;

		if (str[7] != 0)
			return false;
	}
}

void clearVehicleList(Vehicle** arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		delete arr[i];

	delete arr;
}

int main()
{
	size_t N;
	std::cin >> N;

	VehicleList test(N);
	//...

	return 0;
}