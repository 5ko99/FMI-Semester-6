//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Todor Hristov
// ФН: 82162
// Специалност: KN
// Курс: 1
// Административна група: 2
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
#include <cstdint>
#include <stdexcept	>
using namespace std;

class Date
{
private:
	uint8_t current_day;
	uint8_t current_month;
	uint16_t current_year;
	bool valid_date(unsigned int current_day, 
		unsigned int current_month, unsigned int current_year)
	{
		if (current_day > 31)
		{
			return false;
		}
		if ((current_month == 4 || current_month == 6 ||
			current_month == 9 || current_month == 11) && (current_day > 30))
		{
			return false;
		}
		if (current_month == 2 && current_day > 29)
		{
			return false;
		}
		if (current_month == 2 && current_day == 29 &&
			(current_year % 4 != 0 || current_year % 100 == 0 || current_year % 400 != 0))
		{
			return false;
		}
	}
public:
	Date(unsigned int day, unsigned int month, unsigned int year) :
		current_day(day), current_month(month), current_year(year)
	{
		if (valid_date(current_day, current_month, current_year) == false) {
			throw invalid_argument("invalid date");
		}
			
	}
	Date(const Date& other) :
		current_day(other.current_day),
		current_month(other.current_month),
		current_year(other.current_year)
	{
		if (valid_date(current_day, current_month, current_year) == false) {
			throw invalid_argument("invalid date");
		}
	}
	Date& operator= (const Date& other)
	{
		current_day = other.current_day;
		current_month = other.current_month;
		current_year = other.current_year;
		if (valid_date(current_day, current_month, current_year) == false) {
			throw invalid_argument("invalid date");
		}
	}
	~Date() {}
	
	unsigned int day() const {
		return (unsigned int)current_day;
	}
	unsigned int month() const 
	{
		return (unsigned int)current_month;
	}
	unsigned int year() const
	{
		return (unsigned int)current_year;
	}
	bool operator==(const Date& rhs) const
	{
		if (current_day == rhs.current_day &&
			current_month == rhs.current_month &&
			current_year == rhs.current_year)
		{
			return true;
		}
		return false;
	}
	bool operator<(const Date& rhs) const
	{
		if (current_year < rhs.current_year)
		{
			return true;
		}
		if (current_year == rhs.current_year && current_month < rhs.current_month)
		{
			return true;
		}
		if (current_year == rhs.current_year && 
			current_month == rhs.current_month && 
			current_day < rhs.current_day)
		{
			return true;
		}
		return false;
	}
};
class Registration
{
private:
	string id;
	Date date;
public:
	Registration(const string& id, const Date& date) :
		id(id), date(date){}
	Registration(const Registration& other) :
		id(other.id), date(other.date) {}
	Registration& operator= (const Registration& other) 
	{
		id = other.id;
		date = other.date;
	}

	bool operator==(const Registration& rhs) const 
	{
		if (id == rhs.id && date == rhs.date) 
		{
			return true;
		}
		return false;
	}
	bool operator<(const Registration& rhs) const
	{
		if (date < rhs.date || (date == rhs.date && id < rhs.id))
		{
			return true;
		}
		return false;
	}
	~Registration(){}

};
class RegistrationList
{
private:
	size_t r_capacity = 0;
	size_t r_currentNumRegistered = 0;
	Registration** registration = nullptr;
	void inicialize(size_t r_capacity)
	{
		try
		{
			registration = new Registration * [r_capacity];
		}
		catch (...)
		{
			cerr << "not enough space";
		}
	}
public:
	RegistrationList(size_t capacity): r_capacity(r_capacity)
	{
		inicialize(r_capacity);
	}
	RegistrationList(const RegistrationList& other) : 
		r_capacity(other.r_capacity)
	{
		inicialize(r_capacity);
		for (size_t i = 0; i < r_capacity; i++)
		{
			registration[i] = other.registration[i];
		}
	}
	RegistrationList& operator=(const RegistrationList& other)
	{
		r_capacity = other.r_capacity;
		inicialize(r_capacity);
		for (size_t i = 0; i < r_capacity; i++)
		{
			registration[i] = other.registration[i];
		}
	}

	~RegistrationList()
	{
		for (size_t i = 0; i < r_capacity; i++)
		{
			delete registration[i];
		}
		delete[] registration;
	}
	void insert(const std::string& id, const Date& date)
	{
		if (r_currentNumRegistered >= r_capacity)
		{
			throw exception("the list is full");
		}
		if (r_currentNumRegistered == 0)
		{
			registration[0] = new Registration(id, date);
		}
		else
		{
			bool changed = 0;
			Registration* temp = new Registration(id, date);
			for (size_t i = r_currentNumRegistered; i > 0; i++)
			{
				if (registration[i - 1] < temp)
				{
					registration[i] = new Registration(id, date);
					changed = 1;
					break;
				}
				else 
				{
					registration[i] = registration[i - 1];
				}
			}
			if (changed == 0)
			{
				registration[0] = new Registration(id, date);
			}
			delete temp;
		}
		++r_currentNumRegistered;
	}
	const Registration& at(std::size_t index) const
	{
		if (index > r_currentNumRegistered)
		{
			throw out_of_range("no such element");
		}
		return *registration[index-1];
	}
	bool empty() const
	{
		if (r_currentNumRegistered == 0)
		{
			return true;
		}
		return false;
	}
	size_t capacity() const
	{
		return r_capacity;
	}
	size_t size() const
	{
		return r_currentNumRegistered;
	}
};
int main()
{
	size_t n;
	cin >> n;
	if (n < 0)
	{
		throw exception("wrong size");
	}
	RegistrationList** registered = nullptr;
	try
	{
		registered = new RegistrationList * [n];
	}
	catch (...)
	{
		cerr << "not enough space";
	}
	
	for (size_t i = 0; i < n; i++)
	{
		string id;
		cin >> id;
		uint8_t day;
		cin >> day;
		uint8_t month;
		cin >> month;
		uint16_t year;
		cin >> year;
		Date* date = new Date(day, month, year);
		//registered[i] = new RegistrationList;
		//registered[i].insert(id, *date);
		delete date;
	}
	for (size_t i = 0; i < n; i++)
	{
		cout << registered[i];
	}
	for (size_t i = 0; i < n; i++)
	{
		delete registered[i];
	}
	delete[] registered;
	return 0;
}
