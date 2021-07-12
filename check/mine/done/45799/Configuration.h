//
// Created by tedo3637 on 14.06.21 г..
//

#ifndef UNTITLED8_CONFIGURATION_H
#define UNTITLED8_CONFIGURATION_H

#include <vector>
#include "Component.h"

class Configuration {
private:
    std::vector<Component *> container;

    Configuration() = default;

    void insert(const Component *c);

public:

    static Configuration* create_configuration();

    Configuration(const Configuration &other) = delete;

    Configuration &operator=(const Configuration &other) = delete;

    ~Configuration();

    double price() const;

    std::size_t size() const;

    const Component &operator[](size_t index);

    friend std::ostream& operator<<(std::ostream &out, const Configuration &conf);

    Configuration* operator+=(const Component* component);
};


#endif //UNTITLED8_CONFIGURATION_H
