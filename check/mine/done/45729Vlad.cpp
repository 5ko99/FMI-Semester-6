// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Владимир Стоянов
// ФН:45729
// Специалност:Информатика
// Курс:1
// Административна група:6
// Ден, в който се явявате на контролното: 
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
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cctype>

class Registration 
{
public:
	Registration(const char* regNumber) 
	{
		if (!isValidRegNumber(regNumber)) 
		{
			throw std::exception();
		}

		this->regNumber = new char[strlen(regNumber) + 1];
		strcpy(this->regNumber, regNumber);
		
	}
	~Registration() 
	{
		delete[] this->regNumber;
		this->regNumber = nullptr;
	}
	

	Registration& operator=(const char* str) 
	{


		if (&this->regNumber != &str  ) 
		{
			if (!isValidRegNumber(str)) 
			{
				throw std::exception();
			}
			char* newMemory = new char[strlen(str) + 1];
			strcpy(newMemory, str);
			delete[] this->regNumber;
			this->regNumber = newMemory;
		
		}
	
		return *this;
	}

	bool operator==(const char* str) const 
	{
		return strcmp(this->regNumber, str) == 0;
	
	}

	const char* toString() const 
	{
		return this->regNumber;
	}

	const char* getCarNumber()const 
	{
		return this->regNumber;
	}

private:
	char* regNumber;

	bool isValidRegNumber(const char* regNum) 
	{
		if (strlen(regNum) > 8 || strlen(regNum) < 6) 
		{
			return false;
		}

		int inc = 0;

		if (!isalpha(regNum[0])) 
		{
			return false;
		}

		if (isalpha(regNum[1])) 
		{
			for (size_t i = 2; i < 6; i++)
			{
				if (!isdigit(regNum[i])) 
				{
					return false;
				}

			}
			for (size_t i = 6; i < strlen(regNum); i++)
			{
				if (!isalpha(regNum[i])) 
				{
					return false;
				}
				++inc;
				if (inc > 2) {
					return false;
				}
			}

		}else

		if (isdigit(regNum[1])) {
		
			for (size_t i = 2; i < 5; i++)
			{
				if (!isdigit(regNum[i]))
				{
					return false;
				}
			}

			for (size_t i = 6; i < strlen(regNum); i++)
			{
				if (!isalpha(regNum[i]))
				{
					return false;
				}
				++inc;
				if (inc > 2) {
					return false;
				}
			}

		}

		if (inc != 2) 
		{
			return false;
		}
		
		return true;
	}
	

};


class Vehicle 
{
public:
	Vehicle(const char* carNumber, const char* desctiption)
	{

		this->carNumber = new Registration(carNumber);
		this->description = new char[strlen(desctiption) + 1];
		strcpy(this->description, desctiption);
	}
	Vehicle& operator=(const Vehicle* other) 
	{
		if ((&this->carNumber != &other->carNumber) && (&this->description!=&other->description) ) 
		{
			char* newDesc = new char[strlen(other->description) + 1];
			strcpy(newDesc, this->description);

			delete[] this->description;
			this->description = newDesc;
		}
	
	}

	~Vehicle()
	{
		delete[] this->description;
		delete[] this->carNumber;
		this->description = nullptr;
		this->carNumber = nullptr;
	}

	const char* getCarNumber()const 
	{
		return carNumber->getCarNumber();
	}

private:
	Registration* carNumber;
	char* description;

};

class VehicleList 
{
public:
	VehicleList(std::size_t capacity)
	{
		this->initialCapacity = capacity;
		this->initialSize = 0;
		this->vehicles = new Vehicle * [capacity];
	}

	~VehicleList() 
	{
		for (size_t i = 0; i < this->initialSize; i++)
		{
			delete this->vehicles[i];
		}
	}

	void insert(const char* regnum, const char* description) 
	{
		if (this->initialSize >= this->initialCapacity) {
			throw std::exception();

		}
		
		Vehicle* vehicle =new  Vehicle(regnum, description);

		if (isDuplicatedCarNumber(vehicle)) 
		{
			throw std::exception();
		}

		

		this->vehicles[this->initialSize] = vehicle;
	
		++this->initialSize;
	}

	const Vehicle& at(std::size_t index) const 
	{
		if (index < 0 || index >= this->initialCapacity) 
		{
			throw  std::out_of_range("invalid index");
		}

		return *this->vehicles[index];
	
	}
	bool empty() const 
	{
		return this->initialSize == 0;
	}

	std::size_t capacity() const 
	{
		return this->initialCapacity;
	}

	std::size_t size() const
	{
		return this->initialSize;
	}

	const Vehicle* find(const char* regnum) const 
	{
		for (size_t i = 0; i < this->initialSize; i++)
		{
			if (strcmp(vehicles[i]->getCarNumber(), regnum) == 0) 
			{
				return vehicles[i];
			}
		}
		
		return nullptr;
	}

private:
	std::size_t initialCapacity;
	std::size_t initialSize;
	Vehicle** vehicles;

	bool isDuplicatedCarNumber( Vehicle*& car) 
	{
		for (size_t i = 0; i < this->initialSize; i++)
		{
			if (strcmp(car->getCarNumber(), this->vehicles[i]->getCarNumber()) == 0) 
			{
				return true;
			}
		}
		return false;
	}

};



int main()
{
	std::cout << "Enter number: ";
	size_t n;

	std::cin >> n;
	
	VehicleList vl = VehicleList(n);

	char* regNum=new char[9];
	char* carDesc=new char[100];

	for (size_t i = 0; i < n; i++)
	{
		std::cout << "Enter car Number: ";
		std::cin >> regNum;

		std::cout << "Enter carDesc: ";
		std::cin >> carDesc;

		
		try
		{
			vl.insert(regNum, carDesc);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			i--;
		}
		


	}

	std::cout << "insertion success" << std::endl;

	std::cout << "Enter car number to find in the system :" << std::endl;

	std::cin >> regNum;

	if (vl.find(regNum)) 
	{
		std::cout << "There is car with that number " << std::endl;
	}
	else
	{
		std::cout << "There is not  car with that number " << std::endl;


	}


	delete[] regNum;
	delete[] carDesc;
	return 0;
}