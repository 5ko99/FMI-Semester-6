#pragma once
#include <string>

class Validation
{
    public:
    Validation() = delete;
    static bool is_letter(char c);
    static bool is_digit(char c);
    static std::string to_upper_all(std::string);
    static char to_upper(char c);
};

