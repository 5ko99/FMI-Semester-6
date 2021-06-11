#ifndef HOMEWORK_2_COMMAND_HANDLER_H
#define HOMEWORK_2_COMMAND_HANDLER_H

#include "PersonCollection.h"

/// For educational purposes we have two different approaches - std::string vs c-style string
/// NB! This would not be good idea in a real project due to its inconsistency

const unsigned MAX_INPUT = 150;

class CommandHandler {
private:
    char m_input[MAX_INPUT];
    char *m_command;

    // Helpers - may be put in separate class Utils (for example)
    void toLower(char *string);

    bool isUpper(char letter);

    bool isAlpha(char symbol);

    void saveToFile(char *path,
                    const PersonCollection &personCollection,
                    const VehicleCollection &vehicleCollection);

public:
    /// Realisation is done with std::string
    void readFromFile(std::string &path,
                      PersonCollection &personCollection,
                      VehicleCollection &vehicleCollection);

    /// Realisation is done with c-style strings
    void readFromConsole(PersonCollection &personCollection, VehicleCollection &vehicleCollection);

};


#endif //HOMEWORK_2_COMMAND_HANDLER_H
