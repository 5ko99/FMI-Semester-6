#include "Registration.h"
#include <cstring>
#include <algorithm>

//helper functions
bool Registration::isLetter(char c)
{
    return (c >= 'A' && c <= 'Z');
}

bool Registration::isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool Registration::isValid(const std::string & regNumber)
{
    const std::size_t len = regNumber.size();

    return (len >= Registration::MIN_LEN && len <= Registration::MAX_LEN) && (isLetter(regNumber[len - 1]) && isLetter(regNumber[len - 2])) && (isDigit(regNumber[len - 3]) && isDigit(regNumber[len - 4]) && isDigit(regNumber[len - 5]) && isDigit(regNumber[len - 6]) && isLetter(regNumber[len - 7])) && (len == Registration::MIN_LEN || isLetter(regNumber[len - 8]));
}

Registration::Registration(const std::string & regNumber)
{
    //validate registration
    if (!this->isValid(regNumber))
    {
        throw std::invalid_argument("The registration " + regNumber + " is not valid. The format is XX####XX or X#####XX, where X is a capital letter, # is a number");
    }

    const std::size_t len = regNumber.size();
    std::copy_n(regNumber.c_str(), len, this->registration);
    this->registration[len] = '\0';
}

Registration::Registration(const Registration &other)
{
    std::copy_n(other.registration, MAX_LEN + 1, this->registration);
}

Registration &Registration ::operator=(const Registration &other)
{
    std::copy_n(other.registration, MAX_LEN + 1, this->registration);
    return *this;
}
bool Registration::operator==(const Registration &other) const
{
    return strncmp(this->registration, other.registration, MAX_LEN + 1) == 0;
}
const char *Registration::getNumber() const
{
    return this->registration;
}
