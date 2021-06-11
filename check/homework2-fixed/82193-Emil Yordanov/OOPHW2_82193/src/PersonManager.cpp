#include"PersonManager.h"

PersonManager::PersonManager() : people() { }

PersonManager::~PersonManager() {
    people.clear();
    people.shrink_to_fit();
}

bool PersonManager::AddPerson(Person* personToAdd) {
    try {
        this->people.push_back(personToAdd);

        return true;
    }
    catch(...) {
        return false;
    }
}

bool PersonManager::RemovePerson(unsigned int personId) {
    // It's enough to create a dummy vehicle with the given
    // registration and check if a vehicle in the collection
    // is equal to it (because for equality we only check registrations)
    Person dummyPerson = Person("", personId);

    for (size_t iterator = 0; iterator < this->people.size(); iterator++)
    {
        if(*this->people[iterator] == dummyPerson) {
            if(this->people[iterator]->IsOwner()) {
                std::cout << "Cannot remove a person that owns vehicles!" << std::endl;

                return false;
            }

            this->people.erase(this->people.begin() + iterator, this->people.begin() + (iterator + 1));

            return true;
        }
    }

    std::cout << "No such vehicle was found in the collection!" << std::endl;

    return false;
}

Person* PersonManager::GetPersonById(unsigned int personId) {
    // It's enough to create a dummy person with the given
    // id and check if a person in the collection
    // is equal to it (because for equality we only check ids)
    Person dummyPerson = Person("", personId);

    for (size_t iterator = 0; iterator < this->people.size(); iterator++)
    {
        if(*this->people[iterator] == dummyPerson) {
            return this->people[iterator];
        }
    }
}

std::vector<Person*> PersonManager::GetAll() {
    return this->people;
}
