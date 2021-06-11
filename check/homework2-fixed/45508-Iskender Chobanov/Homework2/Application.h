#pragma once
#include "Vehicle.h"
#include "Person.h"
#include <vector>
#include <iostream>
#include <fstream>
//Class that controls the whole application
class Application
{
private:
	std::vector<Vehicle> Vehicles;
	std::vector<Person> Persons;// formal, plural for person
	std::string path_;
public:
	Application();
	bool add_Vehicle(const char*,std::string);//Add vehicle by registration and description
	bool add_Person(const std::string,const unsigned);//Add person by name and id
	bool add_Person_as_object(const Person&);
	bool aquire(const unsigned, const std::string); //Person id and Licence plate
	bool release(const unsigned, const std::string);//id does not own vehicle with licence plate
	bool remove(const std::string);
	bool has_Vehicle(std::string) const;
	bool has_Person(unsigned id);
	Person& get_person(unsigned id);
	Vehicle& get_vehicle(const std::string reg);
	bool id_is_unique(unsigned id) const;
	bool reg_is_unique(std::string reg) const;
	void show_cars() const;
	void show_persons() const;
	void show(std::string command);
	void set_path(const char* path_);


	//input commands/output interface
	std::string normalize_command(std::string command); 
	//This function normalizes makes all letters cap, ex: SaveAs returns SAVEAS , VeHiCle returns VEHICLE, 
	bool input_command(std::string commnad,std::string arg1,std::string arg2);
	bool split_input(const std::string); // takes string and splits it into command argument1 argument2 then puts it in input_command
	void output_begin();
	void help();
	
	//I/O files
	void open_database(const char* path);
	void save(const char* path);

	


};

