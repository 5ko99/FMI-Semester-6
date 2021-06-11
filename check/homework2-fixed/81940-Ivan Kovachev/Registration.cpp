#include "Registration.h"

bool Registration::isLetter(const char& c) const
{
    return (c >= 'A' && c <= 'Z');
}
bool Registration::isDigit(const char& d) const
{
    return (d >= '0' && d <= '9');
}

bool Registration::isValid(const std::string reg) const
{
    if(reg.size() == 7 &&
       isLetter(reg[0])&& isDigit(reg[1]) && isDigit(reg[2]) && isDigit(reg[3]) && isDigit(reg[4]) &&
       isLetter(reg[5]) && isLetter(reg[6]))
    {
            return true;
    }
    if(reg.size() == 8 &&
       isLetter(reg[0])&& isLetter(reg[1]) &&
       isDigit(reg[2]) && isDigit(reg[3]) && isDigit(reg[4]) && isDigit(reg[5]) &&
       isLetter(reg[6]) && isLetter(reg[7]))
    {
            return true;
    }
    else return false;
}
Registration::Registration() { reg = ""; }
/*
Registration::Registration(std::string reg)
{
    if(isValid(reg))
    {
        this->reg = reg;
    }
    else throw std::invalid_argument("invalid registration");
}
*/
std::string Registration::getReg() { return reg; }
Registration::Registration(const std::string reg)
{
    if(isValid(reg))
    {
        this->reg = reg;
    }
    else throw std::invalid_argument("invalid registration");
}
Registration::Registration(const Registration &other):reg(other.reg) {}

Registration& Registration::operator=(const Registration& other)
{
    if(this != &other)
    {
        reg = other.reg;
    }
    return *this;
}
std::ostream & operator<< (std::ostream& os, const Registration& arg)
{
    os << arg.reg ;
}
bool operator==(const Registration& lhs, const Registration& rhs)
{
    return (lhs.reg == rhs.reg);
}

Registration::~Registration(){}
