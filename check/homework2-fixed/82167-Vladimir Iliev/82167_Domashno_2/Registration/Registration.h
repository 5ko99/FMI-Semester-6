#pragma once

#include <string>

class Registration {
protected:
    const std::string registration;

private:
    static bool isLetter(char a);
    static bool isDigit(char a);

public:
    Registration() = delete;
    explicit Registration(std::string reg);
    const std::string& getRegistration() const;

    static bool isValidRegistration(const std::string& registration);
};
