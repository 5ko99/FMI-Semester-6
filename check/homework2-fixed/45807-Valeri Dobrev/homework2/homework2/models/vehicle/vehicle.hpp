#pragma once

#include "../registration/registration.hpp"
class Person;


class Vehicle{
    Registration registration;
    std::string description;
    Person* owner = nullptr;
public:

    /**
     * Constructor 
     * @param registration 
     * @param description 
     */
    Vehicle(const char* registration, const std::string& description);

    /**
     * Destructor
     */
    ~Vehicle();
    
    /**
     * Copy constructor.
     * @param other
     */
    Vehicle(const Vehicle& other);

    /**
     * Assign operator
     * @param other
     */
    Vehicle& operator=(const Vehicle& other);

    /**
     * Overloaded operator == that checks if the Vehicle's registration is equal to the given one
     * @param registration
     */
    const bool operator==(const char* registration) const;

    /**
     * Getters
     */
    const Registration& getId() const;

    const std::string& getDescription() const;

    const Person* getOwner() const;

    /**
     * Method that checks if the vehicle has relations with a person
     */
    const bool needConfirmToDelete()const;

    /**
     * Method that sets the vehicle owner to nullptr and removes it from the owner's list of vehicles
     * This method is called when the vehicle has relation with a person and the user wants to delete the vehicle
     */
    void prepareForDelete();

    /**
     * Method that returns the name of the class
     */
    const static std::string getClassName();

    /**
     * Method that converts the registration to a string format
     */
    const std::string getIdToString() const;
    
    /**
     * Method that changes the vehicle owner and removes the vehicle from the owner's list 
     * 
     */
    void setOwner(Person* owner);

    /**
     * Method that puts Vehicle's information to the output stream
     * @param os
     * @param v
     */
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};
