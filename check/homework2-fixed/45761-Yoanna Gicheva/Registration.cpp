#include "Registration.h"
#include <iostream>
#include <sstream> 


Registration::Registration(char* registration) {
    if (!this->IsValid(registration)) 
    {
        throw std::invalid_argument("Registration number is not valid!");
    }

	this->registration = registration;
}

bool Registration::IsValid(char* registration)
{
    int size = strlen(registration);
    if (size != 7 && size != 8) 
    {
        return false;
    }
    if (!isalpha(registration[size - 1]) || !isalpha(registration[size - 2])) 
    {
        return false;
    }
    if (!isdigit(registration[1]) && !isalpha(registration[1])) 
    {
        return false;
    }
    if(!isdigit(registration[size - 3]) || !isdigit(registration[size - 4]) || !isdigit(registration[size - 5]))
    {
        return false;
    }

    return true;

}

std::string Registration::ConvertToString()
{
    int i;
    std::stringstream stream;
    char* reg = this->registration;
    int size = strlen(reg);
    for (i = 0; i < size; i++) {
        stream << this->registration[i];
    }
    return stream.str();
}
