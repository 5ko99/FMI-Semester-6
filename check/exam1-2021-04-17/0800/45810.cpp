// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Владислав Витанов
// ФН: 45810
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17/4/2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstddef>

class Registration
{
private:
	bool ValidReg();// Minor flaw
	char registration[9];

public:
	Registration(const char* str);// Works Properly
	Registration& operator=(Registration& other);//Kinda works
	Registration& operator=(const char* str);//Broken
	bool operator==(const char* str) const;//Broken
	const char* toString() const;//Works Properly
	~Registration();//Works Properly

};


bool Registration::ValidReg()
{
	if (isalpha(this->registration[0]) && isalpha(this->registration[1]) && isdigit(this->registration[2])
		&& isdigit(this->registration[3]) && isdigit(this->registration[4]) && isdigit(this->registration[5])
		&& isalpha(this->registration[6]) && isalpha(this->registration[7]))
	{
		return true;
	}
	else if(isalpha(this->registration[0]) &&  isdigit(this->registration[1])&& isdigit(this->registration[2])
		&& isdigit(this->registration[3]) && isdigit(this->registration[4])
		&& isalpha(this->registration[5]) && isalpha(this->registration[6]) && !isalpha(this->registration[7])
		&& !isdigit(this->registration[7]))//&& Символи??;
	{
		return true;
	}
	else
	{
		return false;
	}

}

Registration::Registration(const char* str)
{
	strcpy_s(this->registration, strlen(str) + 1, str);
	if (!ValidReg())
	{
		throw std::exception("Invalid Registration");
	}
}

Registration& Registration::operator=(Registration& other)
{
	strcpy_s(this->registration, strlen(other.registration), other.registration);
	return *this;
}


Registration& Registration::operator=(const char* str)
{
	if (!ValidReg())
	{
		throw std::exception("Invalid Registration");
	}
	strcpy_s(this->registration, strlen(str) + 1, str);
	return *this;
}

bool Registration::operator==(const char* str) const
{
	Registration reg = str;
	if (this->registration == reg.registration)
		return true;
	else
		return false;
}

const char* Registration::toString() const
{
	return this->registration;
}

Registration::~Registration()
{
	delete[] this->registration;
}

class Vehicle
{
private:

public:
	Registration regnum;
	std::string description;
	Vehicle(const char* regnum, const char* description);
	~Vehicle();

};

//Vehicle::Vehicle(const char* regnum, const char* description)
//{
//	
//}

Vehicle::~Vehicle()
{
}

int main()//trashy tests
{
	Registration* reg = new Registration("C1234AB");
	Registration* reg2 = new Registration("CA1234AB");

	std::cout << reg->toString();
	reg = reg2;
	std::cout << reg->toString();
	
	reg->~Registration();
	reg2->~Registration();

	return 0;
}