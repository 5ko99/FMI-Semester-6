// -std=c++11
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Мария Роглева
// ФН: 82172
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
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

class Date
{
private:
	std::uint8_t dayD;
	std::uint8_t monthD;
	std::uint16_t yearD;

	bool leapYear(unsigned int year);

public:
	Date(unsigned int day, unsigned int month, unsigned int year);

	unsigned int day() const; //връща деня като unsigned int
	unsigned int month() const; //връща месеца като unsigned int.
	unsigned int year() const; //връща годината като unsigned int.
	bool operator==(const Date& rhs) const; //Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.
	bool operator<(const Date& rhs) const; //връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.
};

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	if(month>0 && month<13)
	{
		if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
		{
			if(day<32 && day>0)
			{
				dayD = day;
				monthD = month;
				yearD = year;
			}
			else
			{
				throw std::invalid_argument("Invalid date1.");
			}
		}
		if(month==4 || month==6 || month==9 || month==11) 
		{
			if(day<31 && day>0)
			{
				dayD = day;
				monthD = month;
				yearD = year;
			}
			else
			{
				throw std::invalid_argument("Invalid date2.");
			}
		}
		if(month == 2)
		{
			if(day<29 && day>0)
			{
				dayD = day;
				monthD = month;
				yearD = year;
			}
			if(day==29)
			{
				if(leapYear(year) == true)
				{
					dayD = day;
					monthD = month;
					yearD = year;
				}
				else
				{
					throw std::invalid_argument("Invalid date3.");
				}
			}
			else
			{
				throw std::invalid_argument("Invalid date4.");
			}		
		}		
	}
	else
	{
		throw std::invalid_argument("There is no such month.");
	}
}

bool Date::leapYear(unsigned int year) 
{
	if(year%4 == 0)
	{
		if(year%400 == 0)
		{
			return true;
		}
		if(year%100 != 0)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

unsigned int Date::day() const
{
	return dayD;
}

unsigned int Date::month() const
{
	return monthD;
}

unsigned int Date::year() const
{
	return yearD;
}

bool Date::operator==(const Date& rhs) const
{
	if(yearD == rhs.yearD)
	{
		if(monthD == rhs.monthD)
		{
			if(dayD == rhs.dayD)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
			else
			{
				return false;
			}
	}
	else
	{
		return false;
	}	
}

bool Date::operator<(const Date& rhs) const
{
	if(yearD<rhs.yearD)
	{
		if(monthD<rhs.monthD)
		{
			if(dayD<rhs.dayD)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

class Registration
{
public:
	const std::string* id;
	const Date* date;

	Registration(const std::string* id, const Date* date);
	
	bool operator==(const Registration& rhs) const; //Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
	bool operator<(const Registration& rhs) const; //Проверява дали текущата регистрация предхожда тази в rhs

};

Registration::Registration(const std::string* id, const Date* date)
{
	this->id = id;
	this->date = date;
}

bool Registration::operator==(const Registration& rhs) const
{
	if(id == rhs.id)
	{
		if(date == rhs.date)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Registration::operator<(const Registration& rhs) const
{
	if(date < rhs.date)
	{
		return true;
	}
	if(date == rhs.date)
	{
		if(id < rhs.id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

class RegistrationList
{
private:
	std::size_t capacityR;
	Registration** list;
	std::size_t used;

public:
	RegistrationList(std::size_t capacity);
	void copy(const RegistrationList& rhs); //
	~RegistrationList();

	void insert(const std::string& id, const Date& date); //добавя регистрацията с номер id и дата date.
	const Registration& at(std::size_t index) const; //достъп до елемента намиращ се на позиция index
	const Registration& operator[](std::size_t index) const; //достъп до елемента намиращ се на позиция index.
	bool empty() const; //Проверява дали списъка е празен
	std::size_t capacity() const; //капацитет на списъка.
	std::size_t size() const; //брой регистрации добавени в списъка.

};

RegistrationList::RegistrationList(std::size_t capacity)
{
	list = new Registration*[capacity]; //in case of bad allocation, the execution stops here
	used = 0;
}

///////

RegistrationList::~RegistrationList()
{
	for(std::size_t i = 0; i<used; ++i)
	{
		delete list[i];
	}

	delete[] list;
	list = nullptr;
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
	if(used<capacityR)
	{
		Registration temp(&id, &date);
		for(std::size_t i = 0; i<capacityR; ++i)
		{
			
		}
	}
	else
	{
		throw std::invalid_argument("");
	}
}

const Registration& RegistrationList::at(std::size_t index) const
{
	if(index < used)
	{
		//return list[index];
	}
	else
	{
		throw std::out_of_range("Out of range;");
	}
}




int main()
{
	std::size_t N;
	std::cout<<"Enter the RegistrationList capacity:"<<std::endl;
	//do{
	std::cin>>N;
	//}while(!cin);
	RegistrationList regl(N);
	std::cout<<"A RegistrationList with a capacity of "<<N<<" was created.\n";


	// const Date test(29, 3, 401);
	// std::cout<<test.month()<<std::endl<<400%4;
	// const std::string s = "abvgde";
	// Registration reg(&s, &test);
	// RegistrationList regl(5);
	// std::cout<<"OK";
	return 0;
}