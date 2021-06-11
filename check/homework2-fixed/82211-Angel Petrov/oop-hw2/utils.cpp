#include <iostream>
#include <fstream>
#include "utils.h"

// checks if a file with the same name exists
bool exists(std::string& name) {

    std::ifstream file(name);

    if(!file)
        return false;
    return true;
}

// command case vehicle
void vehicle(Allocator* alloc, Commands* cmnd) {

    Registration registration = cmnd->toRegistration(cmnd->getFirstArg());
    std::string description = cmnd->getSecondArg();

    alloc->addVehicle(registration, description);
}

// command case person
void person(Allocator* alloc, Commands* cmnd) {

    std::string name = cmnd->getFirstArg(), idString =cmnd->getSecondArg();
    unsigned id = atoi(idString.c_str());
    
    alloc->addPerson(name, id);
}

// command case acqurie
void acquire(Allocator* alloc, Commands* cmnd) {

    unsigned id = atoi(cmnd->getFirstArg().c_str());
    Registration registration = cmnd->toRegistration(cmnd->getSecondArg());

    alloc->acquire(id, registration);
}

// command case release
void release(Allocator* alloc, Commands* cmnd) {

    unsigned id = atoi(cmnd->getFirstArg().c_str());
    Registration registration = cmnd->toRegistration(cmnd->getSecondArg());

    alloc->release(id, registration);
}

// command case remove
void remove(Allocator* alloc, Commands* cmnd) {

    std::string arg = cmnd->getFirstArg();

    if(arg[0] >= '0' && arg[0] <= '9') {
        unsigned id = atoi(cmnd->getFirstArg().c_str());

        alloc->removePerson(id);
    } 
    else {
        Registration registration = cmnd->getFirstArg();

        alloc->removeVehicle(registration);
    }
}

// command case save
void save(Allocator* alloc, Commands* cmnd) {
    
    // extracts the file path
    std::string path = cmnd->getFirstArg();

    // if a file with the same name exists, ask the user for confirmation
    if(exists(path)) {

        int option;
        std::cout << "File already exist. Press 1 to continue and 0 to enter new path.\n";
        std::cin >> option;
        std::cin.ignore();

        // if he declines let him enter new path
        if(!option) {

            std::cout << "Enter new path.\n";
            std::getline(std::cin, path);
        } 

    }

    // open the file
    std::ofstream out;

    out.open(path);

    // get access to the people and the vehicles
    std::vector<Person> pToPrint = alloc->getPeople();
    std::vector<Vehicle> vToPrint = alloc->getVehicles();

    // print the vehicles without owner first
    out << "1) Vehicles without owner:\n";
    for (size_t i = 0; i < vToPrint.size(); ++i) {
        if(vToPrint[i].getOwner() == nullptr) 
            out << vToPrint[i];
    }

    // print the people without vehicles second
    out << "\n2) People without vehicles:\n";
    for (size_t i = 0; i < pToPrint.size(); ++i) {
        if(pToPrint[i].getNumberOfVehiclesOwned() == 0) 
            out << pToPrint[i];
    }

    // print all related objects
    out << "\n3) ";
    for (size_t i = 0; i < pToPrint.size(); ++i) {
        // if the person has at least 1 vehicle print him and the vehicle
        if(pToPrint[i].getNumberOfVehiclesOwned() > 0) {
            out << "All vehicles related to:\n";
            out << pToPrint[i];
            out << "Vehicles:\n";
            
            // get access to the person's vehicles
            std::vector<Vehicle*> vehiclesOfPersonI = pToPrint[i].getVehicles();
            
            for (size_t j = 0; j < vehiclesOfPersonI.size(); ++j) {
                out << (*vehiclesOfPersonI[j]);
            }
        }
    }
    // an ending symbol
    out << "#";
    out.close();
}

// command case show
void show(Allocator* alloc, Commands* cmnd) {

    // extract the first arg
    std::string arg = cmnd->argumentToCaps(cmnd->getFirstArg());

    // print people only
    if (arg == "PEOPLE") {

        alloc->printPeople();
    } 
    // print vehicls only
    else if (arg == "VEHICLES") {

        alloc->printVehicles();
    } 
    // prints related objects
    else {
        std::string arg = cmnd->getFirstArg();

        if(arg[0] >= '0' && arg[0] <= '9') {
            unsigned id = atoi(cmnd->getFirstArg().c_str());

            alloc->printById(id);
        } 
        else {
            Registration registration = cmnd->getFirstArg();

            alloc->printByLicensePlate(registration);
        }
    }
}

void loadFile(Allocator* alloc, Commands* cmnd, std::string dir) {

    // opens file
    std::string line;
    std::ifstream in;
    in.open(dir);

    // if file is opened successfully
    if(in.is_open()) {
        
        while (in) {
            
            std::getline(in, line);
            
            // read vehicles without owner
            if(line[0] == '1') {

                readVehicles(alloc, cmnd, in);
            }
            // read people wihout vehicles
            else if(line[0] == '2') {

                readPeople(alloc, cmnd, in);
            }
            // read related objects
            else if(line[0] == '3') {

                readRelatedObjects(alloc, cmnd, in);
            }
        }

        in.close();
    }
}

// read vehicles without owners
void readVehicles(Allocator* alloc, Commands* cmnd, std::ifstream& in) {

    while (true) {

        std::string line2, toBeReg, desc;
        std::getline(in, line2); // reads a line

        // if we encounter an empty line break the cycle
        if(!line2.size())
            break;

        size_t i = 0;
        // reads the registration
        while(line2[i] != ',') {
            toBeReg.push_back(line2[i]);
            ++i;
        }

        i += 2; // skips ',' and whitespace

        // reads the description
        while(line2[i] != ';') {
            desc.push_back(line2[i]);
            ++i;
        }
        
        // adds the object
        Registration reg(toBeReg);
        alloc->addVehicle(reg, desc);
    }
}

// read people without vehicles
void readPeople(Allocator* alloc, Commands* cmnd, std::ifstream& in) {

    while(true) {

        std::string name, idStr, line2;
        unsigned id;
        std::getline(in, line2); // reads a line

        if(!line2.size()) // if we encounter an empty line
            break;        // break the cycle
        
        size_t i = 0;

        // reads the name
        while(line2[i] != ',') {
            name.push_back(line2[i]);
            ++i;
        }

        i += 2; // skips ',' and whitesapce

        // reads the id
        while (line2[i] != ';') {
            idStr.push_back(line2[i]);
            ++i;
        }

        // converts the id to unsigned
        id = atoi(idStr.c_str());
        // adds the person
        alloc->addPerson(name, id);
    }   
}

// reads related objects
void readRelatedObjects(Allocator* alloc, Commands* cmnd, std::ifstream& in) {

    // a cycle to add the owner
    while(true) {

        std::string name, idStr, desc, toBeReg, line2; 
        unsigned id;
        size_t i = 0;

        // if we reach eof break the cycle 
        if(in.eof())
            break;

        std::getline(in, line2); // read a line
        
        if(!line2.size()) // if we encounter an empty 
            continue;     // line just skip it

        // reads the name
        while(line2[i] != ',') {
            name.push_back(line2[i]);
            ++i;
        }

        i += 2; // skips ',' and whitespace

        // reads the id
        while(line2[i] != ';') {
            idStr.push_back(line2[i]);
            ++i;
        }

        // converts id to unsigned
        id = atoi(idStr.c_str());
        // add the person
        alloc->addPerson(name, id);
        
        std::getline(in, line2); // skips "Vehicles:"

        // a cycle to add his vehicles
        while(true) {

            std::string line3;
            std::getline(in, line3); // read a line
            i = 0; // reset the counter

            if(!line3.size()) {           // if we encounter an empty line read 
                std::getline(in, line3);  // "All vehicles related to:"
                break;                   // and break the cycle to read a new owner
            }                            
            else if(line3[i] == '#') // if eof is reached 
                break;               // break the cycle

            // reads the license plate
            while(line3[i] != ',') {
                toBeReg.push_back(line3[i]);
                ++i;
            }

            i += 2; // skips ',' and whitespace

            // reads the description
            while(line3[i] != ';') {
                desc.push_back(line3[i]);
                ++i;
            }

            // add the vehicle
            Registration reg(toBeReg);
            alloc->addVehicle(reg, desc);
            // connect the objects
            alloc->acquire(id, reg);
        }
    }
}
