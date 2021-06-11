
#ifndef HW2_PERSON_H
#define HW2_PERSON_H
# include <string>
class Vehicle;
#ifndef VEHICLE_H
# define VEICLE_H
# include "Vehicle.h"
# endif
# include <vector>
class Person {
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> arr;
public:
    
    void setName(const std::string&);
    void setId(const unsigned int);
    Person(std::string, unsigned int);
    void print()const;
    void addVehicle( Vehicle*);
    void removeVehicles();
    void eraseAt(std::string);
    std::string getName()const;
    unsigned int getId()const;
    Vehicle* getVehicleAt(int)const;
    std::size_t vehicleCount()const;
};
#endif //HW2_PERSON_H
