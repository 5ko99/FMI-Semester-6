#pragma once
#include "Vehicle.cpp"
#include "MyString.cpp"

class Garage
{
private:
	size_t Capacity = 0;
	size_t TakenSpaces = 0;
	size_t MaxNumberOfvehicles = 10;
	size_t insertedVehicles = 0;
	Vehicle** Vehicles = new Vehicle*[10];
public:
	Garage(size_t size);
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(size_t pos) const;
	const Vehicle& operator[](size_t pos) const;
	bool empty() const;
	size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;
};