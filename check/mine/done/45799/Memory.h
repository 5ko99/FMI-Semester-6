//
// Created by tedo3637 on 14.06.21 г..
//

#ifndef UNTITLED8_MEMORY_H
#define UNTITLED8_MEMORY_H

#include <iostream>
#include "Component.h"

class Memory : public Component{
private:
    unsigned short capacity;

    void setCapacity(unsigned short capacity);
public:
    Memory();
    Memory(std::string& label, unsigned short capacity);

    double price() const override;
};


#endif //UNTITLED8_MEMORY_H
