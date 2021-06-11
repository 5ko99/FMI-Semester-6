#include "Registration.h"

Registration::Registration(const string& registration)
{
	if (!isValid(registration))
	{
		throw std::invalid_argument("Invalid registration!");
	}
	m_registration = registration;
}

bool Registration::isValid(const string& reg) const {
	if (reg.size() > 8)
	{
		return false;
	}

	if (!isalpha(reg[0]))
	{
		return false;
	}
	else
	{
		if (isalpha(reg[1]))
		{
			if (!isdigit(reg[2]) || !isdigit(reg[3]) || !isdigit(reg[4]) || !isdigit(reg[5])
				|| !isalpha(reg[6]) || !isalpha(reg[7]))
			{
				return false;
			}
		}
		else 
		{
			if (!isdigit(reg[1]) || !isdigit(reg[2]) || !isdigit(reg[3]) || !isdigit(reg[4])
				|| !isalpha(reg[5]) || !isalpha(reg[6]))
			{
				return false;
			}
		}
	}

	return true;
}
