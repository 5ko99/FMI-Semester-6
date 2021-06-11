#include "invalidNumberOfArgumentsException.h"

InvalidNumberOfArgumentsException::InvalidNumberOfArgumentsException()
    :std::runtime_error("Wrong number of arguments for this command!")
{}
