#include "../include/registration.h"
#include <iostream>
#include <cstring>
#include <cctype>

typedef int (*Validate)(int);

bool Registration::validate(const char* reg)
{
    //used idea shared in the discord channel
    int length = strlen(reg);
    const Validate validators[9] = {isupper, isupper, isdigit, isdigit, isdigit, isdigit, isupper, isupper};
    const Validate* check = (length == 8) ? validators : validators + 1;
    
    for (size_t i = 0; i < length; i++)
    {
        if(!check[i](reg[i]))
        {
            return false;
        }
    }
    
    return true;
}

Registration::Registration(const char* reg)
{
    if(!validate(reg))
    {
        throw std::invalid_argument("Invalid registration number");
    }
    strcpy(registration, reg);
}

Registration::Registration(const Registration& other)
{
    //other's registration has already been validated
    strcpy(registration, other.registration);
}

Registration& Registration::operator=(const Registration& other)
{
    strcpy(registration, other.registration);
    return *this;
}

const char* Registration::getRegistration()
{
    return registration;
}
