#include "Registration.h"

std::regex Registration::validReg{ std::regex("^[a-zA-Z]{1,2}[0-9]{4}[a-zA-Z]{2}$") };

bool Registration::isRegistrationValid(const std::string& reg)
{
	return regex_match(reg, validReg);
}

const std::string& Registration::content() const
{
	return _content;
}

Registration::Registration(const std::string& content)
{
	if (!isRegistrationValid(content))
	{
		throw std::invalid_argument("Invalid registration number");
	}
	this->_content = content;
}
