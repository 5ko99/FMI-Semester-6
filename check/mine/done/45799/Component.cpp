//
// Created by tedo3637 on 14.06.21 г..
//

#include "Component.h"

Component::Component() : label(""), currentPrice(0){
}

Component::Component(std::string &label, double price)
:label(label), currentPrice(price){

}

void Component::output(std::ostream &out) const {
    if(out.good()){
        out << "Price: " << this->price() << " Label: " << this->label << "\n";
    }
}

double Component::price() const {
    return currentPrice;
}

Component::~Component() {
}
