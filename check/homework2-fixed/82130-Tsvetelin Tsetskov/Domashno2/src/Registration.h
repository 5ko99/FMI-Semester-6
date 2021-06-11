#pragma once

#include <ostream>

class Registration
{
public:
	Registration(const char reg[9]);
	~Registration();

	Registration(const Registration& other);

	Registration& operator=(const Registration& other);

	const std::string& asStr() const;

	bool operator==(const Registration& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Registration& reg);
private:
	const char* number;

	static bool validNumber(const char reg[9]);
};

