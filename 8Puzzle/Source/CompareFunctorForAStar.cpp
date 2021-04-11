#include "CompareFunctorForAStar.h"
#include "State.h"

bool CompareFunctorForAStar::operator()(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2) const {
    int cost1 = (node1->getState()).manhattanCost() + (node1->getState()).hammingCost()
            + (node1->getDepth());
    int cost2 = (node2->getState()).manhattanCost() + (node2->getState()).hammingCost()
                + (node2->getDepth());
    return cost1<cost2;
}