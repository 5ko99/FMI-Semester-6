#ifndef PV_DATABASE
#define PV_DATABASE

#include "../ObjectHolders/PersonHolder/PersonHolder.h"
#include "../ObjectHolders/VehicleHolder/VehicleHolder.h"
#include "../CommandInterpreter/CommandInterpreter.h"
#include "../FileHandlers/FileReader/FileReader.h"

class PVDatabase {
    private:
        PersonHolder pH;
        VehicleHolder vH;
        
        void printCommands();
    public:
        PVDatabase();

        // Generates data from file if such one is given
        void setUp(int numParam, char* param[]);
        void readCommands();
};

#endif
