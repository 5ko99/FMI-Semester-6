#include <iostream>
#include "Command.h"

Command* Command::instance = 0;

int main(int argc, char* argv[]) {
    Command* cmparser = cmparser->getInstance();
    string line;
    if(argc > 1){
        std::ifstream file(argv[1]);
        if(file.is_open()){
            while(std::getline(file,line)){
                cmparser->readLine(line);
            }
            file.close();;
        }
        else{
            std::cout<<"File could not open\n";
        }
    }
    line = "";
    while (line != "exit"){
        std::cout<<"Enter a command \n";
        std::getline(std::cin,line);
        try{
            cmparser->execute(line);
        }
        catch(std::exception &e){
            std::cout<<e.what()<<"\n";
        }
    }
    return 0;
}
