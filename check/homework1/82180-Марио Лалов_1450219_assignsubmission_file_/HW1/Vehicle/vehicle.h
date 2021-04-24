#ifndef VEHICHLE_H
#define VEHICHLE_H
#include "../MyString/MyString.h"

class Vehicle
{
private:
    MyString reg_number;
    MyString description;
    //how many parking spaces are needed
    std::size_t parking_spaces = 0; 

public:
    Vehicle(const char *in_registration, const char *in_description, std::size_t in_spaces); //parameter constructor
    const char *getRegistration() const;                                                     //get reg_num as char*
    const char *getDescription() const;                                                      //get description as char*
    std::size_t getSpaces() const;                                                           //get spaces occupied
    Vehicle &operator=(const Vehicle &other);
    bool operator==(const Vehicle &other) const;
    void print() const;
};

#endif