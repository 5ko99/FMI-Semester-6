
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Киара Чобанова
// ФН: 82200
// Специалност: КН
// Курс: първи
// Административна група: четвърта
// Ден, в който се явявате на контролното:  17.04.21 
// Начален час на контролното: <тук попълнете часа за вашата група> 10:30
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> Visual C++
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

class Date {
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint8_t m_year;

public:
	bool validation();
	Date(unsigned int day, unsigned int month, unsigned int year);
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};

bool Date::validation() {

	return !(m_month > 12 || m_month < 1);
	return !((m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12) && m_day > 31);
	return !((m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11) && m_day > 30);
	return !(m_year % 4 == 0 && m_year % 100 == 0 && m_year % 400 != 0) && (m_month == 2 && m_day > 29);
	return !(m_year % 4 == 0 && m_year % 100 != 0 && m_year % 400 == 0) && (m_month == 2 && m_day > 28);

}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	m_day = day;
	m_month = month;
	m_year = year;
	try {
		validation();
	}
	catch (std::invalid_argument) {
		std::cout << "Inavaild argument!";
		exit(0);
	}
}

unsigned int Date::day() const {
	return m_day;
}

unsigned int Date::month() const {
	return m_month;
}

unsigned int Date::year() const {
	return m_year;
}

bool Date::operator==(const Date& rhs) const {

	const uint8_t day = rhs.m_day;
	const uint8_t month = rhs.m_month;
	const uint8_t year = rhs.m_year;
	return (m_day == day && m_month == month && m_year == year);
}

bool Date::operator<(const Date& rhs) const {
	const uint8_t day = rhs.m_day;
	const uint8_t month = rhs.m_month;
	const uint8_t year = rhs.m_year;

	return (m_year < year || (m_month < month&& m_year < year) || (m_day < day&& m_month < month&& m_year < year));
}

class Registration {
public:
	const std::string m_id;
	Date m_date;
	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const;
	Registration operator=(const Registration& rhs) const;
	std::string getRegistration();
};

std::string Registration::getRegistration() {
	return m_id;
}

//Registration::Registration(const std::string& id, const Date& date) {
//}

bool Registration::operator==(const Registration& rhs) const {
	return (m_id == rhs.m_id && m_date == rhs.m_date);
}

bool Registration::operator<(const Registration& rhs) const {
	return ((m_date < rhs.m_date) || (m_date == rhs.m_date && m_id < rhs.m_id));
}

const int MAX_CAPACITY = 100;

class RegistrationList {

	const std::size_t m_capacity = MAX_CAPACITY; 
	void erase();
public:
	RegistrationList();
	~RegistrationList();
	RegistrationList(const Registration& other);


	RegistrationList(std::size_t capacity);
	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index) const;
	const Registration& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;
};

std::size_t RegistrationList::capacity() const {
	return m_capacity;
}

std::size_t RegistrationList::size() const {
	size_t size = MAX_CAPACITY - m_capacity;
	return size;
}

bool RegistrationList::empty() const {
	return (m_capacity == MAX_CAPACITY);
}



int main() {
	size_t N;
	std::cout << "Enetr N:";
	std::cin >> N;

	return 0;
}