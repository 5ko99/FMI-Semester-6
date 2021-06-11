#ifndef REGISTRATION
#define REGISTRATION

#include <iostream>
#include <string>

class Registration
{
    std::string str;

    friend std::ostream& operator<<(std::ostream& out, const Registration& reg);

    bool validate(const std::string& str);

public:

    Registration() = default;

    Registration(const std::string& str);

    Registration(const Registration& other);

    bool operator==(const Registration& other);

    const std::string getString() const;

};

#endif
