#include <iostream>
#include "Registration.h"

bool Registration::isValid()
{
	if (registration.size() < 7 || registration.size() > 8)
	{
		return false;
	}
	if (registration[0] >= 'A' && registration[0] <= 'Z')
	{
		if (registration.size() == 8 && !(registration[1] >= 'A' && registration[1] <= 'Z'))
		{
			return false;
		}
		for (unsigned short i = 1 + (registration.size() == 8); i < registration.size() - 2; i++)
		{
			if (!(registration[i] >= '0' && registration[i] <= '9'))
			{
				return false;
			}
		}
	}
	else {
		return false;
	}
	if (!(registration[registration.size() - 1] >= 'A' && registration[registration.size() - 1] <= 'Z'
		&& registration[registration.size() - 2] >= 'A' && registration[registration.size() - 2] <= 'Z'))
	{
		return false;
	}
	return true;

}

Registration::Registration(std::string reg) :registration(reg)
{
	if (!isValid())
	{
		throw std::logic_error("Invalid Registration!\n");
	}
	//registration = reg;
}

Registration::Registration(const Registration& other) :registration(other.registration)
{
}

Registration::Registration(Registration&& other) noexcept :registration(std::move(other.registration))
{
}



Registration& Registration::operator=(Registration&& other) noexcept
{
	registration = std::move(other.registration);
	return *this;
}

const std::string Registration::getAsString() const
{
	return registration;
}

std::ostream& operator<<(std::ostream& os, const Registration& reg)
{
	os << reg.getAsString();
	return os;
}
