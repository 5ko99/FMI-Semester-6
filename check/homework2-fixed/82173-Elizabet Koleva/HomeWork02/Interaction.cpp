#include "Interaction.h"

Interaction::~Interaction() {
    people.clear();
    people.resize(0);

    allVehicles.clear();
    allVehicles.resize(0);
}

void Interaction::capitalizeString(string& source) {
    size_t i = 0;

    while(i < source.length() && source[i] != ' ') {
        if(source[i] >= 'a' && source[i] <= 'z') {
            source[i] -= 'a'-'A';
        }
        ++i;
    }
}

unsigned int Interaction::getArgumentsNumber() const {
    unsigned int numberOfArguments = 1;

    for(size_t i = 0; i < (command.length()-1); ++i) {
        if(command[i] == ' ' && command[i+1] != ' ') {
            ++numberOfArguments;
        }
    }

    return numberOfArguments;
}

unsigned int Interaction::getArgument(const unsigned int& lastArgPos) {
    bool foundNewWord = false;
    size_t i = lastArgPos;

    while(!foundNewWord && i<command[i]-1) {
        if(command[i] != ' ' && command[i+1] == ' ') {
        foundNewWord = true;
      }
      ++i;
    }
   // while (i < command.size() && command[i] != ' ') {
   //     i++; 
   // }

    //while (i < command[i] && command[i] == ' ') {
    //    i++;
    //}

    size_t foundAt = command.find("\"");
    if (foundAt != string::npos) {
      return i+1;
    }

    return i+1;
}

unsigned int Interaction::areThereMultipleArguments() const{
    size_t foundAt = command.find("\"");

    if (foundAt != string::npos) {
        return foundAt+1;
    }

    return 0;
}

unsigned int Interaction::getQuote(const unsigned int& lastQuotePos) const{
    size_t foundAt = command.find("\"", lastQuotePos+1);

    if (foundAt != string::npos) {
        return foundAt;
    }

    return 0;
}

void Interaction::copyUserChoice(string userInput) {
    command = userInput;
}

void Interaction::userPreference(string userCommand) {
    unsigned int numberOfArguments;
    
    copyUserChoice(userCommand);
    
    userPref = userCommand;
    //capitalizeString(userCommand); //added by me
    numberOfArguments = getArgumentsNumber();
    if (numberOfArguments < 2) {
        cout << "Not enough arguments in the command! :( Or maybe the command is unknown! :/" << endl 
             << "Try again with more!" << endl;
        throw std::invalid_argument("");
    }
    else {
        unsigned int posRegNumber = 0;
        unsigned int posDescript = 0;
        unsigned int posPersId = 0;
        unsigned int posWhatObj = 0;

        if (userCommand.find("VEHICLE") != string::npos) {
            posRegNumber = getArgument(0);

            if(areThereMultipleArguments()) {
                posDescript = areThereMultipleArguments();
            }
            else {
                posDescript = getArgument(posRegNumber);
            }

            userPref.addCar(posRegNumber, posDescript, allVehicles);
        }
        else if (userCommand.find("PERSON") != string::npos) {
            if(areThereMultipleArguments()) {
                unsigned int posPersFirstName = areThereMultipleArguments();
                unsigned int posPersLastName = getQuote(posPersFirstName);
                posPersId = getArgument(posPersLastName);
                userPref.addPerson(posPersFirstName, posPersLastName, posPersId, people);
            }
            else {
                unsigned int posPersName = getArgument(0);
                posPersId = getArgument(posPersName);
                userPref.addPerson(posPersName, 0, posPersId, people);
            }
        }
        else if (userCommand.find("ACQUIRE") != string::npos) {
            posPersId = getArgument(0);
            posRegNumber = getArgument(posPersId);
            userPref.acquireCar(posPersId, posRegNumber, people, allVehicles);
        }
        else if (userCommand.find("RELEASE") != string::npos) {
            posPersId = getArgument(0);
            posRegNumber = getArgument(posPersId);
            userPref.releaseCar(posPersId, posRegNumber, people, allVehicles);
        }
        else if (userCommand.find("REMOVE") != string::npos) {
            posWhatObj = getArgument(0);
            userPref.removeObject(posWhatObj, people, allVehicles);
        }
        else if (userCommand.find("SAVE") != string::npos) {
            unsigned int file = getArgument(0);
            saveFile(userCommand, file);
        }
        else if (userCommand.find("SHOW") != string::npos) {
            posWhatObj = getArgument(0);
            showInfo(userCommand, posWhatObj);
        }
        else {
            cout << "Unknown command! :( Try again with one of the above!" << endl;
            throw std::invalid_argument("");
            return;
        }
            
    }        
}



void Interaction::checkAnswer(string& answer) {
    cin >> answer;

    capitalizeString(answer);

    if (answer != "YES" && answer != "NO") {
        do {
            cout << "Unknown answer! Please enter only yes or no!" << endl;
            cin >> answer;
            capitalizeString(answer);
        } while (answer != "YES" && answer != "NO");
    }
}

void Interaction::saveFile(string& userCommand, unsigned int filePos) {
    std::fstream file;
    while (filePos < userCommand.size() && userCommand[filePos]==' ') {
        filePos++;
    }
    userCommand = userCommand.substr(filePos);
    
    if (userCommand.size() >=2 && userCommand.front()=='\"' && userCommand.back()=='\"') {//so its quoted adress
        userCommand = userCommand.substr(1,userCommand.size()-2);
    }
    file.open(userCommand);
    if (file.good()) {
        file.close();
        std::cout << "The file already exists. Do you want to overwrite it? Please, enter only yes or no!";
        std::string answer;
        checkAnswer(answer);
        if (answer == "NO") {
            return;
        }
    }
    file.open(userCommand, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open()) {
        cout << "Couldn't open the file!" << endl;
        return;
    }
    else {
        for (unsigned int i = 0; i < people.size(); ++i) {
            (*people[i]).printCommand(file);
            cout << "Person #" << i+1 << " with name " << (*people[i]) << endl;

        }

        for (unsigned int i = 0; i < allVehicles.size(); ++i) {
            (*allVehicles[i]).printCommand(file);
            (*allVehicles[i]).printCommand(cout);

        }
    }
    std::cout << "All the data was saved!" << endl;
    file.close();
}

void Interaction::showInfo(string& userCommand, size_t positionOfWhat) const {
    userCommand.erase(userCommand.begin(), userCommand.begin() + (positionOfWhat));

    unsigned int userID = 0;
    bool isID = false;

    if(userCommand.front() >= '0' && userCommand.front() <= '9') {
        userID = stoi(userCommand);
        isID = true;
    }

    Interaction::capitalizeString(userCommand);

    cout << userCommand << endl;

    if ((userCommand.find("PEOPLE") != string::npos)) {
        for (unsigned int i = 0; i < people.size(); ++i) {
            cout << "Person #" << i+1 << " with name " << (*people[i]) << endl;
        }
    }
    else if ((userCommand.find("VEHICLES") != string::npos)) {
        for (unsigned int i = 0; i < allVehicles.size(); ++i) {
            cout << "Vehicle #" << i+1 << " with reg number: " << (*allVehicles[i]) << endl;
        }
    }
    else if (isID) {
        int persPosit = -2;

        try {
            persPosit = Commands::personPosition(userID, people);
        }
        catch (const int number) {
            throw -1;
        }
        catch (const std::out_of_range())
        {
            std::cerr << "Couldn't find!" << endl;
            return;
        }

        cout << "Name: " << (*people[persPosit]) << endl;

        people[persPosit]->printOwnedCars();
    }
    else {
        try {
            Registration userReg(userCommand);
            int position = Commands::getCarPosition(userCommand, allVehicles);

            if (position != -1) {
                allVehicles[position]->printEverything(cout);
            }
            else {
                cout << "The vehicle with the registration number: " << userCommand << " doesn't exist! :/ "<< endl;
            }
        }
        catch (const int number)
        {
            if (number == -1) {
                std::cerr << "Problems with the input data! Cannot find a vehicle with this plate number - " << userCommand << endl;
            }
        }
    }
}

Interaction Interaction::operator=(const Interaction& otherInteract) {
    if (this != &otherInteract) {
        command = otherInteract.command;
        userPref = otherInteract.userPref;
        people = otherInteract.people;
        allVehicles = otherInteract.allVehicles;
    }

    return *this;
}
