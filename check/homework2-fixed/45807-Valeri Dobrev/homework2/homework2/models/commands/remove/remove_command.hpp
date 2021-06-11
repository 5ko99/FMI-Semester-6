#pragma once
#include "../command.hpp"


class RemoveCommand : public Command{

    

public:
    /**
     * Constructor
     */
    RemoveCommand(const std::vector<std::string>& args);

    void execute()const;
};
