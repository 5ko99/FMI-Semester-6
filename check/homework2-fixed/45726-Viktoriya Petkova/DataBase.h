#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Person.h"
#include "Vehicle.h"

using namespace std;

class DataBase
{
	vector<Person*> list_people;
	vector<Vehicle*> list_vehicles;

	bool check_reg_unique(const Registration& reg);
public:
	DataBase(vector<Person*>& people, vector<Vehicle*>& vehicles);
	void add_vehicle(Registration& reg, string desc);
	void add_person(string name, unsigned int id);
	void release_vehicle(unsigned int owner_id, Registration& vehicle_id);
	void acquire(unsigned int owner_id, Registration& vehicle_id);
	void remove_person(unsigned int owner_id);
	void remove_vehicle(Registration& vehicle_id);
	void show_all_people();
	void show_all_vehicle();
	void show_info_vehicle( Registration& vehicle_id);
	void show_info_people( unsigned int owner_id);
	void save(const char* file_path);
};

