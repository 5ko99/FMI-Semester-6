#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"

class Person {
	unsigned int m_id;
	std::string m_name;
	std::vector<Vehicle*> m_vehicles;
	static std::vector<unsigned int> usedId;
public:
	Person(const std::string& name,unsigned int id);
	Person(const Person& other) = delete;
	Person& operator=(const Person& other) = delete;
	~Person();
	unsigned int id() const;
	std::string name() const;
	void add(Vehicle* v);
	void remove(Vehicle* v);
	bool owns(const Vehicle* v) const;
	size_t numberOfVehicles() const;
	void removeAll();
	friend std::ostream& operator<<(std::ostream& os, const Person& p);
	void printVehicles() const;
private:
	bool used(unsigned int id);

};
