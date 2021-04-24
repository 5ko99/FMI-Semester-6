
// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Георги Апостолов Хърлев
// ФН:82165
// Специалност:КН
// Курс:1
// Административна група:2
// Ден, в който се явявате на контролното: 17.04
// Начален час на контролното: 10:30
// Кой компилатор използвате: Visual C++
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::exception;


#pragma region headers

class  Date {
private:
	std::uint8_t dateDay;
	std::uint8_t dateMonth;
	std::uint16_t dateYear;

	bool isLeapYear(unsigned int year) const;
	bool isValidDate(unsigned int day, unsigned int month, unsigned int year) const;
public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date(const Date& other);
	~Date();
	unsigned int day() const;
	unsigned int month() const;
	unsigned int year() const;
	Date& operator=(const Date& other);
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;


};

#pragma endregion date declaration


#pragma region sources

bool Date::isLeapYear(unsigned int year) const {
	return ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)));
}

bool Date::isValidDate(unsigned int day, unsigned int month, unsigned int year)const {
	if (day > 31 || month > 12 || day == 0 || month == 0) //base case , works for the rest of the months as well
	{
		return false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return day <= 30;
	}
	if (month == 2)
	{
		if (isLeapYear(year))
		{
			return day <= 29;
		}
		else {
			return day <= 28;
		}
	}
	return true;
}


Date::Date(const Date& other) :dateDay(other.dateDay), dateMonth(other.dateMonth), dateYear(other.dateYear) {

}
Date::Date(unsigned int day, unsigned int month, unsigned int year) : dateDay(day), dateMonth(month), dateYear(year) {
	if (!isValidDate(dateDay, dateMonth, dateYear))
	{
		dateDay = dateMonth = dateYear = 0;
		throw std::invalid_argument("Invalid date");
	}

}
Date::~Date() {
	dateDay = dateMonth = dateYear = 0;
}
unsigned int Date::day() const {
	return dateDay;

}
unsigned int Date::month() const {
	return dateMonth;
}
unsigned int Date::year() const {
	return dateYear;
}
bool Date::operator==(const Date& rhs) const {
	return (rhs.dateDay == dateDay && rhs.dateMonth == dateMonth && rhs.dateYear == dateYear);
}
bool Date::operator<(const Date& rhs) const {
	if (rhs.dateYear != dateYear)
	{
		return dateYear < rhs.dateYear;
	}
	//equal
	if (rhs.dateMonth != dateMonth) {
		return dateMonth < rhs.dateMonth;
	}

	return dateDay < rhs.dateDay;

}

Date& Date::operator=(const Date& other) {
	if (this != &other) {
		dateDay = other.dateDay;
		dateMonth = other.dateMonth;
		dateYear = other.dateYear;
	}
	return *this;
}

#pragma endregion date initializations


#pragma region header

class Registration {
private:
	string id;
	Date date;

public:
	Registration(const std::string& id, const Date& date);
	Registration(const Registration& other);
	Registration(Registration&& other) noexcept;
	~Registration();
	Registration& operator=(const Registration& other);
	Registration& operator=(Registration&& other) noexcept;
	bool operator==(const Registration& rhs) const;
	bool operator<(const Registration& rhs) const;

	void print(std::ostream& os)const;
};

#pragma endregion registration

#pragma region cpp

Registration::Registration(const std::string& id, const Date& date) :id(id), date(date) {

}

Registration::Registration(const Registration& other) : id(other.id), date(other.date) {

}

Registration::Registration(Registration&& other)noexcept :id(other.id), date(std::move(other.date)) {

}
Registration::~Registration() {
	id.clear();
}

Registration& Registration::operator=(Registration&& other) noexcept {

	date = other.date;
	id = (std::move(other.id));
	return *this;
}

Registration& Registration::operator=(const Registration& other) {
	if (this != &other) {
		date = other.date;
		id = other.id;
	}
	return *this;
}

bool Registration::operator==(const Registration& rhs) const {
	return (rhs.id == id && rhs.date == date);
}

bool Registration::operator<(const Registration& rhs) const {
	if (!(rhs.date == date))
	{
		return date < rhs.date;
	}
	return id < rhs.id;
}

#pragma endregion registration Initialization

#pragma region header

class RegistrationList {
private:
	Registration** registrations = nullptr;
	size_t maxCapacity = 0;
	size_t curSize = 0;
	size_t allocated = 0;

	bool isDublicated(const Registration& other) const;
	bool allocateReg(size_t newSize);
public:
	RegistrationList(std::size_t capacity);
	RegistrationList(const RegistrationList& other);
	RegistrationList(RegistrationList&& other)noexcept;

	~RegistrationList();
	void insert(const std::string& id, const Date& date);
	const Registration& at(std::size_t index) const;
	const Registration& operator[](std::size_t index) const;
	RegistrationList& operator=(const RegistrationList& other);
	RegistrationList& operator=(RegistrationList&& other) noexcept;
	bool empty() const;
	std::size_t capacity() const;
	std::size_t size() const;
	void print(std::ostream& os)const;
};

#pragma endregion registrationList

#pragma region cpp


bool  RegistrationList::isDublicated(const Registration& other) const {
	for (size_t i = 0; i < curSize; i++)
	{
		if (*registrations[i] == other)
		{
			return true;
		}
	}
	return false;
}

bool RegistrationList::allocateReg(size_t newSize) {
	Registration** newReg = nullptr;
	try {
		newReg = new Registration * [newSize];
	}
	catch (...)
	{
		return false;
	}

	for (size_t i = 0; i < curSize; i++)
	{
		newReg[i] = registrations[i];
	}
	allocated = newSize;
	delete[] registrations;
	registrations = newReg;
	return true;

}

RegistrationList::RegistrationList(std::size_t capacity) :maxCapacity(capacity) {
	//as capacity can be very big , we will reallocate it periodically when needed more space
	if (!allocateReg(2)) {
		allocated = 0;
	}
	curSize = 0;

}
RegistrationList::RegistrationList(const RegistrationList& other) :maxCapacity(other.maxCapacity) {
	if (!allocateReg(other.curSize))
	{
		allocated = 0;
		curSize = 0;
		throw exception("Memory allocation error");
	}
	curSize = allocated = other.curSize;

	for (size_t i = 0; i < curSize; i++)
	{
		registrations[i] = new Registration(other[i]);
	}

}

void Registration::print(std::ostream& os)const {
	os << "Id: " << id << " Date:" << date.day() << "." << date.month() << "." << date.year() << endl;
}

RegistrationList::RegistrationList(RegistrationList&& other)noexcept :maxCapacity(other.maxCapacity) {
	if (this != &other)
	{
		registrations = other.registrations;
		curSize = other.curSize;
		allocated = other.allocated;
	}
	other.registrations = nullptr;
	other.curSize = other.allocated = 0;

}

RegistrationList::~RegistrationList() {
	for (size_t i = 0; i < curSize; i++)
	{
		delete registrations[i];
	}
	delete[] registrations;
	curSize = allocated = 0;

}
void RegistrationList::insert(const std::string& id, const Date& date) {

	if (curSize == maxCapacity)
	{
		throw std::exception("Capacity reached!");
	}
	Registration* newReg = new Registration(id, date);
	if (isDublicated(*newReg))
	{
		throw std::exception("Registration duplicated!");
	}
	if (curSize >= allocated) {
		if (!allocateReg(curSize + 1))
		{
			throw exception("Memory allocation error");
		}
	}

	size_t index;
	for (index = curSize - 1; index >= 0; index--)
	{
		if (registrations[index] < newReg) {//we found the place to insert 
			break;
		}
	}
	for (size_t i = curSize; i > index; i--) //now we move them one position
	{
		registrations[i] = registrations[i - 1];
	}
	registrations[index] = newReg;
	newReg = nullptr;

}

const Registration& RegistrationList::at(std::size_t index) const {
	if (index >= curSize)
	{
		throw  std::out_of_range("Out of range.");
	}
	return *registrations[index];
}
const Registration& RegistrationList::operator[](std::size_t index) const {
	assert(index >= curSize);

	return *registrations[index];
}
RegistrationList& RegistrationList::operator=(const RegistrationList& other) {
	if (this != &other)
	{
		if (!allocateReg(other.curSize))
		{
			allocated = 0;
			curSize = 0;
			throw exception("Memory allocation error");
		}
		curSize = allocated = other.curSize;
		maxCapacity = other.maxCapacity;
		for (size_t i = 0; i < curSize; i++)
		{
			registrations[i] = new Registration(other[i]);
		}
	}
	return *this;
}

RegistrationList& RegistrationList::operator=(RegistrationList&& other) noexcept {
	if (this != &other)
	{
		registrations = other.registrations;
		maxCapacity = other.maxCapacity;
		curSize = other.curSize;
		allocated = other.allocated;

		other.registrations = nullptr;
		other.maxCapacity = other.allocated = other.curSize = 0;
	}
	return *this;

}

bool RegistrationList::empty() const {
	return curSize == 0;
}
std::size_t RegistrationList::capacity() const {
	return maxCapacity;
}
std::size_t RegistrationList::size() const {
	return curSize;
}

void RegistrationList::print(std::ostream& os)const {
	for (size_t i = 0; i < curSize; i++)
	{
		registrations[i]->print(os);
	}
}

#pragma endregion registrationList

#pragma region tests

void testDate(size_t day, size_t mon,size_t year)
{
	try {
		Date date(day, mon, year);
	}
	catch(exception & e){
		cout << e.what();
		return;
	}
	cout << "Successful!";
}

#pragma endregion testCases



int main()
{
	size_t n;
	string id;
	std::uint8_t day;
	std::uint8_t month;
	std::uint16_t year;

	cout << "Input list size: ";
	cin >> n;
	if (!cin) {
		cout << "Incorrect size input\n";
		return -1;
	}
	RegistrationList regList(n);
	cout << "List created!\n";
	for (size_t i = 0; i < n; i++)
	{
		cout << "Add new registration:\n";
		cout << "Id:";
		cin >> id;
		cout << "Day";
		cin >> day;
		cout << "Month:";
		cin >> month;
		cout << "Year:";
		cin >> year;
		try {
			Date newDate(day, month, year);
			regList.insert(id, newDate);
		}
		catch (std::exception& e)
		{
			cout << e.what();
		}
	}
	cout << "Registered:\n";
	regList.print(cout);

	return 0;
}

