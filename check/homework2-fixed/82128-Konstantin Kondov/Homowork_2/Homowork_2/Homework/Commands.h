#ifndef COMMANDS_H
#define COMMANDS_H

#include "Vehicle.h"
#include "Person.h"
#include "Database.h"

#include <cctype> //for to_upper()

class Command {
private:

	std::string command;
	std::string arg1;
	std::string arg2;

	//pointer to the database we are using
	Database *database;

private:

	//used to get the argument within QuotationMark from a user's input
	//usefull when getting the argument for PERSON, VEHICLE, SAVE
	std::string Get_Argument_within_QuotationMark(std::string& args);

	bool Does_Arg_Contains_2_QuotationMarks(std::string& args);

	//used to get the other arguments that are not within QuotationMark
	//usefull for the other commands
	std::string Get_Other_Argument(std::string& args);

	//removing the leading whitespaces in the case the user inputted them by mistake
	void Remove_Leading_Whitespaces(std::string& args);

	//making the inputted string command with upper letters so that i can recognise the commands
	std::string& str_toupper(std::string& str);

	//checks if there is a person with the same id in the database
    bool Is_There_Duplicated_Person(unsigned int& per_id);

	//runs the command PERSON
	void Execute_Person();


	////checks if there is a vehicle with the same registraiton in the database
	bool Is_There_Duplicated_Vehicle(std::string& arg);

	//runs the command VEHICLE
	void Execute_Vehicle();

	

	//runs the command ACQUIRE
    void Execute_Acquire();

	//runs the command RELEASE
	void Execute_Release();

	//runs the command REMOVE
	void Execute_Remove();

	//runs the command SHOW
	void Execute_Show();

	void Execute_Save();

public:

	Command(std::string command, std::string args, Database& data_base);

	std::string& GetCommand();
	std::string& GetFirstArg();
	std::string& GetSecondArg();

};






#endif
