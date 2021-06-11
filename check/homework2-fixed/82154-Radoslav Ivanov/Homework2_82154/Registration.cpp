#include "Registration.h"

Registration::Registration()
{
    registration = "UNKNOWN";
}


//The validation of reg takes place before calling the constructor
Registration::Registration(const std::string& reg) : registration(reg) 
{
    //makes all letters capital ones, because vehicles have capital letter registrations
    for (size_t i=0; i<registration.size(); ++i){
        if ( registration[i] >= 'a' && registration[i] <= 'z'){
            registration[i] -= 'a' - 'A';
        }
    }
}

Registration::Registration(const Registration& other)
{
    this->registration = other.registration;
}

Registration& Registration::operator=(const Registration& other)
{
    if (this != &other){
        this->registration = other.registration;    
    }
    return *this;
}

bool Registration::operator==(const Registration& other) const
{
    return (this->registration == other.registration);
}

std::ostream& operator<<(std::ostream &os, const Registration& reg)
{
    os << reg.registration;
    return os;
}

bool Registration::validateRegistration(const std::string& newReg)
{
    int len = newReg.size();
    return (len == 7 || len == 8) &&
            isalpha(newReg[len - 1]) &&
            isalpha(newReg[len - 2]) &&
            isdigit(newReg[len - 3]) &&
            isdigit(newReg[len - 4]) &&
            isdigit(newReg[len - 5]) &&
            isdigit(newReg[len - 6]) &&
            isalpha(newReg[len - 7]) &&
            (len == 7 || isalpha(newReg[len - 8]));
}
