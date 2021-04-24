// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Самуил Антонов Миланов
// ФН: 45744
// Специалност: Информатика
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.21
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>


class Registration
{
private:

	char* Reg = new char [9];
public:
	Registration(const char* str)
	{
		if (strlen(str) > 9)
		{
			throw std::exception("Not a valid Reg number");
		}
		strcpy(Reg, str);
	}
	
	Registration& operator=(const char* str)
	{
		if (strlen(str) > 9)
		{
			throw std::exception("Not a valid Reg number");
		}
		strcpy(Reg, str);

		return *this;
	}
	bool operator==(const char* str) const
	{
		bool equal = false;
		if (strcmp(this->Reg, str) == 0)
		{
			equal = true;
		}
		return equal;
	}
	const char* toString() const
	{
		return &this->Reg[0];
	}

};

class Vehicle {
private:
	const Registration* RegNum;
	std::string description;
public:
	Vehicle(const char* regnum, const char* description)
	{
		this->description = description;
		this->RegNum = new Registration(regnum) ;
	}
	
	const Registration& getreg()
	{
		return *this->RegNum;
	}
};

class VehicleList
{
private:
	std::size_t capacity = 0;
	Vehicle** List;
	std::size_t TakenSpaces = 0;
public:
	VehicleList(std::size_t capacity)
	{
		this->List = new Vehicle*[capacity];
	}
	~VehicleList()
	{
		delete [] List;
	}
	VehicleList(VehicleList & v)
	{
		this->capacity = v.capacity;
		for (std::size_t i = 0; i < this->capacity; i++)
		{
			this->List[i] = v.List[i];
		}
	}
	VehicleList& operator=(VehicleList & v)
	{
		this->List = v.List;
		return *this;
	}
	void insert(const char* regnum, const char* description)
	{
		if (strlen(regnum) <= 9)
		{
			this->List[TakenSpaces] = new Vehicle(regnum, description);
			TakenSpaces++;
		}
		
	}
	const Vehicle& at(std::size_t index) const
	{
		if (index > TakenSpaces + 1)
		{
			throw std::out_of_range("Invalid Position");
		}
		return *this->List[index];
	}
	const Vehicle& operator[](std::size_t index) const
	{
		assert(index < TakenSpaces + 1);
		return *this->List[index];
	}
	bool empty() const
	{
		if (TakenSpaces == 0)
		{
			return true;
		}
		return false;
	}
	std::size_t getcapacity() const
	{
		return this->capacity;
	}
	std::size_t size() const
	{
		return this->TakenSpaces;
	}
	const Vehicle* find(const char* regnum) const
	{
		for (size_t i = 0; i < TakenSpaces; i++)
		{
			if (strcmp(this->List[i]->getreg().toString(), regnum) == 0)
			{
				return this->List[i];
			}
		}
		return nullptr;
	}


};

void FindOrQuit(VehicleList& List)
{
	std::cout << "Press 1 to find a car, or 2 to quit" << std::endl;
	int command;
	std::cin >> command;
	if (command == 1)
	{
		char* reg = new char[9];
		std::cin >> reg;
		if (List.find(reg) == nullptr)
		{
			std::cout << "The car is not in the List" << std::endl;
			FindOrQuit(List);
			return;
		}
		std::cout << "The car is in the List"<< std::endl;
		FindOrQuit(List);
		return;
	}
	return;
}


int main()
{
	std::cout << "How much space for Vehicles is needed?" << std ::endl;
	size_t n;
	std::cin >> n;
	VehicleList List(n);
	for (size_t i = 0; i < n; i++)
	{
		char* reg = new char [9];
		char* descr = new char [512];
		std::cin >> reg;
		std::cin >> descr;
		List.insert(reg, descr);
	}
	
	FindOrQuit(List);

	return 0;
}