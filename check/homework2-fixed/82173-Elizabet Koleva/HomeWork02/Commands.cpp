#include "Commands.h"

Commands::Commands() 
    : userCommand("")
{
}

//Commands::Commands(string userInput)
//    : userCommand(userInput)
//{
//}

unsigned int Commands::countLengthTillSpace(const string& source, const size_t& startPos) const{
    unsigned int i = startPos;
    
    unsigned int counter = 0;
    while ( i < source.length() && source[i] != ' ') {
        ++i;
        ++counter;
    }
    return counter;
}

void Commands::capitalize(string& what) {
   
    for(size_t i = 0; i < (what.length()); ++i) {
        if(what[i] >= 'a' && what[i] <= 'z') {
            what[i] -= 'a'-'A';
        }
    }

}

void Commands::checkAnswer(string& answer) {
    cin >> answer;

    capitalize(answer);

    if (answer != "YES" && answer != "NO") {
        do {
            cout << "Unknown answer! Please enter only yes or no!" << endl;
            cin >> answer;
            capitalize(answer);
        } while (answer != "YES" && answer != "NO");
    }
}

void Commands::removeSpaces(string& line)
{
    unsigned i = 0;
    while (i < line.size() && line[i] == ' ') {
        i++;
    }
    line = line.substr(i);

}

string Commands::getCommand() {
    return userCommand;
}

void Commands::addCar(size_t posRegNumb, size_t posDescrip, std::vector<Vehicle*>& allVehicles) {
    userCommand = userCommand.substr(posRegNumb);
    removeSpaces(userCommand);
    string regNumber = userCommand.substr(0, countLengthTillSpace(userCommand, 0));
    
    Registration* newReg;
    newReg = new Registration(regNumber);

    string vehDescr = userCommand.substr(posDescrip-posRegNumb, (userCommand.length()- posDescrip+posRegNumb));
   
    bool found = Commands::getCarPosition(regNumber, allVehicles);

    if (found != -1) {
        Vehicle* newVeh;
        newVeh = new Vehicle(*newReg, vehDescr);
        allVehicles.push_back(newVeh);

        // delete newReg;
    }
    else {
        // cout << "Car with this registration number already exists! Add new one! :/" << endl;
        throw std::invalid_argument("");
        return;
    }
}

void Commands::addPerson(size_t posFirstName, size_t posLastName, size_t posID, std::vector<Person*>& people) {
    string name;
    int userID;

    if (posLastName) {
        name = userCommand.substr(posFirstName, (posLastName-posFirstName));
    }
    else {
        name = userCommand.substr(posFirstName, countLengthTillSpace(userCommand, posFirstName));
    }

    userCommand.erase(userCommand.begin(), userCommand.begin() + (posID));//whats left is the id
   
    removeSpaces(userCommand);

    for (unsigned int i = 0; i < userCommand.length(); ++i) {
        if (userCommand[i] < '0' || userCommand[i] > '9') {
            // cout << "The id must contains only positive whole numbers!" << endl;
            throw std::invalid_argument("");
            return;
        }
    }
    userID = std::stoi(userCommand);

    if (personPosition(userID, people) != -1) {
        // cout << "Person with the same ID already exists! :/" << endl;
        throw std::invalid_argument("");
        return;
    }

    Person* newPerson;
    newPerson = new Person(name, userID);
    people.push_back(newPerson);

}

void Commands::acquireCar(size_t posOwnerId, size_t posRegNumb, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles) {
    string ownerIdStr = userCommand.substr(posOwnerId, countLengthTillSpace(userCommand, posOwnerId));

    unsigned int uniqueId = stoi(ownerIdStr);
    
    string userRegNumb = userCommand.substr(posRegNumb, (userCommand.length()- posRegNumb));
  
    int carPos = Commands::getCarPosition(userRegNumb, allVehicles);
    int personPos = personPosition(uniqueId, people);

    if (carPos != -1 && personPos != -1) {
        allVehicles[carPos]->setOwner((*people[personPos]));
    }
   
}


void Commands::releaseCar(size_t posOwnerId, size_t posRegNumb, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles) {
    string ownerIdStr = userCommand.substr(posOwnerId, countLengthTillSpace(userCommand, posOwnerId));

    unsigned int uniqueId = stoi(ownerIdStr);

    string userRegNumb = userCommand.substr(posRegNumb, (userCommand.length() - posRegNumb));

    int carPos = Commands::getCarPosition(userRegNumb, allVehicles);
    int personPos = personPosition(uniqueId, people);

    if (carPos != -1 && personPos != -1) {
        allVehicles[carPos]->removeOwner();
    }
}

void Commands::removeObject(size_t positionOfWhat, std::vector<Person*>& people, std::vector<Vehicle*>& allVehicles) {
    capitalize(userCommand);

    userCommand.erase(userCommand.begin(), userCommand.begin() + (positionOfWhat));
    removeSpaces(userCommand);
    if (userCommand[0] >= '0' && userCommand[0] <= '9') {
        unsigned int uniqueId = stoi(userCommand);
        int persPosit = personPosition(uniqueId, people);

        if (persPosit == -1) {
            // cout << "No person exists with this id!" << endl;
            throw std::invalid_argument("");
            return;
        }

        if (people[persPosit]->doIPossessVehicles()) {
            cout << "This person owns cars! Do you really wanna remove him/her? Yes / No answers" << endl;
            string answer;
            
            checkAnswer(answer);

            if (answer == "YES") {
                people[persPosit]->removeAllOwnedVehicles();
                delete people[persPosit];
                people.erase(people.begin() + persPosit);
            }
            else {
                return;
            }
        }
        else {
            delete people[persPosit];
            people.erase(people.begin() + persPosit);
        }
    }
    else if (userCommand[0] >= 'A' && userCommand[0] <= 'Z') {
        int vehiclePosit = Commands::getCarPosition(userCommand, allVehicles);
        
        if (vehiclePosit == -1) {
            // cout << "No vehicle exists with this reg number!" << endl;
            throw std::invalid_argument("");
            return;
        
        }

        if (allVehicles[vehiclePosit]->isOwned()) {
            cout << "This car is owned by someone! Do you really wanna remove it? Yes / No answers" << endl;
            string answer;
            
            checkAnswer(answer);

            if (answer == "YES") {
                allVehicles[vehiclePosit]->removeOwner();
                delete allVehicles[vehiclePosit];
                allVehicles.erase(allVehicles.begin() + vehiclePosit);
            }
            else {
                return;
            }
        }
        else {
            delete allVehicles[vehiclePosit];
            allVehicles.erase(allVehicles.begin() + vehiclePosit);
        }
    }
    else {
        // cout << "Unknown argument! Please enter either an ID of someone or car's plate number!" << endl;
        throw std::invalid_argument("");
        return;
    }

}

Commands Commands::operator=(const string& userInput) {
    if (userCommand != userInput) {
        userCommand = userInput;
    }

    return *this;
}

int Commands::personPosition(const unsigned int& ownerId, const std::vector<Person*>& people) {
    if (people.size() > 0) {
        try {
            for (size_t i = 0; i < people.size(); ++i) {
                if (people[i]->getID() == ownerId) {
                    //found = true;
                    return i;
                }
            }
            return -1;
        }
        catch (const std::out_of_range())
        {
            cout << "Couldn't find!" << endl;
            return -1;
        }
        catch (...)
        {
            cout << "Caught a problem!" << endl;
            return -1;
        }
    }
    else {
        cout << "No people available!" << endl;
        return - 1;
    }

}

int Commands::getCarPosition(const string& regNumber, const std::vector<Vehicle*>& allVehicles) {
    for (size_t i = 0; i < allVehicles.size(); ++i) {
        if (allVehicles[i]->getRegistrationNumb() == regNumber) {
            return i;
        }
    }
    return -1;
}
