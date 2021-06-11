#include "registration.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

using Validator = int (*)(int);

Registration::Registration(const std::string &reg) {
    if (!validate(reg)) throw std::runtime_error("Error: Invalid registration");

    m_reg = reg;
}

bool Registration::validate(const std::string &reg) {
    const Validator validators[9] = {std::isupper, std::isupper, std::isdigit, std::isdigit, std::isdigit, std::isdigit, std::isupper, std::isupper};
    const Validator *check = reg.size() == 8 ? validators : validators + 1;

    for (int i = 0; i < reg.size(); i++) {
        if (!check[i](reg[i])) return false;
    }

    return true;
}

std::string Registration::to_string() const { return m_reg; }
