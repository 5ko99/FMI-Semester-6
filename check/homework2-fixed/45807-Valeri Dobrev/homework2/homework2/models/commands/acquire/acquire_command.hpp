#pragma once
#include "../command.hpp"

class AcquireCommand : public Command{

public:

    /**
     * Constructor
     */
    AcquireCommand(const std::vector<std::string>& args);

    void execute()const;
};
