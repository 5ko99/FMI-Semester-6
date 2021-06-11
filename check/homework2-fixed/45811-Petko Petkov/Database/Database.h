#pragma once
#include "Person.h"

class Database {
private:
	vector<Person> people;
	vector<Vehicle> vehicles;

	/**
	*	Private default constructor
	*
	*	Database class is singleton
	*/
	Database();
public:
	/**
	*	Static class method
	*
	*	returns static instance of Database object
	*/
	static Database& getInstance();

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	Database(Database&&) = delete;
	Database& operator=(Database&&) = delete;

	/**
	*	Adds person with name(name) and id(id) to the database's inner people list
	*	Throws if there is already a person with such id
	*
	*	@param name - name of person
	*	@param id   - id of person
	*/
	void addPersonRecord(const string& name, unsigned int id);

	/**
	*	Deletes person with id(id) and releases all the vehicles that he/she posseses
	*	Throws if there is no person with such id
	*
	*	@param id - id of person to be removed
	*/
	void deletePersonRecord(unsigned int id);

	/**
	*	Find person object by id.
	*
	*	@param id - id of the person to be found
	*	returns pointer to the person object with id(id) or nullptr if there is no record with such id
	*/
	Person* findPersonById(unsigned int id);

	/**
	*	Deletes vehicle with registration number(reg) and releases it from the owner's list
	*	Throws if there is no vehicle with such registration
	*
	*	@param reg - registration number of the vehicle that is to be deleted
	*/
	void deleteVehicleRecord(const string& reg);

	/**
	*	Adds vehicle with registration number(reg) and description(description) to the list of vehicles
	*	Throws if there is already a vehicle with such registration number
	*
	*	@param reg - registration of vehicle
	*	@param id  - description of vehicle
	*/
	void addVehicleRecord(const string& reg, const string& description);

	/**
	*	returns pointer to vehicle with registration(reg) or nullptr if there is no vehicle with such reg.
	*
	*	@param reg - registration number to be looked for
	*/
	Vehicle* findVehicleByRegistration(const string& reg);

	/**
	*	Assigns vehicle with registration(vehicleID) to the person with id(ownerID)
	*	Throws if there is no person with id ownerID
	*	Throws if there is no vehicle with registration vehicleID.
	*	If the vehicle is already owned by someone else then it is released from the former owner
	*	and assigned to the new owner.
	*
	*	@param ownerID   - id of person
	*	@param vehicleID - registration number of vehicle
	*/
	void assignVehicleToOwner(unsigned ownerID, const string& vehicleID);

	/**
	*	Releases vehicle with registration(vehicleID) of the person with id(ownerID)
	*	Throws if there is no person with id ownerID
	*	Throws if there is no vehicle with registration vehicleID.
	*
	*	@param ownerID   - id of person
	*	@param vehicleID - registration number of vehicle
	*/
	void releaseVehicleOfOwner(unsigned ownerID, const string& vehicleID);

	/**
	*	Checks if a given string is ID of a person
	*
	*	@param id - string to be checked
	*	returns true if the string matches the ID format of Person object.
	*/
	bool isStringPersonID(const string& id) const;

	/**
	*	Prints the menu commands
	*/
	void menu() const;

	/**
	*	Prints details of all vehicles in the database
	*/
	void printVehicles() const;

	/**
	*	Prints details of all people int he database
	*/
	void printPeople() const;

	/**
	*	Reads commands from file and interprets them as if entered by person.
	*	Populates database lists of vehicles and people.
	*
	*	Throws if path is incorrect.
	*	Throws if opening file failed
	*
	*	@param path		  - path to file
	*	@param cmdHistory - commands history(list of commands to keep track of them)
	*/
	void readFromFile(const string& path, vector<string>& cmdHistory);

	/**
	*	Saves the commands that had been entered up to this point into a text file
	*
	*	Throws if path is incorrect
	*	Throws if opening file failed
	*
	*	@param ath		  - path to file
	*	@param cmdHistory - commands history(list of commands to keep track of them)
	*/
	void saveToFile(const string& path, const vector<string>& cmdHistory) const;

	/**
	*	Execute method
	*	Gives start to the program's main logic
	*	Prompts the user to input commands and operate with the database
	*/
	void exe();
};
