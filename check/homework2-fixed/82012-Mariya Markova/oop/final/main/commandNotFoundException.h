#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class CommandNotFoundException : public std::runtime_error
{
public:
    CommandNotFoundException();
};
