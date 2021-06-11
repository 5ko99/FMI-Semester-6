#include "Registration.h"

bool Registration::isNumber(char input)
{
    if (input >= '0' && input <= '9')
        return true;
    return false;
}

bool Registration::isAChar(char input)
{
    if (input >= 'A' && input <= 'Z')
        return true;
    return false;
}

bool Registration::isValid(const char *arr)
{
    bool flag1 = true, flag2 = false, flag3 = false;

    for (int i = 0; i < 8; i++)
    {
        switch (i)
        {
        case 0:
            if (!isAChar(arr[i]))
                return false;
        case 1:
            if (isNumber(arr[i]))
            {
                if (isNumber(arr[i + 1]) && isNumber(arr[i + 2] && isNumber(arr[i + 3])))
                {
                    i += 3;
                    break;
                }
                else
                    return false;
            }
            if (!isAChar(arr[i]))
                return false;
        case 2:
            if (isNumber(arr[i]) && isNumber(arr[i + 1]) && isNumber(arr[i + 2] && isNumber(arr[i + 3])))
            {
                i += 3;
                break;
            }
            else
                return false;
        case 5:
            if (isAChar(arr[i]) && isAChar(arr[i + 1]))
            {
                i += 2;
                break;
            }
            else
                return false;
        }
    }
    return true;
}

void Registration::copy(const char *arr)
{
    if (isValid(arr))
    {
        empty();
        for (int i = 0; arr[i] != '/0'; i++)
        {
            number[i] = arr[i];
        }
    }
}

void Registration::empty()
{
    for (int i = 0; i < 8; i++)
    {
        number[i] = '/0';
    }
}

Registration::Registration(const char *arr)
{
    this->copy(arr);
}

Registration &Registration::operator=(const Registration &other)
{
    if (this != &other)
    {
        this->empty();
        this->copy(other.number);
    }
    return *this;
}

Registration::~Registration()
{
    delete number;
}

void Registration::setRegistration(const char *number)
{
    this->copy(number);
}

const char *Registration::getRegistration() const
{
    return number;
}

void Registration::print()
{
    for (int i = 0; i < 8; i++)
        std::cout << number[i];
}

bool Registration::isEmpty() const
{
    if (number[0] == '\0')
        return true;
    return false;
}
