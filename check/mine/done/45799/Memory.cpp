//
// Created by tedo3637 on 14.06.21 г..
//

#include "Memory.h"

Memory::Memory() : Component() {
}

Memory::Memory(std::string &label, unsigned short capacity)
: Component(label, 0){
    setCapacity(capacity);
}

void Memory::setCapacity(unsigned short capacity) {
    if(capacity < 1 || capacity > 10000){
        throw std::invalid_argument("Capacity must be between 1 and 10000!");
    }

    this->capacity = capacity;
}

double Memory::price() const {
    return this->capacity * 89.99;
}
