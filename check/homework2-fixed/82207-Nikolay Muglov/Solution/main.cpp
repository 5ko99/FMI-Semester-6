#include <iostream>
#include <fstream>
#include "Solution.h"

int main(int argc, char **argv)
{
    Solution sol;

    if (argc == 2)
    {
        std::fstream file(argv[1], std::fstream::in);
        while (!file.eof())
        {
            sol.execCommand(file);
        }
        file.close();
    }

    while (true)
    {
        sol.execCommand(std::cin);
    }
    return 0;
}
