#pragma once
#include "Vehicle.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

class Person {
private:
	string name;
	size_t ID;
	vector<Registration> vehicles;
public:
	/**
	*	Initializes person object with name(name) and id(id).
	*
	*	@param name - name of person
	*	@param id   - person id
	*/
	Person(const string& name, unsigned int id);

	/**
	*	Getter
	*
	*	returns ID private member
	*/
	size_t getID() const;

	/**
	*	Adds registration number(reg) to the list of registrations
	*
	*	@param reg - registration string to be added
	*/
	void addRegistrationNumber(const string& reg);

	/**
	*	Removes registration number(reg) from the list of registrations
	*
	*	@param reg - registration string to be removed
	*/
	void removeRegistrationNumber(const string& reg);

	/**
	*	Finds the registration (reg) in the list of registrations
	*
	*	@param reg - registration string to be searched for
	*	returns index of registration number.
	*/
	int getIndexOf(const string& reg) const;

	/**
	*	Access the registration number at pos
	*
	*	@param pos - position to accesses
	*	returns registration number as string
	*/
	const string& getRegistrationAt(size_t pos) const;

	/**
	*	Getter
	*
	*	returns the number of registrations of person
	*/
	size_t getRegistrationsCount() const;

	/**
	*	Prints object details on the console.
	*
	*	@param o - ostream object
	*	@param p - Person object to be printed
	*
	*	returns ostream object
	*/
	friend ostream& operator<<(ostream& o, const Person& p);
};
