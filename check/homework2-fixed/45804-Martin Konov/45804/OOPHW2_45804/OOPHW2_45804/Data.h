#pragma once
#include "Person.h"
#include "Vehicle.h"
#include "Commands.h";
#include<fstream>;
using std::ofstream;

class Data {
	string first_cmd;
	string second_cmd;
	size_t id;
private:
	bool check_if_veh_is_already_created(const string reg);
	bool check_if_person_is_already_created(const size_t id);
	size_t find_place_in_people_list(const size_t id);
	size_t find_place_in_veh_list(const string reg);
public:
	static vector<Person> list_of_created_people;
	static vector<Vehicle> list_of_created_vehicles;
	Data(string fist_cmd, string second_cmd);
	Data(string fist_cmd, size_t second_cmd);
	Data(size_t first_cmd, string second_cmd);
	~Data();
	void create_veh();
	void create_person();
	void acquire(const size_t id, const string registration);
	void release(const size_t id, const string registration);
	void remove_if_person(const size_t id);
	void remove_if_veh(const string registration);
	void show_people();
	void show_vehicles();
	void show_owner_of_veh(const string reg);
	void show_owned_vehicles(const size_t id);
};
