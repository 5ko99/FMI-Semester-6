#include"../Headers/Engine.h"
#include <stdexcept>
#include <iostream>

#define CONSOLE std::cin

void Engine::run(int argc, char** argv) {
    if(argc > 1) {
        file.open(argv[1]); //Path var is argv[1].
        if(!file.good()) {
            throw std::invalid_argument("File cannot be opened.");
        }
    }
    while(!commandExecutor.isExitCommand()) {
        try{
            if(argc > 1 && !file.eof()) {
                try{
                    commandParser.parseCommand(file);
                }
                catch(std::invalid_argument e) {
                    std::cout<<e.what()<<std::endl;
                }
                catch(std::out_of_range e) {
                }
            }
            else {
                try{
                    commandParser.parseCommand(CONSOLE);
                }
                catch(std::invalid_argument e) {
                    std::cout<<e.what()<<std::endl;
                }
                catch(std::out_of_range e) {
                }
            }

            commandExecutor.executeCommand(
            commandParser.getCommandType(), 
            commandParser.getCopyOfArguments());
        }
        catch(std::exception e) {
            std::cout<<"in 3"<<std::endl;
            std::cout<<e.what()<<std::endl;
        }     
    }
    file.close();
}
