
#include "MyString.h"
class Vehicle
{
public:
    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
    ~Vehicle();
private:
    MyString reg;
    MyString descr;
    std::size_t spaceTaken;
};

