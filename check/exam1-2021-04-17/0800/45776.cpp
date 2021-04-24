// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Кристиан Емилов Еков
// ФН: 45776
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 4/17/2021
// Начален час на контролното: 08:00 <тук попълнете часа за вашата група>
// Кой компилатор използвате: Visual Studio <посочете едно от Visual C++, GCC или Clang>
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

using namespace std;

class Registration {
public:
	Registration(const char* str) {
		try {
			if (!validateNumber(str))
			{
				throw  std::exception();
			}
		}
		catch (std::exception) {
			// invalid number
		}

		for (size_t i = 0; i < length; i++)
		{
			RegistrationNumber[i] = str[i];
		}
	}

	const char* toString() const {
		if (length == 7)
		{
			char* str = new char[8];

			for (size_t i = 0; i < 7; i++)
			{
				str[i] = RegistrationNumber[i];
			}
			str[7] = '\0';
			return str;
		}
		if (length == 8)
		{
			char* str = new char[9];

			for (size_t i = 0; i < 8; i++)
			{
				str[i] = RegistrationNumber[i];
			}
			str[8] = '\0';
			return str;
		}
	}

	Registration& operator=(const char* str) {
		try {
			if (!validateNumber(str))
			{
				throw  std::exception();
			}
		}
		catch (std::exception) {
			// invalid number
		}

		for (size_t i = 0; i < length; i++)
		{
			RegistrationNumber[i] = str[i];
		}
	}

	bool operator==(const char* str) const {
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] != RegistrationNumber[i])
			{
				return false;
			}
		}

		return true;
	}
private:
	char* RegistrationNumber = new char[9];
	unsigned int length = 0;

	bool isLetter(char ch) {
		if ('A' <= ch && ch <= 'Z')
		{
			return true;
		}

		if ('a' <= ch && ch <= 'z')
		{
			return true;
		}

		return false;
	}

	bool isDigit(char ch) {
		if ('0' <= ch && ch <= '9') {
			return true;
		}
		return false;
	}

	bool validateNumber(const char* str) {
		bool result = false;
		bool flagStartsWithTwoLetters = false;

		if (isLetter(str[0]))
		{
			result = true;
		}

		if (result && isLetter(str[1]))
		{
			result = true;
			flagStartsWithTwoLetters = true;
		}

		if (result && !flagStartsWithTwoLetters && isdigit(str[1]))
		{
			result = true;
		}

		if (result)
		{
			if (flagStartsWithTwoLetters)
			{
				for (size_t i = 2; i < 6; i++)
				{
					if (!isDigit(str[i])) {
						result = false;
						break;
					}
				}

				if (result)
				{
					if (!isLetter(str[6]) || !isLetter(str[7]))
					{
						result = false;
					}
				}

			}
			else {
				for (size_t i = 1; i < 5; i++)
				{
					if (!isDigit(str[i])) {
						result = false;
						break;
					}
				}

				if (result)
				{
					if (!isLetter(str[5]) || !isLetter(str[6]))
					{
						result = false;
					}
				}
			}
		}

		if (result)
		{
			if (flagStartsWithTwoLetters)
			{
				length = 8;
			}
			else {
				length = 7;
			}
		}

		return result;
	}
};


class Vehicle {
	Registration regnum;
	string description;
};

class VehicleList {
public:
	VehicleList(std::size_t capacity) {
		Capcity = capacity;
		UsedCapcity = 0;
		Vehicles = new Vehicle * [capacity];
	}

	

	const Vehicle& at(std::size_t index) const {
		if (index > (UsedCapcity - 1))
		{
			throw  std::out_of_range("NO vehicle on this index!");
		}
		return  *Vehicles[index];
	}

	const Vehicle& operator[](std::size_t index) const {
		assert(index > (UsedCapcity - 1));
		return *Vehicles[index];
	}

	bool empty() const {
		if (UsedCapcity > 0)
		{
			return false;
		}
		return true;
	}

	std::size_t capacity() const {
		return Capcity;
	}

	std::size_t size() const {
		return UsedCapcity;
	}

	

private:
	std::size_t Capcity;
	std::size_t UsedCapcity;

	Vehicle** Vehicles;
};

int main()
{
	Registration r("C1234AB");
	cout << r.toString() << endl;

	Registration r2("XY1111YX");
	cout << r2.toString() << endl;

	Registration r3("111145");

	Registration r4 = r;
	cout << r4.toString() << endl;
	cout << (r4 == "C1234AB");
	return 0;
}
