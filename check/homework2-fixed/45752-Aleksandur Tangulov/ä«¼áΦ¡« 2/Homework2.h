#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

class Registration {
private:
	std::string registration;	
public:
	bool validate();
	std::string getRegistration();
	Registration(const std::string registration);	
};

class Vehicle; //forward declaration, because of circular dependency

class Person {
private:
	std::string name;
	unsigned int idNum;
	std::vector<std::string> vehicles; //saving registrations
public:
	Person(const std::string name, unsigned int idNum);
	void addVehicle(Vehicle& vehicle);  //adds the registration number of a given vehicle to the vehicles vector
	void removeVehicle(Vehicle& vehicle);
	std::string getName();
	std::string getVehicleAt(std::size_t pos);
	unsigned int getID();
    size_t vehiclesCount();	
};

class Vehicle {
private:
	Registration registration;
	std::string description;
	Person* owner;
public:
	Vehicle(const std::string registration, const std::string description);
	void setOwner(Person& person);
	void removeOwner(Person& person);
	Person& getOwner();
	std::string getRegistration();
	std::string getDescription();
	bool hasOwner();
};

class PersonDatabase {
private:
	std::vector<Person> personArray;	
public:
	bool validate(Person person); //validates, that a person has a unique idNum, that's not already in the database																   
	PersonDatabase();
	size_t size();
    Person& at(size_t pos);
	void insert(Person& person); 
	void erase(Person& person);
	void print();
};

class VehicleDatabase {
private:
	std::vector<Vehicle> vehicleArray;
public:
	bool validate(Vehicle vehicle); //validates, that a vehicle has a unique registration, that's not already in the database
	VehicleDatabase();
	size_t size();
	Vehicle& at(size_t pos);
    void insert(Vehicle& vehicle);
	void erase(Vehicle& vehicle);
	void print();
};

class Command {
private:
	//domains for the command
	PersonDatabase& pd;
	VehicleDatabase& vd; 
	//type + arguments
	std::vector<std::string> command;
public:
	std::string getArgumentAt(size_t pos);
	Command(PersonDatabase& pd, VehicleDatabase& vd, std::string command);
	//functions to scan the databases with
	bool existsInPD(unsigned int id);
	bool existsInVD(std::string registration);
	Person& findByID(unsigned int id);
	Vehicle& findByReg(std::string registration); 

	//functions to validate a given command with our program's databases
	bool validateCommandType();
	bool validateArguments();

	//helper-functions for the validation functions
	bool canInsertP(unsigned int id);  
	bool canInsertV(std::string registration); 
	bool canAcquire(unsigned int id, std::string registration); 
	bool canRelease(unsigned int id, std::string registration); 
	bool canRemove(std::string argument);
	bool validateSavePath(std::string path); 
	bool canShow(std::vector<std::string> arguments);

	//command execution function
	void execute();

    //helper-functions for command execution
	void insertP(std::string name, unsigned int id);
	void insertV(std::string registration, std::string description);
	void acquire(unsigned int id, std::string registration);
	void release(unsigned int id, std::string registration);
	void remove(std::string argument);
	void save(std::string path);
	void show(std::vector<std::string> arguments);
};

//function to read from file and store information into given databases
void readFromFile(VehicleDatabase& vd, PersonDatabase& pd);
