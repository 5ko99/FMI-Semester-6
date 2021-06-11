#ifndef PERSON_H
#define PERSON_H
#include <vector> //for std::vector<>
#include "Registration.h"

//forward-declaring class Vehicle
class Vehicle;

class Person {
private:


	std::string Name;
	unsigned int UniNum;
	std::vector<Vehicle*> OwnVehs;


public:
	//default constructor with arguments
	Person(std::string Name_str, unsigned int UniNum);
	//copy constructor
	Person(const Person& per);

	//adds Vehicle object to the vector
	void AddVeh(Vehicle& veh);

	//removes Vehicle object from the vector
	void RemoveCar(Vehicle& veh);

	//getter for Person's id
	unsigned int& GetUniNum();
	//getter for Person's name
	std::string& GetName();
	//getter for the vector of Person's owned cars
	std::vector<Vehicle*> GetOwnVehs();

	//friend function for outputing to console
	friend std::ostream& operator<<(std::ostream& out, const Person& per);

	//friend function for outputting to file
	friend std::ofstream& operator<<(std::ofstream& out, const Person& per);

};





#endif
