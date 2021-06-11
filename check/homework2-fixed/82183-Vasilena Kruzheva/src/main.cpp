#include <iostream>
#include "../include/input.hpp"

int main(int argc, char* argv[])
{
    Input input;

    if(argc > 1)
    {
        input.loadFromFile(argv[1]);
    }
    
    while(input.read()) {}

    return 0;
}
