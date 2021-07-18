//
// Created by tedo3637 on 14.06.21 г..
//

#ifndef UNTITLED8_COMPONENT_H
#define UNTITLED8_COMPONENT_H

#include <iostream>

class Component {
private:
    std::string label;
    double currentPrice;

public:
    Component();
    Component(std::string& label, double price);
    virtual ~Component();

    virtual double price() const;
    void output(std::ostream& out) const;

};


#endif //UNTITLED8_COMPONENT_H
