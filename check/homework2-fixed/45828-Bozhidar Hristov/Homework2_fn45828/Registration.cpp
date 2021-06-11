#include "Registration.h"

bool Registration::isValidRegistration()
{
	bool flag = false;
	if (reg[0] < 'A' || reg[0] > 'Z')
		return false;
	if (reg[1] >= '0' && reg[1] <= '9')
	{
		flag = false;
		for (size_t i = 1; i < 5; i++)
		{
			if (reg[i] < '0' || reg[i] > '9')
				return false;
		}
	}
	if (reg[1] >= 'A' && reg[1] <= 'Z')
	{
		flag = true;
		for (size_t i = 2; i < 6; i++)
		{
			if (reg[i] < '0' || reg[i] > '9')
				return false;
		}
	}
	if(flag)
		for (size_t i = 6; i < 8; i++)
		{
			if (reg[i] < 'A' || reg[i]>'Z')
				return false;
		}
	if(!flag)
		for (size_t i = 5; i < 7; i++)
		{
			if (reg[i] < 'A' || reg[i]>'Z')
				return false;
		}
	return true;
}

void Registration::setReg(const char* rhs)
{
	for (size_t i = 0; i < 9; i++)
	{
		reg[i] = rhs[i];
	}
	reg[8] = '\0';
}

const char* Registration::getReg() const
{
	return this->reg;
}

Registration::Registration()
{
	this->reg[0] = '\0';
}

Registration::Registration(char rhs[9])
{
	for (size_t i = 0; i < 8; i++)
	{
		this->reg[i] = rhs[i];
	}
	reg[8] = '\0';
}
