//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Теодор Тодоров Карушков
// ФН: 82204
// Специалност: КН
// Курс: Първи
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>	 //(за работа със uint8_t и uint16_t).
#include <stdexcept> //(за работа с класовете за изключения).
#include <cstddef>	 //(за работа със std::size_t).

bool isValid(unsigned int _day, unsigned int _month, unsigned int _year);
bool isLeapYear(unsigned int _year);

class Date
{
	std::uint8_t _day;
	std::uint8_t _month;
	std::uint16_t _year;

	void copy(const Date &other)
	{
		_day = other._day;
		_month = other._month;
		_year = other._year;
	}

public:
	Date() = delete;
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (isValid(day, month, year) == 0)
			throw std::invalid_argument("Invalid Date");

		_day = day;
		_month = month;
		_year = year;
	}
	Date(const Date &other)
	{
		copy(other);
	}
	unsigned int day() const
	{
		return _day;
	}
	unsigned int month() const
	{
		return _month;
	}
	unsigned int year() const
	{
		return _year;
	}
	bool operator==(const Date &rhs) const
	{
		if (_day == rhs._day && _month == rhs._month && _year == rhs._year)
			return true;

		return false;
	}
	bool operator<(const Date &rhs) const
	{
		if (_day < rhs._day && _month <= rhs._month && _year <= rhs._year)
			return true;

		return false;
	}
	const Date &operator=(const Date &other)
	{
		if (this != &other)
			copy(other);

		return *this;
	}
};

class Registration
{
	std::string id;
	//const
	Date date;

	void copy(const Registration &other)
	{
		id = other.id;
		date = other.date;
	}

public:
	Registration() = delete;
	Registration(const std::string &id, const Date &date) : date(date)
	{
		this->id = id;
		//this->date = date;
	}
	bool operator==(const Registration &rhs) const
	{
		if (id == rhs.id)
			return true;

		return false;
	}
	bool operator<(const Registration &rhs) const
	{
		if (id < rhs.id)
			return true;

		return false;
	}
	const Registration &operator=(const Registration &other)
	{
		if (this != &other)
			copy(other);

		return *this;
	}
};

class RegistrationList
{
	Registration **regList = nullptr;
	std::size_t _capacity;
	std::size_t regAmount;

public:
	RegistrationList()
	{
		_capacity = 2;
		try
		{
			regList = new Registration *[_capacity];
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
		regAmount = 0;
	}
	RegistrationList(std::size_t capacity)
	{
		_capacity = capacity;
		try
		{
			regList = new Registration *[_capacity];
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
		regAmount = 0;
	}
	void insert(const std::string &id, const Date &date)
	{
		try
		{
			Registration **newRegList = new Registration *[_capacity++];
			for (std::size_t i = 0; i < _capacity; ++i)
			{
				newRegList[i] = regList[i];
			}

			for (std::size_t i = 0; i < _capacity; ++i)
			{
				delete[] regList[i];
			}
			delete regList;

			Registration addReg(id, date);
			std::size_t index = 0;
			for (std::size_t i = 0; i < _capacity + 1; ++i)
			{
				if (addReg < *newRegList[i])
				{
					index = i;
				}
			}

			for (std::size_t i = 0; i < _capacity + 1; ++i)
			{
				if (i > index)
				{
					newRegList[i] = newRegList[i + 1];
				}
			}

			addReg = *newRegList[index];
			regList = new Registration *[++_capacity];
			++regAmount;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	const Registration &at(std::size_t index) const
	{
		if (index >= regAmount)
			throw std::out_of_range("Invalid index");

		return *regList[index];
	}
	const Registration &operator[](std::size_t index) const
	{
		assert(index < regAmount);
		return *regList[index];
	}
	bool empty() const
	{
		return !regAmount;
	}
	std::size_t capacity() const
	{
		return _capacity;
	}
	std::size_t size() const
	{
		return regAmount;
	}
};

int main()
{
	unsigned int N;

	std::cout << "Enter number of registrations: ";
	std::cin >> N;

	RegistrationList myRegList(N);

	unsigned int userDay, userMonth, userYear;

	for (std::size_t i = 0; i < N; ++i)
	{
		bool isValidDate = true;
		do
		{
			std::cout << "Day: ";
			std::cin >> userDay;
			std::cout << "Month: ";
			std::cin >> userMonth;
			std::cout << "Year: ";
			std::cin >> userYear;
			try
			{
				if (isValid(userDay, userMonth, userYear) == 0)
				{
					throw std::exception();
					isValidDate = false;
				}
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}

		} while (isValidDate == 0);

		Date myDate(userDay, userMonth, userYear);
		std::string reg;
		//bool regExists = false;
		//do
		//{
		std::cout << "Enter registration: ";
		std::cin >> reg;
		//try
		//{
		//for (std::size_t i = 0; i < N; ++i)
		//if (reg == myRegList[i].id)
		//{
		//throw std::exception();
		//regExists = true;
		//}
		//}
		//catch (const std::exception &e)
		//{
		//std::cerr << e.what() << '\n';
		//}

		//} while (!regExists);

		myRegList.insert(reg, myDate);
	}

	return 0;
}

bool isValid(unsigned int day, unsigned int month, unsigned int year)
{
	if (month < 1 || month > 12)
		return false;
	if (day == 0)
		return false;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day > 31)
			return false;
		break;

	case 2:
		if (!isLeapYear(year) && day > 29)
			return false;
		if (isLeapYear(year) == 0 && day > 28)
			return false;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
			return false;
		break;
	}

	return true;
}
bool isLeapYear(unsigned int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
			return true;
		else if (year % 100 == 0 && year % 400 == 0)
			return true;
	}
	return false;
}
