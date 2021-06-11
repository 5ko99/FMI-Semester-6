#include <stdexcept>
#include <string>

#include "Utils.h"
#include "PersonVehicles.h"

using namespace std;

Registration::Registration(string reg)
{
	if (reg.length() != 7 && reg.length() != 8)
		throw length_error("");
	if ((reg.length() == 8 && isLetter(reg[0]) && isLetter(reg[1]) && isDigit(reg[2]) && isDigit(reg[3]) && isDigit(reg[4]) && isDigit(reg[5]) && isLetter(reg[6]) && isLetter(reg[7]))
		|| (reg.length() == 7 && isLetter(reg[0]) && isDigit(reg[1]) && isDigit(reg[2]) && isDigit(reg[3]) && isDigit(reg[4]) && isLetter(reg[5]) && isLetter(reg[6])))
	{
		this->reg = reg;
	}
	else
	{
		throw invalid_argument("");
	}
}

bool Registration::operator==(const Registration& registration) const
{
	return this->reg == registration.reg;
}

string Registration::getReg() const
{
	return reg;
}
