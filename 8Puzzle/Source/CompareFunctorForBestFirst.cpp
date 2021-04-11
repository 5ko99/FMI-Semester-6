#include "CompareFunctorForBestFirst.h"
#include "State.h"
bool CompareFunctorForBestFirst::operator()(const std::shared_ptr<Node> &node1,
                                            const std::shared_ptr<Node> &node2) const {
    int cost1 = (node1->getState()).manhattanCost();
    int cost2 = (node2->getState()).manhattanCost();
    return cost1<cost2;
}