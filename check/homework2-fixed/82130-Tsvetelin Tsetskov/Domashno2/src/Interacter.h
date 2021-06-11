#pragma once

#include "Person.h"
#include "Vehicle.h"

#include <iostream>
#include <string>
#include <vector>

class Interacter
{
public:
	Interacter(std::istream& in, std::ostream& out, bool isFileMode = false);

	~Interacter();

	bool shouldExit() const;
	void repl();

	static Interacter interacterWithFile(const std::string& filepath);
private:
	bool isFileMode;
	bool exiting;
	std::istream& in;
	std::ostream& out;

	std::vector<Person> people;
	std::vector<Vehicle> vehicles;
};

