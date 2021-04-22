
#include "helpers.h"

unsigned int Mystrlen(const char *array)
{
    unsigned int len = 0;
    while (array[len])
    {
        len++;
    }
    return len;
}

void Mystrcpy(char *target, const char *source)
{
    unsigned int len = 0;
    while (source[len])
    {
        target[len] = source[len];
        len++;
    }

    target[len] = '\0';
}

void Mystrcpy(char *target, const char *source, std::size_t size)
{
    unsigned int len = 0;
    while (source[len])
    {
        target[size] = source[len];
        len++;
        size++;
    }

    target[size] = '\0';
}

char *Mystrconcat(const char *string1, const char *string2)
{
    char *concatString = new char[Mystrlen(string1) + Mystrlen(string2)];

    Mystrcpy(concatString, string1);
    Mystrcpy(concatString, string2, Mystrlen(string1));

    return concatString;
}

char *Mystrconcat(const char *string1, const char v)
{
    char *concatString = new char[Mystrlen(string1) + 2];

    Mystrcpy(concatString, string1);
    concatString[Mystrlen(string1)] = v;
    concatString[Mystrlen(string1) + 1] = '\0';

    return concatString;
}

bool MystrcmpareEquality(const char *string1, const char *string2)
{
    if (Mystrlen(string1) == Mystrlen(string2))
    {
        for (std::size_t i = 0; i < Mystrlen(string1); i++)
        {
            if (string1[i] != string2[i])
            {
                return false;
            }
        }

        return true;
    }

    return false;
}
bool MystrcmpareSmaller(const char *string1, const char *string2)
{
    if (Mystrlen(string1) == Mystrlen(string2))
    {
        for (std::size_t i = 0; i < Mystrlen(string1); i++)
        {
            if (string1[i] > string2[i])
            {
                return false;
            }
            else if (string1[i] < string2[i])
            {
                return true;
            }
        }
    }

    return Mystrlen(string1) < Mystrlen(string2);
}

bool onlyWhiteSpaces(const char *string)
{
    for (size_t i = 0; i < Mystrlen(string); i++)
    {
        if (string[i] != ' ')
        {
            return false;
        }
    }

    return true;
}