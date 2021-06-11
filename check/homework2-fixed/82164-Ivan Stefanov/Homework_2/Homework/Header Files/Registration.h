#pragma once
#include <cstring>
#include <string>

class Registration {

    char reg[9]{};

    static bool isValid(const char *str);
public:
    explicit Registration(const char *str);
    bool operator==(const char *str) const;
    const char* c_str() const;
};
