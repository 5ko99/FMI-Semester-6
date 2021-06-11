#include "acquire_command.hpp"

AcquireCommand::AcquireCommand(const std::vector<std::string>& args) : Command(args, "ACQUIRE"){
}

void AcquireCommand::execute()const{

    checkArgs(2,true);
    
    PersonVehicleRelation::acquire(stoi(args[0]), args[1].c_str());
}
