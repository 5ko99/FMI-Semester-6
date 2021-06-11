#pragma once
#include<string>

using std::string;

class Registration {
private:
	string reg;

	/**
	*	Private class method, used to validate whether a registration
	*	number is valid or not.
	*
	*	@param s - string to be validated
	*/
	bool isRegValid(const string& s);
public:
	/**
	*	Initialized registration number with the given str.
	*	Throws if str is invalid reg number.
	*
	*	@param str - string to be initialized with
	*/
	Registration(const string& str);

	/**
	*	Assignment operator, copies contents of reg into the current
	*	object.
	*
	*	@param str - string to be copied
	*/
	Registration& operator=(const Registration& reg);

	/**
	*	Compares two strings.
	*
	*	@param reg - registration to be compared with
	*
	*	returns true if strings are equal, false otherwise
	*/
	bool operator==(const Registration& reg) const;

	/**
	*	returns reg string
	*/
	const string& toString() const;
};
