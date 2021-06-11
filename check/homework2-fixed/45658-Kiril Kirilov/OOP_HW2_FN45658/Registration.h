#pragma once
#include <string>
#include <fstream>

class Registration
{
	char id[9];
	
public:	
	bool isValid() const;
	Registration();
	Registration(std::string string);
	Registration(const Registration& other);
	const char* getID() const;
	bool operator==(const Registration& other) const;
	friend std::ostream& operator<<(std::ostream& file, const Registration& registration);
};


bool isValidRegistration(std::string string);
