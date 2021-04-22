// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Делчо Дичев
// ФН: 82209
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: четвърта
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
#include<cstdint>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
private:
	std::uint8_t day;
	std::uint8_t month;
	std::uint16_t year;
	bool validation();
public:
	Date(unsigned int day, unsigned int month, unsigned int year); //if the date is not valid throw exception std::invalid_argument
	unsigned int get_day() const;
	unsigned int get_month() const;
	unsigned int get_year() const;
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};

class Registration
{
public:
	const std::string ID;
	const Date dateOfRegistration;
	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const; //return true if the ID and the date match those in rhs
	bool operator<(const Registration& rhs) const; //check is the current registration is before that in rhs:
												  //1. if the date of the object is before the date is rhs;
												 //2. If both date are the same but the ID of our object is lexicographically before that in rhs.
};

class RegistrationList
{
private:
	std::size_t capacity; //const
	std::size_t used;
	Registration** registrationOfCar;
	void copyFucn(const RegistrationList& copy);
public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& copy);
	RegistrationList& operator=(RegistrationList& other);
	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index) const;
	const Registration& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t get_capacity() const;
	std::size_t get_size() const;
	~RegistrationList();
};


int main()
{
	std::size_t cap,tempDay,tempMonth,tempYear;
	std::string tempID;
	std::cout << "Enter capacity of the list: ";
	std::cin >> cap;
	RegistrationList myregs(cap);

	for (size_t i = 0; i < cap; i++)
	{
		std::cout << "Enter day: ";
		std::cin >> tempDay;
		std::cout << "Enter month: ";
		std::cin >> tempMonth;
		std::cout << "Enter year: ";
		std::cin >> tempYear;
		std::cout << "Enter ID: ";
		std::cin >> tempID;
		try
		{
			Date tempDate(tempDay, tempMonth, tempYear);
			/*if ()
			{

			}*/
			myregs.insert(tempID, tempDate);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what();
			
		}
		
	}
	return 0;
}

bool Date::validation()
{
	if ((month >= 1 && month <= 12) && (day != 0))
	{
		switch (month)
		{
		case 1:
		{
			return day <= 31;
			break;
		}
		case 3:
		{
			return day <= 31;
			break;
		}
		case 5:
		{
			return day <= 31;
			break;
		}
		case 7:
		{
			return day <= 31;
			break;
		}
		case 8:
		{
			return day <= 31;
			break;
		}
		case 10:
		{
			return day <= 31;
			break;
		}
		case 12:
		{
			return day <= 31;
			break;
		}
		case 4:
		{
			return day <= 30;
			break;
		}
		case 6:
		{
			return day <= 30;
			break;
		}
		case 9:
		{
			return day <= 30;
			break;
		}
		case 11:
		{
			return day <= 30;
			break;
		}
		case 2:
		{
			return (year % 4 == 0 && day <= 29) || (year % 4 != 0 && day <= 28);
			break;
		}
		default:
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;

	if (!validation())
	{
		throw std::invalid_argument("The given date is not valid");
	}

	//test in main
	/*try
	{
		Date today(17, 4, 2021), today2(2, 4, 2021);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what();
		throw;
	}*/
}

unsigned int Date::get_day() const
{
	return (uint8_t)day;
}

unsigned int Date::get_month() const
{
	return (uint8_t)month;
}

unsigned int Date::get_year() const
{
	return month;
}

bool Date::operator==(const Date& rhs) const
{
	return (day == rhs.day) && (month == rhs.month) && (year == rhs.year);
}

bool Date::operator<(const Date& rhs) const
{
	return(((day < rhs.day) && (month <= rhs.month) && (year <= rhs.year)) || ((month < rhs.month) && (year <= rhs.year)) || (year < rhs.year));
}



Registration::Registration(const std::string& id, const Date& date) :ID(id), dateOfRegistration(date)
{
}

bool Registration::operator==(const Registration& rhs) const
{
	return ((ID == rhs.ID) && (dateOfRegistration == rhs.dateOfRegistration));
}

bool Registration::operator<(const Registration& rhs) const
{
	return (dateOfRegistration < rhs.dateOfRegistration) || ((dateOfRegistration == rhs.dateOfRegistration) && (ID < rhs.ID));
}



void RegistrationList::copyFucn(const RegistrationList& copy)
{
	capacity = copy.capacity;
	used = copy.used;
	registrationOfCar = new Registration * [copy.capacity];
	for (size_t i = 0; i < copy.capacity; i++)
	{
		registrationOfCar[i] = new Registration(copy[i].ID, copy[i].dateOfRegistration);
	}
}

RegistrationList::RegistrationList(std::size_t capacityR) :capacity(capacityR), used(0)
{
	registrationOfCar = new Registration * [capacityR];
	for (size_t i = 0; i < capacity; i++)
	{
		registrationOfCar[i] = nullptr;
	}
}

RegistrationList::RegistrationList(const RegistrationList& copy)
{
	copyFucn(copy);
}

RegistrationList& RegistrationList::operator=(RegistrationList& other)
{
	try
	{
		if (this != &other)
		{
			copyFucn(other);
		}
		return *this;
	}
	catch (const std::exception&)
	{
		std::cout << "Error";
	}
	
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
	bool ins = false;
	for (size_t i = 0; i < capacity; i++)
	{
		if ((registrationOfCar[i] != nullptr) && (date < registrationOfCar[i]->dateOfRegistration) && (used < capacity))
		{
			registrationOfCar[used] = new Registration(id, date);
			used++;
			ins = true;
			break;
		}
	}
	if (!ins)
	{
		throw std::exception("Something wrong happened");
	}
}

const Registration& RegistrationList::at(std::size_t index) const
{
	if (index < used && index >= 0)
	{
		return *registrationOfCar[used];
	}
	else
	{
		throw std::out_of_range("This is not a valid index");
	}
}

const Registration& RegistrationList::operator[](std::size_t index) const
{
	assert(index < used&& index >= 0);
	return *registrationOfCar[used];
}

bool RegistrationList::empty() const
{
	return used;
}

std::size_t RegistrationList::get_capacity() const
{
	return capacity;
}

std::size_t RegistrationList::get_size() const
{
	return used;
}

RegistrationList::~RegistrationList()
{
	for (size_t i = 0; i < used; i++)
	{
		delete registrationOfCar[i];
	}
	delete[] registrationOfCar;
}