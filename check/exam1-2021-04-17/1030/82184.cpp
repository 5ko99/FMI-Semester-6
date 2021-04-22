// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Венета Славчева Кирева
// ФН: 82184
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>
#include <iostream>

class Date {
	std::uint8_t d;
	std::uint8_t m;
	std::uint16_t y;

	void setDay(unsigned int day){
		d = day;
	}

	void setMonth(unsigned int month){
		d = month;
	}

	void setYear(unsigned int year){
		y = year;
	}

	bool checkDate(unsigned int day, unsigned int month, unsigned int year)
	{
		if (month < 0 && month > 13){
			return false;
		}

		if (day < 1) {
			return false;
		}

		if ( month == 1 || month == 3 || month == 5 || month == 7 
		  || month == 8 || month == 10 || month == 12 ) {
			  if (day > 31) {
				  return false;
			  }
			  else {
				  return true;
			  }
		}

		if (month == 4 || month == 6 || month == 9 || month == 11 ) {
			if (day > 30) {
				  return false;
			  }
			  else {
				  return true;
			  }
		}

		if (year % 4 == 0 || day > 29) return false;
		if (day > 28) return false;
		return true;
	}

public:

	Date(unsigned int day, unsigned int month, unsigned int year)
	{
		
		if ( checkDate(day, month, year) ){
			setDay(day);
			setMonth(month);
			setYear(year);
		}
		else {
			throw std::invalid_argument("Invalid date");
		} 
		
	}

	unsigned int day() const
	{
		return d;
	}

	unsigned int month() const
	{
		return m;
	}

	unsigned int year() const
	{
		return y;
	}

	bool operator==(const Date& rhs) const
	{
		if (rhs.day() == this->day() && 
			rhs.month() == this->month() &&
			rhs.year() == this->year())
			{
				return true;
			}
		return false;
	}

	bool operator<(const Date& rhs) const
	{
		if (rhs.day() < this->day() && 
			rhs.month() < this->month() &&
			rhs.year() < this->year())
			{
				return true;
			}
		return false;
	}

	const Date& operator=(const Date& newDate)
	{
		setDay(newDate.day());
		setMonth(newDate.month());
		setYear(newDate.year());
		return *this;
	}
};

class Registration {

	const std::string id;
	const Date date;

	void setId(std::string newId)
	{
		id = newId;
	}

	void setDate(Date newDate)
	{
		date = newDate;
	}

	std::string getId() const
	{
		return &id;
	}

	Date& getDate() const
	{
		return &date;
	}

public:
	Registration(const std::string& id, const Date& date)
	{
		setId(id);
		setDate(date);
	}

	const Registration& operator=(const Registration& newRegistration)
	{
		setId(newRegistration.getId());
		setDate(newRegistration.getDate());
		return *this;
	}

	bool operator==(const Registration& rhs) const
	{
		if (getId() == rhs.getId() && rhs.getDate() == getDate())
		{
			return true;
		}
		return false;
	}

	bool operator<(const Registration& rhs) const
	{
		if (getDate() < rhs.getDate()) {
			return true; 
		}
		if (getDate() == rhs.getDate() && getId() < rhs.getId() ){
			return true;
		}

		return false;

	}

};

class RegistrationList{

	std::size_t listCapacity = 0;
	std::size_t occupiedList = 0;
	Registration * list = nullptr;

public:
	RegistrationList(std::size_t capacity)
	{
		listCapacity = capacity;
		list = new Registration[capacity];
	}
	~Registration()
	{
		delete [] list;
	}

	void insert(const std::string& id, const Date& date)
	{
		if (occupiedList < listCapacity) {
			Registration tempReg(id, date);
			list[occupiedList] = tempReg;
			occupiedList++;
		}
		else{
			throw std::logic_error("List full");
		}
	}

	const Registration& at(std::size_t index) const 
	{
		if (occupiedList >= index) {
			throw std::out_of_range("No such element.");
		}
		else {
			return list[index];
		} 
	}

	const Registration& operator[](std::size_t index) const
	{
		return list[index];
	}

	bool empty() const
	{
		if (occupiedList == 0){
			return true;
		}
		return false;
	}

	std::size_t capacity() const
	{
		return listCapacity;
	}

	std::size_t size() const
	{
		return occupiedList;
	}

};

int main()
{
	std::size_t N;
	std::cin >> N;
	RegistrationList list(N);

	for (size_t i = 0; i < N; i++)
	{
		std::string tempID;
		std:: cout << "Enter ID:";
		std::cin >> tempID;

		std::size_t day;
		std:: cout << "Enter day:";
		std::cin >> day;

		std::size_t month;
		std:: cout << "Enter month:";
		std::cin >> month;

		std::size_t year;
		std:: cout << "Enter year:";
		std::cin >> year;

		Date tempDate(day, month, year);

		try {
			list.insert(tempID, tempDate);
		}
		catch (const std::logic_error& e)
		{
			std::cout << e.what();
		}
	}

	return 0;
}