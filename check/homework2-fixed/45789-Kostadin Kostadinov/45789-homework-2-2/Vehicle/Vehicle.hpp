#ifndef VEHICLE_H
#define VEHICLE_H
#include "../Registration/Registration.hpp"
#include "../Person/Person.hpp"

class Person;

class Vehicle {
public:
	Vehicle() = delete;
	Vehicle(Registration& number, std::string desc);

	bool operator==(const Vehicle& rhs) const; 

	Registration getReg() const;
	Person* getOwner() const;

	void setOwner(Person* owner);
	void removeOwner();

	void print();
	void printAll();

private:
	Registration number;
	std::string desc;
	Person* owner;
};
#endif
