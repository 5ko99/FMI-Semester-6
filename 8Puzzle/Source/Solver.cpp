#include "Solver.h"
#include<ranges>
#include <functional>
#include <algorithm>

typedef std::shared_ptr<Node> NodePtr;

Solver::Solver(const State &_start, const State &_goal, TypeOfAlgorithm _type) : goal(_goal), solved(false),
                                                                                 type(_type) {
    NodePtr root(new Node(_start, nullptr, 0));
    openList.push_back(root);
}

std::array<short, 4> Solver::getNeighboursOfEmpty(const NodePtr &nodePtr) {
    short emptyPos = nodePtr->getState().findEmptyTile();
    std::array<short, 4> directions{};//0-up,1-down,2-left,3-right
    directions[0] = emptyPos - 3 >= 0 ? emptyPos - 3 : -1;
    directions[1] = emptyPos + 3 < SIZE ? emptyPos + 3 : -1;
    directions[2] = (emptyPos - 1) >= 0 && emptyPos % ROWS != 0 ? emptyPos - 1 : -1;
    directions[3] = (emptyPos + 1) < SIZE && emptyPos % ROWS != 2 ? emptyPos + 1 : -1;
    return directions;
}

bool Solver::contains(const State &state, const StateVector &closedList) {
    auto equalTo = [](const State &state) {
        return [state](const State &state1) { return state == state1; };
    };
    return std::ranges::any_of(closedList, equalTo(state));
}

void Solver::expandNode(const NodePtr &current) {
    if (current->getState() == goal) {
        solved = true;
        return;
    }
    const std::array<short, 4> neighbours = getNeighboursOfEmpty(current);

    for (short neigh : neighbours) {
        if (neigh == -1)
            continue;
        State state = current->getState();
        state.swapWithEmpty(neigh);
        if (!contains(state, closedList)) {
            NodePtr newStatePointer(new Node(state, current, current->getDepth() + 1));
            openList.push_back(newStatePointer);
        }
    }
}

bool Solver::isSolvable(const State &state) {
    short inv_count = 0;
    const std::array<short, SIZE> arr = state.getArray();
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
    return (inv_count % 2 == 0);
}

NodePtr Solver::getNextNode() {
    if (openList.empty()) return nullptr;
    NodePtr curr;
    switch (type) {
        case TypeOfAlgorithm::AStar: {
            auto curr_itr(std::min_element(openList.begin(),
                                           openList.end(),
                                           CompareFunctorForAStar()));
            if (curr_itr == openList.end()) return nullptr;
            curr = *curr_itr;
            openList.erase(curr_itr);
            closedList.push_back(curr->getState());
            break;
        }
        case TypeOfAlgorithm::BEST_FIRST_SEARCH: {
            auto curr_itr(std::min_element(openList.begin(),
                                           openList.end(),
                                           CompareFunctorForAStar()));
            if (curr_itr == openList.end()) return nullptr;

            curr = *curr_itr;

            openList.erase(curr_itr);
            closedList.push_back(curr->getState());
            break;
        }
    }
    return curr;
}

bool Solver::isSolved() const {
    return solved;
}

std::vector<NodePtr> Solver::solve() {
    NodePtr node;
    while (!isSolved()) {
        node = getNextNode();
        expandNode(node);
    }
    std::vector<NodePtr> solution;
    do {
        solution.push_back(node);
        node = node->getParent();
    } while (node != nullptr);
    return solution;
}

void Solver::printSolution(const std::vector<NodePtr> &solution, std::ostream &stream) {
    stream << "Puzzle solved in " << solution.size() - 1 << " steps.\n Solution is:\n";
    for (const auto &state: solution) {
        state->getState().printState(stream);
    }
    stream << '\n';
}
