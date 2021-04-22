// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Радослав Юлиянов Маринов
// ФН:45767
// Специалност:Информатика
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <8:00>
// Кой компилатор използвате: <Visual C++>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Registration
{
public:
	char* data = new char [9];

	~Registration()
	{
		delete[] this->data;
	}

	Registration(const char* str)
	{
		if (CheckNum(str) == 0)
			std::exception;
	}
	Registration& operator=(const char* str)
	{
		if (CheckNum(str) == 0)
			std::exception;
	}

	const char* toString(char* data) const
	{
		std::string newString = data;
	}

	bool CheckNum (const char* str)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if(strlen(str)==8)
			{ 
				if(i==0 || i>=5)
				{
					if (str[i] < 'A' && str[i] >'Z')
						return 0;
				}
				if (i > 0 || i < 5)
				{
					if (str[i] < '0' && str[i] > 9)
						return 0;
				}
			}

			if (strlen(str) == 9)
			{
				if (i == 0 || i == 1 || i >= 6)
				{
					if (str[i] < 'A' && str[i] >'Z')
						return 0;
				}
				if (i > 1 || i < 6)
				{
					if (str[i] < '0' && str[i] > 9)
						return 0;
				}
			}
		}
		return 1;
	}
};

class Vehicle
{
	Vehicle(const char* regnum, const char* description)
	{
		char* regnumnew = new char[strlen(regnum)];
		*regnumnew = *regnum;

		std::string* descriptionnew = new std::string[strlen(description)];
		*descriptionnew = *description;
	}
};

class VehicleList
{
	const size_t MAX_LIST_SIZE = 1024;
	size_t CURRENT_SIZE = 0;

	VehicleList(std::size_t capacity)
	{
		char* list = new char[capacity];
	}

	void insert(const char* regnum, const char* description)
	{
		if(CheckMaxSize(CURRENT_SIZE)!=0);
			std::exception;

		Registration::CheckNum(regnum);

		list[CURRENT_SIZE] = Vehicle::Vehicle(regnum, description);

		CURRENT_SIZE++;
	}

	const Vehicle& at(std::size_t index) const
	{
		if (index > MAX_LIST_SIZE)
			std::exception;

		if (list[index] == '\0')
			std::out_of_range;

		this->list = list[index];
		return this->list;
	}

	bool empty() const
	{
		if (list[at(CURRENT_SIZE)] == '\0')
			return 1;
		return 0;
	}

	std::size_t capacity() const
	{
		return MAX_LIST_SIZE;
	}

	std::size_t size() const
	{
		return CURRENT_SIZE;
	}

	const Vehicle* find(const char* regnum) const
	{
		for (int i = 0; i < CURRENT_SIZE; i++)
		{
			if (CheckIfSame(regnum, list[i]) == 1)
				return list[i];
		}
	}

	const bool CheckMaxSize(size_t CURRENT_SIZE) const
	{
		if (CURRENT_SIZE >= MAX_LIST_SIZE)
			std::exception;
		return 0;
	}

	bool CheckIfSame(const char* regnum1, const char* regnum2)
	{
		for (int i = 0; i < 9; i++)
		{
			if (regnum1[i] != regnum2[i])
				return 0;
		}
		return 1;
	}
};

int main()
{
	std::size_t N;
	std::cout << "Insert List Capacity"<<std::endl<<"N = ";
	std::cin >> N;
	VehicleList::VehicleList(N);

	for (int i = 0; i < N; i++)
	{
		char num[9];
		for (int j = 0; j < 9 j++)
		{
			std::cin >> num[j];
		}
		std::string desc;
		std::cin >> desc ;
		VehicleList::insert(num, desc);
	}

	return 0;
}