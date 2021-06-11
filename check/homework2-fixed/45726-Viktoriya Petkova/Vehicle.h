#pragma once
#include<iostream>
#include<cstring>
#include"Registration.h"
using namespace std;
class Person;
class Vehicle
{
	Registration reg_num;
	string description;
	Person* owner;

public:
	Vehicle(Registration reg_num, string description, Person* owner = nullptr);
	friend ostream& operator<<(ostream&, const Vehicle&);
	Registration getReg_num() const { return reg_num; }
	Person* get_owner() const { return owner; }
	string get_description() const { return description; }
	void set_owner(Person* owner) { this->owner = owner; }
	void cout_owner(Person* owner);
};

