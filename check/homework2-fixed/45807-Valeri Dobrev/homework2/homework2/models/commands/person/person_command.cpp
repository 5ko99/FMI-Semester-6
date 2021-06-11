#include "person_command.hpp"


PersonCommand::PersonCommand(const std::vector<std::string>& args) : Command(args, "PERSON"){
}

void PersonCommand::execute()const{
    checkArgs(2, true, 1);
    PersonFactory::getInstance()->create(stoi(args[1]), args[0]);
}
