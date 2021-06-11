#include <string>
#include "Helpers.h"

int getDigit(char c)
{
    return c - '0';
}
bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}
bool isCapitalLetter(char c)
{
    return 'A' <= c && c <= 'Z';
}
void toLower(std::string& command)
{
    for (int i = 0; i < command.size(); i++)
    {
        if (isCapitalLetter(command[i]))command[i] = command[i] - 'A' + 'a';
    }
}
