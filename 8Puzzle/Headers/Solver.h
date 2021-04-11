#pragma once
#include<memory>
#include <vector>
#include "Node.h"
#include "State.h"
#include<array>

enum class TypeOfAlgorithm {
    BEST_FIRST_SEARCH = 0,
    AStar
};

class Solver {
private:
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;
    NodeList openList;
    NodeList closedList;
    const State& goal;
    bool solved;
    TypeOfAlgorithm type;
public:
    Solver(const State& start, const State& goal, TypeOfAlgorithm type = TypeOfAlgorithm::AStar);
};

