#ifndef CommandController_hpp
#define CommandController_hpp

#include "../PersonVehicleController/PersonVehicleController.hpp"
#include "../Command/Command.hpp"
#include "../Person/Person.hpp"
#include "../Vehicle/Vehicle.hpp"
#include "../Utils/Utils.hpp"

#include <fstream>

class CommandController{
private:
    std::vector<Command> comArr;
    PersonVehicleController pvc;
    void readFromFile(std::string fileName);
    void saveToFile(std::string path);
    bool executeCommand(const Command& cmd, std::istream& istr);
public:
    CommandController();
    CommandController(std::string path);
    
    void startReading();
    
};

#endif
