// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Кирил Кирилов
// ФН: 45658
// Специалност: Информатика
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>



class Registration {
	char id[9];
	
	bool isValidRegistration(const char* str)
	{
		if (strlen(str) == 7) {
			if (isalpha(str[0])) {
				for (int i = 1; i <= 4; i++) {
					if (!isdigit(str[i])) {
						return false;
					}
				}
				if (isalpha(str[5]) && isalpha(str[6])) {

				}
				else return false;
			}
			else return false;
		}
		else if (strlen(str) == 8) {
			if (isalpha(str[0]) && isalpha(str[1])) {
				for (int i = 2; i <= 5; i++) {
					if (!isdigit(str[i])) {
						return false;
					}
				}
				if (isalpha(str[6]) && isalpha(str[7])) {

				}
				else return false;
			}
			else return false;
		}
		else return false;

		return true;
	}
public:

	Registration(const char* str) {
		if (isValidRegistration(str)) {
			std::strcpy(id, str);
		}
		else {
			throw;
		}
	}
	Registration& operator=(const char* str) {
		if (isValidRegistration(str)) {
			std::strcpy(id, str);
		}
		else {
			throw;
		}
		return *this;
	}

	bool operator==(const char* str) const {
		return strcmp(id, str) == 0 ? 1 : 0;
	}
	const char* toString() const {
		return id;
	}
};


class Vehicle {
public:
	Registration regnum;
	std::string description;
	Vehicle(const char* regnum, const char* description) : regnum(regnum), description(description) {

	}
};




int main()
{
	return 0;
}


