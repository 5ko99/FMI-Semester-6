#ifndef CommandProcessor_H_INCLUDED
#define CommandProcessor_H_INCLUDED

#include <iostream>
#include <vector>
#include "Vehicle.h"

class CommandProcessor
{
public:
	~CommandProcessor();
	std::string ProcessCommand(std::string command, bool saveCommand);
	
private:
	void CreateVehicle(char* registration, std::string description);
	void CreatePerson(std::string name, unsigned int id);
	void Acquire(unsigned int ownerId, char* registration);
	void Release(unsigned int ownerId, char* registration);
	std::string Remove(std::string target);
	void Save(std::string path);
	std::string Show(std::string target);
	bool RegistrationDuplicates(char* registrationNumber);
	std::string GetMoreInformation();
	Person* FindPerson(unsigned int id);
	Vehicle* FindVehicle(char* registration);
	void TokenizeCommand(std::string const& str, const char delim, std::vector<std::string>& out);

	std::vector<Vehicle*> vehicles;
	std::vector<Registration*> registrations;
	std::vector<Person*> people;
	std::vector<std::string> commandsList;
};

#endif // !CommandProcessor_H_INCLUDED
