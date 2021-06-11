#pragma once

#include <vector>
#include "../vehicle/vehicle.hpp"


class Person{
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> vehicles;

    /** 
     * Method that removes a vehicle from the list of vehicles by Vehicle's  address
     * @param vehicle
     * @throw invalid_argument when nullptr is passed
     */
    void add(Vehicle* vehicle);

    /**
     * Method that removes vehicle from the list of vehicles by Vehicle's address
     * @param vehicle
     * @throw invalid_argument when nullptr is passed
     */
    void remove(Vehicle* vehicle);

    /**
     * Method that checks if the Person has the given Vehicle
     * @param vehicle
     */
    bool hasVehicle(const Vehicle* vehicle)const;
public:
   
    /**
     * Constructor 
     * @param name of the person
     * @param id - unique identifier of the person
     */
    Person(const unsigned int id,const std::string& name);

    /**
     * Destructor
     */
    ~Person();

    /** 
     * Copy constructor 
     * @param other
     */
    Person(const Person& other);

    /** 
     * Assign operator 
     * @param other
     */
    Person& operator=(const Person& other);
    

    /**
     * Overloaded operator for checking if the person's ID match the provided one
     * @param id 
     */
    bool operator==(const unsigned id) const;

    /**
     * Getters
     */
    const unsigned& getId() const;

    const std::string& getName()const;

    const std::vector<Vehicle*>& getVehicles() const;
    
    /**
     * Method that checks if the person has relations with vehicle     * 
     */
    const bool needConfirmToDelete() const;

    /**
     * Method that removes all vehicles and sets their owner to nullptr
     * This method is called when the person has relations wiht vehicles and the user wants to delete the person
     */
    void prepareForDelete();

    /**
     * Method that returns the name of the class
     */
    const static std::string getClassName();

    /**
     * Method that converts the ID to a string format
     */
    const std::string getIdToString()const;

    /**
     * Method that returns the number of vehicles that the person possess
     */
    const size_t getNumberOfVehicles() const;

    /**
     * Method that adds Vehicle to the vehicle list and set its owner to this
     * @param vehicle
     * @throw invalid_argument when nullptr is passed
     */
    void addVehicle(Vehicle* vehicle);

    /**
     * Method that removes Vehicle fromt the vehicle list and set the its owner to nullptr
     * @param vehicle
     * @throw invalid_argument when nullptr is passed
     * @throw invalid_argument when the person doesn't possess the given vehicle
     */
    void removeVehicle(Vehicle* vehicle);

    /**
     * This way the Vehicle's methods can access the Person's private methods and fields
     */
    friend class Vehicle;

    /**
     * Method that puts Person's information to the output stream
     * @param os
     * @param p
     */
    friend std::ostream& operator<<(std::ostream& os,const Person& p);
};
