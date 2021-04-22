// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Александър Йорданов Банков
// ФН:82174
// Специалност:Компютърни науки
// Курс:1
// Административна група:3
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
using std::string;

class Date
{
private:
	uint8_t _day;
	uint8_t _month;
	uint16_t _year;

	static bool isValid(unsigned int, unsigned int, unsigned int);
	static bool isLeap(unsigned int);

public:
	Date(unsigned int, unsigned int, unsigned int);

	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;

	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	if (!isValid(day, month, year))
	{
		throw std::invalid_argument("not a valid date");
	}
	this->_day = day;
	this->_month = month;
	this->_year = year;
}

unsigned int Date::day() const
{
	return _day;
}

unsigned int Date::month() const
{
	return _month;
}

unsigned int Date::year() const
{
	return _year;
}

bool Date::operator==(const Date& rhs) const
{
	return _year == rhs._year && _month == rhs._month && _day == rhs._day;
}

bool Date::operator<(const Date& rhs) const
{
	return _year < rhs._year || 
		(_year == rhs._year && _month < rhs._month) || 
		(_year == rhs._year && _month == rhs._month && _day < rhs._day);
}

bool Date::isValid(unsigned int day, unsigned int month, unsigned int year)
{
	if (day < 1 || day > 31 || month < 1 || month > 12)
	{
		return false;
	}
	else if (((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) ||
		(month == 2 && day > 29) ||
		(month == 2 && day == 29 && !isLeap(year)))
	{
		return false;
	}
	return true;
}

bool Date::isLeap(unsigned int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

class Registration
{
public:
	const string id;
	const Date date;

	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const;
};

Registration::Registration(const std::string& id, const Date& date) : id(id), date(date)
{

}

bool Registration::operator==(const Registration& rhs) const
{
	return (date == rhs.date && id == rhs.id);
}

bool Registration::operator<(const Registration& rhs) const
{
	return date < rhs.date || (date == rhs.date && id < rhs.id);
}

class RegistrationList 
{
private:
	const size_t _capacity;
	Registration** list;
	size_t _size;

	void deleteList();
public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& from);
	~RegistrationList();


	void insert(const std::string& id, const Date& date);
	RegistrationList& operator=(const RegistrationList& rhs);
	const Registration& at(std::size_t index) const;
	const Registration& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;
};



void RegistrationList::deleteList()
{
	for (size_t i = 0; i < _size; i++)
	{
		delete list[i];
	}
	delete[] list;
}

RegistrationList::RegistrationList(std::size_t capacity) : _capacity(capacity)
{
	_size = 0;
	list = new Registration * [_capacity];
}

RegistrationList::RegistrationList(const RegistrationList& from) : _capacity(from._capacity)
{
	_size = from._size;

	list = new Registration * [_capacity];
	for (size_t i = 0; i < _size; i++)
	{
		list[i] = new Registration(from[i]);
	}
}

RegistrationList::~RegistrationList()
{
	deleteList();
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
	if (_size == _capacity)
	{
		throw std::exception("There is no more space left.");
	}

	size_t place = 0;
	bool placeFound = false;
	Registration* temp = new Registration(id, date);

	for (size_t i = 0; i < _size; i++)
	{
		if (*temp < *list[i])
		{
			place = i;
			placeFound = true;
		}
	}

	if (placeFound)
	{
		for (size_t i = _size; i > place; i--)
		{
			list[i] = list[i - 1];
		}
		list[place] = temp;
	}
	else
	{
		list[_size] = temp;
	}
	
	_size++;
}

RegistrationList& RegistrationList::operator=(const RegistrationList& rhs)
{
	if (_capacity != rhs._capacity)
	{
		throw std::exception("cannot copy the object here");
	}
	Registration** temp = new Registration * [_capacity];

	for (size_t i = 0; i < rhs._size; i++)
	{
		temp[i] = new Registration(rhs[i]);
	}

	deleteList();
	list = temp;

	return *this;
}

const Registration& RegistrationList::at(std::size_t index) const
{
	if (index >= _size)
	{
		throw std::exception("Invalid index.");
	}
	return *list[index];
}

const Registration& RegistrationList::operator[](std::size_t index) const
{
#ifdef DEBUG
	assert(index < _size);
#endif
	return *list[index];
}

bool RegistrationList::empty() const
{
	return _size == 0;
}

std::size_t RegistrationList::capacity() const
{
	return _capacity;
}

std::size_t RegistrationList::size() const
{
	return _size;
}

class UserInterface
{
private:
	RegistrationList regList;

public:
	UserInterface(size_t registrationCount);
	void input();
	void print();
};

int main()
{
	size_t N;
	std::cin >> N;

	UserInterface ui(N);

	ui.input();
	ui.print();

	return 0;
}

UserInterface::UserInterface(size_t registrationCount) :regList(registrationCount)
{
}

void UserInterface::input()
{
	string id;
	size_t day, month, year;
	while (regList.size() != regList.capacity())
	{
		
		std::cout << "Input the date in format day month year then input the id." << std::endl;

		std::cin >> day >> month >> year >> id;

		try
		{
			Date date(day, month, year);
			regList.insert(id, date);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what()<<std::endl<<"Something went wrong try again."<<std::endl;
		}
	}
}

void UserInterface::print()
{
	std::cout << std::endl;
	for (size_t i = 0; i < regList.size(); i++)
	{
		std::cout << regList[i].date.day() << " " << regList[i].date.month() << " " << regList[i].date.year() << 
			"	" << regList[i].id << std::endl;
	}
}
