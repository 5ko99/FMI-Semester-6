#pragma once
#include<fstream>
#include "../command.hpp"


class SaveCommand : public Command{


public:
    /**
     * Constructor
     */
    SaveCommand(const std::vector<std::string>& args);

    void execute() const;

};
