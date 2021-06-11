#include <iostream>
#include "Headers/Vehicle.h"
#include "Headers/PersonCollection.h"
#include "Headers/CommandHandler.h"

int main(int argc, char *argv[]) {
    CommandHandler ch;
    PersonCollection personCollection;
    VehicleCollection vehicleCollection;

    if (argc == 2) {
        std::string fileName = argv[1];
        ch.readFromFile(fileName, personCollection, vehicleCollection);
    }
    ch.readFromConsole(personCollection, vehicleCollection);
    return 0;
}
