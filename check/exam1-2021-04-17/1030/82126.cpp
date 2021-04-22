// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Борислав Мартинов Минчев
// ФН: 82126
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
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

#include <vector>

bool validDate(unsigned int day, unsigned int month, unsigned int year)
{
	bool validMonth = month >= 1 && month <= 12;
	bool isLeap = (year%400 == 0) || (year %4 == 0 && year%100 !=0);

	unsigned int daysInCurrentMonth = 0;
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:	daysInCurrentMonth = 31; break;
	case 4:case 6:case 9:case 11: daysInCurrentMonth = 30; break;
	case 2: isLeap ? daysInCurrentMonth = 29 : daysInCurrentMonth = 28;
	default:
		break;
	}

	if (validMonth && (day > 0 && day <= daysInCurrentMonth))
	{
		return true;
	}
	return false;
}
class Date
{

	std::uint8_t d;
	std::uint8_t m;
	std::uint16_t y;

	
public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (!validDate(day, month, year)) 
		{
			throw std::invalid_argument("Invalid date");
		}
		this->d = day;
		this->m = month;
		this->y = year;
	}

	~Date() {}
	Date(const Date& other) :d(other.d), m(other.m), y(other.y) {}
	Date& operator=(const Date& other) 
	{
		Date d(other);
		return d;
	}

	unsigned int day() const
	{
		return this->d;
	}
	unsigned int month() const
	{
		return this->m;
	}
	unsigned int year() const
	{
		return this->y;
	}
	bool operator==(const Date& rhs) const
	{
		return this->d == rhs.d && this->m == rhs.m && this->y == rhs.y;
	}
	bool operator<(const Date& rhs) const
	{
		if (this->y > rhs.y)
		{
			return false;
		}
		else if (this->y < rhs.y)
		{
			return true;
		}
		else //this->year == rhs.year
		{
			if (this->m > rhs.m)
			{
				return false;
			}
			else if (this->m < rhs.m)
			{
				return true;
			}
			else //this->month == rhs.month
			{
				if (this->d > rhs.d)
				{
					return false;
				}
				else if (this->d < rhs.d)
				{
					return true;
				}
			}
		}
			
		return false;
	}
	
};

class Registration
{
	std::string id;
	Date date;
public:
	Registration(const std::string& id, const Date& date) : id(id), date(date) {}
	~Registration() {}
	Registration(const Registration& other) :id(other.id), date(other.date) {}
	Registration& operator=(const Registration& other)
	{
		Registration r(other);
		return r;
	}
	bool operator==(const Registration& rhs) const
	{
		return this->id == rhs.id && this->date == rhs.date;
	}
	bool operator<(const Registration& rhs) const
	{
		if (this->date < rhs.date)
		{
			return true;
		}
		else if (this->date == rhs.date && this->id < rhs.id)
		{
			return true;
		}
		return false;
	}
};

class RegistrationList
{
	std::size_t capacity;
	Registration** list;
	std::size_t indexToInsert(const std::string& id, const Date& date)
	{
		if (!this->list[0])
		{
			return 0;
		}
		Registration r(id, date);
		
		for (std::size_t i = this->size(); i >= 0; i--)
		{
			if (*this->list[i] < r)
			{
				return i;
			}
		}
		return this->size();
	}
public:
	RegistrationList(std::size_t capacity)
	{
		this->capacity = capacity;
		this->list = new Registration * [capacity];
		for (std::size_t i = 0; i < capacity; i++)
		{
			list[i] = nullptr;
		}
	}
	~RegistrationList() 
	{
		delete[] this->list;
	}
	RegistrationList(const RegistrationList& other) 
	{
		this->capacity = other.capacity;
		this->list = new Registration * [other.capacity];
		for (size_t i = 0; i < this->capacity; i++)
		{
			this->list[i] = other.list[i];
		}
	}
	RegistrationList& operator=(const RegistrationList& other)
	{
		
		if (this != &other)
		{
			Registration** cpy = new Registration * [other.capacity];
			this->capacity = other.capacity;
			for (std::size_t i = 0; i < this->capacity; i++)
			{
				cpy[i] = other.list[i];
			}
			delete[] this->list;
			this->list = cpy;

		}
		return *this;
	}
	std::size_t size() const
	{
		if (!this->list[0])
		{
			return 0;
		}
		std::size_t s = 1;
		for (std::size_t i = 1; i < this->capacity; i++)
		{
			if (!this->list[i]) 
			{
				return s;
			}
			s = i;
		}
		return s + 1;
	}
	void insert(const std::string& id, const Date& date)
	{
		Registration** l = new Registration * [this->capacity];
		Registration r(id, date);
		for (std::size_t i = 0; i < this->size(); i++)
		{
			if (*this->list[i] == r) 
			{
				throw std::exception("Already in list");
			}
		}

		std::size_t idx = indexToInsert(id, date);
		for (size_t i = 0; i < idx; i++)
		{
			l[i] = this->list[i];
		}
		
		l[idx] = &r;
		for (std::size_t i = idx + 1; i < this->capacity + 1; i++)
		{
			l[i] = this->list[i - 1];
		}
		delete this->list;
		this->list = l;
	}
	const Registration& at(std::size_t index) const
	{
		if (index<0 || index>this->size())
		{
			throw std::out_of_range("Invald index");
		}
		return *(this->list[index]);
	}

	const Registration& operator[](std::size_t index) const
	{
		assert(index >= 0 && index < this->size());
		return *(this->list[index]);
	}
	bool empty() const
	{
		return this->size() == 0;
	}
	std::size_t capacitty() const
	{
		return capacity;
	}
};

//class RegistrationAllocator
//{
//	std::size_t size;
//	Registration** list;
//public:
//	RegistrationAllocator()
//	{
//
//	}
//	~RegistrationAllocator()
//	{
//
//	}
//	Registration* allocate()
//};

int main()
{
	
	std::size_t n;
	std::cin >> n;
	if (n == 0 || !std::cin)
	{
		std::cout << "Error occcured";
		return 1;
	}

	RegistrationList list(n);
	for (std::size_t i = 0; i < n; i++)
	{
		std::string id;
		std::uint8_t d;
		std::uint8_t m;
		std::uint16_t y;
		std::cout << i << ") "<<std::endl;
		std::cout << "Enter id: ";
		std::cin >> id;
		std::cout << "Enter date: ";
		std::cin >> d >> m >> y;
		try
		{
			Date date(d, m, y);
			list.insert(id, date);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			return 1;
		}

	}
	
	
	return 0;
}