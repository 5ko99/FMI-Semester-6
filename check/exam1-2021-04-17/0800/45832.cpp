// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Анастасия Стефанова Стефанова
// ФН: 45832
// Специалност: Информатика
// Курс: 1
// Административна група: 6
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual Studio Code
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

class Registration
{
	private:
	const char* registration;
	std::size_t regNumber;

	public:
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;
};

Registration::Registration(const char* str)
{
	if(str)
	{
		this->regNumber;
		this-> regNumber = strlen(registration));
	}
	else
	{
		regNumber = nullptr;
		registration = nullptr;
	}
}

Registration& Registration::operator=(const char* str)
{
	if(str)
	{
		this-> registration = new char[registration.str];
		strcpy[this->registration, str];
	}
	return *this;
}

bool Registration::operator==(const char* str) const
{
	if(registration != str.registration)
	{
		return true;
	}
	return false;
}

const char* Registration::toString() const
{

}


class  Vehicle
{
	public:
	Registration* regNum;
	std::string descriptions;
	Vehicle(const char* regnum, const char* description);
};

Vehicle::Vehicle(const char* regnum, const char* description)
{
	if(regnum, description)
	{
		this->regNum = new char [regnum];
		this-> descriptions = new char[description];
	}
	else
	{
		this->regNum = nullptr;
		this->descriptions = nullptr;
	}
}

class VehicleList
{
	private:
	std::size_t capacity;
	std::size_t cars;

	public:
	VehicleList(std::size_t capacity);
	VehicleList(const VehicleList& list);
	~VehicleList();
	VehicleList& operator=(const VehicleList& other);
	void insert(const char* regnum, const char* description);
	const Vehicle& at(std::size_t index) const;
	const Vehicle& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;
	const Vehicle* find(const char* regnum) const;
};

VehicleList::VehicleList(std::size_t capacity)
{

}

VehicleList::VehicleList(const VehicleList& list)
{

}

VehicleList::~VehicleList()
{

}

VehicleList &VehicleList::operator=(const VehicleList& other)
{
	if (this != &other)
	{
		
	}
}

void VehicleList::insert(const char* regnum, const char* description)
{

}

const Vehicle& VehicleList::at(std::size_t index) const
{

}

const Vehicle& VehicleList::operator[](std::size_t index) const
{

}

bool VehicleList::empty() const
{

}

std::size_t VehicleList::capacity() const
{

}

std::size_t VehicleList::size() const
{

}

const Vehicle* VehicleList::find(const char* regnum) const
{

}


int main()
{

	return 0;
}