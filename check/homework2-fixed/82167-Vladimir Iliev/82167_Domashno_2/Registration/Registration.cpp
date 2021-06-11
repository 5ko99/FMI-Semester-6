#include "Registration.h"

#include <stdexcept>

bool Registration::isLetter(char a)
{ return ('A' <= a && a <= 'Z'); }

bool Registration::isDigit(char a)
{ return ('0' <= a && a <= '9'); }

bool Registration::isValidRegistration(const std::string& registration)
{
    if (registration.length() == 8) {
        for (short i = 0; i < 2; ++i)
            if (!isLetter(registration[i]))
                return false;
        for (short i = 2; i < 6; ++i)
            if (!isDigit(registration[i]))
                return false;
        for (short i = 6; i < 8; ++i)
            if (!isLetter(registration[i]))
                return false;
    } else if (registration.length() == 7) {
        if (!isLetter(registration.front()))
            return false;
        for (short i = 1; i < 5; ++i)
            if (!isDigit(registration[i]))
                return false;
        for (short i = 5; i < 7; ++i)
            if (!isLetter(registration[i]))
                return false;
    } else {
        return false;
    }
    return true;
}

Registration::Registration(std::string reg)
    : registration(std::move(reg))
{
    if (!isValidRegistration(registration))
        throw std::invalid_argument("Invalid Registration");
}

const std::string& Registration::getRegistration() const
{ return registration; }
