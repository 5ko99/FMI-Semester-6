// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Александър Михайлов Тангълов
// ФН: 45752
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Registration
{
private:
	char registration[9];
	int length;

public:
	Registration& operator=(Registration& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < length; i++)
			{
				registration[i] = other.registration[i];
			}
		}

		return *this;
	}
	Registration(Registration& other)
	{
		length = other.length;
		for (int i = 0; i < length; i++)
		{
			registration[i] = other.registration[i];
		}
	}
	bool isValid(const char* str)
	{
		if (strlen(str) == 7)
		{
			try
			{
				if (!isalpha(str[0]))
				{
					throw std::exception("The first symbol is not a letter");
				}
			}
			catch (std::exception)
			{
				std::cerr << "The first symbol is not a letter.";
			}
			
			try
			{
				for (int i = 1; i = 4; i++)
				{
					if (!isdigit(str[i]))
					{
						throw std::exception("One of the symbols 2-5 is not a digit");
					}
				}
			}
			catch (std::exception)
			{
				std::cerr << "One of the symbols 2-5 is not a digit";
			}
			
			try
			{
				for (int i = 5; i = 6; i++)
				{
					if (!isalpha(str[i]))
					{
						throw std::exception("One of the last 2 symbols is not a letter");
					}
				}
			}
			catch (std::exception)
			{
				std::cerr << "One of the last 2 symbols is not a letter.";
			}
			if (strlen(str) == 8)
				try
			{
				for (int i = 0; i = 1; i++)
				{
					if (!isalpha(str[i]))
					{
						throw std::exception("One of the symbols 1-2 is not a letter");
					}
				}
			}
			catch (std::exception)
			{
				std::cerr << "One of the symbols 1-2 is not a digit";
			}
			try
			{
				for (int i = 2; i = 5; i++)
				{
					if (!isdigit(str[i]))
					{
						throw std::exception("One of the symbols 3-6 is not a digit");
					}
				}
			}
			catch (std::exception)
			{
				std::cerr << "One of the symbols 3-6 is not a digit";
			}
			try
			{
				for (int i = 6; i = 7; i++)
				{
					if (!isalpha(str[i]))
					{
						throw std::exception("One of the last 2 symbols is not a letter");
					}
				}
			}
			catch (std::exception)
			{
				std::cerr << "One of the last 2 symbols is not a letter.";
			}
		}
		return 1;
	}
	Registration(const char* str)
	{
		if (isValid(str)) {
			for (int i = 0; i = 7; i++)
			{
				registration[i] = str[i];
			}
		}
	}
	Registration& operator=(const char* str)
	{
		if (isValid(str))
		{
			for (int i = 0; i = 7; i++)
			{
				registration[i] = str[i];
			}
		}

		return *this;
	}
	bool operator==(const char* str)
	{
		for (int i = 0; i = 7; i++)
		{
			if (registration[i] != str[i])
			{
				return 0;
			}
			return 1;
		}
	}
	const char* toString() const
	{
		return registration;
	}
};

class Vehicle
{
private:

public:	
	Registration regnum;
	std::string description;
	Vehicle(const char* regnum, const char* description)
	{
		this->regnum = regnum;
		this->description = description;
	}
};

class VehicleList
{
private:
	std::size_t capacity;
	std::size_t used;
	std::size_t vehicleCount;
	Vehicle** vehicleArray;
	char* regList;

public:
	VehicleList(std::size_t capacity)
	{
		this->capacity = capacity;
		used = 0;
		vehicleCount = 0;
		regList = new char [capacity];
		vehicleArray = new Vehicle * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			vehicleArray[i] = new Vehicle[i];
		}
	}
	VehicleList()
	{
		capacity = 10;
		used = 0;
		vehicleCount = 0;
		regList = new char[10];
		vehicleArray = new Vehicle * [10];
		for (int i = 0; i < 10; i++)
		{
			vehicleArray[i] = new Vehicle[i];
		}
	}
	~VehicleList()
	{
		for (int i = 0; i < capacity; i++)
		{
			delete vehicleArray[i];
		}
		delete[] vehicleArray;
		delete[] regList;
	}
	VehicleList(VehicleList& other)
	{
		capacity = other.capacity;
		used = other.used;
		vehicleCount = other.vehicleCount;
		for (int i = 0; i < capacity; i++)
		{
			vehicleArray[i] = other.vehicleArray[i];
		}
	}
	VehicleList& operator=(VehicleList& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < capacity; i++)
			{
				delete vehicleArray[i];
			}
			delete[] vehicleArray;
			capacity = other.capacity;
			used = other.used;
			vehicleCount = other.vehicleCount;
			for (int i = 0; i < capacity; i++)
			{
				vehicleArray[i] = other.vehicleArray[i];
			}
		}

		return *this;
	}
	void insert(const char* regnum, const char* description)
	{
		Vehicle currentVehicle(regnum, description);
		try 
		{
			used++;
			if (used > capacity)
			{
				throw std::exception("Not enough space");
			}
		}
		catch (std::exception)
		{
			std::cerr << "Not enough space";
		}
		
		try
		{
			char* currentRegistration;
			for (int i = 0; i < used; i++)
			{
				currentRegistration[i] = regList[i];
				if (currentRegistration[i] == *regnum)
				{
					throw std::exception("A car with the same registration is already in the list");
				}
			}			
		}
		catch (std::exception)
		{
			std::cerr << "A car with the same registration is already in the list";
		}
		
		try
		{ 	
			if (!currentVehicle.regnum.isValid(regnum))
			{
				throw std::exception("Registration is inalid");
			}
		}
		catch (std::exception)
		{
			std::cerr << "Registration is invalid";
		}

		vehicleCount++;
		regList[used] = *regnum;		
		vehicleArray[used] = &currentVehicle;
	}
	const Vehicle& at(std::size_t index) const
	{
		try
		{
			if (!vehicleArray[index])
			{
				throw std::out_of_range("No vehicle at given idex");
			}
		}
		catch (std::out_of_range)
		{
			std::cerr << "No vehicle at given idex";
		}

		return *vehicleArray[index];
	}
	const Vehicle& operator[](std::size_t index) const
	{
		return at(index);
	}
	bool empty() const
	{
		return !used;
	}
	std::size_t capacity() const
	{
		return capacity;
	}
	std::size_t size() const
	{
		return vehicleCount;
	}
};



int main()
{

	return 0;
}