#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"../../models/person/person.hpp"


/**
 * Template implemented by the vehicle and person factory. It is hybrid of Pool and Factory patterns
 * @class T - Vehicle or Person
 * @class I - the type of the Id of the object
 */
template <class T, class I> class Factory{
    std::vector<T*> elements;
    static Factory<T,I>* factory;
    
    /**
     * Method that gives access to the object with the given ID
     * @return nullptr if not found
     */
    T* findById(const I& id) const;

    /**
     * Default constructor
     */
    Factory();
public: 
    /**
     * Deleted the copy constructor and the assign operator
     */
    Factory(const Factory<T,I>& other) = delete;
    Factory& operator=(const Factory<T,I>& other) = delete;

    /**
     * Static method for retrieving the Factory instance
     */
    static Factory<T,I>* getInstance();

    /**
     * Method for freeing the resources allocated by the factory
     */
    void destroy();

   
    /**
     * Method that creates an objec of type T (Person/Vehicle)
     * @param id - the unique identifier of the object (unsigned for Person, char* for Vehicle)
     * @param s - the name of the Person or the description of the Vehicle 
     * @throw std::invalid_argument if the ID is null
     *                              if object with the given ID already exists
     */
    T* create(const I& id,const std::string& s);

    /**
     * Method that deletes an object by the provided ID
     * @param id - the unique identifier of the object (unsigned for Person, char* for Vehicle)
     * @param user_confirmation - if user_confirmation is false then if the object has owner(for Vehicles) or has vehicles(for Person) does not delete the object
     *                            if the user_confirmation is false and the object is not related with others it is deleted
     *                            if the user_confirmation is true the object is deleted
     * @throw std::invalid_argument if the object with the given ID is not found
     *                              if no user confirmation is received and the object is related
     * 
     */
    void remove(const I& id,const bool user_confirmation =false);

    /**
     * Retrieves a object by ID
     * @param id
     * @throw std::invalid_argument if object not found
     */
    const T* getById(const I& id) const;

    T* getById(const I& id);

    /**
     * Retrieves the total number of objects created
     */
    const size_t getNumberOfElements() const;  

    const std::vector<T*> getElements() const;
};
/**
 * Defining one of the use cases of the Factory. 
 * It is placed here so that when the factory file is included the PersonFactory can be used
 */
typedef Factory<Person, unsigned> PersonFactory;
typedef Factory<Vehicle,const char*> VehicleFactory;

