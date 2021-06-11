#pragma once
#include "../command.hpp"

class ShowCommand : public Command{

public:
    /**
     * Constructor
     */
    ShowCommand(const std::vector<std::string>& args);

    void execute()const;
};
