#include "commands.h"
#include <iostream>
#include <fstream>

void Commands::VEHICLE(const Registration& reg, const std::string& descript)
{
    Vehicle newVehicle (reg, descript);
    AV.addVehicle(newVehicle);
    std::cout << "New vehicle registered successfully!" << std::endl;
}

void Commands::PERSON(const std::string& name, const unsigned id)
{
    Person newPerson(name, id);
    PPL.addPerson(newPerson);
    std::cout << "New person registered successfully!" << std::endl;
}

void Commands::ACQUIRE(const unsigned id, const Registration& reg)
{
    Person* newOwner = PPL.getPerson(id);
    Vehicle* vehicle = AV.getVehicle(reg);
    newOwner->addVehicle(*vehicle); //add the vehicle to the new owner
    vehicle->releaseOwner(); //release the old vehicle's owner
    vehicle->addOwner(*newOwner); //add the new owner to the vehicle
    std::cout << "New owner successfully added to a vehicle!" << std::endl;
}

void Commands::RELEASE(const unsigned id, const Registration& reg)
{

    PPL.getPerson(id)->releaseVehicle(reg); //remove vehicle from owner
    AV.getVehicle(reg)->releaseOwnerWithoutCheck(); //remove owner from vehicle
    std::cout << "Vehicle released successfully!" << std::endl;
}

void Commands::REMOVE(const std::string& arg)
{
    int type = whatIsThis(arg);
    if (type == 1){
        unsigned id;
        //'arg' may be too big to be stored in unsigned int
        try {
            id = std::stoi(arg);
        } catch (const std::out_of_range& e){
            throw std::invalid_argument("Invalid ID!");
        }
        if (PPL.getPerson(id)->hasAnyVehicles()){
            std::cout << "WARNING: This person possesses several vehicles. Do you want to remove him anyway? (Y/N)\n";
            char x;
            do {
                std::cin >> x;
                std::cin.get(); //to get the '\n' symbol
            } while (x!='Y' && x!='y' && x!='N' && x!='n');

            if (x == 'N' || x == 'n'){
                std::cout << "Operation canceled!" << std::endl;
                return;
            }
        }
        PPL.removePerson(id);
        std::cout << "Person removed successfully!" << std::endl;
    }

    else if (type == 2){
        Registration reg(arg); 
        if (AV.getVehicle(reg)->getOwner() != nullptr){
            std::cout << "WARNING: This vehicle has an owner. Do you want to remove it anyway? (Y/N)" << std::endl;
            char x;
            do {
                std::cin >> x;
                std::cin.get(); //to get the '\n' symbol
            } while (x!='Y' && x!='y' && x!='N' && x!='n');

            if (x == 'N' || x == 'n'){
                std::cout << "Operation canceled!" << std::endl;
                return;
            }
        }
        
        AV.removeVehicle(reg);
        std::cout << "Vehicle removed successfully!" << std::endl; 
    }

    else {
        throw std::invalid_argument("Invalid command!");
    }
}

void Commands::SAVE(std::ofstream& file)
{
    for (size_t i=0; i<AV.getCount(); ++i){
        file << "VEHICLE " << AV[i]->getRegistration() << " " 
             << "\"" << AV[i]->getDescript() << "\"" << "\n"; 
    }

    for (size_t i=0; i<PPL.getCount(); ++i){
        file << "PERSON " << "\"" << PPL[i]->getName() << "\"" << " " 
             << PPL[i]->getId() << "\n"; 
    }

    for (size_t i=0; i<PPL.getCount(); ++i){
        for (size_t j=0; j<PPL[i]->getCountOfVehs(); ++j){
            file << "ACQUIRE " << PPL[i]->getId() << " "
                 << PPL[i]->getOwnedVehicle(j)->getRegistration() << "\n";               
        }
    }

    std::cout << "Data saved successfully!" << std::endl;
}

void Commands::SHOW(std::string& arg) 
{
    toLowerCase(arg);
    if (arg == "vehicles"){
        AV.showAllInfo();
    }
    else if (arg == "people"){
        PPL.showAllInfo();
    }
    else if (whatIsThis(arg) == 2){
        AV.showInfo(arg);
    }
    else if (whatIsThis(arg) == 1){
        try {
            PPL.showInfo(std::stoi(arg)); 
        } catch (const std::out_of_range& e){
            throw std::invalid_argument("Invalid ID!");
        }
        
    }
    else throw std::invalid_argument("Invalid Command!");
}

void Commands::HELP() const
{
    std::cout << "Supported commands:\n"
              << "VEHICLE <registration> <description>   Register a new vehicle\n"
              << "PERSON    <name>            <id>       Register a new person\n"
              << "ACQUIRE <owner-id>      <vehicle-id>   Add a vehicle to an owner\n"
              << "RELEASE <owner-id>      <vehicle-id>   Release vehicle from an owner\n"
              << "REMOVE    <what>                       Remove vehicle/person\n"
              << "SAVE      <path>                       Save info into a file\n"
              << "SHOW    [PEOPLE|VEHICLES|<id>]         Show info about all People/Vehicles or certain person/vehicle\n" 
              << "HELP                                   Show help\n"
              << "EXIT                                   Quit the program"<< std::endl;  
}

//returns 2 if str is vehicle's registration
//returns 1 if str is person's id (maybe)
//returns 0 if str is neither vehicle nor person
int Commands::whatIsThis(const std::string& str)
{   
    if (Registration::validateRegistration(str)){
        return 2;
    }

    for (size_t i=0; i<str.size(); ++i){
        if (!isdigit(str[i])){
            return 0;
        }
    }

    return 1;
}

void Commands::toLowerCase(std::string& str)
{
    for (size_t i=0; i<str.size(); ++i){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 'a' - 'A';
        }
    }
}

//The following 2 are only created for the unit tests
AllVehicles& Commands::getAV() {return AV;}

People& Commands::getPPL() {return PPL;}
