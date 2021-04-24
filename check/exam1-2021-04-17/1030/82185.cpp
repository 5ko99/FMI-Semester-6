//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Веселин Ангелов
// ФН: 82185
// Специалност: КН
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
//

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
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint16_t m_year;

	bool CheckYear(unsigned int year)
	{
		if (year % 4 != 0)
		{
			return false;
		}
		else
		{
			if (year % 100 != 0)
			{
				return true;
			}
			else
			{
				if (year % 400 != 0)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
	bool CheckDateCorrect(unsigned int day, unsigned int month, unsigned int year)
	{
		if (month >= 1 && month <= 12 && day > 0)
		{
			bool result = CheckYear(year);
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day <= 31)
					return true;
				else
					return false;
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day <= 30)
					return true;
				else
					return false;
			}
			else if (month == 2 && result)
			{
				if (day <= 29)
					return true;
				else
					return false;
			}
			else if (month == 2 && !result)
			{
				if (day <= 28)
					return true;
				else
					return false;
			}
		}
	}

public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (CheckDateCorrect(day, month, year))
		{
			this->m_day = day;
			this->m_month = month;
			this->m_year = year;
		}
		else
		{
			throw std::invalid_argument("Invalid date!");
		}
	}
	Date(const Date &date)
	{
		this->m_day = date.m_day;
		this->m_month = date.m_month;
		this->m_year = date.m_year;
	}
	Date &operator=(const Date &date)
	{
		if (this != &date)
		{
			this->m_day = date.m_day;
			this->m_month = date.m_month;
			this->m_year = date.m_year;
			return *this;
		}
	}
	unsigned int day() const
	{
		return this->m_day;
	}

	unsigned int month() const
	{
		return this->m_month;
	}

	unsigned int year() const
	{
		return this->m_year;
	}

	bool operator==(const Date &rhs) const
	{
		if (this->m_day == rhs.m_day && this->m_month == rhs.m_month && this->m_year == rhs.m_year)
			return true;
		else
			return false;
	}

	bool operator<(const Date &rhs) const
	{
		if (this->m_year < rhs.m_year)
			return true;
		else if (this->m_year > rhs.m_year)
			return false;
		else
		{
			if (this->m_month < rhs.m_month)
				return true;
			else if (this->m_month > rhs.m_month)
				return false;
			else
			{
				if (this->m_day < rhs.m_day)
					return true;
				else
					return false;
			}
		}
	}
};

class Registration
{
private:
	std::string m_id;
	const Date* m_date;

public:
	
	Registration(const std::string &id, const Date &date)
	{
		std::size_t SIZE=1;
		this->m_id = id;
		this->m_date=&date;
	}
	Registration &operator=(const Registration &other)
	{
		if (this != &other)
		{
			this->m_id = other.m_id;
			this->m_date = other.m_date;
		}
	}
	~Registration()
	{
		delete this->m_date;
	}
	bool operator==(const Registration &rhs) const
	{
		if (this->m_id == rhs.m_id && this->m_date == rhs.m_date)
			return true;
		else
			return false;
	}
	bool operator<(const Registration &rhs) const
	{
		if (this->m_date < rhs.m_date)
			return true;
		else if (this->m_date == rhs.m_date)
		{
			if (this->m_id < rhs.m_id)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	std::string get_id() const
	{
		return this->m_id;
	}
};

class RegistrationList
{
private:
	std::size_t m_capacity;
	Registration **m_registrations;
	std::size_t m_count;

public:
	RegistrationList(std::size_t capacity)
	{
		this->m_capacity = capacity;
		this->m_registrations = new Registration *[capacity];
		for (int i = 0; i < capacity; i++)
		{
			this->m_registrations[i] == nullptr;
		}
		this->m_count = 0;
	}
	~RegistrationList()
	{
		for (int i = 0; i < this->m_capacity; i++)
		{
			delete this->m_registrations[i];
		}
		delete[] this->m_registrations;
	}
	RegistrationList(const RegistrationList &other)
	{
		this->m_registrations = new Registration *[other.m_capacity];
		this->m_capacity = other.m_capacity;
		for (int i = 0; i < this->m_capacity; i++)
		{
			Registration r(*(other.m_registrations[i]));
			this->m_registrations[i] = &r;
		}
		this->m_count = other.m_count;
	}
	RegistrationList &operator=(const RegistrationList &other)
	{
		if (this != &other)
		{
			this->m_registrations = new Registration *[other.m_capacity];
			this->m_capacity = other.m_capacity;
			for (int i = 0; i < this->m_capacity; i++)
			{
				Registration r(*(other.m_registrations[i]));
				this->m_registrations[i] = &r;
			}
			this->m_count = other.m_count;
			return *this;
		}
	}
	void insert(const std::string &id, const Date &date)
	{
		if (this->m_count == this->m_capacity)
		{
			throw std::exception();
		}
		else
		{
			Registration r(id, date);
			int indexToMove = 0;
			//check where to insert
			for (int i = 0; i < this->m_count; i++)
			{
				if (&r > this->m_registrations[i])
				{
					indexToMove = i;
					break;
				}
			}
			//move all bigger
			for (int i = this->m_count; i > indexToMove; i--)
			{
				this->m_registrations[i] = this->m_registrations[i - 1];
			}
			this->m_registrations[indexToMove] = &r;
			this->m_count++;
		}
	}
	const Registration &at(std::size_t index) const
	{
		if (index < 0 || index > this->m_capacity - 1 || this->m_registrations[index] == nullptr)
		{
			throw std::out_of_range("Invalid index");
		}
		else
		{
			return *this->m_registrations[index];
		}
	}
	const Registration &operator[](std::size_t index) const
	{
		assert(index < 0 || index > this->m_capacity - 1 || this->m_registrations[index] == nullptr);
		return *this->m_registrations[index];
	}
	bool empty() const
	{
		return this->m_count == 0;
	}
	std::size_t capacity() const
	{
		return this->m_capacity;
	}
	std::size_t size() const
	{
		return this->m_count;
	}
};

bool IsInList(std::string id,const RegistrationList &list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if(id==list.at(i).get_id()) return true;
	}
	return false;
}
void Print(const RegistrationList &list)
{
	for (int i = 0; i < list.capacity(); i++)
	{
		std::cout << list.at(i).get_id();
	}
}
int main()
{
	std::size_t N;
	std::cout << "Enter list size: ";
	std::cin >> N;
	RegistrationList list(N);
	int insertedCount = 0;
	std::string id;
	std::size_t day;
	std::size_t month;
	std::size_t year;
	while (insertedCount < N)
	{
		std::cout << "Enter id: ";
		std::cin >> id;
		std::cout << "Enter day: ";
		std::cin >> day;
		std::cout << "Enter month: ";
		std::cin >> month;
		std::cout << "Enter year: ";
		std::cin >> year;
		Date date(day, month, year);
		if(!IsInList(id,list))
		{
			list.insert(id,date);
			insertedCount++;
		}
	}
	Print(list);
	return 0;
}