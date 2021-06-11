#include "Validation.h"

bool Validation::is_letter(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool Validation::is_digit(char c)
{
    return c >= '0' && c <= '9';
}

std::string Validation::to_upper_all(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        str[i] = to_upper(str[i]);
    }

    return str;
}

char Validation::to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return char(int(c) - 32);
    }

    return c;
}
