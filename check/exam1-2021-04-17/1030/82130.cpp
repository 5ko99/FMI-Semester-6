// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Цветелин Костадинов Цецков
// ФН: 82130
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 10:30
// Начален час на контролното: 10:30
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>

static const int OUT_OF_MEMORY_EXIT_CODE = 1;

class Date
{
public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (day == 0)
		{
			throw std::invalid_argument("[Malformed date] The day cannot be 0!");
		}
		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (day > 31)
			{
				throw std::invalid_argument("[Malformed date] In months: 1, 3, 5, 7, 8, 10, 12 the day cannot be over 31!");
			}
			break;
		case 4: case 6: case 9: case 11:
			if (day > 30)
			{
				throw std::invalid_argument("[Malformed date] In months: 4, 6, 9, 11 the day cannot be over 30!");
			}
			break;
		case 2:
			if (leapYear(year))
			{
				if (day > 29)
				{
					throw std::invalid_argument("[Malformed date] The days in february in a leap year go to 29!");
				}
			}
			else {
				if (day > 28)
				{
					throw std::invalid_argument("[Malformed date] The days in february in a normal year go to 28!");
				}
			}
			break;
		default: throw std::invalid_argument("[Malformed date] The month is in the range [1;12]!");
		}

		this->d = day;
		this->m = month;
		this->y = year;
	}

	unsigned int day() const { return this->d; }
	unsigned int month() const { return this->m; }
	unsigned int year() const { return this->y; }

	bool operator==(const Date& rhs) const
	{
		return this->d == rhs.d
			&& this->m == rhs.m
			&& this->y == rhs.y;
	}
	bool operator<(const Date& rhs) const
	{
		if (this->y < rhs.y)
		{
			return true;
		}
		else if (this->y > rhs.y) {
			return false;
		}
		else { // years ==
			if (this->m < rhs.m)
			{
				return true;
			}
			else if (this->m > rhs.m)
			{
				return false;
			}
			else { // months ==
				if (this->d < rhs.d)
				{
					return true;
				}
				else { // days >=
					return false;
				}
			}
		}
	}
private:
	std::uint8_t d;
	std::uint8_t m;
	std::uint16_t y;

	bool leapYear(unsigned int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
};

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.day() << '.' << date.month() << '.' << date.year();
	return os;
}


class Registration
{
public:
	const std::string id; // id of the reg
	const Date date; // date of registration

	Registration(const std::string& id, const Date& date)
		: id(id), date(date)
	{}

	bool operator==(const Registration& rhs) const
	{
		return this->id == rhs.id
			&& this->date == rhs.date;
	}

	bool operator<(const Registration& rhs) const
	{
		if (this->date < rhs.date)
		{
			return true;
		}
		else if (this->date == rhs.date)
		{
			return this->id < rhs.id;
		}
		else {
			return false;
		}
	}
};

std::ostream& operator<<(std::ostream& os, const Registration& reg)
{
	os << reg.id << " (" << reg.date << ')';
	return os;
}

class RegistrationList
{
public:
	RegistrationList(std::size_t capacity)
		:rawCapacity(capacity), nextFreeIndex(0)
	{
		try {
			regs = new Registration*[capacity];
			for (std::size_t i = 0; i < capacity; ++i)
			{
				regs[i] = nullptr;
			}
		}
		catch (std::bad_alloc&)
		{
			std::cerr << "Registration list was denied memory. Aborting and rethorwing" << std::endl;
			throw;
		}
	}

	RegistrationList(const RegistrationList& other)
		:rawCapacity(other.rawCapacity), nextFreeIndex(other.nextFreeIndex)
	{
		try {
			regs = new Registration*[rawCapacity];
			for (std::size_t i = 0; i < rawCapacity; ++i)
			{
				regs[i] = new Registration(*other.regs[i]);
			}
		}
		catch (std::bad_alloc&)
		{
			std::cerr << "Registration list was denied memory. Aborting and rethorwing" << std::endl;
			throw;
		}
	}

	RegistrationList& operator=(const RegistrationList& other)
	{
		try {
			Registration** newBuf = new Registration*[other.rawCapacity];
			for (std::size_t i = 0; i < rawCapacity; ++i)
			{
				newBuf[i] = new Registration(*other.regs[i]);
			}

			// cleanup----
			for (std::size_t i = 0; i < nextFreeIndex; i++)
			{
				delete regs[i];
			}
			delete[] regs;
			// cleanup----

			this->regs = newBuf;
			this->rawCapacity = other.rawCapacity;
			this->nextFreeIndex = other.nextFreeIndex;
		}
		catch (std::bad_alloc&)
		{
			std::cerr << "The copy constructor of registration list was denied memory. Aborting copy and rethrowing. The objects are left in an unchanged state." << std::endl;
			throw;
		}
	}

	~RegistrationList()
	{
		for (std::size_t i = 0; i < nextFreeIndex; i++)
		{
			delete regs[i];
		}
		delete[] regs;
		regs = nullptr;
		rawCapacity = 0;
		nextFreeIndex = 0;
	}

	void insert(const std::string& id, const Date& date)
	{
		if (nextFreeIndex >= rawCapacity)
		{
			throw std::exception("The registration list is out of available space!");
		}

		try {
			Registration* registration = new Registration(id, date);
			regs[nextFreeIndex] = registration;
			for (std::size_t i = 0; i < nextFreeIndex; ++i)
			{
				if (*regs[nextFreeIndex] < *regs[i])
				{
					std::swap(regs[nextFreeIndex], regs[i]);
				}
			}
			nextFreeIndex++;
		}
		catch (std::bad_alloc&)
		{
			std::cerr << "Could not allocate for a registration! Aborting addition and rethrowing." << std::endl;
			throw;
		}
	}

	const Registration& at(std::size_t index) const
	{
		if (index >= nextFreeIndex)
		{
			throw std::out_of_range("Requested registration after the end of the list!");
		}
		return *regs[index];
	}

	const Registration& operator[](std::size_t index) const
	{
		assert(index < nextFreeIndex);
		return *regs[index];
	}

	bool empty() const { return nextFreeIndex == 0; }

	std::size_t capacity() const { return rawCapacity; }

	std::size_t size() const { return nextFreeIndex; }
private:
	std::size_t rawCapacity;
	std::size_t nextFreeIndex;
	Registration** regs;
};

std::ostream& operator<<(std::ostream& os, const RegistrationList& regList)
{
	for (std::size_t i = 0; i < regList.size(); ++i)
	{
		std::cout << "\t - " << i + 1 << " - " << regList[i] << std::endl;
	}
	return os;
}

bool isInList(const std::string& id, const RegistrationList& list)
{
	for (std::size_t i = 0; i < list.size(); ++i)
	{
		if (list[i].id == id)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	bool successful = false;
	do {
		std::size_t n;
		std::cout << "Insert the number of registrations you want: ";
		std::cin >> n;
		try {
			RegistrationList list(n);
			successful = true;
			for (std::size_t i = 0; i < n; i++)
			{
				std::string id;
				unsigned int day, month, year;

				bool okID = true;
				bool okDate = true;

				do {
					if (!okID)
					{
						std::cerr << "The id is already registered, try another one!" << std::endl;
					}
					std::cout << "input id: ";
					std::cin >> id;
					okID = false;
				} while (isInList(id, list));

				do {
					std::cout << "input day: ";
					std::cin >> day;
					std::cout << "input month: ";
					std::cin >> month;
					std::cout << "input year: ";
					std::cin >> year;
					try {
						Date date(day, month, year);
						try {
							list.insert(id, date);
						}
						catch (std::bad_alloc&)
						{
							std::cerr << "The list could not allocate a new registration! Exiting!" << std::endl;
							return OUT_OF_MEMORY_EXIT_CODE;
						}
						catch (std::exception&)
						{
							std::cerr << "The list ran out of memory preemptively! Exiting!" << std::endl;
							return OUT_OF_MEMORY_EXIT_CODE;
						}
						okDate = true;
					}
					catch (std::invalid_argument& e)
					{
						std::cerr << e.what() << std::endl;
						okDate = false;
					}
				} while (!okDate);
			}

			std::cout << "The registration list is: " << std::endl;
			std::cout << list;
		}
		catch (std::bad_alloc&)
		{
			std::cerr << "Could not create with " << n << " registrations, maybe try a smaller amount" << std::endl;
			successful = false;
		}
	} while (!successful);
	return 0;
}