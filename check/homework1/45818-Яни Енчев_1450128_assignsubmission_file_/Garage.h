#pragma once
#include "MyString.h"
#include "Vehicle.h"
#include <stdexcept>
#include <cassert>

class Garage
{
public:
	Garage(std::size_t size);
	~Garage();
	void insert(Vehicle& v);
	void clear();
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	const Vehicle* find(const char* registration) const;

private:
	std::size_t capacity;
	Vehicle** vehicles;
	std::size_t numberVehicles;
	std::size_t capacityLeft;
	std::size_t vehiclesBuffer;
	bool validRegistationNumber(const Vehicle& v) const;
	bool swapVehicles(const Vehicle& toSwap);
	void dataClear();
};

void printGarage(Garage& toPrint);
void clear(Vehicle** arr, size_t sz);