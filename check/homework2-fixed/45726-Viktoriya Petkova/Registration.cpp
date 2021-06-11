#include "Registration.h"

bool Registration::isValid(const char* reg)
{
	if (strlen(reg) == 8)
	{
		return isalpha(reg[0]) && isalpha(reg[1])
			&& isdigit(reg[2]) && isdigit(reg[3])
			&& isdigit(reg[4]) && isdigit(reg[5])
			&& isalpha(reg[6]) && isalpha(reg[7]);
	}
	else if (strlen(reg) == 7)
	{
		return isalpha(reg[0])
			&& isdigit(reg[1]) && isdigit(reg[2])
			&& isdigit(reg[3]) && isdigit(reg[4])
			&& isalpha(reg[5]) && isalpha(reg[6]);
	}
}

Registration::Registration()
{
	strcpy_s(this->reg, "/0");
}

Registration::Registration(const char* reg)
{
	if (isValid(reg))
	{
		strcpy_s(this->reg, reg);
	}
	else
	{
		throw invalid_argument("Invalid registration number");
	}
}

const char* Registration::getReg() const
{
	return reg;
}

void Registration::setReg(const char* src)
{
	strcpy_s(reg, src);
}

bool Registration::operator==(const Registration& rhs)
{
	return strcmp(reg,rhs.getReg()) == 0;
}

ostream& operator<<(ostream& ofs, const Registration& r)
{
	return ofs << r.reg;
}

istream& operator>>(istream& ist, Registration& r)
{
	return ist >> r.reg;
}
