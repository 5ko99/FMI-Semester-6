#include "Registration.h"
#include <cstring>
#include <stdexcept>
bool Registration::isValid(const char str[])
{
    if (strlen(str) < 7 || strlen(str) > 8)
        return false;
    if (!isalpha(str[0]))
        return false;
    int pos = 1;
    if (isalpha(str[1]))
        ++pos;
    if (!isdigit(str[pos]) || !isdigit(str[pos + 1]) || !isdigit(str[pos + 2]) || !isdigit(str[pos + 3]))
        return false;
    pos += 4;
    if (!isalpha(str[pos]) || !isalpha(str[pos + 1]))
        return false;
    return true;
}
Registration::Registration()
{
    strcpy(m_str, "");
}
Registration::Registration(const char str[])
{
    if (!isValid(str))
    {
        throw std::invalid_argument("Invalid registration");
    }
    strcpy(m_str, str);
}
bool Registration::operator==(Registration &other) const
{
    return (strcmp(m_str, other.m_str) == 0);
}
