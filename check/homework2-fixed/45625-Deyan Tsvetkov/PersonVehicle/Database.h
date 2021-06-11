#include "Person.h"
#include "Vehicle.h"
#include <fstream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::getline;
using tokens = vector<string>;

#pragma once
class Database
{
public:
	Database(const Database& other) = delete;
	Database& operator=(const Database& other) = delete;
	Database(Database&& other) = delete;
	Database& operator=(Database&& other) = delete;

	static Database& i();

	// adds person to the vector
	void addPerson(const string& name, unsigned int ID);

	// removes person from the vector
	void removePerson(unsigned int ID);

	// returns the index of a person in the vector or -1 if the person is not in the vector
	int findPerson(unsigned int ID) const;

	// adds vehicle to the vector
	void addVehicle(const string& reg, const string& description);

	// removes vehicle from the vector
	void deleteVehicle(const string& reg);

	// returns the index of a vehicle in the vector or -1 if the vehicle is not in the vector
	int findVehicle(const string& reg) const;

	// sets a new onwer with id "ID" to a vehicle with registration "reg"
	void acquire(unsigned int ID, const string& reg);

	// releases the vehicle with registration "reg" from the owner with id "ID"
	void release(unsigned int ID, const string& reg);

	// prints all people in the vector
	void printPeople() const;

	// prints all vehicles in the vector
	void printVehicles() const;

	// shows all commands
	void displayHelp() const;

	// saves the database to a file
	void writeToFile(const string& file) const;

	// loads the database from a file
	void readFromFile(const string& file);

	// let's the user to enter commands and operate with the database
	void run();

private:
	Database();

	// separates the input command to tokens
	void process(const string& command, tokens& tokens);

	// makes all symbols in the command to a uppercase
	const string& toUpper(string& command);

	// returns a tokens at position "ind"
	const string& at(size_t ind, const tokens& tokens) const;

	// converts a string to unsigned int
	unsigned int stoi(const string& str);

	// returns true if str is a number
	bool isID(const string& str) const;

	vector<Person> m_people;
	vector<Vehicle> m_vehicles;
};

