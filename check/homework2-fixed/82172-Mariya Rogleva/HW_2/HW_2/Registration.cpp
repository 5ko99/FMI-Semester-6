#include "Registration.hpp"

Registration::Registration(std::string reg)
{
    if(Verify::isValidRegistration(reg))
    {
        registration = reg;
    }
    else
    {
        throw std::runtime_error("This registration is not valid");
    }
}

std::string Registration::getReg() const
{
    return registration;
}
