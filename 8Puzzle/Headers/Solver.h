#pragma once
#include<memory>
#include <vector>
#include "Node.h"
#include "State.h"
#include<array>
#include<vector>


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

    void expandNode(const NodePtr& current);

    inline bool isSolved() const;

    static bool contains(const State& state, const NodeList& arr);

    static bool isSolvable(const State& state);

    NodePtr getNextNode();

    std::vector<NodePtr> solve();

    static void printSolution(const NodeList& solution, std::ostream& stream);
private:
   [[nodiscard]] std::array<short,4> getNeighboursOfEmpty(const NodePtr& node) const;
};

