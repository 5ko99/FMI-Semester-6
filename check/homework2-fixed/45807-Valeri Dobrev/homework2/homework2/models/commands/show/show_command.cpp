#include "show_command.hpp"

ShowCommand::ShowCommand(const std::vector<std::string>& args) : Command(args, "SHOW"){
}

void ShowCommand::execute()const{ 
    checkArgs(1);
    if(args[0]=="PEOPLE"){
        for(Person* e: PersonFactory::getInstance()->getElements() ){
            std::cout<<(*e)<<"\n";
        }
    }else if(args[0] == "VEHICLES"){
        for(Vehicle* e: VehicleFactory::getInstance()->getElements() ){
            std::cout<<(*e)<<"\n";
        }
    }else if(isNumber(args[0])){
        std::cout<<(*PersonFactory::getInstance()->getById(stoi(args[0])))<<"\n";
    }else {
        std::cout<<(*VehicleFactory::getInstance()->getById(args[0].c_str()))<<"\n";
    }
}
