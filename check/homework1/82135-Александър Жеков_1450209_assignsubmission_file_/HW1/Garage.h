#pragma once

#include <cstdio>
#include "Vehicle.h"

class Garage {
private:
	Vehicle** Vehicles = nullptr;
	size_t numSpaces = 0;
	size_t occupiedSpaces = 0;
	size_t numVehicles = 0;

public:
	Garage(std::size_t size);
	Garage(const Garage* grg);
	~Garage();

	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	bool empty() const;
	bool isFull() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;

	Garage& operator=(const Garage& othergrg);
	const Vehicle& operator[](std::size_t pos) const;
};