#include "Person.h"

// Person::Person() 
//     : name(""), uniqueID(0)
// {
// }

Person::Person(const string& newPerson, unsigned int idPerson) 
    : name(newPerson), uniqueID(idPerson)
{
    if (idPerson < 0 || newPerson == "") {
        throw std::invalid_argument("You should input a name and a positive whole number!");
    }
}

unsigned int Person::getID() const {
    return uniqueID;
}

string Person::getName() const {
    return name;
}

bool Person::doIPossessVehicles() const{
    return vehicles.size() != 0;
}

int Person::vehiclePositionStorage(const Vehicle& newVehicle) const {
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        if ((*vehicles[i]).getRegistrationNumb() == newVehicle.getRegistrationNumb()) {
            return i;            
        }
    }
    return -1;
}

// TODO throws try catch

// void Person::addVehicle(const string& regNumber) {
//     if (vehiclePositionStorage(regNumber) != -1) { 
//         throw std::invalid_argument("Vehicle with this car plate is already owned by this person!");
//     }
    
//     try {
//         // newVehicle.setOwner(*this);
//         vehicles.push_back(&newVehicle);
//     }
//     catch (const std::bad_alloc&) 
//     {
//         std::cerr << "Couldn't allocate memory for the vehicle!" << endl;
//         // throw ;
//         // TODO: What is rethrow
//     }
// }

void Person::addVehicle(Vehicle& newVehicle) {
    if (vehiclePositionStorage(newVehicle) != -1) { 
        throw std::invalid_argument("Vehicle with this car plate is already owned by this person!");
    }

    vehicles.push_back(&newVehicle);
    
    // try {
    //     // newVehicle.setOwner(*this);
    // }
    // catch (const std::bad_alloc&) 
    // {
    //     std::cerr << "Couldn't allocate memory for the vehicle!" << endl;
    //     // throw ;
    //     // TODO: What is rethrow
    // }
}

void Person::removeVehicle(const string& regNumber) {
    Registration* tempReg = new Registration(regNumber);
    Vehicle* tempVeh = new Vehicle((*tempReg), "Temp");

    int pos = vehiclePositionStorage(*tempVeh);

    delete tempReg;
    delete tempVeh;

    if (pos != -1) {
        vehicles.erase(vehicles.begin() + pos);
        return;
    }
    // else {
    //     throw std::invalid_argument("");
    // }

    
}

// void Person::removeVehicle(const Vehicle& removeVehicle) {
//     int pos = vehiclePositionStorage(removeVehicle);

//     if (pos != -1) {
//         vehicles.erase(vehicles.begin() + pos);
//         return;
//     }
// }

void Person::removeAllOwnedVehicles() {
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        vehicles[i]->removeOwner();
    }
    
    vehicles.clear();
}

void Person::printOwnedCars() const {
    if (!vehicles.size()) {
        cout << "This person doesn't own any cars! :/" << endl;
        return;
    }
    for(unsigned int i = 0; i < vehicles.size(); ++i) {
        cout << "Vehicle #" << i+1 << " " << (*vehicles[i]) << endl;
    }
}

void Person::printCommand(std::ostream& out) const {
    out << "PERSON " << "\"" << name << "\"" << " " << uniqueID << endl;
}

Person Person::operator=(const Person newPerson) {
    if (this != &newPerson) {
        name = newPerson.name;
        uniqueID = newPerson.uniqueID;
        for (unsigned i = 0; i < newPerson.vehicles.size(); ++i) {
            vehicles[i] = newPerson.vehicles[i];
        }
    }

    return *this;
}

bool Person::operator==(const Person& otherPerson) const {
    return name == otherPerson.name && uniqueID == otherPerson.uniqueID && vehicles == otherPerson.vehicles;
}

std::ostream& operator<<(std::ostream& out, const Person newPerson) {
    out << newPerson.getName() << " ID: " << newPerson.getID();
    return out;
}
