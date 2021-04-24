#include "Node.h"

#include <utility>
Node::Node(const State& _state, std::shared_ptr<Node>  _parent, unsigned int _depth)
    : state(_state), parent(std::move(_parent)), depth(_depth){}

unsigned int Node::getDepth() const {
    return depth;
}

std::shared_ptr<Node> Node::getParent() {
    return parent;
}

const std::shared_ptr<Node>& Node::getParent() const {
    return parent;
}

const State & Node::getState() const {
    return state;
}

void Node::setParent(Node *node) {
    parent.reset(node);
}

void Node::setParent(std::shared_ptr<Node> node) {
    parent = std::move(node);
}

void Node::print(std::ostream &out) const {
    state.printState(out);
    out<<"Depth:"<<depth<<'\n';
}

bool operator==(const Node &lhs, const Node &rhs) {
    return lhs.getState() == rhs.getState();
}
bool operator!=(const Node &lhs, const Node &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.getDepth() < rhs.getDepth();
}

bool operator>(const Node &lhs, const Node &rhs) {
    return lhs.getDepth() > rhs.getDepth();
}