#ifndef Vehicle_hpp
#define Vehicle_hpp

#include "../Registration/Registration.hpp"
#include "../Person/Person.hpp"

class Person;
class Vehicle{
private:
    friend class Person;
    
    Registration registration;
    std::string description;
    Person* owner;
    
    void copy(const Vehicle& veh);
public:
    Vehicle(const Registration& reg, const std::string& str);
    
    bool operator==(const Vehicle& veh) const;
    
    Person& getOwner() const;
    Person* getOwnerPtr() const;
    const Registration& getReg() const;
    const std::string& getDesc() const;
    
    void print() const;
    void printWithOwner() const;
};


#endif
