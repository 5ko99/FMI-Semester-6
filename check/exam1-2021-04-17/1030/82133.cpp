// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Карина Христова
// ФН: 82133
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: MSVC
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

bool IsLeapYear(uint16_t y)
{
	bool divisibleBy4 = y % 4 == 0;
	bool divisibleBy100 = y % 100 == 0;
	bool divisibleBy400 = y % 400 == 0;

	if (!divisibleBy4) {
		return false;
	}
	else if (divisibleBy4 && !divisibleBy100) {
		return true;
	}
	else if (divisibleBy4 && divisibleBy100) {
		if (!divisibleBy400)
			return false;
	}
	else {
		return true;
	}
}

bool IsDayValid(uint8_t d, uint8_t m, uint16_t y)
{
	if (d == 0)
		return false;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		return d <= 31;
	if (m == 4 || m == 6 || m == 9 || m == 11)
		return d <= 30;
	if (m == 2)
	{
		if (IsLeapYear(y))
		{
			return d <= 29;
		}
		else
		{
			return d <= 28;
		}
	}
}

bool IsMonthValid(uint8_t m)
{
	return (m >= 1 && m <= 12);
}

class Date
{
	std::uint8_t dayDate;
	std::uint8_t monthDate;
	std::uint16_t yearDate;

	//% 4 == 0 && % 100 != 0
	//%4 == 0 && % 100 == 0 &&

public:
	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		if (!IsDayValid(day, month, year) || IsMonthValid(month))
			throw std::invalid_argument("Incorrect date");

		this->dayDate = day;
		this->monthDate = month;
		this->yearDate = year;
	}

	unsigned int day() const
	{
		unsigned int d = this->dayDate;
		return d;
	}

	unsigned int month() const
	{
		unsigned int m = this->monthDate;
		return m;
	}

	unsigned int year() const
	{
		unsigned int y = this->yearDate;
		return y;
	}

	bool operator==(const Date& rhs) const
	{
		bool sameDay = this->dayDate == rhs.day();
		bool sameMonth = this->monthDate == rhs.month();
		bool sameYear = this->yearDate == rhs.year();

		bool isDateSame = sameDay && sameMonth && sameYear;
		return isDateSame;
	}

	bool operator<(const Date& rhs) const
	{
		bool sameYear = this->yearDate == rhs.year();
		bool sameMonth = this->dayDate == rhs.month();

		if (sameYear) {
			if (sameMonth) {
				if (this->dayDate < rhs.day())
					return true;
				else
					return false;
			}
			else {
				if (this->monthDate < rhs.month())
					return true;
				else
					return false;
			}
		}
		else {
			if (this->yearDate < rhs.year())
				return true;
			else
				return false;
		}
	}
};

class Registration
{
	std::string id; //Registration number
	Date date;
public:
	Registration(const std::string& id, const Date& date)
		:id(id), date(date)
	{
	}

	bool operator==(const Registration& rhs) const
	{
		bool sameId = this->id == rhs.id;
		bool sameDate = (this->date == rhs.date);

		bool sameReg = sameId && sameDate;
		return sameReg;
	}

	//Thuis registration is before rhs if:
	//1)This date is before rhs date
	//2)Same dates, but this id is before rhs id
	bool operator<(const Registration& rhs) const
	{
		bool sameDate = (this->date == rhs.date);
		if (!sameDate) {
			bool thisIsFirst = (this->date < rhs.date);
			return thisIsFirst;
		}
		else {
			bool thisIdIsFirst = (this->id < rhs.id);
			return thisIdIsFirst;
		}
	}

	void printReg()
	{
		std::cout << this->id << " : " << this->date.day() << this->date.month() << this->date.year() << std::endl;
	}
};

//Notice:
//Регистрациите в списъка трябва да се пазят сортирани в нарастващ ред.
class RegistrationList
{
	std::size_t capacityOfList;
	Registration** registrations;
	std::size_t storedRegistrations;

public:
	RegistrationList(std::size_t capacity)
	{
		this->capacityOfList = capacity;
		this->storedRegistrations = 0;

		registrations = new (std::nothrow) Registration * [1];
		if (registrations == nullptr)
			throw std::exception("Could not allocate memory");
	}

	RegistrationList(RegistrationList& other)
	{
		this->capacityOfList = other.capacityOfList;
		this->storedRegistrations = other.storedRegistrations;

		int regLen = other.storedRegistrations;

		this->registrations = new (std::nothrow) Registration * [storedRegistrations];
		if (this->registrations == nullptr)
			throw std::exception("Could not allocate memory");

		for (size_t i = 0; i < regLen; i++)
			this->registrations[i] = other.registrations[i];
	}

	~RegistrationList()
	{
		if (this->storedRegistrations != 0) {
			for (size_t i = 0; i < this->storedRegistrations; i++)
				delete this->registrations[i];

			delete[] this->registrations;
		}
	}

	RegistrationList operator=(RegistrationList& other)
	{
		int regLen = other.storedRegistrations;

		Registration** newRegistrations = new(std::nothrow) Registration * [storedRegistrations];
		if (newRegistrations == nullptr)
			throw std::exception("Could not allocate memory");

		for (size_t i = 0; i < regLen; i++)
			newRegistrations[i] = other.registrations[i];

		if (this->storedRegistrations != 0) {
			for (size_t i = 0; i < this->storedRegistrations; i++)
				delete[] this->registrations[i];

			delete[] this->registrations;
		}

		this->registrations = newRegistrations;
		this->capacityOfList = other.capacityOfList;
		this->storedRegistrations = other.storedRegistrations;
	}

	bool IsRegistrationPresent(Registration& reg)
	{
		if (this->storedRegistrations != 0)
		{
			bool isPresent = false;
			for (size_t i = 0; i < this->storedRegistrations; i++)
				if ((*(this->registrations[i]) == reg)) {
					isPresent = true;
					break;
				}
			return isPresent;
		}
		else
			return false;
	}
	//Before adding a reg check if it is full!!
	void insert(const std::string& id, const Date& date)
	{
		
		Registration newReg = Registration(id, date);
		if (IsRegistrationPresent(newReg))
			throw std::exception("Registration is already present in the registration list!");
		
		Registration* p = &newReg;
		//Checking if there is enough space in the NON-EMPTY list
		if (this->storedRegistrations != 0)
		{
			if ((this->storedRegistrations + 1 < this->capacityOfList)) {
				int indexOfLastOne = this->storedRegistrations - 1;
				bool lastOneIsBefore = (*(this->registrations[indexOfLastOne]) < newReg);
				int len = this->storedRegistrations + 1;

				if (lastOneIsBefore) //Put the new reg on last position
				{
					Registration** newRegistrations = new (std::nothrow) Registration * [len];
					if (newRegistrations == nullptr)
						throw std::exception("Could not allocate memory");

					for (size_t i = 0; i < this->storedRegistrations; i++)
						newRegistrations[i] = this->registrations[i];
					newRegistrations[this->storedRegistrations] = p;

					//Delete the previous content of this->registrations
					for (size_t i = 0; i < this->storedRegistrations; i++)
						delete[] this->registrations[i];
					delete[] this->registrations;
					//New content of registrations
					this->registrations = newRegistrations;
					this->storedRegistrations = len;
				}
				else //Find the pos in which the newReg should be added
				{
					int pos = 0;

					for (size_t i = 0; i < this->storedRegistrations; i++) {
						bool newRegIsBefore = (newReg < *(this->registrations[i]));
						if (newRegIsBefore) {
							pos = i;
							break;
						}
					}

					Registration** newRegistrations = new (std::nothrow) Registration * [len];
					if (newRegistrations == nullptr)
						throw std::exception("Could not allocate memory");

					for (size_t i = 0; i < pos; i++) //Copy regs before pos
						newRegistrations[i] = this->registrations[i];

					newRegistrations[pos] = p; //Place newReg on pos

					for (size_t i = pos + 1; i < len; i++) //Copy regs after pos
						newRegistrations[i] = this->registrations[i];

					//Delete previous content of this->registrations
					for (size_t i = 0; i < this->storedRegistrations; i++)
						delete[] this->registrations[i];
					delete[] this->registrations;

					this->registrations = newRegistrations;
					this->storedRegistrations = len;
				}
			}
		}
		else {
			if (this->storedRegistrations + 1 < this->capacityOfList) {
				int len = this->storedRegistrations + 1;
				Registration** newRegistrations = new (std::nothrow) Registration * [len];
				if (newRegistrations == nullptr)
					throw std::exception("Could not allocate memory");
				for (size_t i = 0; i < len; i++)
					newRegistrations[i] = this->registrations[i];
			}
			else
				throw std::exception("Garage capacity reached");
		}
	}

	const Registration& at(std::size_t index) const
	{
		if (index < 0 || index >= this->storedRegistrations)
			throw std::out_of_range("Index out of range!");

		Registration& r = *(this->registrations[index]);
		return r;
	}

	const Registration& operator[](std::size_t index) const
	{
		assert(index >= 0 && index < this->storedRegistrations);

		Registration& r = *(this->registrations[index]);
		return r;
	}

	bool empty() const
	{
		return (this->storedRegistrations == 0);
	}

	std::size_t capacity() const
	{
		return this->capacityOfList;
	}

	std::size_t size() const
	{
		return this->storedRegistrations;
	}

	

	void printContentOfRegList()
	{
		for (size_t i = 0; i < this->storedRegistrations; i++)
		{
			Registration currReg = *(this->registrations[i]);
			currReg.printReg();
		}
	}
};

int main()
{
	size_t lenOfRegList = 0;
	std::cout << "Please enter the length of the list: " << std::endl;
	std::cin >> lenOfRegList;

	RegistrationList myRegList = RegistrationList(lenOfRegList);
	int mistakes = 0;

	for (size_t i = 0; i < lenOfRegList; i++)
	{
		std::string currentRegID;
		unsigned int currDay, currMonth, currYear;

		while (true)
		{
			std::cout << "Please enter data for the current registartion (registration number, day, month, year): " << std::endl;
			std::cin >> currentRegID >> currDay >> currMonth >> currYear;

			bool isDayCorrect = IsDayValid(currDay, currMonth, currYear);
			bool isMonthCorrect = IsMonthValid(currMonth);
			bool isDateCorrect = isDayCorrect && isMonthCorrect;
			
			if (isDateCorrect)
				break;
		}

		Date currDate = Date(currDay, currMonth, currYear);

		try {
			myRegList.insert(currentRegID, currDate);
		}
		catch (const std::exception& e) {
			std::cout << e.what();
			mistakes++;
			lenOfRegList++;
		}

	}

	myRegList.printContentOfRegList();

}