#pragma once
#include"MyString.h"
#include"Vehicle.h"

class Garage
{
private:
	Vehicle** allVehicles;
	size_t capacity;
	size_t takenSpace;
	size_t numOfVehicles;

public:
	Garage(size_t);
	Garage();
	Garage(const Garage&);
	Garage& operator=(const Garage&);
	~Garage();
	void clear();
	void insert(Vehicle&);
	void erase(const char* registration);
	const Vehicle& at(size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	size_t size() const;
	const Vehicle* find(const char* registration) const;

};

