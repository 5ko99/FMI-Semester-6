// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:
// ФН:
// Специалност: КН
// Курс: 1
// Административна група:
// Ден, в който се явявате на контролното: 17ти април
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: g++
//

// #define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;


class Date{
private:
		uint8_t	 _day;
		uint8_t _month;
		uint16_t _year;

	bool _isLeap(unsigned int year)
	{
		if(year % 4 != 0)
		{
			return false ;
		}
		else
		{
			if(year % 100 != 0)
			{
				return true;
			}
			else{
				if(year % 400 != 0) return false;
			}

		}

		return false;
	}

	bool _isValid(unsigned int day, unsigned int month, unsigned int year)
	{
		if(day <= 0) return false;

 		if(month <= 0 || month > 12) return false;

		if(month == 2 && day > 28 + (uint8_t)_isLeap(year)) return false;

		if(month == 1
		|| month == 3
		|| month == 5
		|| month == 7
		|| month == 8
		|| month == 10
		|| month == 12)
		{
			if(day > 31) return false;
		}
		else if(month == 4
			|| month == 6
			|| month == 9
			|| month == 11)
		{
			if(day > 30) return false;
		}

		return true;
	}

public:

	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if(!_isValid(day, month, year))
		{
			throw std::invalid_argument("Date should be valid");
		}

		_day =  (uint8_t)day;
		_month = (uint8_t)month;
		_year = (uint16_t)year;
	}

	unsigned int day() const
	{
		return (unsigned int)_day;
	}

	unsigned int month() const
	{
		return (unsigned int)_month;
	}

	unsigned int year() const
	{
		return (unsigned int)_year;
	}

	bool operator==(const Date& rhs) const
	{
		return _day == rhs._day && _month == rhs._month && _year == rhs._year;
	}

	bool operator<(const Date& rhs) const
	{
		if(_year == rhs._year)
		{
			if(_month == rhs._month)
			{
				return _day < rhs._day;
			}
			return _month < rhs._month;
		}
		return _year < rhs._year;
	}
};

class Registration{

public:
	std::string id;
	Date date;

	Registration(const std::string& _id, const Date& _date) :id(_id), date(_date){}

	bool operator==(const Registration& rhs) const
	{
		return date == rhs.date && id == rhs.id;
	}

	bool operator<(const Registration& rhs) const
	{
		if(date == rhs.date)
		{
			return strcmp(id.c_str(), rhs.id.c_str()) < 0;
		}


		return date < rhs.date;
	}

};

class RegistrationList{

private:
	size_t _capacity;
	Registration** regs;
	size_t _size;

public:
	RegistrationList(size_t capacity): _capacity(capacity), _size(0)
	{
		regs = new Registration*[_capacity];
	}

	RegistrationList(const RegistrationList& other)
	{
		regs = new Registration*[other._capacity];

		for (size_t i = 0; i < other._size; i++)
		{
			regs[i] = new Registration(other[i].id, other[i].date);
		}
	}

	~RegistrationList()
	{
		for (size_t i = 0; i < _size; i++)
		{
			delete regs[i];
		}

		delete [] regs;
	}

	void insert(const std::string& id, const Date& date)
	{
		if(_size >= _capacity)
		{
			throw std::exception();
		}

		Registration* newReg = new Registration(id, date);

		size_t i = 0;

		for (; (i < _size) && !(*newReg < *regs[i]); i++);

		// cout << i << endl;

		for (size_t j = _size; j > i; j--)
		{
			regs[j] = regs[j-1];
		}

		// cout << i << endl;

		regs[i] = newReg;

		_size++;

		// cout <<  "assertion: " << (*regs[i] == *newReg) << endl;

	}

	const Registration& at(std::size_t index) const
	{
		if(index < 0 || index >= _size)
		{
			throw std::out_of_range("Index out of bounds");
		}

		return *(regs[index]);
	}

	const Registration& operator[](std::size_t index) const
	{
		return *(regs[index]);
	}

	bool empty() const
	{
		return _size == 0;
	}

	std::size_t capacity() const
	{
		return _capacity;
	}

	std::size_t size() const
	{
		return _size;
	}
};

int main()
{
	try{

		Date d1(28, 2, 2010);
		Date d2(28, 2, 2010);

		Registration r1("82183", d1);
		Registration r2("82182", d2);

		RegistrationList l(10);

		l.insert("82183", d1);
		l.insert("82182", d1);
		l.insert("82181", d1);
		l.insert("82184", d1);
		l.insert("82187", d1);
		l.insert("82185", d1);

		for (size_t i = 0; i < l.size(); i++)
		{
			cout << l[i].id << endl;
		}

		cout << l.size() << endl;
		size_t N;
		cout << "Enter N: ";
		cin >> N;
		RegistrationList list(N);

		cout << "\tregistration list created with capacity " << list.capacity() << endl;

		for (size_t i = 0; i < list.capacity(); i++)
		{
			std::string id;
			unsigned long day, month, year;
			cout << "Enter reg. id: ";
			cin >> id;

			cout << "Eenter day, month and year: ";
			cin >> day >> month >> year;

			list.insert(id, Date(day, month, year));

		}

		for (size_t i = 0; i < list.size(); i++)
		{
			cout << "ID: " << 
				list[i].id << 
				" Date: " <<
				list[i].date.day() << "." << 
				list[i].date.month() << "." << 
				list[i].date.year() << endl;
		}

	}
	catch(std::invalid_argument& e)
	{
		cout << e.what();
	}
	catch(std::exception& e)
	{
		cout << "exception caught" << endl;
	}
	return 0;
}