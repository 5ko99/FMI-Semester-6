#include "save_command.hpp"

SaveCommand::SaveCommand(const std::vector<std::string>& args) : Command(args){}

void SaveCommand::execute()const{
    checkArgs(1);
    std::fstream f(args[0], std::ios::trunc | std::ios::out);
    if(!f.is_open()){
        throw std::invalid_argument("Unable to open file: " + args[0]);
    }

    PersonFactory* personFactory = PersonFactory::getInstance();
    VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

    std::string line;
    for(auto *e: vehicleFactory->getElements()){
        line = "VEHICLE " + e->getIdToString() + " " + e->getDescription()+ "\n";
        f<<line; 
        line.clear();
    }
    for(Person *e: personFactory->getElements()){
        line = "PERSON " + e->getName() + " " + e->getIdToString() + "\n";
        f<<line;
        line.clear();
        for(Vehicle *v: e->getVehicles()){
            line = "ACQUIRE " + e->getIdToString() + " " + v->getIdToString() + "\n";
            f<<line;
            line.clear();
        } 
    }

    

}
