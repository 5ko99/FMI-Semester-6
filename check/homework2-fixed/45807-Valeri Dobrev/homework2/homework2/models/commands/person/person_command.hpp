#pragma once
#include "../command.hpp"

class PersonCommand: public Command{


public:
    /**
     * Constructor
     */
    PersonCommand(const std::vector<std::string>& args);

    void execute()const;
};
