#pragma once
#include "ICommand.h"
#include <string>
#include <vector>

class Console
{
public:
    static void run(System& receiver, std::istream& in = std::cin);
};
