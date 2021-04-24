#pragma once
#include <cstddef>//size_t
#include "Vehicle.h"


class Garage {
private:
	size_t capacity;
	size_t numCars;
	size_t maxCars;

	Vehicle** vehicles;

	bool allocateMemory(size_t newSize, Vehicle**& arr) const;
	void nullifyAll(); 
	size_t findTotalCapacity(const Garage& newGarage);

public:
	Garage();
	Garage(std::size_t size);
	Garage(const Garage& newGarage);//copy constr
	Garage(Garage&& newGarage) noexcept;
	~Garage();
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;

	const Vehicle& operator[](std::size_t pos) const;
	Garage& operator=(const Garage& newGarage);//copy assign
	Garage& operator=(Garage&& newGarage)noexcept;
	bool operator==(const Garage& other) const;  //checks if there are the same cars in it in the same places

};

