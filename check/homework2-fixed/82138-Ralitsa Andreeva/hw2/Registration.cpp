#include <stdexcept>
#include <cstddef>
#include "Registration.h"
#include "Helpers.h"

Registration::Registration(const std::string& plate)
{
	if (!isValid(plate))throw std::invalid_argument("Invalid registration");
	m_plate = plate;
}
std::string Registration::plate() const
{
	return m_plate;
}
bool Registration::operator==(const Registration& reg) const
{
	return m_plate == reg.m_plate;
}
std::ostream& operator<<(std::ostream& os, const Registration& reg)
{
	os << reg.m_plate;
	return os;
}
bool Registration::isValid(const std::string& plate)
{
	std::size_t length = plate.size();
	if (length != 7 && length != 8) return 0;
	bool valid = isCapitalLetter(plate[0]);
	if (length == 8)valid = valid && isCapitalLetter(plate[1]);
	
	for (int i = 3; i < 7; i++)
		valid = valid && isDigit(plate[length - i]);
	
	valid = valid && isCapitalLetter(plate[length - 1]) && isCapitalLetter(plate[length - 2]);
	return valid;
}
