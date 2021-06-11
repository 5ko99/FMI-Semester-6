#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "CommandEnum.h"
#include "Vehicle.h"

class CommandHelper
{
public:
	static std::vector<Vehicle*> vehicleContainer;
	static std::vector<Person*> personContainer;
	static Command translateCommand(const std::string input);
	static std::string normalizeString(const std::string& rawString);
	static void executeCommand(const std::string command, const std::vector<std::string> args);
	static void deallocateMemory();
private:
	static void executeVehicle(std::vector<std::string> args);
	static void executePerson(std::vector<std::string> args);
	static void executeAcquire(std::vector<std::string> args);
	static void executeRelease(std::vector<std::string> args);
	static void executeRemove(std::vector<std::string> args);
	static void executeSave(std::vector<std::string> args);
	static void executeShow(std::vector<std::string> args);
	static void executeNoSuchCommand(std::vector<std::string> args);
};

