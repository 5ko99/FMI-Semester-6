#include "Registration.hpp"
#include <cstdint>
#include <iostream>
#include <cstring>
#include <string>


Registration::Registration(const std::string& str)
{
    if(!validate(str))
    {
        throw std::invalid_argument("Invalid registration format.");
    }

    this->str = str;
}

Registration::Registration(const Registration& other)
{
    str = other.str;
}

bool Registration::operator==(const Registration& other)
{
    return str == other.str;
}

bool Registration::validate(const std::string& str)
{
    size_t len = str.size();

    size_t i = 0;

    for (; str[i] >= 'A' && str[i] <= 'Z'; i++);

    if(i == 0 || i > 2) return false;

    size_t j = 0;

    for (; (str[i + j] >= '0' && str[i + j] <= '9'); j++);

    if(j != 4) return false;

    if((len - (i + j) ) != 2) return false;

    return true;
}

const std::string Registration::getString() const
{
    return str;
}

std::ostream& operator<<(std::ostream& out,  Registration const& reg)
{
    out << reg.str;

    return out;
}
