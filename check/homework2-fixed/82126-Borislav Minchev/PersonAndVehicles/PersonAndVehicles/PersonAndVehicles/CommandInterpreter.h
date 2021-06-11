#pragma once

#include "PersonAndVehicleManager.h"
#include <string>

class CommandInterpreter
{
	PersonAndVehicleManager manager;

	std::string toLowerCase(std::string s);
	std::vector<std::string> splitArguments(std::string s);
	bool isNumber(std::string num);

	bool executeNewPerson(std::string name, unsigned int id);
	bool executeNewVehicle(std::string regisration, std::string	description);
	bool executeAcquire(unsigned int id, std::string regisration);
	bool executeRelease(unsigned int id, std::string regisration);
	bool executeRemovePerson(unsigned int id);
	bool executeRemoveVehicle(std::string regisration);
	void executeSave(std::string path);
	void executeShowPeople();
	void executeShowVehicles();
	void executeShowPersonById(unsigned int id);
	void executeShowVehicleByRegistration(std::string regisration);

	void writeCommandToHelperFile(std::string cmd) const;
	
public:
	CommandInterpreter(std::string path = "");
	~CommandInterpreter();


	void executeCommand(std::string command);


};
