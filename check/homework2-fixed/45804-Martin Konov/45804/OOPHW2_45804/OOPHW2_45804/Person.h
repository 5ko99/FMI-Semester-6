#pragma once
#include<iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Person {
	string name;
	size_t id;
private:
	bool isNotOwned(const string veh_to_check_if_owned);
public:
	vector<string> list_of_owned_vehicles;
	Person(string name, size_t id);
	Person(const Person& old_person);
	~Person();
	size_t show_id();
	string show_name();
	void add_vehicle(const string veh_id_to_add);
	void remove_vehicle(const string veh_to_remove);
	size_t check_pos_for_veh_to_remove(const string veh_to_remove);
};
