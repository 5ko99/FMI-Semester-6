// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Михаил Сашков
// ФН: 82190
// Специалност: Компютърни науки
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>



class Date {
private:
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint16_t m_year;
	void copy(const Date& other);

public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date(const Date& other);
	Date& operator =(const Date& other);
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator ==(const Date& rhs) const;
	bool operator <(const Date& rhs) const;

};

class Registration {
private:
	std::string id;
	Date date;

public:
	Registration(const std::string& id, const Date& date);
	bool operator ==(const Registration& rhs) const;
	bool operator <(const Registration& rhs) const;

};

class RegistrationList {
private:
	std::size_t m_capacity = 0;
	std::size_t m_size = 0;
	Registration** registration;
	void copy(const RegistrationList& other);

public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& other);
	RegistrationList& operator =(const RegistrationList& other);
	~RegistrationList();
	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index) const;
	const Registration& operator [](std::size_t index) const;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;

};

void Date::copy(const Date& other) {

	this->m_day = other.m_day;
	this->m_month = other.m_month;
	this->m_year = other.m_year;

}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {

	try {

		if(month < 1 || month > 12) {

			throw std::invalid_argument("The months must be between 1 and 12");

		}

		if(day == 0) {

			throw std::invalid_argument("The day cannot be 0");

		}

		if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {

			throw std::invalid_argument("The days must be under or equal to 31");

		}

		if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {

			throw std::invalid_argument("The days must be under or equal to 30");

		}

		if(month == 2 && ((year % 4 == 0  && year % 100 != 0) || (year % 4 == 0  && year % 100 == 0  && year % 400 == 0)) && day > 29) {

			throw std::invalid_argument("The days must be under or equal to 29");

		}

		if(month == 2 && (year % 4 != 0 || (year % 4 == 0  && year % 100 == 0  && year % 400 != 0)) && day > 28) {

			throw std::invalid_argument("The days must be under or equal to 28");

		}

		m_day = day;
		m_month = month;
		m_year = year;

	}
	catch(std::invalid_argument& ex) {
		
		std::cout<<"invalid_argument detected: "<<ex.what()<<std::endl;

	}

}

Date::Date(const Date& other) {

	copy(other);

}

Date& Date::operator =(const Date& other) {

	if(this != &other) {

		copy(other);

	}

	return *this;

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

	if(this->m_day == rhs.m_day && this->m_month == rhs.m_month && this->m_year == rhs.m_year) {

		return true;

	}

	return false;

}

bool Date::operator<(const Date& rhs) const {

	if((this->m_day < rhs.m_day && this->m_month == rhs.m_month && this->m_year == rhs.m_year) ||
		(this->m_month < rhs.m_month && this->m_year == rhs.m_year) ||
		(this->m_year < rhs.m_year)) {

			return true;

		}

		return false;

}

Registration::Registration(const std::string& id, const Date& date) {

	this->id = id;
	this->date = date;
	

}

bool Registration::operator==(const Registration& rhs) const {

	if(this->date == rhs.date && this->id == rhs.id) {

		return true;

	}

	return false;

}

bool Registration::operator<(const Registration& rhs) const {

	if(this->date < rhs.date || (this->date == rhs.date && this->id < rhs.id)) {

		return true;

	}

	return false;

}

void RegistrationList::copy(const RegistrationList& other) {

	this->m_capacity = other.m_capacity;
	this->m_size = other.m_size;

	this->registration = new Registration*[other.m_capacity];

	for(int i = 0; i < other.m_size; i++) {

		this->registration[i] = new Registration(*(other.registration[i]));

	}

}


RegistrationList::RegistrationList(std::size_t capacity) {

	m_capacity = capacity;
	registration = new Registration*[capacity];

	for(int i = 0; i < capacity; i++) {

		registration[i] = nullptr;

	}

}

RegistrationList::RegistrationList(const RegistrationList& other) {

	copy(other);

}

RegistrationList& RegistrationList::operator  =(const RegistrationList& other) {

	if(this != &other) {

		copy(other);

	}

	return *this;

}

void RegistrationList::insert(const std::string& id, const Date& date) {

	try {

		registration[m_size] = new Registration(id, date);
		m_size++;

		if(m_size == m_capacity) {

			throw std::exception("No more space");
			m_size--;

		}


		for(int i = 0; i < m_size; i++) {

			if(registration[i] == registration[i+1]){

				throw std::exception("This registration already excist");

			}

		}

		
		bool changed;

		do {

			changed = false;

			for(int i = m_size - 1; i >= 0; i--) {

				if(registration[i] < registration[i-1]) {

					std::swap(registration[i], registration[i-1]);

				}
			}

			changed = true;

		}while(!changed);

	}
	catch(std::exception& ex) {

		std::cout<<" exception detected: "<<ex.what()<<std::endl;
	}


}

const Registration& RegistrationList::at(std::size_t index) const {

	if(index < 0 || index >= m_size) {

		throw std::out_of_range("Invalid index");

	}

	return *registration[index];

}

const Registration& RegistrationList::operator[](std::size_t index) const {

	assert(index >= 0 && index < m_size);

	return *registration[index];

}

bool RegistrationList::empty() const {

	if(registration[0] == nullptr) {

		return true;

	}

	return false;

}

std::size_t RegistrationList::capacity() const {

	return m_capacity;

}

std::size_t RegistrationList::size() const {

	return m_size;

}

RegistrationList::~RegistrationList() {

	for(int i = 0; i < m_size; i++) {

		delete[] registration[i];

	}

	delete[] registration;

}





int main() {

	try{




	}
	catch(std::bad_alloc& ex) {

		std::cout<<"bad_alloc detected: "<<ex.what()<<std::endl;

	}


	return 0;

}