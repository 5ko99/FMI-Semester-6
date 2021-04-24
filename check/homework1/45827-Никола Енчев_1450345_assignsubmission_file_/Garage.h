#pragma once

#include "MyString.h"
#include "Vehicle.h"

class Garage
{
public:
	Garage() = delete;
	Garage(size_t size);

	Garage(const Garage& other);
	~Garage();
	Garage& operator=(const Garage& rhs);

	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(size_t pos) const;
	const Vehicle& operator[](size_t pos) const;
	bool empty() const;
	size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;

private:
	size_t capacity;
	Vehicle** vehicles;
	size_t vehicleCount;
	size_t spaceTaken;

};

