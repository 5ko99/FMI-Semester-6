#pragma once
#include "Command.h"
#include <fstream>

class Interface {
private:
	std::vector<Person*> people;
	std::vector<Vehicle*> vehicles;
	Command command;

	void saveToFile();
	void addVehicle();
	void addPerson();
	void acquireVehicle();
	void releaseVehicle();
	void removeObject();
	void removePerson(unsigned const id);
	void removeVehicle(std::string& id);
	void showObjects();
	long long findVehIndexById(std::string id);
	long long findPersonIndexById(unsigned id);
	bool doWants() const;
	void editAdress(std::string& adress);
public:
	Interface() = default;

	~Interface() = default;
	const std::vector<Person*>* getPeoplePointer() const;
	const std::vector<Vehicle*>* getVehiclesPointer() const;
	void executeCommand(std::string commandLine);

};
