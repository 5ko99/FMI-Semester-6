#pragma once
#include <stdexcept>

class InvalidNumberOfArgumentsException : public std::runtime_error
{
public:
    InvalidNumberOfArgumentsException();
};
