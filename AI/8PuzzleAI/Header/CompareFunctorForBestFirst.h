#pragma once
#include<memory>
#include "Node.h"
#define ptr std::shared_ptr<Node>

struct CompareFunctorForBestFirst {
    bool operator()(const ptr& node1,const ptr& node2) const;
};
