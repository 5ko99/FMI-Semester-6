#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <iostream>
#include <cstddef>
class Registration
{
    static constexpr std::size_t MAX_SIZE=2+4+2;
    char regNum[MAX_SIZE+1];
public:
    Registration(const char* str);
    const char* getRegistration() const;
    bool operator==(const Registration& rhs) const;
    static bool isValid(const char* str);

};
    std::ostream& operator<<(std::ostream& os, const Registration& reg);

#endif
