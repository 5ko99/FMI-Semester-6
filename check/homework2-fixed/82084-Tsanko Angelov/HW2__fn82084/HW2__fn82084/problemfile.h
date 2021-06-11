#pragma once

#include <iostream>

class ProblemFile : public std::exception
{
    const char* what() const throw()
    {
        return "Problem with opening the file";
    }
};
