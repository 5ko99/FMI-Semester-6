#ifndef VEHICLE_H
#define VEHICLE_H
#include "Registration.h"

//forward declaring class Person
class Person;

class Vehicle {
private:

	Registration UniRegNum;
	std::string Desc;
	bool isTaken;
	Person* Owner;
	

public:

	//default constructor with arguments
	Vehicle(std::string& reg_str, std::string& desc_str);

	//copy constructor
	Vehicle(const Vehicle& other);

    //sets the owner of the object
	void SetOwner(Person& per);

	//disowning the object which means the objects is noone's properties
	void DisOwn();

	//return true if the object has an owner
	bool Is_Taken();

	//checks whether or not two Vehicle objects are the same
	bool operator==(const Vehicle& veh);

	//returns the owner of the vehicle
	Person& GetOwner();

	//return the registration number of the object
	std::string& GetUniRegNum();

	//friend function to output to an console
	friend std::ostream& operator<<(std::ostream& out, const Vehicle& veh);

	//friend function to output to a file
	friend std::ofstream& operator<<(std::ofstream& out, const Vehicle& veh);

};






#endif
