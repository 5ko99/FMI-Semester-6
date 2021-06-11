#ifndef VEH_H
#define VEH_H

class Person;
class Vehicle {
public:
    Vehicle(const Registration& number, const string& description);
    ~Vehicle()                               = default;
    Vehicle(const Vehicle& other)            = default;
    Vehicle& operator=(const Vehicle& other) = default;

    bool operator==(const Vehicle& other) const;


    friend ostream& operator<<(ostream& out, const Vehicle& veh);

    void addOwner(Person* owner);
    Registration& getReg();
    string& getDes();
    void printOwner();
public:
    Person* owner;
private:
    Registration number;
    string description;
};

#endif
