#pragma once
#include "Vehicle.h"
class Garage
{
private:
	std::size_t capacity = 0;
	std::size_t currentCapacity = 0;
	std::size_t numberOfVehicles = 0;
	Vehicle** vehicles = nullptr;
public:
	Garage(std::size_t size);
	Garage(const Garage& other);
	Garage& operator= (const Garage& other);
	~Garage();
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;
};

