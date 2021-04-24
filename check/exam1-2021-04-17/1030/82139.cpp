// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Иван Мишев Михов
// ФН:82139
// Специалност:КН
// Курс:1ви
// Административна група:1ва
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <10:30>
// Кой компилатор използвате: < GCC>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
# include <cstdint>
bool Leap(std::uint8_t year) {
	if ((year % 4 != 0) || (year % 100 == 0) || ((year % 4 == 0 && year % 100 == 0) && year % 400 != 0)  )
		return false;
	return true;
	
}
class Date {
private : 
	std::uint8_t Day;
	std::uint8_t Month;
	std::uint8_t Year;
public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
};
Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	if (month > 12 || month < 0||day ==0) {
		throw std::invalid_argument("");
	}
	else if ((month == 1 || month == 3 ||
		month == 5 || month == 7 || month == 8 ||
		month == 10 || month == 12) && (day < 0 || day>31)) {
		throw std::invalid_argument("");
	}
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day < 0 || day>30)) {
		throw std::invalid_argument("");
	}
	else if (month == 2 && day > 29) {
		throw std::invalid_argument("");
	}
	else if ((month == 2 && !Leap(year) && day == 29)) {
		throw std::invalid_argument("");
		}
	this->Day = day;
	this->Month = month;
	this->Year = year;
}
unsigned int Date::day()const {
	return this->Day;
}
unsigned int Date::month()const {
	return this->Month;
}
unsigned int Date::year()const {
	return this->Year;
}
bool Date::operator==(const Date& rhs) const {
	if (this->Day == rhs.day() && this->Month == rhs.month() && this->year() == rhs.year())
		return true;
	return false;
}
bool Date::operator<(const Date& rhs) const {
	if (this->Year < rhs.year())
		return true;
	else if (this->Month < rhs.month())
		return true;
	else if (this->Day < rhs.day())
		return true;
	return false;
}
class Registration {
private:
	const std::string * id;
	const Date * date;
public:
	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const;
};
Registration::Registration(const std::string& id, const Date& date) {
	this->id = new std::string(id);
	this->date = new Date(date.day(), date.month(), date.year());

}
bool Registration :: operator==(const Registration& rhs) const {
	if (this->id == rhs.id && this->date == rhs.date)
		return true;
	return false;
}
bool Registration :: operator<(const Registration& rhs) const {
	if (this->date < rhs.date)
		return true;
	else if (this->date == rhs.date && this->id < rhs.id)
		return true;
	return false;
}
class RegistrationList {
private:
	
	Registration** list;
	std::size_t filled;
	std::size_t Capacity;
public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList&);
	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index)const ;
	const Registration& operator[](std::size_t index) const;
	bool empty() const;
	RegistrationList& operator= (const RegistrationList&);
	std::size_t capacity() const;
	std::size_t size() const;
	~RegistrationList();

};
RegistrationList::RegistrationList(std::size_t capacity) {
	this->list = new Registration * [capacity];
	this->filled = 0;
	this->Capacity = capacity;
}
void RegistrationList::insert(const std::string& id, const Date& date) {
	if (this->filled >= this->Capacity)
		throw std::out_of_range("");
	this->list[filled] = new Registration(id, date);
	filled++;
}
const Registration& RegistrationList::at(std::size_t pos)const {
	if (this->list[pos] == nullptr)
		throw std::out_of_range("");
	else if (pos>this->filled)
		throw std::out_of_range("");
	return *this->list[pos];
}
const Registration& RegistrationList::operator[](std::size_t index) const {
	if (this->list[index] == nullptr)
		throw std::out_of_range("");
	else if (index > this->filled)
		throw std::out_of_range("");
	return *this->list[index];
}
bool RegistrationList::empty()const {
	return this->filled == 0;
}
std::size_t RegistrationList::capacity()const {
	return this->Capacity;
}
std::size_t RegistrationList::size()const {
	return this->filled;
}
RegistrationList::RegistrationList(const RegistrationList& other) {
	this->list = new Registration * [other.capacity()];
	this->filled = other.size();
	this->Capacity = other.capacity();
	for (std::size_t i = 0; i < other.size(); i++) {
		this->list[i] = new Registration(other.at(i));
	}
}
RegistrationList& RegistrationList:: operator=(const RegistrationList& other) {
	if (this != &other) {
		if (this->Capacity) {
			if (this->filled)
			{
				for (size_t i = 0; i < this->filled; i++) {
					delete this->list[i];
				}
			}
			delete[]this->list;
		}
		delete[]this->list;
		this->list = new Registration * [other.capacity()];
		this->filled = other.size();
		this->Capacity = other.capacity();
		for (std::size_t i = 0; i < other.size(); i++) {
			this->list[i] = new Registration(other.at(i));
		}
	}
	return *this;
}
RegistrationList::~RegistrationList() {
	if (this->filled)
	{
		for (size_t i = 0; i < this->filled; i++) {
			delete this->list[i];
		}
		delete[]this->list;
	}else delete[]this->list;
}
int main()
{
	int n;
	std::cin >> n;
	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Incorect input ,please try again:";
		std::cin >> n;
	}
	RegistrationList l(n);
	
	for (std::size_t i = 0; i < n; i++) {
		int tempDay;
		int tempYear;
		int tempMonth;
		std::string temp;
		try {
			std::cin >> tempDay >> tempMonth  >> tempYear >> temp;
			Date tp(tempDay, tempMonth, tempYear);
			l.insert(temp, tp);

		}
		catch (...) {
			std::cin.clear();
			std::cin.ignore();
			std::cin >> tempDay >> tempYear >> tempDay >> temp;
			Date tp(tempDay, tempMonth, tempYear);
			l.insert(temp, tp);
		}
	}
	
	return 0;
}