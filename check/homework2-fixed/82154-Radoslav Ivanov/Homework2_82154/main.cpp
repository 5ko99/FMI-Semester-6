#include <iostream>
#include "program.h"

int main (int argc, char* argv[])
{
    Program p;
    if (argc == 2){
        std::ifstream readFile(argv[1]);
        if (readFile.is_open()){
            p.readFromFile(readFile);
            readFile.close();
        }
        else std::cerr << "Error loading file\n";
    }
    else if (argc > 2) std::cerr << "Unexpected count of arguments!\n";
    p.Go();
    return 0;
}
