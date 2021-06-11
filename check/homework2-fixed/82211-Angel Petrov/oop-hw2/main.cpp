#include <iostream>
#include <fstream>
#include "utils.h"

int main(int argc, char* argv[]) {

    Commands* cmnd = Commands::getInstance();
    Allocator* alloc = Allocator::getInstance();

    if(argc > 1) { 

        std::string dir (argv[1]);
        loadFile(alloc, cmnd, dir);
    }

    do {
        cmnd->readAndSplitInput();
        std::string command = cmnd->getCommand();

        if(command == "VEHICLE") {

            vehicle(alloc, cmnd);
        } 
        else if (command == "PERSON") {

            person(alloc, cmnd);
        }
        else if (command == "ACQUIRE" ){

            acquire(alloc, cmnd);
        } 
        else if (command == "RELEASE"){

            release(alloc, cmnd);
        } 
        else if (command == "REMOVE") {

            remove(alloc, cmnd);
        } 
        else if (command == "SAVE") {

            save(alloc, cmnd);
        } 
        else if (command == "SHOW") {

            show(alloc, cmnd);
        } 
        else if (command == "EXIT"){
           break;
        } 

    } while(true);

    return 0;
}
