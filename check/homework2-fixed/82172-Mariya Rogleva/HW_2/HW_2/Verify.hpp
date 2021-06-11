#ifndef VERIFY_H
#define VERIFY_H

#include <iostream>
#include <string>

class Verify
{
public:
    static bool isLetter(const char a);
    static bool isCapital(const char a);
    static bool isLowercase(const char a);

    static bool isNumber(const char a);

    static bool isValidRegistration(std::string reg);
};


#endif
