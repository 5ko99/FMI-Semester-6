//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Деян Крумов
// ФН: 45803
// Специалност: Информатика
// Курс: 1-ви
// Административна група: 5-та
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <8:00>
// Кой компилатор използвате: <Visual C++>
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
	char number[9];

	bool validation(const char *str)
	{
		unsigned symbolcount = 7;
		if (!(isalpha(str[0])))
		{
			std::cout << 1 << std::endl;
			return false;
		}
		else if (isalpha(str[1]))
		{
			symbolcount = 8;
		}
		else if ((isalpha(str[symbolcount - 2] && isalpha(str[symbolcount - 1]))))
		{
			std::cout << 2 << std::endl;
			return false;
		}
		else
		{
			for (unsigned i = 2; i < 7; i++)
			{
				if (!isalnum(str[i]))
				{
					std::cout << 3 << std::endl;
					return false;
				}
			}
		}

		return true;
	}

public:
	Registration(const char *str)
	{
		if (!this->validation(str))
		{
			throw std::exception();
		}

		strcpy(this->number, str);
	}

	Registration &operator=(const char *str)
	{
		if (!this->validation(str))
		{
			throw std::exception();
		}
		strcpy(this->number, str);
		return *this;
	}

	bool operator==(const char *str) const
	{
		if (strcmp(this->number, str) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	const char *toString() const
	{
		return this->number;
	}
};

class Vehicle
{
public:
	const Registration regnum;
	const std::string description;

	Vehicle(const char *regnum, const char *description) : regnum(regnum), description(description)
	{
	}
};

class VehicleList
{
	Vehicle **data = nullptr;
	std::size_t capacity = 0;
	std::size_t occupied = 0;

	void copyFrom(const VehicleList &other)
	{
		if (this != &other)
		{
			for (std::size_t i = 0; i < this->occupied; i++)
			{

				this->data[i] = &Vehicle(other.data[i]->regnum.toString(), other.data[i]->description.c_str());
			}
		}
	}

public:
	VehicleList() = default;

	VehicleList(std::size_t capacity)
	{
		try
		{
			this->data = new Vehicle *[capacity] { nullptr, };
			this->capacity = capacity;
			this->occupied = 0;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	VehicleList(const VehicleList &other)
	{
		this->copyFrom(other);
	}

	VehicleList &operator=(const VehicleList &other)
	{
		delete[] this->data;
		this->copyFrom(other);
		return *this;
	}

	void insert(const char *regnum, const char *description)
	{
		if ((this->capacity == this->occupied))
		{
			throw std::exception();
		}
		for (size_t i = 0; i <= this->occupied; i++)
		{
			if (strcmp(regnum, this->data[i]->regnum.toString()))
			{
				throw std::exception();
			}
			if (this->data[i] == nullptr)
			{
				this->data[i] = &Vehicle(regnum, description);
			}
		}
	}

	~VehicleList()
	{
		delete[] data;
	}
};

int main()
{

	return 0;
}