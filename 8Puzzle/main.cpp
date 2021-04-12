#include <iostream>
#include"Solver.h"
#include<array>

#define ASTAR 0
#define BestFS 1

int main() {
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;
    srand(time(nullptr));
    State goal(std::array<short,SIZE>{0,1,2,
                                      3,4,5,
                                      6,7,8});
    State start(true);
    while (!Solver::isSolvable(start)) {
        start.printState(std::cout);
        std::cout<<"Puzzle is unsolvable! To create another start press enter!\n";
        std::cin.get();
        start.randomize();
    }
    std::cout<<"Start state\n";
    start.printState(std::cout);
    std::cout<<"Solving puzzle...\n";
    short alg;
    std::cout<<"Enter 0 for A* or 1 for Best First Search\n";
    std::cin>>alg;
    NodeList solution;
    if(alg==ASTAR) {
        Solver solver(start,goal,TypeOfAlgorithm::AStar);
        solution = solver.solve();
    } else if(alg==BestFS) {
        Solver solver(start,goal,TypeOfAlgorithm::BEST_FIRST_SEARCH);
        solution = solver.solve();
    } else {
        std::cerr<<"Wrong choose of algorithm.\n You must enter 0 or 1!\n";
        return 1;
    }
    Solver::printSolution(solution,std::cout);
    return 0;
}
