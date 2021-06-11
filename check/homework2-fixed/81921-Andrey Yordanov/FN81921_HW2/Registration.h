#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>

class Registration {
private:
	std::string regis;
public:
	Registration();
	Registration(std::string);
	Registration(const Registration&);
	Registration operator=(Registration&);
	std::string getReg() const;
	void print() const;

};

bool operator==(const Registration&, const Registration&);
