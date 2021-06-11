#include <exception>

#include "registration.h"

using std::cout;
using std::endl; 

bool Registration::validation(std::string reg)
{
    if (reg.length() > 8 || reg.length() < 7)
    {
        return false; 
    }

    if (reg.length() == 7)
    {
        if (std::isupper(reg.at(0)) == 0)
        {
            return false; 
        }
        if (!std::isdigit(reg.at(1)) || !std::isdigit(reg.at(2)) || !std::isdigit(reg.at(3)) || !std::isdigit(reg.at(4)))
        {
            return false; 
        }
        if (std::isupper(reg.at(5))== 0 || std::isupper(reg.at(6)) == 0)
        {
            return false; 
        }
    }

    if (reg.length() == 8)
    {
        if (std::isupper(reg.at(0)) == 0 || std::isupper(reg.at(1)) == 0)   
        {
            return false; 
        }
        if (!std::isdigit(reg.at(2)) || !std::isdigit(reg.at(3)) || !std::isdigit(reg.at(4)) || !std::isdigit(reg.at(5)))
        {
            return false; 
        }
        if (std::isupper(reg.at(6)) == 0 || std::isupper(reg.at(7)) == 0)
        {
            return false; 
        }
    }

    return true; 
}

void Registration::copy(const Registration& other)
{
    this->registration = other.getString(); 
}

Registration::Registration()
{
     
}

Registration::Registration(std::string reg)
{
    if (validation(reg))
    {
        this->registration = reg; 
    }
    else
    {
        throw std::invalid_argument("Inavlid registration!");
    }
     
}

Registration::Registration(const Registration& other)
{
    copy(other); 
}

size_t Registration::getSize() const
{
    return this->registration.size(); 
}

std::string Registration::getString() const
{
    return this->registration.c_str(); 
}


Registration& Registration::operator=(const Registration& other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this; 
}

Registration::~Registration()
{
    
}
