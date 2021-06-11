#ifndef DATA_CONTAINER
#define DATA_CONTAINER

#include <vector>
#include <string>
#include "../Person/person.h"
#include "../Vehicle/vehicle.h"

class DataContainer
{
public:
    std::vector<Person *> peopleList;
    std::vector<Vehicle *> vehiclesList;

    //file operations
    void write(std::string path) const;
    void read(std::string path);
    
    //console operations
    void printVehicles() const;
    void printPeople() const;

    ~DataContainer();
};

#endif
