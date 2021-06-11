#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <cstring> 
#include <string> //for std::string
#include <stdexcept> //for throwing exceptions
#include <iostream> //for cout, cin
#include <fstream> //for inputing and outputing to a file
#include <sstream> //for to_upper(), stoi() and std::stringstream (in unit testing)
class Registration {
private:

	std::string RegNum;
	
private:

	//verifies whether the string is valid Registration number or not
	bool IsStringValid(const std::string& str) const;

	//private case where verifies whether a string with lenght 7 is valid Registration number or not (used in IsStringValid)
	bool CheckValidnessWith7(const std::string& str) const;

	//private case where verifies whether a string with lenght 8 is valid Registration number or not (used in IsStringValid)
	bool CheckValidnessWith8(const std::string& str) const;

public:

	//default conscturcor with argument
	Registration(std::string& str);

	//getter for member string
	std::string& GetRegNum();
	//function to see are two Registration objects equal
	bool operator==(const Registration& other) const;

	//friend function to output to a console
	friend std::ostream& operator<<(std::ostream& out, const Registration& reg);
};

#endif

