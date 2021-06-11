#pragma once
#include<iostream>
#include <string>
#include <vector>
using std::string;

class Registration {
	string reg_num;
private:
	bool isValid(const string reg_num);
public:
	Registration();
	Registration(string reg_num);
	Registration(const Registration& old_registration);
	~Registration();
	string Return_reg();
};
