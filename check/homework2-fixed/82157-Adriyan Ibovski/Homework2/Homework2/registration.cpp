#include "Registration.h"
#include <iostream>
bool Registration::checkReg(const string& reg) {
    short idx = 0;
    while('A' <= reg[idx] && reg[idx] <= 'Z'
        || 'a' <= reg[idx] && reg[idx] <= 'z') idx++;
    if(idx == 0 || idx > 2) return false;
    short old_idx = idx;
    while('0' <= reg[idx] && reg[idx] <= '9') idx++;
    if(idx - old_idx != 4) return false;

    old_idx = idx;
    while('A' <= reg[idx] && reg[idx] <= 'Z'
          || 'a' <= reg[idx] && reg[idx] <= 'z') idx++;

    return idx - old_idx == 2;
}

Registration::Registration(const string &reg) {
    if(checkReg(reg))
        this->m_reg = reg;
    else throw std::invalid_argument("Invalid registration");
}

Registration::~Registration() {
    this->m_reg.clear();
}

Registration::Registration(const Registration &other) {
    this->m_reg = other.m_reg;
}

string Registration::getString() const {
    return this->m_reg;
}

bool Registration::operator==(const Registration &other) {
    return this->m_reg == other.m_reg;
}
