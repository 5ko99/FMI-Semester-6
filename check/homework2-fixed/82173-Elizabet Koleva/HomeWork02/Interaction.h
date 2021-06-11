#ifndef INTERACTION_H
#define INTERACTION_H

#include <fstream>

#include "Commands.h"

class Interaction {

private:

    string command;

    Commands userPref;

    std::vector<Person*> people;

    std::vector<Vehicle*> allVehicles;

    void copyUserChoice(string userInput); // Copying user's input
 
    unsigned int getArgumentsNumber() const; // User's command is checked for the word count

    unsigned int getArgument(const unsigned int& lastArgPos); // Getting the position of an argument in user's command

    unsigned int areThereMultipleArguments() const; // If the user input name is "[name]"

    unsigned int getQuote(const unsigned int& lastQuotePos) const; // Getting the position of the las " in user's input name

    void checkAnswer(string& answer);
    

public:
    Interaction() = default;

    ~Interaction();

    static void capitalizeString(string& source); // Makes the string in capital letters

    void userPreference(string userCommand); // The menu and depending on the command which to function run

    void saveFile(string& userCommand, unsigned int filePos); // Saving the data into a file

    void showInfo(string& userCommand, size_t positionOfWhat) const; // Printing information

    Interaction operator=(const Interaction& otherInteract);

};

#endif
