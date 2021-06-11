#ifndef Registration_hpp
#define Registration_hpp

#include <iostream>

using std::size_t;

class Registration{
private:
    char regArr[9];
    bool regIsValid(const char* str);
    bool charIsNum(const char& c);
    bool charIsLet(const char& c);
public:
    Registration() = delete;
    Registration(const char* str);
    
    Registration& operator=(const char* str);
    Registration& operator=(const Registration& reg);
    
    bool operator==(const char* str) const;
    bool operator==(const Registration& str) const;
    bool operator==(const std::string& str) const;
    const char* toCharArr() const;
};


#endif

