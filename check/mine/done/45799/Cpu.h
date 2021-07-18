//
// Created by tedo3637 on 14.06.21 г..
//

#ifndef UNTITLED8_CPU_H
#define UNTITLED8_CPU_H

#include <iostream>
#include "Component.h"

class Cpu : public Component{
private:
    unsigned short cores;
    double clockSpeed;
    void setCores(unsigned short cores);
public:
    Cpu();
    Cpu(std::string& label, unsigned short cores, double clockSpeed);

    double price() const override;
};


#endif //UNTITLED8_CPU_H
