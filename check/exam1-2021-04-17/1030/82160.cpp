// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Цветомир Каменов
// ФН: 82160
// Специалност: Компютърни Науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>
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
#include <cstdint>
#include <stdexcept>
#include <cstddef>

enum class Month  {
	UNKNOWN = -1,
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

class Date {
	std::uint8_t vDate;
	std::uint8_t vMonth;
	std::uint16_t vYear;

	bool isLeapYear() {
		if (vYear % 4 == 0 && vYear % 100 != 0)
			return true;
		else if (vYear % 4 == 0 && vYear % 100 == 0 && vYear % 400 == 0)
			return true;
		else 
			return false;
	}

	bool isValidMonth() {
		if (vMonth > 0 && vMonth < 13)
			return true;
		else
			return false;
	}

	bool isValidDay() {
		if (vDate > 0 && vDate < 32)
			return true;
		else
			return false;
	}

public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator ==(const Date& rhs) const;
	bool operator <(const Date& rhs) const;
};

Date::Date(unsigned int day, unsigned month, unsigned int year) {

}	

unsigned int Date::day() const {
	return vDate;
}

unsigned int Date::month() const {
	return vMonth;
}

unsigned int Date::year() const {
	return vYear;
}

bool Date::operator ==(const Date& rhs) const {
	if (vDate == rhs.vDate && vMonth == rhs.vMonth && vYear == rhs.vYear)
		return true;
	else
		return false;
}

bool Date::operator <(const Date& rhs) const {
	if (vYear < rhs.vYear)
		return true;
	else if (vYear > rhs.vYear)
		return false;
	else {
		if (vMonth < rhs.vMonth)
			return true;
		else if (vMonth > rhs.vMonth)
			return false;
		else {
			if (vDate < rhs.vDate)
				return true;
			else
				return false;
		}
	}
}

class Registration {
public:
	const std::string vId;
	const Date vdate;

	Registration(const std::string& id, const Date& date);

	bool operator== (const Registration& rhs) const;
	bool operator< (const Registration& rhs) const;

};

Registration::Registration(const std::string& id, const Date& date) {

}

bool Registration::operator== (const Registration& rhs) const {
	if (vId == rhs.vId && vdate == rhs.vdate)
		return true;
	else
		return false;
}

bool Registration::operator< (const Registration& rhs) const {
	if (vdate < rhs.vdate)
		return true;
	else if (vdate == rhs.vdate) {
		if (vId < rhs.vId)
			return true;
		else
			return false;
	}
}

class RegistrationList {
	std::size_t vCapacity;
public:
	RegistrationList(std::size_t capacity);
	RegistrationList() {};
	~RegistrationList();
	RegistrationList(const RegistrationList&);

	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index) const;
	const Registration& operator[](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;

};

int main()
{

	return 0;
}
