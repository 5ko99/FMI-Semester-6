// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Цветан
// ФН: 45796
// Специалност: Информатика
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.21
// Начален час на контролното: <тук попълнете часа за вашата група> 8:00
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> Visual C++
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
#include <stdexcept> 


class Registration
{
public:
	Registration () = delete;
	void copy(const char* str){
		try {
			unsigned size = strlen(str);
			char temp [9];
			if (size < 7 || size > 8) {
				throw std::exception(" ");
			}

			if (!(isalpha(str[0]))) {
				throw std::exception(" ");
			}
			else {
				temp[0] = str[0];
			}

			if (isalpha(str[1])) {
				temp[1] = str[1];
				for (unsigned i = 2; i < 6; i++) {
					if (!(isdigit(str[i]))) {
						throw std::exception(" ");
					}
					else {
						temp[i] = str[i];
					}
				}

				if (!(isalpha(str[6])) || !(isalpha(str[7]))) {
					throw std::exception(" ");
				}
				else {
					temp[6] = str[6];
					temp[7] = str[7];
					temp[7] = '#';
				}
			}
			else if (isdigit(str[1])) {
				temp[1] = str[1];
				for (unsigned i = 2; i < 5; i++) {
					if (!(isdigit(str[i]))) {
						throw std::exception(" ");
					}
					else {
						temp[i] = str[i];
					}
				}

				if (!(isalpha(str[5])) || !(isalpha(str[6]))) {
					throw std::exception(" ");
				}
				else {
					temp[5] = str[5];
					temp[6] = str[6];
					temp[7] = '#';
				}

			}

			for (unsigned i = 0; i < 9; i++) {
				reg_number[i] = temp[i];
			}

		}
		catch (std::exception& e) {

		}
	}
	Registration(const char* str) {

		copy(str);

	}
	Registration& operator=(const char* str) {
		copy(str);
		return *this;
	}
	bool operator==(const char* str) const {

		unsigned index = 0;
		unsigned count = 0;
		while (reg_number[index] != '#') {
			if (reg_number[index] == str[index]) {
				index++;
				count++;
			}
			else {
				return false;
			}
		}
		if (count == strlen(str)) {
			return true;
		}
		else {
			return false;
		}
		
	}
	const char* toString() const {
		char* temp = new(std::nothrow) char[9];
		unsigned index = 0;
		if (temp != nullptr) {
			while (reg_number[index] != '#') {
				temp[index] = reg_number[index];
				index++;
			}
			temp[index] = '\0';
		}
		
		return temp;
	}
private:
	char reg_number[9];
};

class Vehicle {
public:
	Vehicle() = delete;
	Vehicle(const char* regnum, const char* description) {
		//this->regnum = new Registration temp(regnum);
		const Registration* temp = new(std::nothrow) Registration(regnum);
		if (temp != nullptr) {
			this->regnum = temp;
		}
		
		std::size_t size = strlen(description);
		char* temp_descr = new(std::nothrow) char[size + 1];
		if (temp_descr != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				temp_descr[i] = description[i];
			}
			temp_descr[size] = '\0';

			this->description = temp_descr;
		}


	}

	Vehicle(const Vehicle& other) {
		this->regnum = new Registration(other.regnum->toString());
		this->description = new(std::nothrow) char[strlen(other.description)];
		strcpy(this->description, other.description);
	}

	Vehicle& operator= (const Vehicle& other) {
		if (this != &other) {
			delete regnum, description;
			this->regnum = new Registration(other.regnum->toString());
			this->description = new(std::nothrow) char[strlen(other.description)];
			strcpy(this->description, other.description);
		}

		return *this;
	}
	~Vehicle() {
		delete regnum, description;
	}


	const Registration*  regnum;
	char* description;
};

class VehicleList {
	VehicleList(std::size_t capacity) {

		Vehicle** temp = new(std::nothrow) Vehicle*[capacity];
		if (temp != nullptr) {
			cars = temp;
			for (unsigned i = 0; i < capacity; i++) {
				cars[i] = nullptr;
			}
		}

		used = 0;
	}

	~VehicleList() {

		for (unsigned i = 0; i < cap; i++) {
			delete cars[i];
		}

		delete[] cars;
	}


	std::size_t capacity() const {
		return this->cap;
	}
	std::size_t size() const {
		return this->used;
	}

	bool empty() const {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	VehicleList(const VehicleList& other) {
		std::size_t size = other.capacity();
		this->cars = new(std::nothrow) Vehicle * [size];
		if (cars != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				cars[i] = other.cars[i];
			}
		}
	}

	VehicleList& operator=(const VehicleList& rhs) {

		if (this != &rhs) {
			std::size_t size = rhs.capacity();
			delete[] cars;
			this->cars = new(std::nothrow) Vehicle * [size];
			if (cars != nullptr) {
				for (unsigned i = 0; i < size; i++) {
					cars[i] = rhs.cars[i];
				}
			}
		}

		return *this;
	}

	void insert(const char* regnum, const char* description) {
		std::size_t size = capacity();
		try {
			for (unsigned i = 0; i < size; i++) {
				if (strcmp(cars[i]->regnum->toString(), regnum) == 0) {
					throw std::exception("");
				}
			}
		}
		catch (std::exception& e) {

		}
		
		Vehicle** temp = new(std::nothrow) Vehicle* [size];
		if (temp != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				temp[i] = cars[i];
			}

			for (unsigned i = 0; i < size; i++) {
				if (temp[i] != nullptr) {
					Vehicle* veh = new (std::nothrow) Vehicle(regnum, description);
					temp[i] = veh;
					used++;
					break;
				}
			}

			delete[] cars;
			cars = temp;
		}
	}

	const Vehicle& at(std::size_t index) const {
		try {
			if (index < 0 || index > capacity()) {
				throw std::out_of_range("");
			}
			else {
				if (cars[index] != nullptr) {
					return *cars[index];
				}
			}
		}
		catch (std::out_of_range& e) {

		}
		
	}
private:
	std::size_t cap;
	Vehicle** cars;
	std::size_t used;
};

int main()
{
	Registration reg("C1234AB");
	Registration reg1("C1234AB");
	Registration reg2("XY1111YX");
	Vehicle car("C1234AB", "des");
	const char* text = reg.toString();
	
	return 0;
}