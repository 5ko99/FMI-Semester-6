#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Vehicle.h"
using namespace std;

class Person
{

	string name;
	unsigned int unique_ID;
	vector<Vehicle*> own_Vehicles;
public:
	explicit Person(string name = "empty", unsigned int unique_ID = 0, vector<Vehicle*> own_Vehicles = {});
	void add_vehicle(const vector<Vehicle*>& new_vehicles);
	void push_back_vehicle(Vehicle*& new_vehicle);
	string get_name() const { return name; }
	unsigned int get_unique_ID() const { return unique_ID; }
	vector<Vehicle*> get_own_Vehicles() const { return own_Vehicles; }
	void cout_all_vehicles();
	void remove_vehicle(Registration& vehicle_id);

};

