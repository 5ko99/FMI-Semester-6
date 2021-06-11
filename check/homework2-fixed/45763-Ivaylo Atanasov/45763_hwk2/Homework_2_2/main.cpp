#include "CommandController/CommandController.hpp"

int main(int argc, char** argv) {
    
    if(argc == 1){
        CommandController cmdCon;
        cmdCon.startReading();
    } else if(argc >= 2){
        CommandController cmdCon(argv[1]);
        cmdCon.startReading();
    }    
    return 0;
}
