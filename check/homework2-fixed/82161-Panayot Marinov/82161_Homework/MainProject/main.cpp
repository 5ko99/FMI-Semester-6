#include <iostream>
#include "Headers/Engine.h"
#include <stdexcept>


using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
    Engine engine;
    try {
        engine.run(argc, argv);
    }
    catch(std::invalid_argument e) {
        std::cerr<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}
