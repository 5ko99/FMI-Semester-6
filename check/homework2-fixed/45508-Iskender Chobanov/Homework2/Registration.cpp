#include "Registration.h"



bool Registration::validate(const char* reg,bool isEight)
{
	if (isEight)
	{
		if (reg[0] >= 'A' && reg[0] <= 'Z' && reg[1] >= 'A' && reg[1] <= 'Z' && reg[7] >= 'A' && reg[7] <= 'Z' && reg[6] >= 'A' && reg[6] <= 'Z')
		{
			for (int i = 2; i < 6; i++)
			{
				if (reg[i] < '0' || reg[i]>'9')
					return false;
			}
			return true;
		}
		else return false;
	}
	if (reg[0] >= 'A' && reg[0] <= 'Z' && reg[6] >= 'A' && reg[6] <= 'Z' && reg[5] >= 'A' && reg[5] <= 'Z')
	{
		for (int i = 1; i < 5; i++)
		{
			if (reg[i] <= '0' || reg[i]>='9')
				return 0;
		}
		return true;
	}
	else return false;
}
bool Registration::plate_is_valid()
{
	return valid;
}
void Registration::make_reg(const char* reg)
{
	bool isEight = 0; //if strlen is 8
	switch (strlen(reg))
	{
	case 7: strcpy(reg_plate, reg); break;
	case 8: strcpy(reg_plate, reg); isEight = 1; break;
	default:reg_plate[0] = '\0'; valid = false; return;
	}
	if (!validate(reg, isEight))
	{
		reg_plate[0] = '\0';
		valid = false;
		return;
	}
	valid = true;
	return;
}
Registration::Registration(const char* reg)
{

	make_reg(reg);
}
const std::string Registration::get_as_string() const
{
	std::string reg;
	size_t s = strlen(reg_plate);
	for (size_t i = 0; i < s; i++)
	{
		reg.push_back(reg_plate[i]);
	}
	return reg;
}
