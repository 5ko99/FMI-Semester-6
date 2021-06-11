#ifndef CMD_H
#define CMD_H

enum showTYPE {
    PEOPLE,
    VEHICLES,
};

class Command {
public:
    Command() = default;
    Command(const Command& other) = default;
    Command& operator=(const Command& other) = default;
    ~Command() = default;  

    void addVehicle(Registration& reg, const string& des);
    void addPerson(const string& name, const unsigned int& id);
    void release(const unsigned int& ownerId, const Registration& vehicleId);
    void acquire(const unsigned int& ownerId, const Registration& vehicleId);
    void remove(const unsigned int& ownerId);
    void remove(const Registration& vehicleId);
    void save(const string& fileName);
    void show(showTYPE type);
    void showPerInfo(const unsigned int& ownerId);
    void showVehInfo(const Registration& vehicleId);

    //vector<Person> People;
    //vector<Vehicle> Vehicles;
private:
   vector<Person> People;
   vector<Vehicle> Vehicles;
};

#endif
