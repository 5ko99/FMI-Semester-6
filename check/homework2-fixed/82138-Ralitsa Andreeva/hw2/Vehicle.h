#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Registration.h"

class Person;
class Vehicle {
	Registration m_plate;
	std::string m_description;
	Person* m_owner;
	static std::vector<Registration> usedReg;
	friend class Person;
public:
	Vehicle(const Registration& plate, const std::string& description);
	Vehicle(const Vehicle& other) = delete;
	Vehicle& operator=(const Vehicle& other) = delete;
	~Vehicle();
	Registration plate() const;
	std::string description() const;
	Person* owner() const;
	friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
private:
	bool find(const Registration& plate);
};
