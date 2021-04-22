#include "Vehicle.h"

Vehicle::Vehicle()
{
    m_registration = "";
    m_description = "";
    m_space = 0;
}
Vehicle &Vehicle::operator=(const Vehicle &other)
{
    if (this != &other)
    {
        m_registration = other.m_registration;
        m_description = other.m_description;
        m_space = other.m_space;
    }
    return *this;
}
Vehicle::Vehicle(const char *registration, const char *description, std::size_t space)
{
    m_space = space;
    m_registration = MyString(registration);
    m_description = MyString(description);
}

const char *Vehicle::registration() const
{
    char *str = new char[m_registration.size() + 1];
    int i;
    for (i = 0; i < m_registration.size(); ++i)
    {
        str[i] = m_registration[i];
    }
    str[i] = '\0';
    return str;
}
const char *Vehicle::description() const
{
    char *str = new char[m_description.size() + 1];
    int i;
    for (i = 0; i < m_description.size(); ++i)
    {
        str[i] = m_description[i];
    }
    str[i] = '\0';
    return str;
}
std::size_t Vehicle::space() const
{
    return m_space;
}
void Vehicle::clear()
{
    m_registration.~MyString();
    m_description.~MyString();
    m_space = 0;
}