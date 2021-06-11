#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>

class Registration {
public:
	Registration() = delete;
	Registration(const char* newNum);
	Registration(std::string newNum);
	Registration& operator=(const char* newNum);
	Registration& operator=(std::string newNum);
	Registration& operator=(const Registration& other);

	bool operator==(const Registration& rhs) const;
	const char* c_str() const;

	friend std::ostream& operator<<(std::ostream& out, const Registration& reg);
	friend std::istream& operator>>(std::istream& in, const Registration& reg);
	
private:
	char num[9];
	//bool isValid(const char* query);
};
#endif
