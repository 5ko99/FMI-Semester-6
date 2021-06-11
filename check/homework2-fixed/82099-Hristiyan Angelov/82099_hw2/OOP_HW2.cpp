#include <iostream>
#include "Console.h"

int main(int argc, const char* argv[]) {
    Console* console;
    if (argc >= 2) {
        std::ifstream inFile;
        inFile.open(argv[2]);
        console = new Console(inFile);
        console->load();
        std::cout << "FILE LOADED!\n";
    }
    else {
        console = new Console(std::cin);
    }
    console->start();
    return 0;
}
