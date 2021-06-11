#ifndef FILE_COMMANDS_H
#define FILE_COMMANDS_H

#define VEHICLE 1
#define PERSON 2
#define VEHICLES_COM 4
#define PEOPLE_COM 8

#include "../Person/person.h"
#include "../Vehicle/vehicle.h"
#include "../DataContainer/data_container.h"
#include <vector>
#include <string>

class FileCommands
{
public:
    static void createVehicle(std::vector<Vehicle *> &list, std::string registration, std::string description);
    static void createPerson(std::vector<Person *> &list, std::string name, unsigned int id);
    static void acquire(std::string owner_id, std::string vehicle_id, std::vector<Person *> &peopleList, std::vector<Vehicle *> &vehicleList);
    static void release(std::string owner_id, std::string vehicle_id, std::vector<Person *> &peopleList);
    static void remove(std::string input, std::vector<Vehicle *> &vehilceList, std::vector<Person *> &peopleList);
    static void save(std::string input, DataContainer &data);
    static void show(std::string input, DataContainer &data);
    static void initiateCommand(std::string fullCommand, DataContainer &data);
};

//helpers
std::size_t getPersonIndex(unsigned int id, std::vector<Person *> &list);
std::size_t getVehicleIndex(std::string registration, std::vector<Vehicle *> &list);
bool isNumber(std::string input);
int getType(std::string input);
void toUpper(std::string &input);

#endif
