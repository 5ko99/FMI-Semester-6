#pragma once
#include "Vehicle.hpp"


class Garage
{
private:
	size_t capacity;
	size_t curr_capacity;
	Vehicle** vehicles;
	size_t num_vehicles;
public:
	Garage(size_t size);
	Garage(const Garage& copy) noexcept; //copy constructor
	Garage& operator=(const Garage& copy) noexcept; //copy assignment
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;
	~Garage();
};