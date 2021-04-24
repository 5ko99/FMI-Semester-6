// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Божидар Атанасов Христов
// ФН: 45828
// Специалност: Информатика
// Курс: 1
// Административна група: 6
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

bool isValidRegistrationNumber(const char* a) {
	bool first = true, second = true;
	if (isalpha(a[0]) && isalpha(a[1]) && isalpha(a[6]) && isalpha(a[7]))
	{
		for (size_t i = 2; i < 7; i++)
		{
			if (!isdigit(a[i])) first = false;
		}
	}
	else first = false;
	if (first) return first;

	if(isalpha(a[0]) && isalpha(a[5]) && isalpha(a[6]))
		if (isalpha(a[0]) && isalpha(a[1]) && isalpha(a[6]) && isalpha(a[7]))
		{
			for (size_t i = 2; i < 6; i++)
			{
				if (!isdigit(a[i])) second = false;
			}
		}
		else second = false;
	return first || second;
}

class Registration {
	char registration[9]{};
public:
	Registration(const char* str) {
		if (!isValidRegistrationNumber(str)) throw std::exception();
		strcpy(registration, str);
	}

	Registration& operator=(const char* str) {
		for (size_t i = 0; i < strlen(str); i++)
		{
			registration[i] = str[i];
		}
		return *this;
	}

	bool operator==(const char* str) const {
		if (strlen(str) != strlen(this->registration)) return 0;
		for (size_t i = 0; i < strlen(str); i++)
		{
			if (registration[i] != str[i]) return 0;
		}
		return 1;
	}


	const char* toString() const {
		char temp[9];
		for (size_t i = 0; i < 9; i++)
		{
			temp[i] = this->registration[i];
		}
		return temp;
	}

};


class Vehicle {
public:
	Registration regnum;
	std::string description;
	Vehicle(const char* regnum, const char* description) : regnum(regnum){
		this->description = description;
	}
};

class VehicleList {
	size_t cap;
	Vehicle** cars;
	size_t numberOfCars;
public:
	VehicleList(size_t capacity) {
		this->cap = capacity;
		this->numberOfCars = 0;
		cars = new Vehicle*;
	}

	~VehicleList()
	{
		cap = 0;
		numberOfCars = 0;
		delete cars;
		cars = nullptr;
	}
	

	void insert(const char* regnum, const char* description) {
		if (numberOfCars >= cap) throw std::exception();
		for (size_t i = 0; i < numberOfCars; i++)
		{
			if (this->cars[i]->regnum == regnum) throw std::exception();
		}
		cars[numberOfCars]->regnum = regnum;
		cars[numberOfCars]->description = description;
		numberOfCars++;
	}

	const Vehicle& at(std::size_t index) const {
		if (cars[index]->regnum == nullptr) throw std::out_of_range("Out of Range!");
		return *cars[index];
	}

	const Vehicle& operator[](std::size_t index) const {
		assert(index > numberOfCars);
		return *cars[index];
	}

	bool empty() const {
		return (numberOfCars == 0);
	}

	std::size_t capacity() const {
		return this->cap;
	}

	std::size_t size() const {
		return this->numberOfCars;
	}

	const Vehicle* find(const char* regnum) const {
		for (size_t i = 0; i < numberOfCars; i++)
		{
			if (cars[i]->regnum == regnum) return cars[i];
		}
		return nullptr;
	}
};

int main()
{
	size_t N;
	std::cin >> N;
	VehicleList VLIST = VehicleList(N);
	std::string temp1, temp2;
	

	char regnum[9];
	std::cout << "Insert reg number";
	for (size_t i = 0; i < 9; i++)
	{
		std::cin >> regnum;
	}
	if (!VLIST.find(regnum)) std::cout << "No Vehicle with this registration number!\n";
	else std::cout << "Vehicle is in the list!\n";
	return 0;
}