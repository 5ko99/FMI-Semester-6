#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>

class Instruction {

public:
	Instruction(const std::string instr); 
	std::string get_command() const;
	std::string get_first_argument() const;
	std::string get_second_argument() const;
	//std::string get_third_argument() const;
private:

	std::string command;
	std::string first_argument;
	std::string second_argument;
	//std::string third_argument;

};
