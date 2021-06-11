//
// Created by pgpetrov on 22.05.21 Рі..
//

#include <stdexcept>
#include "Registration.h"

Registration::Registration(std::string reg)
{
	if (reg.size() != 8)
	{
		throw std::logic_error("not right size for registration");
	}
	for (std::size_t i = 0; i < 2; ++i)
	{
		if (reg[i] < 'A' || reg[i] > 'Z')
		{
			throw std::logic_error("city name contains char that is not a letter or is not uppercase");
		}
	}
	for (std::size_t i = 2; i < 6; ++i)
	{
		if (reg[i] < '0' || reg[i] > '9')
		{
			throw std::logic_error("registration contains char that is not a digit in the part with the number");
		}
	}
	for (std::size_t i = 6; i < 8; ++i)
	{
		if (reg[i] < 'A' || reg[i] > 'Z')
		{
			throw std::logic_error("registration end contains char that is not a letter or is not uppercase");
		}
	}
	data = reg;
}

std::string Registration::getData() const
{
	return data;
}

bool Registration::operator==(const Registration& other) const
{
	return data == other.data;
}
