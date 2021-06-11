#pragma once
#include <istream>
class Registration
{
    char m_str[9];

public:
    static bool isValid(const char str[]);
    Registration();
    Registration(const char str[]);
    bool operator==(Registration &other) const;
    friend std::istream &operator>>(std::istream &in, Registration &reg)
    {
        in >> reg.m_str;
        if (!isValid(reg.m_str))
            throw std::invalid_argument("Invalid registration");
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const Registration &reg)
    {
        out << reg.m_str;
        return out;
    }
};
