// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Васил 
// ФН: 82129
// Специалност: КН
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
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
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
	uint8_t dayD;
	uint8_t monthD;
	uint16_t yearD;
	bool isLeapYear(unsigned int year)
	{
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}
	bool validateDate(unsigned int day, unsigned int month, unsigned int year)
	{
		if ((month == 0) || (month > 12))
			return false;
		switch (month)
		{
		case 1:
			return (0 < day) && (day <= 31);
		case 2:
			return (0 < day) && (day <= (unsigned)(28 + isLeapYear(year)));
		case 3:
			return (0 < day) && (day <= 31);
		case 4:
			return (0 < day) && (day <= 30);
		case 5:
			return (0 < day) && (day <= 31);
		case 6:
			return (0 < day) && (day <= 30);
		case 7:
			return (0 < day) && (day <= 31);
		case 8:
			return (0 < day) && (day <= 31);
		case 9:
			return (0 < day) && (day <= 30);
		case 10:
			return (0 < day) && (day <= 31);
		case 11:
			return (0 < day) && (day <= 30);
		case 12:
			return (0 < day) && (day <= 31);
		}
	}
public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (validateDate(day, month, year))
		{
			dayD = day;
			monthD = month;
			yearD = year;
		}
		else
		{
			throw std::invalid_argument("");
		}

	}
	unsigned int day() const
	{
		return dayD;
	}
	unsigned int month() const
	{
		return monthD;
	}
	unsigned int year() const
	{
		return yearD;
	}
	bool operator==(const Date& rhs) const
	{
		return ((dayD == rhs.dayD) && (monthD == rhs.monthD) && (yearD == rhs.yearD));
	}
	bool operator<(const Date& rhs) const
	{
		bool isTrue = false;
		if ((yearD < rhs.yearD))
		{
			isTrue = true;
		}
		else if ((yearD == rhs.yearD) && (monthD < rhs.monthD))
		{
			isTrue = true;
		}
		else if ((yearD == rhs.yearD) && (monthD == rhs.monthD) && (dayD < rhs.dayD))
		{
			isTrue = true;
		}
		return isTrue;
	}
};
class Registration
{
	std::string id;
	Date date;
public:
	Registration(const std::string& id, const Date& date) :date(date), id(id)
	{}
	bool operator==(const Registration& rhs) const
	{
		return  ((id == rhs.id) && (date == rhs.date));
	}
	bool operator<(const Registration& rhs) const
	{
		if ((date < rhs.date) || (date == rhs.date) && (id < rhs.id))
		{
			return true;
		}
		return false;
	}
};
class RegistrationList
{
	const size_t capacity;
	size_t cnt;
	Registration** regList;
public:
	RegistrationList(std::size_t capacity) : capacity(capacity), cnt(0), regList(nullptr)
	{

	}
	RegistrationList(RegistrationList& rhs) :capacity(rhs.capacity), cnt(rhs.cnt)
	{
		Registration** buffer = new Registration * [cnt];
		memcpy(buffer, rhs.regList, cnt * sizeof(Registration*));
		regList = buffer;

	}
	RegistrationList& operator=(const RegistrationList& rhs)
	{

	}
	~RegistrationList()
	{
		delete regList;
	}

};

int main()
{
	Date a(1, 1, 1), b(1, 2, 0);
	Registration c("gg", a);
	Registration d("ggs", a);
	std::cout << (c == d);//
	return 0;
}