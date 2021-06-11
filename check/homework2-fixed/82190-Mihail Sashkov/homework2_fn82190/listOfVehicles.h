
#ifndef LIST_OF_VEHICLES
#define LIST_OF_VEHICLES

#include"vehicle.h"
#include"listOfPeople.h"
#include<vector>

//helper class to contain all vehicles in the program

class ListOfVehicles {
private:
    std::vector<Vehicle> allVehicles;              //container for all vehicles

public:
    void addVehicles(const Vehicle& vehicle);      //function which adds vehicle in the program
    Vehicle* getVehicle(std::string id);           //getter for vehicle with the same id
    void addOwner(Person* owner, std::string id);  //function which adds owner for the vehicle with the same id
    void releasePerson(std::string id);            //function which removes the owner of the vehicle with the same id
    void removeVehicle(std::string id);            //function which removes the vehicle with the same id from the program
    void printVehicles() const;                    //function which prints the vehicles in the container
    bool empty() const;                            //function for checking if the container is empty
    std::size_t count() const;                     //getter for the count of vehicles

};


#endif
