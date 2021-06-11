
#ifndef LIST_OF_PEOPLE
#define LIST_OF_PEOPLE

#include<vector>
#include"person.h"

//helper class which contain all people in the program

class ListOfPeople {
private:
    std::vector<Person> people;                                          //container for the people

public:
    void addPerson(const Person& person);                                //function which adds person in the program
    Person* getOwner(unsigned int number);                               //getter for person with the same number
    void addVehicleForThePerson(Vehicle* vehicle, unsigned int number);  //function which adds a vehicle in the collection of the person with the same number
    void releaseVehicleFromPerson(unsigned int number, std::string id);  //function which removes a vehicle with the same id from the collection of the person with the same number
    void removePerson(unsigned int number);                              //function which removes the person with the same number from the program
    void printPeople() const;                                            //function which print all people
    bool empty() const;                                                  //function for checking if the container for the people is empty
    std::size_t count() const;                                           //getter for the count of the people

};


#endif
