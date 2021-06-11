#include <iostream>
#include <string>

#include "Registration.h"

Registration::Registration()
    {

    }

    Registration::Registration(std::string num)
    {
        this->number = num;
    }


    Registration& Registration::operator=(const Registration& source)
    {
        if(this == & source)
        {
            return *this;
        }

        number = source.number;

        return *this;
    }

    const std::string Registration::getNumber() const
    {
        return number;
    }

    Registration::~Registration()
    {

    }
