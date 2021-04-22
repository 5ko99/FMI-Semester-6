//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Марио Петров Лалов
// ФН: 82180
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
private:
	std::uint8_t d_day;
	std::uint8_t d_month;
	std::uint16_t d_year;

public:
	Date(unsigned int in_day, unsigned int in_month, unsigned int in_year);
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator==(const Date &rhs) const;
	bool operator<(const Date &rhs) const;
	Date &operator=(const Date &rhs);
};

Date::Date(unsigned int in_day, unsigned int in_month, unsigned int in_year)
{
	if (in_month > 12 || in_month < 1)
	{
		throw std::invalid_argument("Month incorrect!");
	}

	if (in_day == 0)
	{
		throw std::invalid_argument("Day incorrect!");
	}

	if (in_day > 31 && (in_month == 1 || in_month == 3 || in_month == 5 || in_month == 7 ||
						in_month == 8 || in_month == 10 || in_month == 12))
	{
		throw std::invalid_argument("Day incorrect");
	}

	if (in_day > 30 && (in_month == 4 || in_month == 6 || in_month == 9 || in_month == 11))
	{
		throw std::invalid_argument("Day incorrect");
	}

	bool leap_year = ((in_year % 4 == 0) && (in_year % 100 != 0)) || ((in_year % 4 == 0) && (in_year % 100 == 0) && (in_year % 400 == 0));

	if (in_month == 2 && leap_year && in_day > 29)
	{
		throw std::invalid_argument("Day incorrect");
	}

	if (in_month == 2 && !leap_year && in_day > 28)
	{
		throw std::invalid_argument("Day incorrect");
	}

	d_day = in_day;
	d_month = in_month;
	d_year = in_year;
}

unsigned int Date::day() const
{
	return d_day;
}

unsigned int Date::month() const
{
	return d_month;
}

unsigned int Date::year() const
{
	return d_year;
}

bool Date::operator==(const Date &rhs) const
{
	return (d_day == rhs.d_day && d_month == rhs.d_month && d_year == rhs.d_year);
}

bool Date::operator<(const Date &rhs) const
{
	if (d_year < rhs.d_year)
	{
		return true;
	}
	else if (d_year == rhs.d_year)
	{
		if (d_month < rhs.d_month)
		{
			return true;
		}
		else if (d_month == rhs.d_month)
		{
			if (d_day < rhs.d_day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

Date &Date::operator=(const Date &rhs)
{
	if (this != &rhs)
	{
		this->d_day = rhs.d_day;
		this->d_month = rhs.d_month;
		this->d_year = rhs.d_year;
	}

	return *this;
}

class Registration
{
private:
	std::string id;
	Date date = Date(1, 1, 1);

public:
	Registration(const std::string &in_id, const Date &in_date);
	Registration(Registration &rhs);
	bool operator==(const Registration &rhs) const;
	bool operator<(const Registration &rhs) const;
	void print() const;
};

Registration::Registration(const std::string &in_id, const Date &in_date)
{
	id = in_id;
	date = in_date;
}

Registration::Registration(Registration &rhs)
{
	id = rhs.id;
	date = rhs.date;
}

bool Registration::operator==(const Registration &rhs) const
{
	return (id == rhs.id);
}

bool Registration::operator<(const Registration &rhs) const
{
	return (date < rhs.date) || (date == rhs.date && id < rhs.id);
}

void Registration::print() const
{
	std::cout << "Id: " << id << std::endl;
	std::cout << "Date: " << date.day() << date.month() << date.year() << std::endl;
}

class RegistrationList
{
private:
	Registration **list;
	std::size_t size;

public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList &rhs);
	RegistrationList &operator=(const RegistrationList &rhs);
	void sort();
	void insert(const std::string &id, const Date &date);
	const Registration &at(std::size_t index) const;
	const Registration &operator[](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t getSize() const;
	void print() const;
	~RegistrationList();
};

RegistrationList::RegistrationList(std::size_t capacity)
{
	size = capacity;

	try
	{
		list = new Registration *[size];

		//set all to nullptr
		for (std::size_t i = 0; i < size; i++)
		{
			list[i] = nullptr;
		}
	}
	catch (const std::bad_alloc &err)
	{
		throw err;
	}
}

RegistrationList::RegistrationList(const RegistrationList &rhs)
{
	size = rhs.size;
	list = nullptr;

	try
	{
		list = new Registration *[size];

		//fill with nullptr
		for (std::size_t j = 0; j < size; j++)
		{
			list[j] = nullptr;
		}

		//copy values
		for (std::size_t i = 0; i < size; i++)
		{
			if (rhs.list[i] != nullptr)
			{
				list[i] = new Registration(*rhs.list[i]);
			}
		}
	}
	catch (const std::bad_alloc &err)
	{
		//delete allocated memory
		if (list != nullptr)
		{
			for (std::size_t i = 0; i < size; i++)
			{
				if (list[i] != nullptr)
				{
					delete list[i];
				}
			}

			delete[] list;
		}

		throw err;
	}
}

RegistrationList &RegistrationList::operator=(const RegistrationList &rhs)
{
	//size = rhs.size;
	Registration **new_list = nullptr;

	try
	{
		new_list = new Registration *[rhs.size];

		//fill with nullptr
		for (std::size_t j = 0; j < rhs.size; j++)
		{
			new_list[j] = nullptr;
		}

		//copy values
		for (std::size_t i = 0; i < rhs.size; i++)
		{
			if (rhs.list[i] != nullptr)
			{
				new_list[i] = new Registration(*rhs.list[i]);
			}
		}

		//delete old values
		for (std::size_t k = 0; k < rhs.size; k++)
		{
			if (this->list[k] != nullptr)
			{
				delete this->list[k];
			}
		}

		delete[] this->list;

		//assign new values
		this->list = new_list;
		this->size = rhs.size;

		return *this;
	}
	catch (const std::bad_alloc &err)
	{
		//delete allocated memory
		if (new_list != nullptr)
		{
			for (std::size_t i = 0; i < rhs.size; i++)
			{
				if (new_list[i] != nullptr)
				{
					delete new_list[i];
				}
			}

			delete[] new_list;
		}
		throw err;
	}
}

void RegistrationList::sort()
{
	bool changed = false;

	do
	{
		changed = false;

		for (std::size_t i = 0; i < size - 1; i++)
		{
			if (list[i + 1] != nullptr && list[i] != nullptr)
			{
				if (list[i] < list[i + 1])
				{
					std::swap(list[i + 1], list[i]);
					changed = true;
				}
			}
		}
	} while (changed);
}

void RegistrationList::insert(const std::string &id, const Date &date)
{
	if (getSize() == capacity())
	{
		throw std::invalid_argument("Full");
	}

	//search for empty
	for (std::size_t i = 0; i < size; i++)
	{
		if (list[i] == nullptr)
		{
			try
			{
				list[i] = new Registration(id, date);
				sort();

				return;
			}
			catch (const std::bad_alloc &err)
			{
				throw err;
			}
		}
	}
}

const Registration &RegistrationList::at(std::size_t index) const
{
	if (index >= size || list[index] == nullptr)
	{
		throw std::out_of_range("out of range");
	}
	else
	{
		return *list[index];
	}
}

const Registration &RegistrationList::operator[](std::size_t index) const
{
	assert(index < size && list[index] != nullptr);

	return *list[index];
}

bool RegistrationList::empty() const
{
	return (list[0] == nullptr);
}

std::size_t RegistrationList::capacity() const
{
	return size;
}

std::size_t RegistrationList::getSize() const
{
	std::size_t number = 0;
	for (std::size_t i = 0; i < size; i++)
	{
		if (list[i] != nullptr)
		{
			number++;
		}
	}

	return number;
}

RegistrationList::~RegistrationList()
{
	for (std::size_t i = 0; i < size; i++)
	{
		if (list[i] != nullptr)
		{
			delete list[i];
		}
	}

	delete[] list;
}

void RegistrationList::print() const
{
	for (std::size_t i = 0; i < size; i++)
	{
		if (list[i] != nullptr)
		{
			std::cout << "--------------------------" << std::endl;
			list[i]->print();
		}
	}
}

int main()
{
	Date date1(25, 3, 2004);
	Date date2(29, 3, 2004);
	Registration reg1("abcd", date1);
	Registration reg2("abcc", date1);

	RegistrationList list1(3);

	try
	{
		list1.insert("abcd", date1);
		list1.insert("basd", date2);
		list1.insert("casf", date1);
		list1.insert("asff", date2);
	}
	catch (const std::invalid_argument &err)
	{
		std::cout << "Error";
	}

	//list1.print();
	RegistrationList list2 = list1;
	list2.print();
	return 0;
}