#pragma once
#include "State.h"
#include<memory>
#include<iostream>
class Node {
private:
    State state;
    std::shared_ptr<Node> parent;
    unsigned int depth;
public:
    Node(const State& state, std::shared_ptr<Node> parent, unsigned int depth=0);
    void setParent(Node* node);
    void setParent(std::shared_ptr<Node> node);
    std::shared_ptr<Node> getParent();
    const std::shared_ptr<Node>& getParent() const;
    const State& getState() const;
    unsigned int getDepth() const;

    friend bool operator==(const Node &lhs, const Node &rhs);
    friend bool operator!=(const Node &lhs, const Node &rhs);
    friend bool operator<(const Node &lhs, const Node &rhs);
    friend bool operator>(const Node &lhs, const Node &rhs);

    void print(std::ostream& out) const;
};



