#include "Registration.h"

Registration::Registration(std::string registration)
{
    try
    {
        if (is_valid(registration))
        {
            this->registration = registration;
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
    }
}

Registration::Registration(const Registration &other)
{
    try
    {
        if (is_valid(other.registration))
        {
            this->registration = other.registration;
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
    }
}

Registration &Registration::operator=(const Registration &other)
{
    if (this != &other)
    {
        try
        {
            if (is_valid(other.registration))
            {
                this->registration = other.registration;
            }
            else
            {
                throw std::invalid_argument("");
            }
        }
        catch (std::invalid_argument)
        {
            std::cerr << "Invalid registration cannot be assigned!" << '\n';
        }
    }

    return *this;
}

Registration &Registration::operator=(const std::string other)
{
    if (this->registration != other)
    {
        try
        {
            if (is_valid(other))
            {
                this->registration = other;
            }
            else
            {
                throw std::invalid_argument("");
            }
        }
        catch (std::invalid_argument)
        {
            std::cerr << "Invalid registration cannot be assigned!" << '\n';
        }
    }

    return *this;
}

bool Registration::is_valid(std::string registration) const
{
    if (registration.length() == 7)
    {
        if (Validation::is_letter(registration[0]) && Validation::is_letter(registration[5]) && Validation::is_letter(registration[6]))
        {
            return Validation::is_digit(registration[1]) && Validation::is_digit(registration[2]) && Validation::is_digit(registration[3]) && Validation::is_digit(registration[4]);
        }

        return Validation::is_letter(registration[0]) && Validation::is_letter(registration[5]) && Validation::is_letter(registration[6]);
    }
    else if (registration.length() == 8)
    {
        if (Validation::is_letter(registration[0]) && Validation::is_letter(registration[1]) && Validation::is_letter(registration[6]) && Validation::is_letter(registration[7]))
        {
            return Validation::is_digit(registration[2]) && Validation::is_digit(registration[3]) && Validation::is_digit(registration[4]) && Validation::is_digit(registration[5]);
        }

        return Validation::is_letter(registration[0]) && Validation::is_letter(registration[1]) && Validation::is_letter(registration[6]) && Validation::is_letter(registration[7]);
    }

    return registration.length() == 8 || registration.length() == 7;
}

bool Registration::operator==(const Registration &other) const
{
    return this->registration == other.registration;
}

void Registration::clear()
{
    this->registration.clear();
}
