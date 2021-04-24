// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Нина Пламенова Вълкова
// ФН:82199
// Специалност:Компютърни науки
// Курс:1
// Административна група:4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате:Visual C++
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

//#define _CRT_SECURE_NO_WARNINGS 


#include <cstring>
#include <iostream>
#include <cassert>
#include <string>

using std::string;

class Date {
private:
	std::uint8_t m_date;
	std::uint8_t m_month;
	std::uint16_t m_year;
public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};

Date::Date(unsigned int day=0, unsigned int month=0, unsigned int year=0):m_date(day),m_month(month),m_year(year) {
}

unsigned int Date::day() const {
	return m_date;
}

unsigned int Date::month() const {
	return m_month;
}

unsigned int Date::year() const {
	return m_year;
}

bool  Date::operator==(const Date& rhs) const {
	bool flag = false;
	if (m_date==rhs.m_date && m_month==rhs.m_month && m_year==rhs.m_year) {
		flag = true;
	}
	return flag;
}

bool Date::operator<(const Date& rhs) const {
	bool flag = false;
	if (m_year != rhs.m_year) {
		flag = true;
	}
	else if (m_year == rhs.m_year && m_month < rhs.m_month) {
		flag = true;
	}
	else if (m_year == rhs.m_year && m_month >= rhs.m_month && m_date >= rhs.m_date) {
		flag = false;
	}

	return flag;
}

class Registration {
private:
	std::string id;
	Date date;
public:
	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const;
};

Registration::Registration(const std::string& id, const Date& date) {
	this->id = id;
	this->date = date;
}

bool Registration ::operator==(const Registration& rhs) const {
	if (id == rhs.id && date == rhs.date) {
		return true;
	}
	return false;
}

bool Registration ::operator<(const Registration& rhs) const {

	bool flag = true;

	if (id < rhs.id) {
		flag = false;
	}
	else if (id == rhs.id) {
		flag = false;
	}

	if (date < rhs.date) {
		return false;
	}
	else if (date == rhs.date && flag) {
		return true;
	}
}

class RegistrationList {
private:
	Registration* cars;
	std::size_t m_capacity;
	size_t m_size;

public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& another);
	RegistrationList operator = (const RegistrationList& another);
	~RegistrationList();
	void insert(const std::string& id, const Date& date);
	std::size_t capacity() const;
};

RegistrationList::RegistrationList(std::size_t capacity) {
	m_capacity = capacity;
}

RegistrationList::RegistrationList(const RegistrationList& another) {
	if (this != &another) {
		delete[] cars;
		m_capacity = 0;
		m_size = 0;
	}

	m_capacity = another.m_capacity;
	m_size = another.m_size;

	for (unsigned i = 0; i < m_size; i++) {
		cars[i] = another.cars[i];
	}

}

RegistrationList RegistrationList::operator = (const RegistrationList& another) {
	if (this != &another) {
		delete[] cars;
		m_capacity = 0;
		m_size = 0;
	}

	m_capacity = another.m_capacity;
	m_size = another.m_size;

	for (unsigned i = 0; i < m_size; i++) {
		cars[i] = another.cars[i];
	}
	return *this;
}

RegistrationList::~RegistrationList() {
	delete[] cars;
}

void RegistrationList::insert(const std::string& id, const Date& date) {
	Registration* registration;
	registration[0];
}


std::size_t RegistrationList::capacity() const {
	return m_size;
}

int main()
{
	Date date1(1,5,2011);
	Date date2(2, 5, 2011);

	if (date1 == date2) {
		std::cout << "True"<<"\n";
	}
	else {
		std::cout << "False" << "\n";
	}

	if (date1 < date2) {
		std::cout << "False" << "\n";
	}
	else {
		std::cout << "True" << "\n";
	}

	Registration registration1("1111", date1);
	Registration registration2("1111", date2);

	if (registration1 == registration2) {
		std::cout << "True" << "\n";
	}
	else {
		std::cout << "False" << "\n";
	}

	if (registration1 < registration2) {
		std::cout << "True" << "\n";
	}
	else {
		std::cout << "False" << "\n";
	}

	RegistrationList registrationList(10);
	registrationList.insert("1111", date1);
	return 0;
}