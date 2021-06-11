#include "Verify.hpp"

bool Verify::isLetter(const char a)
{
    if(a >= 'a' && a<= 'z' || a >= 'A' && a <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isCapital(const char a)
{
    if(a >= 'A' && a<='Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isLowercase(const char a)
{
    if(a >= 'a' && a<='z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isNumber(const char a)
{
    if(a >= '0' && a<='9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isValidRegistration(std::string reg)
{
    if(reg.length() == 7)
        {
            if(Verify::isCapital(reg[0]))
            {
                for(std::size_t i = 1; i < 5; ++i)
                {
                    if(!Verify::isNumber(reg[i]))
                    {
                        return false;
                    }
                }
                for(std::size_t i = 5; i < 7; ++i)
                {
                    if(!Verify::isCapital(reg[i]))
                    {
                        return false;
                    }
                }
                return true;
            }
            else 
            {
                return false;
            }
        }
        if(reg.length() == 8)
        {
            if(Verify::isCapital(reg[0]) && Verify::isCapital(reg[1]))
            {
                for(std::size_t i = 2; i < 6; ++i)
                {
                    if(!Verify::isNumber(reg[i]))
                    {
                        return false;
                    }
                }
                for(std::size_t i = 6; i < 8; ++i)
                {
                    if(!Verify::isCapital(reg[i]))
                    {
                        return false;
                    }
                }
                return true;
            }
            else 
            {
                return false;
            }
        }
        if(reg.length() != 8 && reg.length() != 7)
        {
            return false;
        }
}
