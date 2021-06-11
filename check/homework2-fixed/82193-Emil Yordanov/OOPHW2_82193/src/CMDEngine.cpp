#include"CMDEngine.h"

bool CMDEngine::ParseCMDToData(std::string& userCMD, std::string& firstArgument, std::string& secondArgument, std::string& commandOrderData, PersonManager& pManager, VehicleManager& vManager, bool isDataFromFile) {
    if(StringHelper::StringToLower(userCMD) == "vehicle") {
        try {
            if(!isDataFromFile) {
                std::cin >> firstArgument >> secondArgument;
            }

            Vehicle newVehicle = Vehicle(firstArgument, secondArgument);
            bool isAdded = vManager.AddVehicle(&newVehicle);

            if(!isAdded) {
                std::cout << "New vehicle could not be added. Try again." << std::endl;
            }
            else {
                if(!isDataFromFile) {
                    if(commandOrderData != "") {
                        commandOrderData.append("\n");
                    } 
                    
                    commandOrderData.append(userCMD + " " + firstArgument + " " + secondArgument);
                }
            }
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "person") {
        try {
            if(!isDataFromFile) {
                std::cin >> firstArgument >> secondArgument;
            }

            Person newPerson = Person(firstArgument, std::stoi(secondArgument));
            bool isAdded = pManager.AddPerson(&newPerson);

            if(!isAdded) {
                std::cout << "New person could not be added. Try again." << std::endl;
            }
            else {
                if(!isDataFromFile) {
                    if(commandOrderData != "") {
                        commandOrderData.append("\n");
                    } 
                    
                    commandOrderData.append(userCMD + " " + firstArgument + " " + secondArgument);
                }
            }
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "acquire") {
        try {
            if(!isDataFromFile) {
                std::cin >> firstArgument >> secondArgument;
            }

            Person* personToGet = pManager.GetPersonById(std::stoi(firstArgument));
            Vehicle* vehicleToGet = vManager.GetVehicleByRegistration(secondArgument);

            vehicleToGet->SetOwner(personToGet);
            personToGet->AddVehicleToPersonCollection(vehicleToGet);
            
            if(!isDataFromFile) {
                if(commandOrderData != "") {
                    commandOrderData.append("\n");
                } 
                    
                commandOrderData.append(userCMD + " " + firstArgument + " " + secondArgument); 
            }
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "release") {
        try {
            if(!isDataFromFile) {
                std::cin >> firstArgument >> secondArgument;
            }

            Person* personToGet = pManager.GetPersonById(std::stoi(firstArgument));
            Vehicle* vehicleToGet = vManager.GetVehicleByRegistration(secondArgument);

            personToGet->RemoveVehicleFromPersonCollection(vehicleToGet);
            vehicleToGet->RemoveOwner();

            if(!isDataFromFile) {
                if(commandOrderData != "") {
                    commandOrderData.append("\n");
                } 
                    
                commandOrderData.append(userCMD + " " + firstArgument + " " + secondArgument); 
            }
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "remove") {
        if(!isDataFromFile) {
            std::cin >> firstArgument;
        }
        
        try {
            unsigned int personId = std::stoi(firstArgument);
            
            pManager.RemovePerson(personId);
        }
        catch (std::invalid_argument const &e) {
            vManager.RemoveVehicle(firstArgument);
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
        if(!isDataFromFile) {
            if(commandOrderData != "") {
                commandOrderData.append("\n");
            } 
                
            commandOrderData.append(userCMD + " " + firstArgument); 
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "save" && !isDataFromFile) {
        try {
            std::cin >> firstArgument;
            
            // Opens a stream to a file with the path equal to the 'firstArgument' variable
            std::ofstream outputFile(firstArgument);
            outputFile << commandOrderData;

            return false;
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else if(StringHelper::StringToLower(userCMD) == "show" && !isDataFromFile) {
        try {
            std::cin >> firstArgument;
            
            if(StringHelper::StringToLower(firstArgument) == "people") {
                std::vector<Person*> people = pManager.GetAll();
                for (size_t iterator = 0; iterator < people.size(); iterator++)
                {
                    std::cout << people[iterator]->ToString() << std::endl;
                }
            }
            else if(StringHelper::StringToLower(firstArgument) == "vehicles") {
                std::vector<Vehicle*> vehicles = vManager.GetAll();
                for (size_t iterator = 0; iterator < vehicles.size(); iterator++)
                {
                    std::cout << vehicles[iterator]->ToString() << std::endl;
                }
            }
            else {
                try {
                    unsigned int personId = std::stoi(firstArgument);

                    Person* personToGet = pManager.GetPersonById(personId);
                    std::cout << personToGet->ToString() << std::endl;
                }
                catch (std::invalid_argument const &e) {
                    Vehicle* vehicleToGet = vManager.GetVehicleByRegistration(firstArgument);
                    std::cout << vehicleToGet->ToString() << std::endl;
                }
                catch (std::exception& unhExc) {
                    std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
                }
            }
        }
        catch (std::exception& unhExc) {
            std::cout << "An exception was thrown with the message: " << unhExc.what() << std::endl;
        }
    }
    else {
        if(isDataFromFile) {
            throw std::invalid_argument("File data is not correct!");
        }

        std::cout << "\'" << userCMD << "\'" << " is not a command. Please try again with something else." << std::endl;
    }

    return true;
}
