#include"listOfPeople.h"
#include<stdexcept>
#include<iostream>



void ListOfPeople::addPerson(const Person& person) {

    for(int i = 0; i < people.size(); i++) {

        if(people[i].getId() == person.getId()) {

            throw std::invalid_argument("In the list of people already excist a person with the same id!");

        }

    }

    people.push_back(person);

}

Person* ListOfPeople::getOwner(unsigned int number) {

    bool found = false;

    for(int i = 0; i < people.size(); i++) {

        if(people[i].getId() == number) {

            found = true;
            return &people[i];

        }
   
        if(i == people.size() - 1 && found == false) {
            throw "The information about the person you want is impossible to show because the person does not excist!";
        }

    }

}

void ListOfPeople::addVehicleForThePerson(Vehicle* vehicle, unsigned int number) {

    for(int i = 0; i < people.size(); i++) {

        if(people[i].getId() == number) {

            people[i].addVehicle(vehicle);

        }

    }

}

void ListOfPeople::releaseVehicleFromPerson(unsigned int number, std::string id) {

    for(int i = 0; i < people.size(); i++) {

        if(people[i].getId() == number) {

            people[i].releaseVehicle(id);

        }

    }

}

void ListOfPeople::removePerson(unsigned int number) {

    bool found = false;
    std::string answer;

    for(int i = 0; i < people.size(); i++) {

        if(people[i].getId() == number) {

            if(people[i].isHeHasNoVehicles() == false) {

                std::cout<<"The person has one or more vehicles in the garage. Are you sure that you want to remove this person? (yes/no)"<<std::endl;
                getline(std::cin, answer);

                if(answer.compare("yes") == 0) {

                    for(int j = 0; j < people[i].getVehicles().size(); j++) {

                        people[i].getVehicles()[j]->releaseOwner();

                    }

                    people.erase(people.begin() + i);

                }

                return;

            }

            people.erase(people.begin() + i);
            found = true;

        }

        if(i == people.size() - 1 && found == false) {
            throw "The person does not excist!";
        }

    }

    if(people.empty()) {
        throw "The list of people is empty!";
    }

}

void ListOfPeople::printPeople() const {

    for(int i = 0; i < people.size(); i++) {

        people[i].printPerson();
        std::cout << std::endl;

    }

}

bool ListOfPeople::empty() const {
    return people.empty();
}

std::size_t ListOfPeople::count() const {
    return people.size();
}
