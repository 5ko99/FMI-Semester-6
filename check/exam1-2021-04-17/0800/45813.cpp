// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Атанас Веселинов Караиванов
// ФН: 45813
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: събота 17/4/2021
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
using namespace std;

class Registration {
private:
	char registration[9];
public:
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;
};

Registration::Registration(const char* str) {
	if (isalpha(str[0]) != 0 && isalpha(str[1]) != 0 && isalpha(str[6]) != 0 && isalpha(str[7]) != 0
		&& isdigit(str[2]) != 0 && isdigit(str[3]) != 0 && isdigit(str[4]) != 0 && isdigit(str[5]) != 0) {

		strcpy_s(this->registration, 9, str);
	}
	else {
		throw exception("Invalid registration!");
	}
}

Registration& Registration::operator=(const char* str) {
	if (strcmp(this->registration, str) != 0) {
		strcpy_s(this->registration, 9, str);
	}

	return *this;
}

bool Registration::operator==(const char* str) const {
	if (strcmp(this->registration, str) != 0) {
		return false;
	}

	return true;
}

const char* Registration::toString() const {
	return this->registration;
}

class Vehicle {
public:
	Registration regnum=nullptr;
	string description;
	
	Vehicle(const char* regnum, const char* description);
};

Vehicle::Vehicle(const char* regnum, const char* description) {
	this->regnum = regnum;
	this->description = description;
}

class VehicleList {
private:
	size_t capac;
	Vehicle** vehicles;
	size_t numOfVehicles;

public:
	VehicleList(size_t capacity);
	VehicleList(const VehicleList& list);
	VehicleList& operator=(const VehicleList& list);
	void insert(const char* regnum, const char* description);
	const Vehicle& at(size_t index) const;
	const Vehicle& operator[](size_t index) const;
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	const Vehicle* find(const char* regnum) const;
	~VehicleList();
};

VehicleList::VehicleList(size_t capacity) {
	this->capac = capacity;
	this->numOfVehicles = 0;
	this->vehicles = new Vehicle * [capacity];
	for (size_t i = 0; i < capacity; i++) 		{
		this->vehicles[i] = nullptr;
	}
}

VehicleList::VehicleList(const VehicleList& list) {
	this->capac = list.capac;

	this->vehicles = new Vehicle * [list.capac];
	for (size_t i = 0; i < list.capac; i++) {
		this->vehicles[i] = list.vehicles[i];
	}
}

VehicleList& VehicleList::operator=(const VehicleList& list) {
	if (this != &list) {
		for (size_t i = 0; i < this->capac; i++) 		{
			delete this->vehicles[i];
		}
		delete[] this->vehicles;
		this->capac = list.capac;

		this->vehicles = new Vehicle * [list.capac];
		for (size_t i = 0; i < list.capac; i++) 		{
			this->vehicles[i] = list.vehicles[i];
		}
	}

	return *this;
}

void VehicleList::insert(const char* regnum, const char* description) {
	if (this->numOfVehicles++ > capac) {
		throw exception("VehicleList is full!");
	}
	if (find(regnum) != nullptr) {
		throw exception("Vehicle is already in the list!");
	}

	this->vehicles[numOfVehicles] = new Vehicle(regnum, description);
	this->vehicles[numOfVehicles]->description = description;
	this->vehicles[numOfVehicles]->regnum = regnum;

	this->numOfVehicles++;
}

const Vehicle& VehicleList::at(size_t index) const {
	if (index >= this->capac || index < 0) {
		throw out_of_range("Element is out of range!");
	}

	return *this->vehicles[index];
}

const Vehicle& VehicleList::operator[](size_t index) const {
	return at(index);
}

bool VehicleList::empty() const {
	if (this->numOfVehicles == 0) {
		return true;
	}
	return false;
}

size_t VehicleList::capacity() const {
	return this->capac;
}

size_t VehicleList::size() const {
	return this->numOfVehicles;
}

const Vehicle* VehicleList::find(const char* regnum) const {
	for (size_t i = 0; i < this->numOfVehicles; i++) 		{
		if (strcmp(this->vehicles[i]->regnum.toString(), regnum) == 0) {
			return this->vehicles[i];
		}
	}

	return nullptr;
}

VehicleList::~VehicleList() {
	for (size_t i = 0; i < this->capac; i++) {
		delete this->vehicles[i];
	}
	delete[] this->vehicles;
}


int main() {
	size_t N;
	cin >> N;

	VehicleList vehList(N);

	for (size_t i = 0; i < N; i++) 		{
		char regnum[9];
		char description[100];


		cout << "Regnum: ";
		cin.ignore();
		cin.getline(regnum, 9);

		cout << "descr: ";
		cin.getline(description, 100);

		vehList.insert(regnum, description);
	}

	
	return 0;
}