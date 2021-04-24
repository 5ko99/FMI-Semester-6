// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Елизабет Великова
// ФН: 82173
// Специалност: Компютърни науки
// Курс: 1-ви
// Административна група: 3-та
// Ден, в който се явявате на контролното: 17.04.2021г. 
// Начален час на контролното: 10:30 ч.
// Кой компилатор използвате: GCC
//

//strlen, strcmp и т.н. са дефинирани като deprecated,
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

#include <iostream>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <cstdint>
#include <string>

#define NDEBUG

using std::cout;
using std::cin;
using std::endl;

class Date {
private:
	std::uint8_t m_day;
	std::uint8_t m_month;
	std::uint16_t m_year;

	// unsigned int day;
	// unsigned int month;
	// unsigned int year;

	bool isYearLeap(unsigned int year) {
		// if((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)) {
		// 	return true;
		// }

		return (year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 100 == 0 && year % 400 == 0);
	}

	bool isMonthValid(unsigned int month) {
		return (month > 0 && month <= 12);
	}

	bool isDateValid(unsigned int day, unsigned int month, unsigned int year) {
		if (day > 0 && day <= 31) {
			if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
				return true;
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11) {
				return day <= 30;
			}
			else if (month == 2 && isYearLeap(year)) {
				return day <= 29;
			}
			else if (month == 2 && !isYearLeap(year)) {
				return day <= 28;
			}
		}
		return false;
	}


	// unsigned int transformVariable(std::uint8_t variable) {
	// 	unsigned int output;
	// 	output = variable;
	// 	return output;
	// }

public:
	//конструктор, който създава нов обект за дата с ден day, месец month и година year. Ако датата не е валидна, 
	//да се хвърля изключение от тип std::invalid_argument
	Date(unsigned int day, unsigned int month, unsigned int year) {
		if (!(isDateValid(day, month, year))) {
			throw std::invalid_argument("Please, input a correct day!");
		}
		// New object huh so
		if(isMonthValid(month)) {
			m_day = day;
			m_month = month;
			m_year = year;
			//Date newDate(day, month, year);
		}
	}

	Date(const Date& newDate) {
		m_day = newDate.day();
		m_month = newDate.month();
		m_year = newDate.year();
	}

	Date& operator=(const Date& rhs) {
		m_day = rhs.day();
		m_month = rhs.month();
		m_year = rhs.year();
		return *this;
	}

	//връща деня като unsigned int.
	unsigned int day() const {
		//return transformVariable(day);
		unsigned int newDay;
		newDay = m_day;
		return newDay;
		// return day;
	}

	//връща месеца като unsigned int.
	unsigned int month() const {
		unsigned int newMonth;
		newMonth = m_month;
		return newMonth;
		//return month;
	}

	//връща годината като unsigned int.
	unsigned int year() const {
		unsigned int newYear;
		newYear = m_year;
		return newYear;
		//return year;
	}

	//Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.
	bool operator==(const Date& rhs) const {
		unsigned int dayBool = day();
		unsigned int monthBool = month();
		unsigned int yearBool = year();

		bool dayMatch = (dayBool == rhs.day());
		bool monthMatch = (monthBool == rhs.month());
		bool yearsMatch = (yearBool == rhs.year());

		return dayMatch && monthMatch && yearsMatch;
	}



	//връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.
	bool operator<(const Date& rhs) const {
		unsigned int dayBool = day();
		unsigned int monthBool = month();
		unsigned int yearBool = year();

		bool dayPrior = (dayBool < rhs.day());
		bool monthPrior = (monthBool < rhs.month());
		bool yearsPrior = (yearBool < rhs.year());

		// if(yearsPrior || (yearsPrior && monthPrior) || (yearsPrior && monthPrior && dayPrior)) {
		// 	return true;
		// }
		// else {
		// 	return false;
		// }

		return yearsPrior || (yearsPrior && monthPrior) || (yearsPrior && monthPrior && dayPrior);

		//return yearsPrior || !(!yearsPrior && monthPrior) || !(!yearsPrior && !monthPrior && dayPrior);
	}

};

class Registration {
private:
	std::string m_id;
	Date* m_date;
public:
	Registration(const std::string& id, const Date& date) {
		m_id = id;
		//m_date = &date;

		Date newDate(date.day(), date.month(), date.year());
		*m_date = newDate;
	}

	//Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
	bool operator==(const Registration& rhs) const {
		// m_id == rhs.getId();
		// m_date == rhs.getDate();
		return m_id == rhs.getId() && *m_date == rhs.getDate();
	}
	
	//Проверява дали текущата регистрация предхожда тази в rhs. 
	//Считаме, че една регистрация A предхожда друга регистрация B или (1) ако датата на A е преди тази на B, или 
	// (2) ако двете дати съвпадат, но регистрационният номер на A предхожда лексикографски този на B.
	bool operator<(const Registration& rhs) const {
		bool dateMatch = (*m_date == rhs.getDate() );
		bool datePrior = (*m_date < rhs.getDate() );
		bool idPrior = (m_id < rhs.getId() );
		return datePrior || (dateMatch && idPrior);
	}

	std::string getId() const{
		return m_id;
	}

	Date getDate() const{	
		return *m_date;
	}
	
	//Упътване: класът std::string има оператори < и ==, които можете да използвате наготово.
};

class RegistrationList {
private:
	Registration** registrationsList;
	std::size_t capacityList;
	std::size_t numberOfRegistrations;

public:
	//създава списък, който може да съдържа най-много capacity на брой регистрации.
	RegistrationList(std::size_t capacity) {
		try {
			registrationsList = new Registration*[capacityList]; 
		}
		catch (std::bad_alloc& e) {
			cout << "Bad alloc! " << e.what() << endl;
		}
		for(std::size_t i = 0; i<capacityList; ++i) {
			registrationsList[i] = nullptr;
		}
		capacityList = capacity;
	}


	//добавя регистрацията с номер id и дата date. Тъй като класът трябва да поддържа регистрациите сортирани в нарастващ ред, тази операция трябва да вмъкне новия запис на подходящо място в списъка. Ако операцията не успее (например няма повече място), да се хвърля изключение от тип std::exception. Операцията да дава strong exception guarantee.
	void insert(const std::string& id, const Date& date) {

	}

	//достъп до елемента намиращ се на позиция index. Ако такъв няма, да се хвърля изключение std::out_of_range.
	const Registration& at(std::size_t index) const {
			if(index < 0 || index >= capacityList) {
				throw std::out_of_range("No item at this pos!");
			}
			return *registrationsList[index];
	}

	//достъп до елемента намиращ се на позиция index. 
	//Функцията да не прави проверка за коректност дали index е валидна позиция. 
	//(В debug режим assert-вайте дали index е валидна позиция).
	const Registration& operator[](std::size_t index) const {
		#ifndef NDEBUG
		assert(index => 0 && index < capacity);
		#endif
		return *registrationsList[index];
	}

	//Проверява дали списъка е празен (т.е. в него не е била добавена нито една регистрация).
	bool empty() const {
		return numberOfRegistrations;
	}

	//капацитет на списъка.
	std::size_t capacity() const {
		return capacityList;
	}

	//брой регистрации добавени в списъка
	std::size_t size() const {
		return numberOfRegistrations;
	}
};



//


int main()
{
	Date newDate(12, 2, 2016);
	Date secondDate(16, 3, 2015);
	bool prior = newDate < secondDate;

	cout << prior << endl;

	Registration car1("Kola1", newDate);
	Registration car2("Kola2", secondDate);

	bool older = car1 < car2;
	cout << older << endl;
	/*
	unsigned int numbr;
	std::uint8_t day = 3;
	numbr = day;
	//cin >> day;
	//cout << day << endl;

	//bool areThey = (numbr == day);
	//bool areChar = (let == day);

	cout << numbr << endl;
    */

	return 0;
}