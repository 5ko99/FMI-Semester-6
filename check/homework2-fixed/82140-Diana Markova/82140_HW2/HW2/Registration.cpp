//#define _CRT_SECURE_NO_WARNINGS
#include "Registration.h"
#include <iostream>
#include <cstring>
#include <cstddef>
#include <stdexcept>
#include "helpers.h"

Registration::Registration(const char* str)
{
    if(!isValid(str)) throw std::invalid_argument("Invalid input for registration");
    std::strcpy(regNum, str);
}

bool Registration::isValid(const char* str)
{
    std::size_t len=std::strlen(str);
    if(!(len == 7 || len == 8)) return false;
    if(len == 7)
    {
        if(!isCapitalLetter(str[0])) return false;
        for(std::size_t i = 1; i<=4; ++i) if(!isDigit(str[i]))    return false;
        if(!(isCapitalLetter(str[5]) && isCapitalLetter(str[6]))) return false;
    }
    if(len == 8)
    {
        if(!(isCapitalLetter(str[0]) && isCapitalLetter(str[1]))) return false;
        for(std::size_t i = 2; i<=5; ++i) if(!isDigit(str[i]))    return false;
        if(!(isCapitalLetter(str[6]) && isCapitalLetter(str[7]))) return false;
    }
    return true;
}

bool Registration::operator==(const Registration& rhs) const {return std::strcmp(regNum, rhs.regNum) == 0;}

const char* Registration::getRegistration() const
{
    return regNum;
}

std::ostream& operator<<(std::ostream& os, const Registration& reg)
{
    os<<reg.getRegistration();
    return os;
}
