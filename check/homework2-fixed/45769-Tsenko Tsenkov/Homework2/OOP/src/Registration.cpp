#include "../include/Registration.hpp"

using std::string;
using std::regex;
using std::vector;

Registration::Registration(const string &regNum) : regNum{validateRegNum(regNum)}
{

}

string Registration::validateRegNum(const string &regNum)
{
    if (!regex_match(regNum, regex("[A-Z]{2}[0-9]{4}[A-Z]{2}")))
        throw std::runtime_error("The registration number is invalid");

    return checkUniqueness(regNum);
}

string Registration::getRegistration() const
{
    return regNum;
}
