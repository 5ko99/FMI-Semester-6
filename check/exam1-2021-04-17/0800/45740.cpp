// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Росен Евтимов
// ФН: 45740
// Специалност: Информатика
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: <Visual C++>
//

 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Registration
{
private:
	char* registration = new char[9];

public:
	bool isRegNumberCorrect(const char* str)
	{
		bool isalpha(str[0]);
		return isalpha;
		for (int i = 2; i < 5; i++)
		{
			bool isdigit(str[i]);
			return isdigit;
		}

		for (int i = 6; i < 7; i++)
		{
			bool isalpha(str[i]);
			return isalpha;
		}
	}

	Registration(const char* str)
	{
		if (isRegNumberCorrect(str))
		{
			strcpy_s(this->registration, 8, str);
		}
		throw std::exception("Registration number invalid.");	
	}

	Registration& operator=(const char* str)
	{
		
		if (isRegNumberCorrect(str))
		{
			strcpy_s(this->registration, 8, str);
		}
		throw std::exception("Registration number invalid.");
	}

	bool operator==(const char* str) const
	{
		if( strcmp (this->registration, str) == 0)
		{
			return true;
		}
		return false;
	}

	const char* toString() const
	{
		return this->registration;
	}
}
;

class Vehicle
{
public:
	Registration& regnum = new const char [9];
	std::string description;

	Vehicle(const char* regnum, const char* description)
	{
		this->regnum = regnum;
		this->description = description;
	}
}
;

class VehicleList
{
private:
	std::string* regNumbers;
	std::string* descriptions;
	std::size_t capacity;

public:
	VehicleList(std::size_t capacity)
	{
		this->capacity = capacity;
		regNumbers = new std::string[capacity];
		descriptions = new std::string[capacity];
	}

	VehicleList()
	{
		regNumbers = nullptr;
		descriptions = nullptr;
		capacity = 0;
	}

	VehicleList& operator=(VehicleList& otherList)
	{
		if ((this->capacity != otherList.capacity) || (this->regNumbers != otherList.regNumbers) || (this->descriptions != otherList.descriptions))
		{
			this->regNumbers = nullptr;
			this->descriptions = nullptr;
			this->capacity = 0;

			if ( otherList.capacity || otherList.regNumbers || otherList.descriptions)
			{
				this->regNumbers = new std::string[otherList.capacity + 1];
				strcpy_s(regNumbers, otherList.capacity +1, otherList.regNumbers);
				this->descriptions = new std::string[capacity];
				strcpy_s(descriptions, otherList.capacity + 1, otherList.descriptions);
				this->capacity = otherList.capacity;
			}
		}
		return *this;
	}

	~VehicleList()
	{
		delete[] regNumbers;
		delete[] descriptions;
	}

	void insert(const char* regnum, const char* description)
	{
		for (int i = 0; i < capacity; i++)
		{
			regNumbers[i] = regnum;
		}
	}

	const Vehicle& at(std::size_t index) const
	{
		return regNumbers[index];
		return descriptions[index];
	}

	const Vehicle& operator[](std::size_t index) const
	{
		assert(index > 0);
		return at(index);
	}

	bool empty() const
	{
		if (regNumbers || descriptions)
		{
			return "full";
		}
		return "empty";
	}
	
	std::size_t capacity() const
	{
		return this->capacity;
	}

	std::size_t size() const
	{

	}

	std::size_t size() const
	{
		
	}
};

int main()
{
	Registration("A2345BD");
    return 0;
}