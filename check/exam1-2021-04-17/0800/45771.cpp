// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Наделина Шипочка
// ФН: 45771
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17/04/2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

//Registration.h 
class Registration {
public:
	Registration(const char* str);
	~Registration();

	Registration& operator=(const Registration& reg);
	bool operator==(const Registration& reg) const;

	const char* toString() const;

private:

	static const size_t DIGIT_LEN = 4;
	static const size_t MAX_CHAR_LEN = 2;

	size_t cityDigitsCnt(const char* str);
	bool isValidInput(const char* str);
	void copy(const char* str);
	void copy(const Registration& reg);
	void clear();

	char* city;
	char* num;
	char* end;
};

//Registration.cpp
//Parameter ctor
Registration::Registration(const char* str) {
	if (isValidInput(str)) {
		copy(str);
	}
}

//Dtor
Registration::~Registration() {
	clear();
}

Registration& Registration::operator=(const Registration& reg) {
	if (this != &reg) {
		clear();
		copy(reg);
	}

	return *this;
}
bool Registration::operator==(const Registration& reg) const {

	if (this != &reg) {
		if (strcmp(city, reg.city))
			return false;
		if (strcmp(num, reg.num))
			return false;
		if (strcmp(end, reg.end))
			return false;
	}

	return true;
}

//transforms the object to a string
const char* Registration::toString() const {

	size_t len = strlen(city) + MAX_CHAR_LEN + DIGIT_LEN;

	char* str = new char[len + 1];

	size_t i = 0;
	while (i < len) {
		strcpy(str, city);
		i += strlen(city);
		strcpy(str, num);
		i += DIGIT_LEN;
		strcpy(str, end);
		i += MAX_CHAR_LEN;
	}

	str[i] = '\0';

	return str;
}

//Private methods:

//Counts how long city part of the reg num should be
size_t Registration::cityDigitsCnt(const char* str) {
	size_t cnt = 0;

	while (isalpha(*str)) {
		++cnt;
		++str;
	}

	return cnt;
}

//Checks if we have a correct reg number
bool Registration::isValidInput(const char* str) {

	if (cityDigitsCnt(str) > MAX_CHAR_LEN)
		return false;

	str += cityDigitsCnt(str);

	size_t cnt = 0;

	while (isdigit(*str)) {
		++cnt;
		++str;
	}

	if (cnt != DIGIT_LEN)
		return false;

	cnt = 0;
	while (isalpha(*str)) {
		++cnt;
		++str;
	}

	if (cnt != MAX_CHAR_LEN)
		return false;

	return true;
}

//Copies the string to the different members of the class
void Registration::copy(const char* str) {

	size_t cityDigits = cityDigitsCnt(str);

	city = new char[cityDigits + 1];
	num = new char[DIGIT_LEN + 1];
	end = new char[MAX_CHAR_LEN + 1];

	size_t i = 0;

	for (size_t j = 0; j < cityDigits; ++i, ++j)
		city[j] = str[i];

	city[cityDigits] = '\0';


	for (size_t j = 0; j < DIGIT_LEN; ++i, ++j)
		num[j] = str[i];

	num[DIGIT_LEN] = '\0';

	for (size_t j = 0; j < MAX_CHAR_LEN; ++i, ++j)
		end[j] = str[i];

	end[MAX_CHAR_LEN] = '\0';

}

void Registration::copy(const Registration& reg) {

	size_t cityDigits = strlen(reg.city);

	city = new char[cityDigits + 1];
	num = new char[DIGIT_LEN + 1];
	end = new char[MAX_CHAR_LEN + 1];

	strcpy(city, reg.city);
	strcpy(num, reg.num);
	strcpy(end, reg.end);
}

//Clears the dynamically allocated memory in the obj
void Registration::clear() {
	delete[] city;
	delete[] num;
	delete[] end;
}

//Vehicle.h
class Vehicle {
public:
	Vehicle(const char* regnum, const char* description);

	Registration regnum;
	std::string description;
};

//Vehicle.cpp
Vehicle::Vehicle(const char* regnum, const char* description)
	:regnum(regnum), description(description)
{}

//VehicleList.h
class VehicleList {
public:
	VehicleList(size_t capacity);
	VehicleList(const VehicleList& v);
	~VehicleList();
	VehicleList& operator=(const VehicleList& v);

	void insert(const char* regnum, const char* description);
	const Vehicle& at(size_t index) const;
	const Vehicle& operator[](size_t index) const;
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	const Vehicle* find(const char* regnum) const;

private:

	int vehicleIndex(const char* regnum) const;
	void copy(const VehicleList& v);
	void resize();
	void clear();

	size_t cap;
	size_t filled;
	Vehicle** vehicles;

};

//VehicleList.cpp

VehicleList::VehicleList(size_t capacity)
	:cap(capacity), filled(0) {

	vehicles = new Vehicle * [capacity];
}

VehicleList::VehicleList(const VehicleList& v) {
	copy(v);
}

VehicleList::~VehicleList() {
	clear();
}

VehicleList& VehicleList::operator=(const VehicleList& v) {
	if (this != &v) {
		clear();
		copy(v);
	}

	return *this;
}

//Inserts a new vehicle in the list
void VehicleList::insert(const char* regnum, const char* description) {

	if (vehicleIndex(regnum) != -1)
		throw std::exception("Vehicle in list already");


	Vehicle* v = new Vehicle(regnum, description);

	if (filled >= cap)
		resize();

	vehicles[filled] = v;
	filled++;
}

//Returns the vehicle at this location, if not in list throws an exception
const Vehicle& VehicleList::at(size_t index) const {
	if (index < filled)
		return *vehicles[index];

	throw std::out_of_range("out of range");
}

//Returns the vehicle at this location
const Vehicle& VehicleList::operator[](size_t index) const {
	assert(index < filled);
	return *vehicles[index];
}

//Returns if the list has any vehicles stored
bool VehicleList::empty() const {
	return !filled;
}

//Returns the capacity of hte list
size_t VehicleList::capacity() const {
	return cap;
}

//Returns the number of vehicles in the list
size_t VehicleList::size() const {
	return filled;
}

//Returns ptr to the vehicle with that regnum
//If not in list, returns nullptr
const Vehicle* VehicleList::find(const char* regnum) const {

	int index = vehicleIndex(regnum);
	if (index >= 0)
		return vehicles[index];

	return nullptr;
}

//Private methods:

//Returns the index in the array of a vehicle with this regnum,
//if not in array, returns -1
int VehicleList::vehicleIndex(const char* regnum) const {

	for (size_t i = 0; i < filled; ++i) {
		if (!strcmp(regnum, vehicles[i]->regnum.toString()))
			return i;
	}

	return -1;
}

//Deeply copies the content of another VehicleList
void VehicleList::copy(const VehicleList& v) {
	cap = v.cap;
	filled = v.filled;

	vehicles = new Vehicle * [cap];

	for (size_t i = 0; i < filled; ++i)
		vehicles[i] = new Vehicle(v.vehicles[i]->regnum.toString(), v.vehicles[i]->description.c_str());
}

//Resizes vehicles array with twice the capacity
void VehicleList::resize() {
	cap *= 2;

	Vehicle** tmp = new Vehicle * [cap];

	for (size_t i = 0; i < filled; ++i)
		tmp[i] = vehicles[i];

	delete[] vehicles;
	vehicles = tmp;
}

//Deletes dynamically allocated memory
void VehicleList::clear() {
	for (size_t i = 0; i < filled; ++i)
		delete[] vehicles[i];

	delete[] vehicles;
}


//Main part of program
const size_t MAX_LEN = 1024;

void inputCars(size_t n, VehicleList vehicles) {
	
	char* regnum = new char[MAX_LEN];
	char* descr = new char[MAX_LEN];

	for (size_t i = 0; i < n; ++i) {

		std::cin >> regnum;
		std::cin.getline(descr, MAX_LEN);

		try {
			vehicles.insert(regnum, descr);
		}
		catch (std::exception e) {
			std::cout << "Invalid car number, try again:";

			std::cin >> regnum;
			std::cin >> descr;

			vehicles.insert(regnum, descr);
		}
	}

	delete[] regnum;
	delete[] descr;
}

bool isCarInList(const char* regnum, VehicleList vehicles) {
	if (vehicles.find(regnum) == nullptr)
		return false;

	return true;
}

int main(){

	size_t n;
	std::cin >> n;

	VehicleList vehicles(n);

	inputCars(n, vehicles);

	char* regnum = new char[MAX_LEN];
	std::cin >> regnum;

	std::cout << isCarInList(regnum, vehicles);

	delete[] regnum;

	return 0;
}