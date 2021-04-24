#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <iostream>
#include <vector>
#include "Vehicle.hpp"

class Garage
{
public:
	~Garage();
	Garage(const Garage& other);
	Garage(std::size_t size);
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;
	unsigned int getLastOccupiedIndex();
	void print();

private:
	std::size_t initialCapacity;
	std::size_t capacity;
	Vehicle** vehicles;
	unsigned int counter;
};

#endif // !GARAGE_HPP_INCLUDED