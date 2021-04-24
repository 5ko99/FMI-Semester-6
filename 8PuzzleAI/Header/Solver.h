#pragma once
#include<memory>
#include <vector>
#include "Node.h"
#include "State.h"
#include<array>
#include<vector>
#include<set>
#include "../../8PuzzleAI/Header/CompareFunctorForAStar.h"
#include "CompareFunctorForBestFirst.h"


enum class TypeOfAlgorithm {
    BEST_FIRST_SEARCH = 0,
    AStar
};

class Solver {
private:
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<State> StateVector; //if it's not okay back to vector
    typedef std::vector<NodePtr> NodePtrVec;
    NodePtrVec openList;
    StateVector closedList;
    const State& goal;
    bool solved;
    TypeOfAlgorithm type;
public:
    Solver(const State& start, const State& goal, TypeOfAlgorithm type = TypeOfAlgorithm::AStar);

    void expandNode(const NodePtr& current);

    inline bool isSolved() const;

    static bool contains(const State& state, const StateVector& arr);

    static bool isSolvable(const State& state);

    NodePtr getNextNode();

    std::vector<NodePtr> solve();

    static void printSolution(const std::vector<NodePtr>& solution, std::ostream& stream);
private:
   [[nodiscard]] static std::array<short,4> getNeighboursOfEmpty(const NodePtr& node) ;
};

