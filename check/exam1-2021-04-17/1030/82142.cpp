//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Чудомир Ченков
// ФН: 82142
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: Clang (тестван и с GCC g++)
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
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

class Date {
public:
	Date(unsigned int day, unsigned int month, unsigned int year) {
		if (!validate(day, month, year)) 
			throw std::invalid_argument("Error: Invalid date");

		m_day = day;
		m_month = month;
		m_year = year;
	}

	unsigned int day() const { return m_day; }

	unsigned int month() const { return m_month; }

	unsigned int year() const { return m_year; }

	bool operator==(const Date& rhs) const {
		return m_day == rhs.m_day && 
		       m_month == rhs.m_month && 
			   m_year == rhs.m_year;
	}

	bool operator<(const Date& rhs) const {
		if (m_year < rhs.m_year) return true;
		if (m_year > rhs.m_year) return false;

		if (m_month < rhs.m_month) return true;
		if (m_month > rhs.m_month) return false;

		if (m_day < rhs.m_day) return true;
		
		return false;
	}

private:
	bool validate(unsigned int day, unsigned int month, unsigned int year) const {
		if (month < 1 || month > 12) return false;

		switch(month) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if (day < 1 || day > 31) return false;
				break;
			case 4: case 6: case 9: case 11:
				if (day < 1 || day > 30) return false;
				break;
			case 2:
				if (is_leap(year) && (day < 1 || day > 29)) return false; 
				else if (!is_leap(year) && (day < 1 || day > 28)) return false;
				break;
		}

		return true;
	}

	bool is_leap(unsigned int year) const {
		if (year % 4 != 0) return false;
		if (year % 100 == 0 && year % 400 != 0) return false;

		return true;
	}

private:
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint16_t m_year;
};

class Registration {
public:
	Registration(const std::string& id, const Date& date)
		: m_id(id), m_date(date) {}
	
	bool operator==(const Registration& rhs) const {
		return m_id == rhs.m_id && m_date == rhs.m_date;
	}

	bool operator<(const Registration& rhs) const {
		if (m_date < rhs.m_date) return true;
		if (m_date == rhs.m_date && m_id < rhs.m_id) return true;

		return false;
	}

public:
	const std::string m_id;
	const Date m_date;
};

class RegistrationList {
public:
	RegistrationList(std::size_t capacity) 
		: m_capacity{capacity}, m_size{0}, m_registrations{nullptr}
	{}

	~RegistrationList() {
		for (std::size_t i = 0; i < m_size; i++) {
			delete m_registrations[i];
		}

		delete[] m_registrations;
	}

	RegistrationList(const RegistrationList& rhs) {
		m_capacity = rhs.m_capacity;
		m_size = rhs.m_size;

		m_registrations = new Registration *[m_size];

		for (std::size_t i = 0; i < rhs.m_size; i++) {
			m_registrations[i] = new Registration(
				rhs.m_registrations[i]->m_id, rhs.m_registrations[i]->m_date);
		}
	}

	RegistrationList& operator=(const RegistrationList& rhs) {
		if (this == &rhs) return *this;

		Registration **temp = new Registration *[rhs.m_size];
		for (std::size_t i = 0; i < rhs.m_size; i++) {
			m_registrations[i] = new Registration(
				rhs.m_registrations[i]->m_id, rhs.m_registrations[i]->m_date);
		}

		delete[] m_registrations;
		m_registrations = temp;
		m_capacity = rhs.m_capacity;
		m_size = rhs.m_size;

		return *this;
	}

	void insert(const std::string &id, const Date& date) {
		if (m_size == m_capacity)
			throw std::exception();

		std::size_t new_size = m_size + 1;
		Registration **temp = new Registration *[new_size];

		Registration *reg = new Registration(id, date);

		// if the second new throws an exception, there would be memory leak
		// from the first memory allocation
		// this problem can be resolved using std::nothrow and deleting
		// the first allocated memory block if the second allocation was unsuccessful
		// since <new> header is not allowed, the problem is not resolved in this solution

		std::size_t idx;
		for (idx = 0; idx < m_size; idx++) {
			if (*reg < *(m_registrations[idx])) break;
		}
		
		for (std::size_t i = 0; i < idx; i++) {
			temp[i] = m_registrations[i];
		}

		temp[idx] = reg;

		for (std::size_t i = idx + 1; i < new_size; i++) {
			temp[i] = m_registrations[i - 1];
		}

		delete[] m_registrations;
		m_registrations = temp;
		m_size = new_size;
	}

	const Registration& at(std::size_t index) const {
		if (index >= m_size) 
			throw std::out_of_range("Error: Invalid index");

		return *(m_registrations[index]);
	}

	const Registration& operator[](std::size_t index) const {
		assert(index < m_size);
		return *(m_registrations[index]);
	}

	bool empty() const { return m_size == 0; }

	std::size_t capacity() const { return m_capacity; }

	std::size_t size() const { return m_size; }

private:
	std::size_t m_capacity;
	std::size_t m_size;
	Registration **m_registrations;

};

int main() {
	std::size_t n;
	std::cout << "Enter number of registrations: ";
	std::cin >> n;

	RegistrationList list{n};

	for (std::size_t i = 0; i < n; i++) {
		std::string id;
		std::cout << "Enter id: ";
		std::cin >> id;

		unsigned int day;
		unsigned int month;
		unsigned int year;
		char delim;

		std::cout << "Enter date in format dd/mm/yyyy: ";
		std::cin >> day >> delim >> month >> delim >> year;

		try {
			Date date{day, month, year};
			list.insert(id, date);
		} catch (const std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			i--;
			continue;
		}
	} 

	std::cout << "Saved registrations: " << std::endl;

	for (std::size_t i = 0; i < list.size(); i++) {
		std::cout << list.at(i).m_id << std::endl;
	}

	return 0; 
}