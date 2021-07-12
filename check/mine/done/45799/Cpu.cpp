//
// Created by tedo3637 on 14.06.21 г..
//

#include "Cpu.h"

Cpu::Cpu() : Component() {
}

Cpu::Cpu(std::string &label, unsigned short cores, double clockSpeed)
        : Component(label, 0) {
    setCores(cores);
    this->clockSpeed = clockSpeed;
}

double Cpu::price() const {
    return this->cores * 29.99;
}

void Cpu::setCores(unsigned short cores) {
    if(cores > 8 || cores < 1){
        throw std::invalid_argument("Cores must be between 1 and 8!");
    }

    Cpu::cores = cores;
}
