#pragma once

#include "Vehicle.h"

class Garage
{
public:
	/*
	Constructs a new garage with the specified max size
	*/
	Garage(std::size_t size);
	Garage(const Garage& other);

	~Garage();

	Garage& operator=(const Garage& other);

	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;

	// Although we do not need private access in the operator,
	// Being inside the class makes it a lot more readable and understandable,
	// that it is coupled to this class, specifically
	friend std::ostream& operator<<(std::ostream& os, const Garage& garage);
private:
	Vehicle** vehicles;
	std::size_t occupiedSize;
	std::size_t maxSize;
	std::size_t nextFreeIndex;

	/*
	Searches for the supplied registration number,
	if it is not in the garage,
	then the index after the end of the array is returned
	*/
	std::size_t indexOf(const char* regNumber) const;
};
