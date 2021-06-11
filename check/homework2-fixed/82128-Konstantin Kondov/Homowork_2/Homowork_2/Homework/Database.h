#ifndef DATABASE_H
#define DATABASE_H
#include "Person.h"
#include "Vehicle.h"

class Database{
private:

	//used for storring all the information Vehicles
	std::vector<Vehicle*> AllVehicles;

	//used for storing all the information about Person
	std::vector<Person*> AllPerson;

public:

	//return the sive of ALLPerson
	std::size_t Get_Size_of_Persons() const;

	//Returns the Person at the given index
	Person& Get_Person_At_Index(const std::size_t& index);

	//Adds Person to the AllPerson
	void AddPerson(const Person& per);

	//Removes a Person from AllPerson
	void RemovePerson(std::size_t index);

	//return the sive of ALLVehicles
	std::size_t Get_Size_of_Vehicles() const;

	//Returns the Vehicles at the given index
	Vehicle& Get_Vehicle_At_Index(const std::size_t index);

	//Adds Vehicle to the AllVehicles
	void AddVehicle(const Vehicle& veh);

	//Remove Vehicle from AllVehicles
	void RemoveVehicle(std::size_t index);

	//Saves all the Information in a text
	void SaveText(std::ofstream& file);

	//Loads all the information in the text
	void LoadText(std::ifstream& file);

	~Database();

};




#endif
