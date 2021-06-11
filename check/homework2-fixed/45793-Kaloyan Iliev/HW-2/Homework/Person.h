#ifndef PERSON_H
#define PERSON_H

class Vehicle;
class Person {
public:
    Person(const string& name, const unsigned int& id);
    ~Person()                              = default;
    Person(const Person& other)            = default;
    Person& operator=(const Person& other) = default;

    friend ostream& operator<<(ostream& out, const Person& per);

    const unsigned int getId();
    const string getName();
    void addVehicle(Vehicle* veh);
    void removeVehicle(Vehicle veh);
    void printOwnedVehicles();

    Vehicle* getVehicle(unsigned int pos);
    size_t getVehCnt();

private:
    string name;
    unsigned int id;
    vector<Vehicle*> vehicles;
};

#endif
