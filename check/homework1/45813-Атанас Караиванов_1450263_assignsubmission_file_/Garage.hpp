#pragma once
#include "Vehicle.hpp"

class Garage {
private:
	Vehicle** vehicles;
	size_t capacity;
	size_t sizeOfVehicles;
	size_t numOfVehicles;

	void copyFrom(const Garage& other);

public:
	Garage(const Garage& other);
	Garage(size_t size);
	Garage& operator=(const Garage& other);
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;
	~Garage();
};