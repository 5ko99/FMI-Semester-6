// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Александър Владиславов Жеков
// ФН: 82135
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021 (Събота)
// Начален час на контролното: 10:30
// Кой компилатор използвате: Visual C++
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date {
	private:
		std::uint8_t Day;
		std::uint8_t Month;
		std::uint8_t Year;

		bool isLeapYear(unsigned int year) const;
		bool isValid() const;

	public:
		Date(unsigned int day, unsigned int month, unsigned int year);

		unsigned int day() const;
		unsigned int month() const;
		unsigned int year() const;

		bool operator==(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
};

bool Date::isLeapYear(unsigned int year) const {
	if ((year % 4 == 0 ||year % 400 == 0) && year % 100 != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Date::isValid() const{
	if (Month < 1 || Month > 12) {
		return false;
	}

	unsigned int tempDay;
	if (isLeapYear(Year) && Month == 2) {
		tempDay = 29;
	}
	else if(!isLeapYear(Year) && Month == 2) {
		tempDay = 28;
	}
	else {
		switch (Month) {
			case 4: tempDay = 30; break;
			case 6: tempDay = 30; break;
			case 9: tempDay = 30; break;
			case 11: tempDay = 30; break;

			default: tempDay = 31;
		}
	}

	if (tempDay == Day) {
		return true;
	}
		
	return false;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	Day = day;
	Month = month;
	Year = year;

	if (!isValid()) {
		throw std::invalid_argument("Invalid date!");
	}
}

unsigned int Date::day() const{
	return this->Day;
}

unsigned int Date::month() const {
	return this->Month;
}

unsigned int Date::year() const {
	return this->Year;
}

bool Date::operator==(const Date& rhs) const {
	if (rhs.day() == Day && rhs.month() == Month && rhs.year() == Year) {
		return true;
	}
	
	return false;
}

bool Date::operator<(const Date& rhs) const {
	if (Year <= rhs.year()) {
		return true;
	}
	else {
		return false;
	}

	if (Month <= rhs.month()) {
		return true;
	}
	else {
		return false;
	}

	if (Day <= rhs.day()) {
		return true;
	}
	else {
		return false;
	}
}

class Registration {
	private:
		Date date;
		std::string id;

	public:
		Registration(const std::string& id, const Date& date);
		bool operator==(const Registration& rhs) const;
		bool operator<(const Registration& rhs) const;
};

Registration::Registration(const std::string& id, const Date& date) {
	this->id = id;
	this->date = date;
}

bool Registration::operator==(const Registration& rhs) const {
	if (this->id == rhs.id && this->date == rhs.date) {
		return true;
	}
	return false;
}

bool Registration::operator<(const Registration& rhs) const {
	if (this->date < rhs.date) {
		return true;
	}
	else if (this->date == rhs.date && this->id < rhs.id) {
		return true;
	}
	return false;
}

class RegistrationList {
	private:
		std::size_t Capacity;
		std::size_t Size;
		Registration** Registrations;
		void sort();

	public:
		RegistrationList(std::size_t capacity);
		RegistrationList(const RegistrationList& rlst);
		~RegistrationList();

		void insert(const std::string& id, const Date& date);
		const Registration& at(std::size_t index) const;
		bool empty() const;
		std::size_t capacity() const;
		std::size_t size() const;

		const Registration& operator[](std::size_t index) const;
		RegistrationList& operator=(const RegistrationList& rlst);
};

RegistrationList::RegistrationList(std::size_t capacity) {
	bool freeMem = true;

	try {
		Registrations = new Registration * [capacity];
	}
	catch (std::bad_alloc& ba) {
		freeMem = false;
		throw;
	}

	if (freeMem) {
		Capacity = capacity;
		Size = 0;
	}
}

RegistrationList::RegistrationList(const RegistrationList& rlst) {
	if (rlst.empty()) {
		Capacity = rlst.Capacity;
		Size = 0;
	}
	else {
		bool freeMem = true;
		try {
			Registrations = new Registration * [rlst.Capacity];
		}
		catch (std::bad_alloc& ba) {
			freeMem = false;
			std::cerr << "An exception occured: " << ba.what() << '\n';
		}

		if (freeMem) {
			Capacity = rlst.Capacity;
			Size = rlst.Size;
		
			for (size_t i = 0; i < rlst.Size; ++i) {
				Registrations[i] = new Registration(*rlst.Registrations[i]);
			}
		}
		else {
			std::cerr << "The new registration list couldn't be created!" << '\n';
		}
	}
}

RegistrationList::~RegistrationList() {
	delete[] Registrations;
}

void RegistrationList::sort() {
	for (size_t i = 0; i < Size - 1; ++i) {
		for (size_t j = i + 1; j < Size; ++i) {
			if (*Registrations[i] < *Registrations[j]) {
				Registration* tempPtr = Registrations[i];
				Registrations[i] = Registrations[j];
				Registrations[j] = tempPtr;
			}
		}
	}
}

void RegistrationList::insert(const std::string& id, const Date& date) {
	if (Size + 1 > Capacity) {
		throw std::exception("Registration list is full!");
	}
	else {
		Registration* reg = new Registration(id, date);
		Registrations[Size] = reg;
		++Size;
		sort();
	}
}

const Registration& RegistrationList::at(std::size_t index) const {
	if (index > Size - 1) {
		throw std::out_of_range("No registration at that index");
	}
	else {
		return *Registrations[index];
	}
}

bool RegistrationList::empty() const {
	return (Size == 0);
}

std::size_t RegistrationList::capacity() const {
	return Capacity;
}

std::size_t RegistrationList::size() const {
	return Size;
}

const Registration& RegistrationList::operator[](std::size_t index) const {
	assert(index <= Size - 1);
	return *Registrations[index];
}

RegistrationList& RegistrationList::operator=(const RegistrationList& rlst) {
	if (rlst.empty()) {
		Capacity = rlst.Capacity;
		Size = 0;
	}
	else {
		bool freeMem = true;
		try {
			Registrations = new Registration * [rlst.Capacity];
		}
		catch (std::bad_alloc& ba) {
			freeMem = false;
			std::cerr << "An exception occured: " << ba.what() << '\n';
		}

		if (freeMem) {
			Capacity = rlst.Capacity;
			Size = rlst.Size;

			for (size_t i = 0; i < rlst.Size; ++i) {
				Registrations[i] = new Registration(*rlst.Registrations[i]);
			}
		}
		else {
			std::cerr << "The new registration list couldn't be created!" << '\n';
		}
	}
	return *this;
}

int main()
{
	bool freeMem = true;
	bool invalidDate = true;
	unsigned int listSize;

	std::cout << "Enter the size of the list: "; std::cin >> listSize;
	if (listSize <= 0) {
		std::cout << "The size of the list is invalid! Please enter a vlid one: ";
		std::cin >> listSize;
	}

	RegistrationList* regList = nullptr;

	try {
		regList = new RegistrationList(listSize);
	}
	catch (std::bad_alloc& ba) {
		freeMem = false;
		std::cerr << "There isn't enough memory!" << std::endl;
	}

	if (freeMem) {
		std::string id;
		unsigned int d, m, y;
		for (size_t i = 0; i < listSize; i++) {
			Date* date = nullptr;
			while (invalidDate) {
				invalidDate = false;
				try {
					std::cout << "Enter id: "; std::cin >> id;
					std::cout << "Enter day: "; std::cin >> d;
					std::cout << "Enter month: "; std::cin >> m;
					std::cout << "Enter year: "; std::cin >> y;
					date = new Date(d, m, y);
				}
				catch (std::invalid_argument& err) {
					invalidDate = true;
					std::cerr << err.what() << "Enter a valid one:\n";
				}
			}
			try {
				regList->insert(id, *date);
			}
			catch (std::exception& err) {
				std::cerr << err.what() << '\n';
			}
		}
	}

	return 0;
}