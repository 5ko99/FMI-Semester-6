// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Василена Тодорова Кръжева
// ФН: 82183
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 10:30ч.
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Date
{
private:
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint16_t m_year;
	
	void copy(unsigned int day, unsigned int month, unsigned int year);
	void validateDate(unsigned int day, unsigned int month, unsigned int year);
public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date(const Date& other);
	Date& operator=(const Date& other);

	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;

	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};

class Registration 
{
public:
	const string id;
	const Date date;

	Registration (const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const; // first data then registration
};

class RegistrationList
{
private:
	Registration** m_list;
	std::size_t m_capacity;
	std::size_t m_size;

	void copy(const RegistrationList& other);
	std::size_t findPlace(const Registration& reg) const;
	void moveToTheRight(std::size_t from);
public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& other);
	RegistrationList& operator=(const RegistrationList& other);
	~RegistrationList();

	void insert(const std::string& id, const Date& date);//std::exception
	const Registration& at(std::size_t index) const;//std::out_of_range
	const Registration& operator[](std::size_t index) const; //assert
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;
};


void RegistrationList::copy(const RegistrationList& other)
{
	Registration** tmp = new Registration*[other.m_capacity];

	for (size_t i = 0; i < other.m_size; i++)
	{
		Registration* tmpReg = new Registration((other.m_list[i])->id, (other.m_list[i])->date);
		tmp[i] = tmpReg;
	}

	if(m_list != nullptr) delete m_list;

	m_list = tmp;
	m_size = other.m_size;
	m_capacity = other.m_capacity;
}

std::size_t RegistrationList::findPlace(const Registration& reg) const
{
	std::size_t index = 0;
	while(*(m_list[index]) < reg && index < m_size)
	{
		++index;
	}
	return index;
}

void RegistrationList::moveToTheRight(std::size_t from)
{
	if(from == m_size) return;

	for (size_t i = m_size; i > from; --i)
	{
		m_list[i] = m_list[i-1];
	}
	
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
	if(m_size == m_capacity)
	{
		throw std::length_error("Not enough space");//had problems with std::exception
	}
	Registration* tmpReg = new Registration(id, date);

	std::size_t index = findPlace(*tmpReg);
	moveToTheRight(index);

	m_list[index] = tmpReg;
	++m_size;
}

const Registration& RegistrationList::at(std::size_t index) const
{
	if(index >= m_size)
	{
		throw std::out_of_range("Invalid position");
	}
	return *m_list[index];
}

const Registration& RegistrationList::operator[](std::size_t index) const
{
	return *m_list[index];
}

bool RegistrationList::empty() const
{
	return (m_size == 0);
}

std::size_t RegistrationList::capacity() const
{
	return m_capacity;
}

std::size_t RegistrationList::size() const
{
	return m_size;
}


RegistrationList::RegistrationList(std::size_t capacity):m_list(nullptr), m_capacity(capacity), m_size(0)
{
	m_list = new Registration*[capacity];
}

RegistrationList::RegistrationList(const RegistrationList& other):m_list(nullptr), m_capacity(0), m_size(0)
{
	copy(other);
}

RegistrationList& RegistrationList::operator=(const RegistrationList& other)
{
	if(this != &other)
	{
		copy(other);
	}
	return *this;
}

RegistrationList::~RegistrationList()
{
	for (size_t i = 0; i < m_size; i++)
	{
		delete m_list[i];
	}
	delete[] m_list;
}



Registration::Registration (const std::string& id, const Date& date) : id(id), date(date) {}

bool Registration::operator==(const Registration& rhs) const
{
	return (rhs.id == id && rhs.date == date);
}

bool Registration::operator<(const Registration& rhs) const
{
	return (date < rhs.date || (date == rhs.date && id < rhs.id));
}

void Date::validateDate(unsigned int day, unsigned int month, unsigned int year)
{
	bool isVisokosna = false;
	if(year > 65535 || day == 0 || day > 31 || month > 12 || month == 0)
	{
		throw std::invalid_argument("The entered date is invalid!");
	}

	if((year % 4 == 0 && year%100 == 1) || (year % 400 == 0 && year % 100 == 0))
	{
		isVisokosna = true;
	}

	switch(month)
	{
		/* януари(1), март(3), май(5), юли(7), август(8), октомври(10) или декември(12), денят е ≤ 31
		   април(4), юни(6), септември(9) или ноември(11), денят е ≤ 30 */
		   
		case 2:
			if(day <= 28 + isVisokosna) return;
			break;
			
		case 4: case 6: case 9: case 11:
			if(day <= 30 ) return;
			break;
		default:
			if(day <= 31) return;
			break;
	}

	throw std::invalid_argument("The entered date is invalid!");
}

void Date::copy(unsigned int day, unsigned int month, unsigned int year)
{
	validateDate(day, month, year);
	m_day = day;
	m_month = month;
	m_year = year;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	copy(day, month, year);
}

Date::Date(const Date& other)
{
	copy(other.m_day, other.m_month, other.m_year);
}

Date& Date::operator=(const Date& other)
{
	if(this != &other)
	{
		copy(other.m_day, other.m_month, other.m_year);
	}
	return *this;
}

unsigned int Date::day() const
{
	unsigned int d = m_day;
	return d;
}
unsigned int Date::month() const
{
	unsigned int m = m_month;
	return m;
}
unsigned int Date::year() const
{
	unsigned int y = m_year;
	return y;
}

bool Date::operator==(const Date& rhs) const
{
	return (m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year);
}
bool Date::operator<(const Date& rhs) const
{
	return (m_year < rhs.m_year || (m_year == rhs.m_year && (m_month < rhs.m_month 
								|| (m_month == rhs.m_month && m_day < rhs.m_day))));
}

size_t readNum()
{
	size_t n;

	cin>>n;
	while(!cin)
	{
		cin.clear();
		cin.ignore();
		cout<<"invalid input. Try again: ";
		cin>>n;
	}
	return n;
}

int main()
{
	size_t n = readNum();

	RegistrationList list(n);

	string tmp;
	size_t day, month, year;
	for (size_t i = 0; i < n; i++)
	{
		cout<<i+1<<". ID: ";
		cin>>tmp;

		cout<<"Enter day: ";
		day = readNum();

		cout<<"Enter month: ";
		month = readNum();

		cout<<"Enter year: ";
		year = readNum();

		try
		{
			Date d(day, month, year);
			list.insert(tmp, d);
		}
		catch(const std::invalid_argument& e)
		{
			cout << e.what() << '\n';
			day = 0;
			month = 0;
			year = 0;
			--i;
		}
		catch(const std::length_error& e)
		{
			cout << e.what() << '\n';
			day = 0;
			month = 0;
			year = 0;
			--i;
		}
		catch(...)
		{
			cout<<"Unexpected error\n";
			day = 0;
			month = 0;
			year = 0;
			--i;
		}
	}
	
	for (size_t i = 0; i < n; i++)
	{
		cout<<i+1<<". Registration: ID "<<list[i].id<<", Date "<<list[i].date.day()
				 <<'.'<<list[i].date.month() <<'.'<<list[i].date.year()<<endl;
	}
	
	return 0;
}