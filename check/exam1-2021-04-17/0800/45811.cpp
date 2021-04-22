// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Петко Иванов Петков
// ФН: 45811
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04.2021 
// Начален час на контролното: 08:00
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include<cctype>

using std::string;
using std::isalpha;
using std::out_of_range;
using std::exception;
using std::strcmp;
using std::cout;
using std::cin;

class Registration {
private:
	char reg[9];

	bool isRegValid(const string& s) {
		if (s.size() >= 9)
		{
			return false;
		}

		bool hasTwoSymbolsForCity = false;

		if (isalpha(s[0]) && isalpha(s[1]))
		{
			hasTwoSymbolsForCity = true;
		}

		if (!isalpha(s[0]))
		{
			return false;
		}

		for (size_t i = 0; i < 4; i++)
		{
			if (hasTwoSymbolsForCity)
			{
				if (!isdigit(s[i + 2]))
				{
					return false;
				}
			}
			else
			{
				if (!isdigit(s[i + 1]))
				{
					return false;
				}
			}
		}

		if (hasTwoSymbolsForCity)
		{
			if (!isalpha(s[6]) || !isalpha(s[7]))
			{
				return false;
			}
		}
		else
		{
			if (!isalpha(s[5]) || !isalpha(s[6]))
			{
				return false;
			}
		}

		return true;
	}
public:
	Registration(const char* str) {
		string s(str);

		if (!isRegValid(s))
		{
			throw exception("Invalid registration number.");
		}

		size_t i;
		for (i = 0; i < s.size(); i++)
		{
			reg[i] = s[i];
		}
		reg[i] = '\0';
	}

	Registration& operator=(const char* str) {
		string s(str);

		if (!isRegValid(s))
		{
			throw exception("Invalid registration number.");
		}

		size_t i;
		for (i = 0; i < s.size(); i++)
		{
			reg[i] = s[i];
		}
		reg[i] = '\0';

		return *this;
	}

	bool operator==(const char* str) const {
		string fst(reg);
		string snd(str);

		return fst == snd;
	}

	const char* toString() const {
		return reg;
	}
};

class Vehicle {
public:
	Registration regnum;
	string description;
	Vehicle(const char* regnum, const char* description) : regnum(regnum), description(description) {}

	Vehicle(const Vehicle& v) : regnum(v.regnum), description(v.description) {
	}

	Vehicle& operator=(const Vehicle& v) {
		if (this == &v)
		{
			return *this;
		}

		this->regnum = v.regnum;
		this->description = v.description;

		return *this;
	}
};

class VehicleList {
private:
	size_t cap = 0;
	size_t numOfVehicles = 0;
	Vehicle** vehicles = nullptr;

	void copyFrom(const VehicleList& vl) {
		this->cap = vl.cap;
		this->numOfVehicles = vl.numOfVehicles;
		this->vehicles = new Vehicle * [vl.cap];

		for (size_t i = 0; i < vl.numOfVehicles; i++)
		{
			this->vehicles[i] = new Vehicle(*vl.vehicles[i]);
		}
	}
	void moveFrom(VehicleList& vl) {
		this->vehicles = vl.vehicles;
		vl.vehicles = nullptr;

		this->cap = vl.cap;
		vl.cap = 0;

		this->numOfVehicles = vl.numOfVehicles;
		vl.numOfVehicles = 0;
	}
public:
	VehicleList(std::size_t capacity) {
		this->cap = capacity;
		this->numOfVehicles = 0;
		this->vehicles = new Vehicle * [capacity];
	}

	// Copy ctor
	VehicleList(const VehicleList& vl) {
		copyFrom(vl);
	}

	// Copy assignment operator
	VehicleList& operator=(const VehicleList& vl) {
		if (this == &vl)
		{
			return *this;
		}

		// even if the VehicleList is just initialized with some capacity
		// and no vehicles inside it, then the for construction will just be skipped
		for (size_t i = 0; i < this->numOfVehicles; i++)
		{
			delete this->vehicles[i];
		}
		delete[] this->vehicles;

		copyFrom(vl);

		return *this;
	}

	// Move ctor
	VehicleList(VehicleList&& vl) noexcept {
		moveFrom(vl);
	}

	// Move assignment operator
	VehicleList& operator=(VehicleList&& vl) noexcept {
		if (this == &vl)
		{
			return *this;
		}

		moveFrom(vl);

		return *this;
	}

	~VehicleList() {
		for (size_t i = 0; i < this->numOfVehicles; i++)
		{
			delete this->vehicles[i];
		}

		delete[] vehicles;
	}

	void insert(const char* regnum, const char* description) {
		if (this->numOfVehicles + 1 > this->cap)
		{
			throw exception("Not enough space in the list.");
		}

		if (find(regnum) != nullptr)
		{
			throw exception("There is already a vehicle with the same registration.");
		}

		Vehicle* v = nullptr;

		try
		{
			v = new Vehicle(regnum, description);
		}
		catch (const std::exception& e)
		{
			v = nullptr;
			throw e;
		}

		this->vehicles[this->numOfVehicles] = v;
		this->numOfVehicles++;
	}

	const Vehicle& at(std::size_t index) const {
		if (index >= this->numOfVehicles)
		{
			throw out_of_range("Index out of bounds.");
		}

		return *this->vehicles[index];
	}

	const Vehicle& operator[](std::size_t index) const {
		assert(index < this->numOfVehicles);
		return *this->vehicles[index];
	}

	bool empty() const {
		return (this->numOfVehicles == 0);
	}

	size_t capacity() const {
		return this->cap;
	}

	size_t size() const {

		return this->numOfVehicles;
	}

	const Vehicle* find(const char* regnum) const {
		if (regnum == nullptr)
		{
			return nullptr;
		}

		for (size_t i = 0; i < this->numOfVehicles; i++)
		{
			if (strcmp(this->vehicles[i]->regnum.toString(), regnum) == 0)
			{
				return this->vehicles[i];
			}
		}

		return  nullptr;
	}
};

void readVehicleInfo(char regNum[], char descrp[]) {
	cout << "Enter vehicle's registration number: ";
	cin.getline(regNum, 100);

	cout << "Enter vehicle's description: ";
	cin.getline(descrp, 100);
}

int main()
{
	size_t N;
	cin >> N;

	VehicleList vl(N);
	cin.ignore();

	for (size_t i = 0; i < N; i++)
	{
		char regNum[200];
		char descrp[200];

		cout << "#" << i + 1 << '\n';
		readVehicleInfo(regNum, descrp);

		try
		{
			vl.insert(regNum, descrp);
		}
		catch (const std::exception& e)
		{
			cout << "\n" << e.what() << '\n';
			i--;
			continue;
		}
	}

	char regNum[200];
	cout << "Check if a car is in the last by providing registration number: ";
	cin.getline(regNum, 200);

	if (vl.find(regNum) != nullptr)
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}

	return 0;
}