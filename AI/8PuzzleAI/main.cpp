#include <iostream>
#include"Solver.h"
#include<array>

#define ASTAR 0
#define BestFS 1

const State goal(std::array<short,SIZE>{0,1,2,
                                  3,4,5,
                                  6,7,8});
int main() {
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;
    time_t t;
    srand((unsigned) time(&t));

    State start(true);
    while (!Solver::isSolvable(start)) {
        start.printState(std::cout);
        std::cout<<"Puzzle is unsolvable! To create another start press enter!";
        std::cin.get();
        start.randomize();
    }
    std::cout<<"Start state\n";
    start.printState(std::cout);
    short alg;
    std::cout<<"Enter 0 for A* or 1 for Best First Search: ";
    std::cin>>alg;
    NodeList solution;
    if(alg==ASTAR) {
        Solver solver(start,goal,TypeOfAlgorithm::AStar);
        std::cout<<"Solving puzzle...";
        solution = solver.solve();
    } else if(alg==BestFS) {
        Solver solver(start,goal,TypeOfAlgorithm::BEST_FIRST_SEARCH);
        std::cout<<"Solving puzzle...";
        solution = solver.solve();
    } else {
        std::cerr<<"Wrong choose of algorithm.\n You must enter 0 or 1!\n";
        return 1;
    }
    std::cout<<'\n';
    Solver::printSolution(solution,std::cout);
    return 0;
}