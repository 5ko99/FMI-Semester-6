#pragma once
#include "Registration.h"
using std::ostream;

class Vehicle {
private:
	Registration regnum;
	string description;
	unsigned int ownerID;
public:
	/**
	*	Initializes the object with regnum(regnum), description(description)
	*
	*	@param regnum -		 registration number string to be initialized with
	*	@param description - description string to be initialized with
	*/
	Vehicle(const string& regnum, const string& description);

	/**
	*	Getter
	*
	*	returns regnum private member as string
	*/
	const string& getRegistration() const;

	/**
	*	Getter
	*
	*	returns ownerID private member
	*/
	size_t getOwnerID() const;

	/**
	*	Setter
	*
	*	Sets ownerID of the object
	*
	*	@param id - id to be set with
	*/
	void setOwnerId(unsigned int id);

	/**
	*	Prints the object details
	*
	*	@param o - ostream object
	*	@param v - Vehicle object to be printed
	*/
	friend ostream& operator<<(ostream& o, const Vehicle& v);
};
