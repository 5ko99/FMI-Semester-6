#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "../../ObjectHolders/PersonHolder/PersonHolder.h"
#include "../../ObjectHolders/VehicleHolder/VehicleHolder.h"
#include <fstream>
#include <iostream>

// Writes commands to a file, which generate the same holders.
// File path should be full.
class FileWriter {
    public:
        static void writeToFile(std::string fileAddress, PersonHolder* pH, VehicleHolder* vH);
};

#endif
