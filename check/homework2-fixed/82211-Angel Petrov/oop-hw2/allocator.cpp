#include <iostream>
#include "allocator.h"

Allocator* Allocator::instance = 0;

bool Allocator::isValidPerson(unsigned id) {

    for (size_t i = 0; i < sizePeople; ++i) { // if we encounter a person
        if (people[i].getID() == id) {        // with the same id return false
            return false;
        }
    }
    return true;
}

bool Allocator::isValidVehicle(const Registration& licensePlate) {

    for (size_t i = 0; i < sizeVehicles; ++i) {
        if (vehicles[i].getLicensePlate() == licensePlate) { 
            return false;    // if we encounter a vehicle
        }                   // with the same registration 
    }                       // return false
    return true;
}

Allocator::Allocator() {

    sizePeople = 0;
    sizeVehicles = 0;
}

Allocator* Allocator::getInstance() { // instance accessor

    if (!instance) {
        instance = new Allocator;
    }

    return instance;
}

void Allocator::addPerson(std::string name, unsigned id) {

    try {
        if (!isValidPerson(id))  // if a person with the same id exists we don't add the new person
            throw std::invalid_argument("A person with the same ID already exists!\n");
    }
    catch(std::invalid_argument& e) {  
        std::cout << e.what();
        return;
    }

    Person other(name, id);       // if it's a new id we add the person
    people.emplace_back(other);
    ++sizePeople;
}

void Allocator::addVehicle(const Registration& licensePlate, std::string description) {

    try {
        if (!isValidVehicle(licensePlate)) // if we already have a vehicle with this license plate don't add it
            throw std::invalid_argument("A vehicle with this license plate already exists!\n");
    }
    catch(std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    Vehicle other(licensePlate, description); // if it's a new license plate add it
    vehicles.emplace_back(other);
    ++sizeVehicles;
}

void Allocator::removePerson(unsigned id) {

    try {
        if(isValidPerson(id)) { // if such a person doesn't exist throw exception
            throw std::invalid_argument("Invalid id.\n");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toRemove = 0;

    for (size_t i = 0; i < sizePeople; ++i) {  // finds the index 
        if (people[i].getID() == id) {        // of the person 
            toRemove = i;                   // who should be removed
            break;
        }
    }

    int option;
    if(people[toRemove].getNumberOfVehiclesOwned() != 0) { // if the person owns vehicles asks the user for confirmation
        std::cout << "This person owns at least 1 vehicle. Are you sure you want to remove him?\n";
        std::cout << "Press 1 to continue.\n" << "Press 0 to cancel.\n";
        std::cin >> option;
        std::cin.ignore();

        if(!option)
            return;

        for (size_t i = 0; i < sizeVehicles; ++i) {  // clears the vehicles's owner after the person is removed
            if (vehicles[i].getOwner() != nullptr &&
                        vehicles[i].getOwner()->getID() == people[toRemove].getID()) 
            {
                vehicles[i].clearOwner();
            }
        }
    }
    
    people.erase(people.begin() + toRemove);
    --sizePeople;
}

void Allocator::removeVehicle(const Registration& licensePlate) {

    try {
        if(isValidVehicle(licensePlate)) { // checks if such a vehicle exists
            throw std::invalid_argument("Invalid license plate.\n");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toRemove = 0;

    for (size_t i = 0; i < sizeVehicles; ++i) {                 // finds the registration of the vehicle
        if (vehicles[i].getLicensePlate() == licensePlate) {   // which should be removed
            toRemove = i;
            break;
        }
    }   

    int option;
    if(vehicles[toRemove].getOwner() != nullptr) {                                     // asks the user for 
        std::cout << "This vehicle is owned. Are you sure you want to remove it?\n"; // confirmation if the
        std::cout << "Press 1 to continue.\n" << "Press 0 to cancel.\n";            //  vehicle is owned
        std::cin >> option;
        std::cin.ignore();
        if(!option)
            return;
    }
    
    //  releases the vehicle from its owner
    for (size_t i = 0; i < sizePeople; ++i) { 
        if (people[i].getID() == vehicles[toRemove].getOwner()->getID()) {
            people[i].releaseVehicle(vehicles[toRemove].getLicensePlate());
        }
    }

    vehicles.erase(vehicles.begin() + toRemove);
    --sizeVehicles;

}

void Allocator::acquire(unsigned id, const Registration& licensePlate) {

    // checks if the input is correct
    try {
        if(isValidPerson(id) || isValidVehicle(licensePlate)) {
            throw std::invalid_argument("Invalid id or license plate.\n");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toBeOwner, toBeOwned;

    //finds the index of the person
    for (size_t i = 0; i < sizePeople; ++i) { 
        if (people[i].getID() == id) {
            toBeOwner = i;
        }
    }

    //finds the index of the vehicle
    for (size_t i = 0; i < sizeVehicles; ++i) {
        if (vehicles[i].getLicensePlate() == licensePlate) {
            toBeOwned = i;
        }
    }

    // if the vehicle is owned by someone else, releases it from its owner
    if(vehicles[toBeOwned].getOwner() != nullptr) {
        for (size_t i = 0; i < sizePeople; ++i) {
            if(vehicles[toBeOwned].getOwner()->getID() == people[i].getID()) {
                release(people[i].getID(), vehicles[toBeOwned].getLicensePlate());
                break;
            }
        }
    }

    //sets the new owner
    vehicles[toBeOwned].setOwner(people[toBeOwner]);
    people[toBeOwner].addVehicle(vehicles[toBeOwned]);

}

void Allocator::release(unsigned id, const Registration& licensePlate) {

    // checks if the input is correct
    try {
        if(isValidPerson(id) || isValidVehicle(licensePlate)) {
            throw std::invalid_argument("Invalid id or license plate.\n");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toBeReleased, toRelease;

    //finds the index of the person
    for (size_t i = 0; i < sizePeople; ++i) {
        if (people[i].getID() == id) {
            toRelease = i;
        }
    }

    //finds the index of the vehicle
    for (size_t i = 0; i < sizeVehicles; ++i) {
        if (vehicles[i].getLicensePlate() == licensePlate) {
            toBeReleased = i;
        }
    }

    // releases the vehicle
    vehicles[toBeReleased].clearOwner();
    people[toRelease].releaseVehicle(licensePlate);
}

void Allocator::printPeople() {

    // checks if there is something to be printed
    try {
        if(!sizePeople) {
            throw std::underflow_error("There are no people curretnly.\n");
        }
    }
    catch (std::underflow_error& e) {
        std::cout << e.what();
        return;
    }

    for (size_t i = 0; i < sizePeople; ++i) {
        std::cout << "Person: " << people[i];
    }

    std::cout << "\n";
}

void Allocator::printVehicles() {

    // checks if there is something to be printed
    try {
        if(!sizeVehicles) {
            throw std::underflow_error("There are no vehicles curretnly.\n");
        }
    }
    catch (std::underflow_error& e) {
        std::cout << e.what();
        return;
    }

    for (size_t i = 0; i < sizeVehicles; ++i) {
        std::cout << "Vehicle: " << vehicles[i];
    }

    std::cout << "\n";
}

void Allocator::printById(unsigned id) {

    //  checks if the input is valid
    try {
        if(isValidPerson(id))
            throw std::invalid_argument("Invalid id.\n");
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toPrint;
    
    //finds the index
    for(size_t i = 0; i < sizePeople; ++i) {
        if(id == people[i].getID()) {
            toPrint = i;
            break;
        }
    }

    // checks if the person owns vehicles
    try {
        if(!people[toPrint].getNumberOfVehiclesOwned()) {
            throw std::underflow_error("No vehicles owned by this person.\n");
        }
    } 
    catch (std::underflow_error& e) {
        std::cout << e.what();
        return;
    }

    std::cout << "Printing all objects related to: " << people[toPrint] << "Vehicles:\n";

    people[toPrint].printVehicles();

    std::cout << "\n";
}

void Allocator::printByLicensePlate(const Registration& licensePlate) {

    //  checks if the input is valid
    try {
        if(isValidVehicle(licensePlate))
            throw std::invalid_argument("Invalid registration.\n");
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
        return;
    }

    size_t toPrint;

    //finds the index
    for (size_t i = 0; i < sizeVehicles; ++i) {
        if(vehicles[i].getLicensePlate() == licensePlate) {
            toPrint = i;
            break;
        }
    }

    // checks if the vehicle is owned
    try {
        if(!vehicles[toPrint].getOwner()) {
            throw std::underflow_error("This vehicle has no owner.\n");
        }
    }
    catch (std::underflow_error& e) {
        std::cout << e.what();
        return;
    }

    Person* ownerToPrint = vehicles[toPrint].getOwner();

    std::cout << "Printing the owner of: " << vehicles[toPrint] << "Owner: "<< (*ownerToPrint) << "\n";
}

// accessors
std::size_t Allocator::getPeopleSize() {

    return sizePeople;
}

std::size_t Allocator::getVehiclesSize() {

    return sizeVehicles;
}

std::vector<Person> Allocator::getPeople() {

    return people;
}

std::vector<Vehicle> Allocator::getVehicles() {

    return vehicles;
}

// destr
Allocator::~Allocator(){
    delete instance;
}
