#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;
#include "Common.h"
#include "Command.h"
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

void Command::addVehicle(Registration& reg, const string& des) 
{
    if (!reg.isValid()) {
        cout << "Invalid registration number!\n";
        return;
    }

    for (size_t i = 0; i < Vehicles.size(); ++i) {
        if (Vehicles[i].getReg() == reg) {
            cout << "There already exists a vehicle with this registration number!\n";
            return;
        }
    }

    Vehicles.push_back(Vehicle(reg, des));
}
void Command::addPerson(const string& name, const unsigned int& id) 
{
    for (size_t i = 0; i < name.size(); ++i) {
        if (name[i] >= '0' && name[i] <= '9') {
            cout << "Invalid name!";
            return;
        }
    }

    for (size_t i = 0; i < People.size(); ++i) {
        if (People[i].getId() == id) {
            cout << "There already exists a person with this id!\n";
            return;
        }
    }

    People.push_back(Person(name, id));
}

void Command::release(const unsigned int& ownerId, const Registration& vehicleId) 
{
    for (size_t i = 0; i < Vehicles.size(); ++i) {
        if (Vehicles[i].getReg() == vehicleId) {
            for (size_t j = 0; j < People.size(); ++j) {
                if (People[j].getId() == ownerId) {
                    People[j].removeVehicle(Vehicles[i]);
                }
            }
        }
    }
}
    // TODO: too many same-ish for loops, should make search function, also this function is disgusting
void Command::acquire(const unsigned int& ownerId, const Registration& vehicleId) 
{
    for (size_t i = 0; i < Vehicles.size(); ++i) {
        if (Vehicles[i].getReg() == vehicleId) {                    //find vehicle using id
            if (Vehicles[i].owner) {                                //if that vehicle has non nullptr pointer aka has an owner
                release((Vehicles[i].owner)->getId(), vehicleId);   //release veh from 
            }
            for (size_t j = 0; j < People.size(); ++j) {        //otherwise / continue after releasing veh
                if (People[j].getId() == ownerId) {             //find person with ownerId
                    Vehicles[i].addOwner(&People[j]);           //add pointer of owner to the vehicle
                    People[j].addVehicle(&Vehicles[i]);         //add vehicle pointer to vector in person 
                }
            }
        }
    }
}

void Command::remove(const unsigned int& ownerId) 
{
    for (size_t i = 0; i < People.size(); ++i) {
        if (People[i].getId() == ownerId) {
            for (size_t j = 0; j < Vehicles.size(); ++j) {
                if (Vehicles[j].owner == nullptr) continue;
                if (Vehicles[j].owner->getId() == ownerId) {
                    do {
                        cout << "Are you sure you want to remove this person?\n";
                        cout << "Type YES or NO and press enter to continue:\n";
                        string input;
                        std::getline(std::cin, input);
                        if (input == "YES") {
                            Vehicles[j].owner = nullptr;
                            break;
                        }
                        if (input == "NO") {
                            return;
                        }
                    }
                    while (1);
                }
            }
            People.erase(People.begin() + i);
            return;
        }
    }
    cout << "No owner with this id can be found!\n";
}
void Command::remove(const Registration& vehicleId) 
{
    for (size_t i = 0; i < Vehicles.size(); ++i) {
        if (Vehicles[i].getReg() == vehicleId) {
            if (Vehicles[i].owner) {
                do {
                    cout << "Are you sure you want to remove this vehicle?\n";
                    cout << "Type YES or NO and press enter to continue:\n";
                    string input;
                    std::getline(std::cin, input);
                    if (input == "YES") {
                        Vehicles[i].owner->removeVehicle(Vehicles[i]);
                        break;
                    }
                    if (input == "NO") {
                        return;
                    }
                } 
                while (1);
            }
            Vehicles.erase(Vehicles.begin() + i);
            return;
        }
    }
    cout << "No vehicle with this id can be found!\n";
}

bool fileExists(const string& path)
{
    ifstream infile(path);
    return infile.good();
}

bool hasSpace(const string& str) 
{
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            return 1;
        }
    }
    return 0;
}

void Command::save(const string& fileName) 
{
    if (fileExists(fileName)) {
        do {
            cout << "File already exists, do you want to continue?\n";
            cout << "Type YES or NO and press enter to continue:\n";
            string input;
            std::getline(std::cin, input);
            if (input == "YES") {
                break;
            }
            if (input == "NO") {
                return;
            }
        } 
        while (1);
    }

    ofstream out(fileName, std::ios_base::app);
    if (!out) {
        cout << "File failed to open!\n";
        return;
    }
    for (size_t i = 0; i < People.size(); ++i) {
        string cpy = std::to_string(People[i].getId());
        if (hasSpace(People[i].getName())) {
            out << "PERSON " << '"' << People[i].getName() << '"' << " " << cpy << "\n";
        }
        else {
            out << "PERSON " << People[i].getName() << " " << cpy << "\n";
        }
    }
    for (size_t i = 0; i < Vehicles.size(); ++i) {
        string cpy = std::to_string(People[i].getId());
        if (hasSpace(Vehicles[i].getDes())) {
            out << "VEHICLE " << Vehicles[i].getReg() << " " << '"' << Vehicles[i].getDes() << '"' << "\n";
        }
        else {
            out << "VEHICLE " << Vehicles[i].getReg() << " " << Vehicles[i].getDes() << "\n";
        }
    }
    out.close();
}

void Command::show(showTYPE type) 
{
    switch (type) {
        case PEOPLE: {
            if (People.size() == 0) {
                cout << "No people\n";
                return;
            }
            for (size_t i = 0; i < People.size(); ++i) {
                cout << People[i] << "\n";
            }
            break;
        }
        case VEHICLES: {
            if (Vehicles.size() == 0) {
                cout << "No vehicles\n";
                return;
            }
            for (size_t i = 0; i < Vehicles.size(); ++i) {
                cout << Vehicles[i] << "\n";
            }
            break;
        }
    }
}
void Command::showPerInfo(const unsigned int& ownerId) 
{
    for (size_t i = 0; i < People.size(); ++i) {
        if (People[i].getId() == ownerId) {
            if (People[i].getVehCnt() != 0) {
                cout << People[i].getName() << " owns the following vehicle/ vehicles:\n";
                People[i].printOwnedVehicles();
            }
            if (People[i].getVehCnt() == 0) {
                cout << People[i].getName() << " owns no vehicle/ vehicles\n";
            }
            return;
        }
    }
    cout << "No such person exists!\n\n";
}
void Command::showVehInfo(const Registration& vehicleId) 
{
    for (size_t i = 0; i < Vehicles.size(); ++i) {
        if (Vehicles[i].getReg() == vehicleId) {
            cout << Vehicles[i].getDes() << " is owned by:\n";
            if (Vehicles[i].owner) {
                Vehicles[i].printOwner();
            }
            else {
                cout << "nobody";
            }
            cout << "\n";
            return;
        }
    }
    cout << "No such vehicle exists!\n";
}
