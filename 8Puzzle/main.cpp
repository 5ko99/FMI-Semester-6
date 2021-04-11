#include <iostream>
#include"Solver.h"
#include<array>

static const std::array<short,SIZE> finalStateArr = {0,1,2,3,4,5,6,7,8};
static const State finalState = State(finalStateArr);

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
