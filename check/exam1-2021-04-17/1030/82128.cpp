// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Константин
// ФН:82128
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04
// Начален час на контролното: 10.30
// Кой компилатор използвате:  Visual C++
//


using namespace std;

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>


class Date {
private:
	uint8_t day=0;
	uint8_t month=0;
	uint8_t year=0;

	bool ValidDate(unsigned int day, unsigned int month, unsigned int year) const {

		if (day == 0 || day > 31) throw invalid_argument("You have entered invalid day");
		if (month == 0 || month > 12) throw invalid_argument("You have entered invalid month");
		if (year == 0) throw invalid_argument("You have entered invalid year");


		bool leap = false;
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { leap = true; }

		if (day)
			switch (month) {
			case 4: case 6: case 9: case 11:
				if (day > 30) { throw invalid_argument("You have entered a value over 30 for a month that has 30 days"); }
			case 2:
				if (day > 28 + leap) { throw invalid_argument("You have entered a value over 28 (or 29 if the year is leap) for february"); }
			}

		return true;
	}

public:
	Date() : day(0), month(0), year(0) {};
	Date(unsigned int day, unsigned int month, unsigned int year) {
		if (ValidDate(day, month, year) == false) { throw invalid_argument("You have entered invalid date"); }

		this->day = day;
		this->month = month;
		this->year = year;
	}
	Date& operator=(const Date& other) {
		if (this != &other) {
			this->day = other.getday();
			this->month = other.getmonth();
			this->year = other.getyear();
		}
		return *this;
	}

	unsigned int getday() const {
		unsigned int new_day = this->day;
		return new_day;

	}

	unsigned int getmonth() const {

		unsigned int new_month = this->month;
		return new_month;

	}
	unsigned int getyear() const {
		unsigned int new_year = this->year;
		return new_year;

	}
	void setDay(unsigned int day) {
		this->day = day;
	}
	void setMonth(unsigned int month) {
		this->month = month;
	}
	void setYear(unsigned int year) {
		this->year = year;
	}

	bool operator==(const Date& rhs) const {

		if (this->getday() == rhs.getday() && this->getmonth() == rhs.getmonth() && this->getyear() == rhs.getyear()) return true;
	    else  return false; 

	}
   bool operator<(const Date& rhs) const {
		if (rhs.getyear() > this->getyear()) return true;
		if (rhs.getyear() == this->getyear()) {
			if (rhs.getmonth() > this->getmonth()) return true;
			if (rhs.getmonth() == this->getmonth()) {
				if (rhs.getday() > this->getday()) return true;
			}
		}

		return true;
	}
};



class Registration {

private:
	string id;
	Date day;
public:
	Registration(const string& id, const Date& date){

		if (id == "")  throw invalid_argument("You have entered invalid string");

		this->id = id;
		day.setDay(date.getday());
		day.setMonth(date.getmonth());
		day.setYear(date.getyear());

	}
	bool operator==(const Registration& rhs) const {
		if ((this->id == rhs.id) && (this->day == rhs.day)) return true;
		return false;
	}
	bool operator<(const Registration& rhs) {
		if (this->day < rhs.day) { return true; }
		if (this->day == rhs.day) {
			if (this->id < rhs.id) { return true; }
			if (this->id == rhs.id) { return false; }
		}
		return false;
	}
	string getId() const {
		return this->id;
	}
};


class RegistrationList {
private:
	Registration** RegList=nullptr;
	size_t capacity=0;
	size_t count=0;
public:
	RegistrationList(size_t size) {

		this->capacity = size;
		this->count=0;

	}

	void insert(const string& id, const Date& date) {

		for (size_t i = 0; i < this->count; i++) {
			if (RegList[i]->getId()==id) {
				throw runtime_error("You one to add a registration which was added before");
			}
		}

		Registration new_addition(id, date);

		size_t new_size = this->count + 1;
		Registration** new_reglist = new Registration*[new_size];

		for (size_t i = 0; i < new_size-1; i++) {
			new_reglist[i] = new Registration(*RegList[i]);
		}
		new_reglist[new_size - 1] = new Registration(*(&new_addition));


		delete[] RegList;
		this->RegList = new Registration*[new_size];

		for (size_t i = 0; i < new_size; i++) {
			RegList[i] = new Registration(*new_reglist[i]);
		}

		this -> count = new_size;

		delete[] new_reglist;



	}
	size_t getSize() const {
		return this->count;
	}
	size_t getCapacity() const {
		return this->capacity;
	}
	bool empty() const {
		if (this->count == 0) return true;
		return false;
	}
	


};


int main()
{
	try {
		RegistrationList a(12);
		
		string b2 = "81_123";
		Date b1(28, 10, 13);
		Registration b(b2, b1);

		string c2 = "1321";
		Date c1(19, 10, 2020);
		Registration c(c2, c1);

		a.insert(b2, b1);
		a.insert(c2, c1);
	}
	catch (const exception& e) {
		cout << e.what();
	}
	return 0;
}