#pragma once

#include <iostream>

class FileProblem : public std::exception
{
    const char* what() const throw()
    {
        return "Problem with opening the file";
    }
};

