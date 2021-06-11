#include"listOfVehicles.h"
#include<stdexcept>
#include<iostream>
#include<string>


void ListOfVehicles::addVehicles(const Vehicle& vehicle) {

    for(int i = 0; i < allVehicles.size(); i++) {

        if(allVehicles[i].getRegistration().compare(vehicle.getRegistration()) == 0) {

            throw std::invalid_argument("In the list of vehicles already excists a car with the same registration!");

        }

    }

    allVehicles.push_back(vehicle);

}

Vehicle* ListOfVehicles::getVehicle(std::string id) {

    bool found = false;

    for(int i = 0; i < allVehicles.size(); i++) {

        if(allVehicles[i].getRegistration().compare(id) == 0) {

            found = true;
            return &allVehicles[i];

        }

        if(i == allVehicles.size() - 1 && found == false) {
            throw "The information about the vehicle you want is impossible to show because the vehicle does not excist!";
        }

    }

}

void ListOfVehicles::addOwner(Person* owner, std::string id) {

    for(int i = 0; i < allVehicles.size(); i++) {

        if(allVehicles[i].getRegistration().compare(id) == 0) {    

            allVehicles[i].addPerson(owner);

        }

    }
    
}

void ListOfVehicles::releasePerson(std::string id) {

    for(int i = 0; i < allVehicles.size(); i++) {

        if(allVehicles[i].getRegistration().compare(id) == 0) {    

            allVehicles[i].releaseOwner();

        }

    }
    
}

void ListOfVehicles::removeVehicle(std::string id) {

    bool found = false;
    std::string answer;

    for(int i = 0; i < allVehicles.size(); i++) {

        if(allVehicles[i].getRegistration().compare(id) == 0) {

            if(allVehicles[i].isItHasNoOwner() == false) {

                std::cout<<"The vehicle has an owner. Are you sure that you want to remove the vehicle? (yes/no)"<<std::endl;
                getline(std::cin, answer);

                if(answer.compare("yes") == 0) {

                    allVehicles[i].getPerson()->releaseVehicle(id);
                    allVehicles.erase(allVehicles.begin() + i);

                }
  
                return;  
        
            }    

            allVehicles.erase(allVehicles.begin() + i);
            found = true;
        }

        if(i == allVehicles.size() - 1 && found == false) {
            throw "This vehicle does not excist!";
        }

    }

    if(allVehicles.empty()) {
        throw "The list of vehicles is empty!";
    }

    
}

void ListOfVehicles::printVehicles() const {

    for(int i = 0; i < allVehicles.size(); i++) {

        allVehicles[i].printVehicle();
        std::cout << std::endl;

    }

}

bool ListOfVehicles::empty() const {
    return allVehicles.empty();
}

std::size_t ListOfVehicles::count() const {
    return allVehicles.size();
}
