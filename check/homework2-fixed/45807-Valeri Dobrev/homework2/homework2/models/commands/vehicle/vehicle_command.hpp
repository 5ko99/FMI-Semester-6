#pragma once
#include "../command.hpp"


class VehicleCommand :public Command{


public:
    /**
     * Constructor
     */
    VehicleCommand(const std::vector<std::string>& args);

    void execute()const;
};
