#ifndef _REGISTRATION_HEADER_INCLUDE
#define _REGISTRATION_HEADER_INCLUDE

#include <string>

class Registration
{
private:
    std::string regNum;
public:
    Registration(std::string regNumber);
    bool isValidRegNum(std::string regNumber);
    const char* getRegNum() const;
};

#endif
