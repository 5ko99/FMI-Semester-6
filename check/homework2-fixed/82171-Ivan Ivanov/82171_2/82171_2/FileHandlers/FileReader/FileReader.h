#ifndef FILE_READER_H
#define FILE_READER_H

#include "../../ObjectHolders/PersonHolder/PersonHolder.h"
#include "../../ObjectHolders/VehicleHolder/VehicleHolder.h"
#include <fstream>

// Reads command from file.
// File path should be full.
class FileReader {
    public:
        static void generateFromFile(std::string fileAddress, PersonHolder* pH, VehicleHolder* vH);
};

#endif
