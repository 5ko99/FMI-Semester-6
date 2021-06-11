

#ifndef PERSON
#define PERSON

#include<string>
#include<vector>
#include"vehicle.h"

class Person {
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> vehicles;

public:
    Person(std::string name, unsigned int id);  //constructor for person
    Person(const Person& other);                //copy constructor
    Person& operator =(const Person& other);    //the assignment operator                
    std::string getName() const;                //getter for the name
    unsigned int getId() const;                 //getter for the id
    void addVehicle(Vehicle* vehicle);          //function which adds vehicle in the collection of the person
    void releaseVehicle(std::string id);        //function which removes the vehicle with the same registration from the collection of the person
    bool isHeHasNoVehicles() const;             //function which checks if the person has any vehicles in the collection
    std::vector<Vehicle*>& getVehicles();       //getter for the vehicles in the collection
    void printPerson() const;                   //function which prints the information of the person
    void printTheVehicles() const;              //function which prints the information of the vehicles in the collection of the person

};

#endif
