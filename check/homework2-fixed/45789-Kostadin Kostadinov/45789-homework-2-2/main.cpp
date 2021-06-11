#include "./VPAllocator/VPAllocator.hpp"
#include "./CommandHandler/CommandHandler.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    VPAllocator vpa;

    if (argc>= 2) {
        CommandHandler command_UI(vpa, argv[1]);
        command_UI.run();
    } else {
        CommandHandler command_UI(vpa);
        command_UI.run();
    }

    
    return 0;
}
