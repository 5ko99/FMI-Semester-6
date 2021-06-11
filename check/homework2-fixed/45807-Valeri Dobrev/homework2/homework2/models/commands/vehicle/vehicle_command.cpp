#include"vehicle_command.hpp"

VehicleCommand::VehicleCommand(const std::vector<std::string>& args) : Command(args,"VEHICLE"){
}

void VehicleCommand::execute()const{
    checkArgs(2);
    VehicleFactory::getInstance()->create(args[0].c_str(), args[1]);
}
