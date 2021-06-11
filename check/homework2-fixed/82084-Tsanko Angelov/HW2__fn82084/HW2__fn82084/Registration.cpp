#include <iostream>
#include "Registration.h"

void Registration::copy(const Registration &other)
{
    registration = other.registration;
}

void Registration::clean()
{
    registration.clear();
}

Registration::Registration()
{
    registration.clear();
}

Registration::Registration(const Registration &other)
{
    copy(other);
}

Registration &Registration::operator=(const Registration &other)
{
    if (this != &other)
    {
        clean();
        copy(other);
    }

    return *this;
}

Registration::~Registration()
{
    clean();
}

Registration::Registration(std::string _registration)
{
    registration = _registration;

    if (valid_symbol() == 0)
    {
        throw std::invalid_argument("Error!");
    }
}

std::string Registration::getRegistration() const
{
    return this->registration.c_str();
}

bool Registration::valid_symbol()
{
    if (registration.length() < 7 || registration.length() > 8)
    {
        return false;
    }

    if (registration.length() == 7)
    {
        if (registration.at(0) < 65 || registration.at(0) > 90)
        {
            return false;
        }

        if (registration.at(1) < 48 || registration.at(1) > 57)
        {
            return false;
        }

        if (registration.at(2) < 48 || registration.at(2) > 57)
        {
            return false;
        }

        if (registration.at(3) < 48 || registration.at(3) > 57)
        {
            return false;
        }

        if (registration.at(4) < 48 || registration.at(4) > 57)
        {
            return false;
        }

        if (registration.at(5) < 65 || registration.at(5) > 90)
        {
            return false;
        }

        if (registration.at(6) < 65 || registration.at(6) > 90)
        {
            return false;
        }
    }

    if (registration.length() == 8)
    {
        if (registration.at(0) < 65 || registration.at(0) > 90)
        {
            return false;
        }

        if (registration.at(1) < 65 || registration.at(1) > 90)
        {
            return false;
        }

        if (registration.at(2) < 48 || registration.at(2) > 57)
        {
            return false;
        }

        if (registration.at(3) < 48 || registration.at(3) > 57)
        {
            return false;
        }

        if (registration.at(4) < 48 || registration.at(4) > 57)
        {
            return false;
        }

        if (registration.at(5) < 48 || registration.at(5) > 57)
        {
            return false;
        }

        if (registration.at(6) < 65 || registration.at(6) > 90)
        {
            return false;
        }

        if (registration.at(7) < 65 || registration.at(7) > 90)
        {
            return false;
        }
    }

    return true;
}


