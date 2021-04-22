// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Иван Стоилов
// ФН: 82179
// Специалност: компютърни науки
// Курс: 1-ви
// Административна група: 3-та
// Ден, в който се явявате на контролното: 17,04,2021
// Начален час на контролното: 08:00
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

#include <cassert>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

class Registration
{
private:
	const int registrationLenght = 9;
	char registration[9];

	bool isRegistrationValid (const char* str)
	{
		std::size_t currentRegLen = strlen(str);

		if (currentRegLen == 7)
		{
			if (!isalpha(str[0]))
			{
				return false;
			}
			else
			{
				for (std::size_t counter = 1; counter < currentRegLen-2; ++counter)
				{
					if (!isdigit(str[counter]))
					{
						return false;
					}
					
				}
				
				if (!(isalpha(str[currentRegLen - 2]) && isalpha(str[currentRegLen - 1])))
				{
					return false;
				}
				
			}

			return true;
		}

		else if (currentRegLen == 8)
		{
			if (!(isalpha(str[0]) && isalpha(str[1])))
			{
				return false;
			}
			else
			{
				for (std::size_t counter = 2; counter < currentRegLen-2; ++counter)
				{
					if (!isdigit(str[counter]))
					{
						return false;
					}
					
				}

				if (!(isalpha(str[currentRegLen - 2]) && isalpha(str[currentRegLen - 1])))
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
		
		
	}
	void setRegistration(const char *str)
	{
		std::size_t currentRegLen = strlen(str);
		
		for (std::size_t counter = 0; counter < currentRegLen; counter++)
		{
			registration[counter] = str[counter];
		}

		registration[currentRegLen] = '\0';
	}
	bool areEqual(const char* str, const char* source) const
	{
		for (std::size_t counter = 0; counter < 9; ++counter)
		{
			if (str[counter] != source[counter])
			{
				return false;
			}
			
		}

		return true;
	}


public:
	Registration(const char *str)
	{
		if (isRegistrationValid(str))
		{
			setRegistration(str);
		}
		else
		{
			throw("the registration number is incorrect");
		}
		
	}

	Registration &operator=(const char *str)
	{
		if (isRegistrationValid(str))
		{
			setRegistration(str);
		}
		else
		{
			throw("the registration number is incorrect");
		}

		return *this;
	}

	bool operator==(const char *str) const
	{
		const char *pointer = registration;
		return areEqual(pointer, str);
	}

	const char* toString() const
	{
		return this->registration;
	}
};

class Vehicle
{
public:
	const Registration registrationNumber;
	const std::string vehicleDescription;

	Vehicle(const char* regnum, const char* description) :registrationNumber(regnum), vehicleDescription(description)
	{
		
	}
};

class VehicleList
{
private:
	Vehicle **vehicleList;
	std::size_t capacity;
	int currentVehiclesCount;

	Vehicle** allocateMemory(std::size_t capacity)
	{
		Vehicle **vehicleList = nullptr;
		try
		{
			vehicleList = new Vehicle *[capacity];
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
		}

		return vehicleList;
	}

public:
	VehicleList(std::size_t capacity)
	{
		vehicleList = allocateMemory(capacity);
		this->capacity = capacity;
		currentVehiclesCount = 0;
	}

	~VehicleList()
	{
		for (std::size_t counter = 0; counter < currentVehiclesCount; ++counter)
		{
			delete[] vehicleList[counter];
		}

		delete[] vehicleList;
	}

	void insert(const char* regnum, const char* description)
	{

		if(currentVehiclesCount < capacity)
		{
			try
			{
				vehicleList[currentVehiclesCount] = new Vehicle(regnum, description);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
			
			currentVehiclesCount += 1;
		}
		else
		{
			throw("there is not enough space");
		}
		
	}

	const Vehicle& at(std::size_t index) const
	{
		if(index > capacity || index < 1)
		{
			throw("there is no car at that index");
		}

		return *vehicleList[index-1];
	}

	const Vehicle& operator[](std::size_t index) const
{
	assert((index < capacity && index >=0) && "the index is out of ran out of range");

	return *vehicleList[index];
}

	bool empty() const
	{
		if (currentVehiclesCount >0)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	std::size_t capacity() const
	{
		return this->capacity;
	}

	std::size_t size() const
	{
		return currentVehiclesCount;
	}
};

int main()
{
	std::size_t listCapacity;

	std::cin >> listCapacity;

	VehicleList vehicles (listCapacity);

	return 0;
}