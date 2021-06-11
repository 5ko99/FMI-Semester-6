#include "remove_command.hpp"


RemoveCommand::RemoveCommand(const std::vector<std::string>& args) : Command(args, "REMOVE"){

}




void RemoveCommand::execute()const{ 

    checkArgs(2);
    bool user_confirmation = false;
    if(args[1] == "true"){
        user_confirmation = true;
    }

    if(isNumber(args[0])){
        checkArgs(2,true);
        PersonFactory::getInstance()->remove(stoi(args[0]), user_confirmation);
    }
    else{
        VehicleFactory::getInstance()->remove(args[0].c_str(), user_confirmation);
    }
}
