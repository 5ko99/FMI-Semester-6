//
// Created by tedo3637 on 14.06.21 г..
//

#include "Configuration.h"
#include "Utils.cpp"

double Configuration::price() const {
    double result = 0;

    size_t len = this->container.size();
    for (int i = 0; i < len; ++i) {
        result += container[i]->price();
    }

    return result;
}

std::size_t Configuration::size() const {
    return this->container.size();
}

const Component& Configuration::operator[](size_t index) {
    if(index < 0 || index > this->container.size()){
        throw std::invalid_argument("Index out of bonds!");
    }

    return *this->container[index];

}

void Configuration::insert(const Component *c) {
    size_t len = this->container.size();

    if(len == 0){
        this->container.push_back(const_cast<Component*>(c));
    }

    for (int i = 0; i < len; ++i) {
        if(typeid(*this->container[i]).hash_code() == typeid(c).hash_code()){
            throw std::invalid_argument("This type already exist!");
        }else {
            this->container.push_back(const_cast<Component*>(c));
        }
    }
}

Configuration::~Configuration() {
    size_t len = this->container.size();

    for (int i = 0; i < len; ++i) {
        delete this->container[i];
    }
}

std::ostream &operator<<(std::ostream &out, const Configuration &conf) {
    size_t len = conf.size();

    for (int i = 0; i < len; ++i) {
        conf.container[i]->output(out);
    }

    out << "\nCalculated price: " << conf.price() << "\n";
    return out;
}

Configuration* Configuration::operator+=(const Component* component) {
    this->insert(component);

    return this;
}

Configuration* Configuration::create_configuration() {
    Configuration* ret = new Configuration();
    Component* tempComp;

    char c;
    while(1){
        tempComp = Utils::create_component();
        if(tempComp){
            *ret += tempComp;
        }

        std::cout << "\nType 'q' to exit or 'p' to proceed.\n";
        std::cin >> c;
        if(c == 'q'){
            break;
        }
    }

    return ret;
}

