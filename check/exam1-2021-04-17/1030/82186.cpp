// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Васил Христов Василев
// ФН:82186
// Специалност:Компютърни науки
// Курс:Първи курс
// Административна група:Трета група
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: MSVC
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <cstdint>
#include <stdexcept>
#include <cstddef>

class Date 
{
private:
	std::uint8_t day;
	std::uint8_t month;
	std::uint16_t year;
public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (day == 0) throw std::invalid_argument("Day cannot be 0");
		if (month > 12 || month < 1) throw std::invalid_argument("Month has to be between 1 and 12");
		if (month == 2)
		{
			if (year % 4 != 0 && day > 28)
			{
				throw std::invalid_argument("Not a leap year so days cant be 29");
			}
			else if (year % 4 == 0 && year % 100 !=0 )
			{//Leap year eg.2016
				if(day>29) throw std::invalid_argument("Days in Feb cant be more than 29");
				else
				{
					this->day = day;
					this->month = month;
					this->year = year;
				}				
			}
			else if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
			{
				//Leap year 2000
				if (day > 29) throw std::invalid_argument("Days in Feb cant be more than 29");
				else
				{
					this->day = day;
					this->month = month;
					this->year = year;
				}
			}
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day > 31) throw std::invalid_argument("Day cannot be more than 31");
			else
			{
				this->day = day;
				this->month = month;
				this->year = year;
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30) throw std::invalid_argument("Day cannot be more than 30");
			else
			{
				this->day = day;
				this->month = month;
				this->year = year;
			}
		}
	}

	unsigned int day() const
	{
		return this->day;
	}

	unsigned int month() const
	{
		return this->month;
	}

	unsigned int year() const
	{
		return this->year;
	}

	bool operator==(const Date& rhs) const
	{
		;
	}

	bool operator<(const Date& rhs) const
	{
		;
	}
};

class Registration
{
public:
	std::string id;
	Date date;
	/*Registration(const std::string& id, const Date& date)
	{
		this->id = id;
		this->date = date;
	}*/

};

class RegistrationList
{
private:
	std::size_t number_of_total_regs;
	std::size_t added_regs;
	//Registration reg = new Registration[8];
public:
	RegistrationList(std::size_t capacity)
	{
		this->number_of_total_regs = capacity;
	}

	void insert(const std::string& id, const Date& date)
	{
		;
	}

	const Registration& at(std::size_t index) const
	{
		if (index > number_of_total_regs) throw std::out_of_range("Not a valid position");
	}

	const Registration& operator[](std::size_t index) const
	{
		assert(index < number_of_total_regs);

	}

	bool empty() const
	{
		if (number_of_total_regs == 0)
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
		return this->number_of_total_regs;
	}

	std::size_t size() const
	{
		return this->added_regs;
	}
};



int main()
{

	return 0;
}