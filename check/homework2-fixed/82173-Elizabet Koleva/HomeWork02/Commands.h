#ifndef COMMANDS_H
#define COMMANDS_H

#include "Vehicle.h"
#include <limits>

class Commands {

private:

    string userCommand;

    unsigned int countLengthTillSpace(const string& source, const size_t& startPos) const; // Counting the length of a word

    void capitalize(string& what); // Capitalizing letters, can't use the Interaction static one because I dont want to include it here

    void checkAnswer(string& answer); // Which answer has the user chosen

    void removeSpaces(string& line);


public:
    Commands();

    //Commands(string userInput);

    string getCommand(); // Test purposes, in order to check operator = wit Catch2

    static int getCarPosition(const string& regNumber, const std::vector<Vehicle*>& allVehicles); // getting a car's position in a vector, reusing it in Interaction

    static int personPosition(const unsigned int& ownerId, const std::vector<Person*>& people); // getting a person's position in a vector, reusing it in Interaction
    
    void addCar(size_t posRegNumb, size_t posDescrip, std::vector<Vehicle*>& allVehicles); // Commands as they should be -> adding a car into the vector

    void addPerson(size_t posFirstName, size_t posLastName, size_t posID, std::vector<Person*>& people); // Adding a person into the vector

    void acquireCar(size_t posOwnerId, size_t posRegNumb, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles); // Person possesses a car

    void releaseCar(size_t posOwnerId, size_t posRegNumb, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles); // Person changes its ownership of a car

    void removeObject(size_t positionOfWhat, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles); // removing an object

    Commands operator=(const string& userInput);
    
};



#endif
