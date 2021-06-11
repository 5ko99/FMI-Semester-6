#pragma once
#include <iostream>
#include <string>


class Registration {
	std::string m_plate;
public:
	Registration(const std::string& plate);
	std::string plate() const;
	bool operator==(const Registration& reg) const;
	friend std::ostream& operator<<(std::ostream& os, const Registration& reg);
private:
	bool isValid(const std::string& plate);
};
