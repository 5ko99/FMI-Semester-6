#ifndef PERSON_HOLDER_H
#define PERSON_HOLDER_H

#include <vector>
#include "../../Person/Person.h"

// Contains objects of type Person in a vector
// and functions, through which they can be accessed, removed,
// or new ones can be added.
// The data for a person cannot be changed trough any of the functions.
class PersonHolder {
    private:
        std::vector<Person> people;

        std::size_t getIndexByID(unsigned int id);

        void printPersonAt(std::size_t i);
        void printPersonsVehiclesAt(std::size_t i);
    public:
        PersonHolder();

        PersonHolder* operator*();

        // Throws an exception if a person with the given ID is already in the holder.
        void add(Person person);

        // Throws an exception when there is no person with the given ID.
        // Does not clear the owner of the vehicles, owned by the removed person.
        void removeByID(unsigned int id);

        // Does not allocate memory.
        // Delete should not be called on the returned *.
        Person* getByID(unsigned int id);
        const std::vector<Person> getAllPeople() const;

        void printAll();
        void printDetailed(unsigned int id);
};

#endif
