#include "Solver.h"

Solver::Solver(const State &_start, const State &_goal, TypeOfAlgorithm _type): goal(_goal), solved(false),type(_type) {
    NodePtr root(new Node(_start, nullptr, 0));
    openList.push_back(root);
}
