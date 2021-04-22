// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Мартин Попов
// ФН: 82134
// Специалност: компютърни науки
// Курс: първи
// Административна група: първа
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>


class Date {
	std::uint8_t currentDay;
	std::uint8_t currentMonth;
	std::uint16_t currentYear;

	bool isLeap(std::uint16_t y) {
		if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
			return true;
		}
		return false;
	}
	bool validDate(unsigned int d, unsigned int m, unsigned int y) {
		if (m < 1 || m > 12) {
			return false;
		}
		if (d < 1 || d > 31) {
			return false;
		}
		bool leap = isLeap(y);

		switch (m) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (d == 31) {
				return false;
			}
			break;
		case 2:
			if (leap) {
				if (d > 29) {
					return false;
				}
			}
			else {
				if (d > 28) {
					return false;
				}
			}
		default:
			break;
		}
		
		return true;
	}

public:
	Date(unsigned int day, unsigned int month, unsigned int year) {
		if (validDate(day, month, year)) {
			currentDay = day;
			currentMonth = month;
			currentYear = year;
		}
		else {
			throw std::invalid_argument("invalid arguments for date");
		}
	}

	bool operator==(const Date& rhs) const {
		//compare *this with rhs
		if (this == &rhs) {
			return true;
		}
		if (this->currentDay == rhs.currentDay &&
			this->currentMonth == rhs.currentMonth &&
			this->currentYear == rhs.currentYear) {
			return true;
		}
		return false;
	}
	bool operator<(const Date& rhs) const {
		//check if *this before rhs
		if (this->currentYear < rhs.currentYear) {
			return true;
		}
		else if (this->currentYear > rhs.currentYear) {
			return false;
		}
		else {
			//this year = rhs year
			if (this->currentMonth < rhs.currentMonth) {
				return true;
			}
			else if (this->currentMonth > rhs.currentMonth) {
				return false;
			}
			else {
				//this month = rhs month
				if (this->currentDay < rhs.currentDay) {
					return true;
				}
				else {
					return false;
				}
			}
		}


		//return false;
	}
	unsigned int day() const {
		return currentDay;
	}
	unsigned int month() const {
		return currentMonth;
	}
	unsigned int year() const {
		return currentYear;
	}
};

class Registration {
	std::string id;
	Date date;

public:
	Registration(const std::string& id, const Date& date): id(id), date(date) {

	}
	Registration(const Registration& reg) : id(reg.id), date(reg.date) {

	}
	Registration& operator=(const Registration& reg) {
		if (this != &reg) {
			this->id = reg.id;
			this->date = reg.date;
		}
		return *this;
	}
	~Registration() {

	}

	bool operator==(const Registration& rhs) const {
		if (this == &rhs) {
			return true;
		}
		if (this->id == rhs.id && this->date == rhs.date) {
			return true;
		}
		return false;
	}
	bool operator<(const Registration& rhs) const {
		if (this->date < rhs.date) {
			return true;
		}
		if (this->date == rhs.date) {
			if (this->id < rhs.id) {
				return true;
			}
		}

		return false;
	}

};

class RegistrationList {
	std::size_t maxCapacity;
	Registration** vehicles = nullptr;

	std::size_t registrationsCapacity = 2;
	std::size_t numOfRegistrations = 0;

	void copy(const RegistrationList& regList) {
		Registration** newVehicles = new Registration * [regList.registrationsCapacity]();
		for (std::size_t i = 0; i < regList.numOfRegistrations; i++) {
			Registration* reg = new Registration(*regList.vehicles[i]);
			newVehicles[i] = reg;
		}

		for (std::size_t j = 0; j < numOfRegistrations; j++) {
			delete vehicles[j];
		}
		delete[] vehicles;

		this->vehicles = newVehicles;
		maxCapacity = regList.maxCapacity;
		registrationsCapacity = regList.registrationsCapacity;
		numOfRegistrations = regList.numOfRegistrations;
	}
	void expand() {
		Registration** newVehicles = new Registration * [registrationsCapacity * 2]();
		for (std::size_t i = 0; i < numOfRegistrations; i++) {
			newVehicles[i] = vehicles[i];
		}

		delete[] vehicles;
		vehicles = newVehicles;
		registrationsCapacity *= 2;
	}
	bool existsInRegistrationList(const Registration& reg) {
		for (std::size_t i = 0; i < numOfRegistrations; i++) {
			if (*vehicles[i] == reg) {
				return true;
			}
		}
		return false;
	}
public:
	RegistrationList(std::size_t capacity) {
		vehicles = new Registration * [registrationsCapacity]();
		this->maxCapacity = capacity;
	}

	RegistrationList(const RegistrationList& regList) {
		copy(regList);
	}
	RegistrationList& operator==(const RegistrationList& regList) {
		if (this != &regList) {
			copy(regList);
		}
		return *this;
	}
	~RegistrationList() {
		for (std::size_t i = 0; i < numOfRegistrations; i++) {
			delete vehicles[i];
		}
		delete[] vehicles;
		maxCapacity = 0;
		numOfRegistrations = 0;
		registrationsCapacity = 0;
	}

	void insert(const std::string& id, const Date& date) {
		if (numOfRegistrations == registrationsCapacity) {
			if (registrationsCapacity < maxCapacity) {
				expand();
			}
			else {
				throw std::exception("not enough space");
			}
		}


		Registration* newReg = new Registration(id, date);

		if (existsInRegistrationList(*newReg)) {
			delete newReg;
			throw std::exception("already exists");
		}
		//add exists in rL


		for (std::size_t i = numOfRegistrations; i > 0; i--) {
			if (*newReg < *vehicles[i - 1]) {
				vehicles[i] = vehicles[i - 1];
			}
			else {
				vehicles[i] = newReg;
				break;
			}

		}

		numOfRegistrations++;
	}

	const Registration& at(std::size_t index) const {
		if (index >=  numOfRegistrations) {
			throw std::out_of_range("index is out of range");
		}
		return *vehicles[index];
	}
	const Registration& operator[](std::size_t index) const {
		assert(index < numOfRegistrations);
		return *vehicles[index];
	}

	bool empty() const {
		if (numOfRegistrations == 0) {
			return true;
		}
		return false;
	}
	std::size_t capacity() const {
		return maxCapacity;
	}
	std::size_t size() const {
		return numOfRegistrations;
	}

};



int main() {

	//try {
	//	Date d1(30, 6, 2019);
	//	Date d2(13, 5, 2020);
	//	Date d3(23, 4, 2001);


	//	RegistrationList rL(5);
	//	rL.insert("test1", d1);
	//	rL.insert("test2", d2);
	//	rL.insert("test3", d3);

	//	RegistrationList rL2 = rL;
	//	std::cout << rL2.size() << " " << rL2.capacity() << " " << rL2[2].test();
	//	//std::cout << d.day() << "." << d.month() << "." << d.year();
	//}
	//catch (const std::invalid_argument& e) {
	//	std::cerr << e.what();
	//}
	//catch (const std::exception& e) {
	//	std::cerr << e.what();
	//}

	std::size_t n;
	std::cin >> n;
	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Please enter valid number\n";
		std::cin >> n;
	}
	std::cout << n;

	RegistrationList regList(n);

	for (std::size_t i = 0; i < n; i++) {

		//regList.insert()
	}


	return 0;
}

