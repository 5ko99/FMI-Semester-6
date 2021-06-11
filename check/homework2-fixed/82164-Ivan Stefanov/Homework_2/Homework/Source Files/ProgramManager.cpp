#include "ProgramManager.h"

const size_t MAX = 500;

bool file_exists(const std::string& str)
{
    std::ifstream fs(str);
    return fs.is_open();
}

const char* toUpper(std::string str)
{
    for(size_t i = 0;i < str.size();++i)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = (char)((int)str[i] + (int)'A' - (int)'a');
        }
    }
    return str.c_str();
}

ProgramManager& ProgramManager::getInstance()
{
    static ProgramManager process;
    return process;
}

ProgramManager::ProgramManager()
{
    Person::instancesOfPerson.clear();
    Vehicle::instancesOfVehicle.clear();
}

void ProgramManager::getInputFromFile(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout<<"Couldn't load data from file : "<<path<<std::endl;
        return;
    }
    while(!file.eof())
    {
        char buffer[MAX];
        file.getline(buffer,MAX,'\n');
        input = std::string(buffer);
        tokenize();
        executeCommand();
        tokens.clear();
    }
}


void ProgramManager::getInputFromConsole()
{
    char buffer[MAX];
    std::cout<<'>';
    std::cin.getline(buffer,MAX,'\n');
    input = std::string(buffer);
    tokenize();
    executeCommand();
    tokens.clear();
}

void ProgramManager::tokenize()
{
    char *token = strtok(const_cast<char*>(input.c_str()), " \t");
    while (token != nullptr)
    {
        tokens.emplace_back(token);
        token = strtok(nullptr, " \t");
    }
}

bool ProgramManager::runProgram() const
{
    return !terminateProgram;
}

void  ProgramManager::executeCommand()
{
    if(tokens.size() > 3)
    {
        std::cout<<"Unknown command!"<<std::endl;
    }
    else if(tokens.size() == 1)
    {
        if(strcmp(toUpper(tokens[0]),"EXIT") == 0)
        {
            command_EXIT();
        }
        else
        {
            std::cout<<"Unknown command!"<<std::endl;
        }
    }
    else if(tokens.size() == 2)
    {
        if(strcmp(toUpper(tokens[0]),"REMOVE") == 0)
        {
            command_REMOVE();
        }
        else if(strcmp(toUpper(tokens[0]),"SAVE") == 0)
        {
            command_SAVE();
        }
        else if(strcmp(toUpper(tokens[0]),"SHOW") == 0)
        {
            command_SHOW();
        }
        else
        {
            std::cout<<"Unknown command!"<<std::endl;
        }
    }
    else if(tokens.size() == 3)
    {
        if(strcmp(toUpper(tokens[0]),"VEHICLE") == 0)
        {
            command_VEHICLE();
        }
        else if(strcmp(toUpper(tokens[0]),"PERSON") == 0)
        {
           command_PERSON();
        }
        else if(strcmp(toUpper(tokens[0]),"ACQUIRE") == 0)
        {
            command_ACQUIRE();
        }
        else if(strcmp(toUpper(tokens[0]),"RELEASE") == 0)
        {
            command_RELEASE();
        }
        else
        {
            std::cout<<"Unknown command!"<<std::endl;
        }
    }
}

void ProgramManager::command_EXIT()
{
    std::cout<<"Any unsaved data will be lost. "
             <<"Are you sure you want to close the program? "
             <<"Yes/No"
             <<std::endl;
    std::string user_input;
    while(true)
    {
        std::cin>>user_input;
        if(strcmp(toUpper(user_input),"YES") == 0)
        {
            terminateProgram = true;
            break;
        }
        else if(strcmp(toUpper(user_input),"NO") == 0)
        {
            break;
        }
        else
        {
            std::cout<<"Answer with Yes/No "
                     <<"(regardless of capitalisation)"
                     <<std::endl;
        }
    }
}

void ProgramManager::command_REMOVE()
{
    unsigned int temp_person_id;
    std::string temp_vehicle_id;
    bool isPerson = true;
    try
    {
        temp_person_id = std::stoul(tokens[1]);
    }
    catch(const std::invalid_argument&)
    {
        isPerson = false;
    }

    if(isPerson)
    {
        Person* temp_person = Person::findPerson(temp_person_id);
        if(temp_person)
        {
            if(temp_person->ownedVehiclesCount() == 0)
            {
                std::cout<<"Person with id: "
                         <<temp_person_id
                         <<" removed!"<<std::endl;
                Person::removePerson(temp_person);
            }
            else
            {
                std::cout<<"The Person with id: "
                         <<temp_person_id
                         <<" owns "<<temp_person->ownedVehiclesCount()<<" Vehicle(s). "
                         <<"Are you sure you want to remove it? "
                         <<"Yes/No"
                         <<std::endl;
                std::string user_input;
                while(true)
                {
                    std::cin>>user_input;
                    if(strcmp(toUpper(user_input),"YES") == 0)
                    {
                        std::cout<<"Person with id: "
                                 <<temp_person_id
                                 <<" removed!"<<std::endl;
                        temp_person->releaseAllOwnedVehicles();
                        Person::removePerson(temp_person);
                        break;
                    }
                    else if(strcmp(toUpper(user_input),"NO") == 0)
                    {
                        break;
                    }
                    else
                    {
                        std::cout<<"Answer with Yes/No "
                                 <<"(regardless of capitalisation)"
                                 <<std::endl;
                    }
                }
            }
        }
        else
        {
            std::cout<<"There is no Person with id: "
                     <<temp_person_id
                     <<std::endl;
        }
    }
    else
    {
        temp_vehicle_id = tokens[1];
        Vehicle* temp_vehicle = nullptr;
        try {
            temp_vehicle = Vehicle::findVehicle(temp_vehicle_id.c_str());
        }
        catch(const std::invalid_argument& e)
        {
            std::cout<<e.what()<<std::endl;
            temp_vehicle = nullptr;
        }
        if(temp_vehicle)
        {
            if(temp_vehicle->isOwned())
            {
                std::cout<<"The Vehicle with registration: "
                         <<temp_vehicle_id
                         <<" is owned. "
                         <<"Are you sure you want to remove it? "
                         <<"Yes/No"
                         <<std::endl;
                std::string user_input;
                while(true)
                {
                    std::cin>>user_input;
                    if(strcmp(toUpper(user_input),"YES") == 0)
                    {
                        std::cout<<"Vehicle with registration: "
                                 <<temp_vehicle_id
                                 <<" removed!"<<std::endl;
                        temp_vehicle->setOwner(nullptr);
                        Vehicle::removeVehicle(temp_vehicle);
                        break;
                    }
                    else if(strcmp(toUpper(user_input),"NO") == 0)
                    {
                        break;
                    }
                    else
                    {
                        std::cout<<"Answer with Yes/No "
                                 <<"(regardless of capitalisation)"
                                 <<std::endl;
                    }
                }
            }
            else
            {
                std::cout<<"Vehicle with registration: "
                         <<temp_vehicle_id
                         <<" removed!"<<std::endl;
                Vehicle::removeVehicle(temp_vehicle);
            }
        }
        else
        {
            std::cout<<"There is no Vehicle with registration: "
                     <<temp_vehicle_id
                     <<std::endl;
        }
    }
}

void ProgramManager::command_SAVE()
{
    if(file_exists(tokens[1]))
    {
        std::cout<<"The file with name: "
                 <<tokens[1]
                 <<" already exists."
                 <<" Are you sure you want to overwrite it? "
                 <<"Yes/No"
                 <<std::endl;
        std::string user_input;
        while(true)
        {
            std::cin>>user_input;
            if(strcmp(toUpper(user_input),"YES") == 0)
            {
                std::cout<<"File will be overwritten!"<<std::endl;
                break;
            }
            else if(strcmp(toUpper(user_input),"NO") == 0)
            {
                std::cout<<"Canceling SAVE command!"<<std::endl;
                return;
            }
            else
            {
                std::cout<<"Answer with Yes/No "
                         <<"(regardless of capitalisation)"
                         <<std::endl;
            }
        }
    }

    std::ofstream save_file(tokens[1].c_str(),std::ios::trunc);
    if (!save_file.is_open())
    {
        std::cout<<"Couldn't open file : "<<tokens[1]<<std::endl;
        return;
    }

    std::size_t numberOfPeople,numberOfVehicles;
    numberOfPeople = Person::instancesOfPerson.size();
    numberOfVehicles = Vehicle::instancesOfVehicle.size();
    for(std::size_t i = 0;i < numberOfPeople;++i)
    {
        save_file<<"PERSON "
                 <<Person::instancesOfPerson[i].getName()
                 <<' '<<Person::instancesOfPerson[i].getOwnerID()
                 <<'\n';
    }

    for(std::size_t i = 0;i < numberOfVehicles;++i)
    {
        save_file<<"VEHICLE "
                 <<Vehicle::instancesOfVehicle[i].getVehicleID()
                 <<' '<<Vehicle::instancesOfVehicle[i].getVehicleDescription()
                 <<'\n';
    }

    for(std::size_t i = 0;i < numberOfPeople;++i)
    {
        std::size_t vehicleCount = Person::instancesOfPerson[i].ownedVehiclesCount();
        for(std::size_t j = 0;j < vehicleCount;++j)
        {
            save_file<<"ACQUIRE "
                     <<Person::instancesOfPerson[i].getOwnerID()
                     <<' '<<Person::instancesOfPerson[i].vehicleAt(j)->getVehicleID()
                     <<'\n';
        }
    }
    save_file.close();
    std::cout<<"Data was saved in file : "<<tokens[1]<<std::endl;
}

void ProgramManager::command_SHOW()
{
    if(strcmp(toUpper(tokens[1]),"PEOPLE") == 0)
    {
        std::size_t numberOfPeople = Person::instancesOfPerson.size();
        for(std::size_t i = 0;i < numberOfPeople;++i)
        {
            std::cout<<"PERSON "
                     <<Person::instancesOfPerson[i].getName()
                     <<' '<<Person::instancesOfPerson[i].getOwnerID()
                     <<'\n';
        }
    }
    else if(strcmp(toUpper(tokens[1]),"VEHICLES") == 0)
    {
        std::size_t numberOfVehicles = Vehicle::instancesOfVehicle.size();
        for(std::size_t i = 0;i < numberOfVehicles;++i)
        {
            std::cout<<"VEHICLE "
                     <<Vehicle::instancesOfVehicle[i].getVehicleID()
                     <<' '<<Vehicle::instancesOfVehicle[i].getVehicleDescription()
                     <<'\n';
        }
    }
    else
    {
        unsigned int temp_person_id;
        std::string temp_vehicle_id;
        bool isPerson = true;
        try
        {
            temp_person_id = std::stoul(tokens[1]);
        }
        catch(const std::invalid_argument&)
        {
            isPerson = false;
        }

        if(isPerson)
        {
            Person* temp_person = Person::findPerson(temp_person_id);
            if(temp_person)
            {
                std::size_t vehicleCount = temp_person->ownedVehiclesCount();
                for(std::size_t i = 0;i < vehicleCount;++i)
                {
                    std::cout<<"VEHICLE "
                             <<temp_person->vehicleAt(i)->getVehicleID()
                             <<' '<<temp_person->vehicleAt(i)->getVehicleDescription()
                             <<'\n';
                }
                std::cout<<"PERSON "
                         <<temp_person->getName()
                         <<' '<<temp_person_id<<std::endl;
            }
            else
            {
                std::cout<<"There isn't a Person with id: "
                         <<temp_person_id<<std::endl;
            }
        }
        else
        {
            temp_vehicle_id = tokens[1];
            Vehicle* temp_vehicle = nullptr;
            try {
                temp_vehicle = Vehicle::findVehicle(temp_vehicle_id.c_str());
            }
            catch(const std::invalid_argument& e)
            {
                std::cout<<e.what()<<std::endl;
                temp_vehicle = nullptr;
            }

            if(temp_vehicle)
            {
                std::cout<<"VEHICLE "
                         <<temp_vehicle_id
                         <<' '<<temp_vehicle->getVehicleDescription()
                         <<std::endl;
                if(temp_vehicle->isOwned())
                {
                    std::cout<<"PERSON "
                             <<temp_vehicle->owner->getName()
                             <<' '<<temp_vehicle->owner->getOwnerID()
                             <<std::endl;
                }
            }
            else
            {
                bool validRegistration = true;
                try {
                    Registration temp(temp_vehicle_id.c_str());
                }
                catch(const std::invalid_argument&)
                {
                    validRegistration = false;
                }

                if(validRegistration)
                {
                    std::cout<<"There isn't a Vehicle with registration: "
                             <<temp_vehicle_id<<std::endl;
                }
                else
                {
                    std::cout<<"Wrong input!"<<std::endl;
                }
            }
        }
    }
}

void ProgramManager::command_VEHICLE()
{
    if(Vehicle::findVehicle(tokens[1].c_str()))
    {
        std::cout<<"A Vehicle with registration:"
                 <<tokens[1]
                 <<" already exists!"<<std::endl;
    }
    else
    {
        Vehicle::instancesOfVehicle.emplace_back(Vehicle(tokens[1].c_str(),tokens[2]));
        std::cout<<"Vehicle created!"<<std::endl;
    }
}

void ProgramManager::command_PERSON()
{
    unsigned int temp_person_id;
    temp_person_id = std::stoul(tokens[2]);
    if(Person::findPerson(temp_person_id))
    {
        std::cout<<"A Person with id:"
                 <<temp_person_id
                 <<" already exists!"<<std::endl;
    }
    else
    {
        Person::instancesOfPerson.emplace_back(Person(tokens[1],temp_person_id));
        std::cout<<"Person created!"<<std::endl;
    }
}

void ProgramManager::command_ACQUIRE()
{
    unsigned int temp_person_id;
    temp_person_id = std::stoul(tokens[1]);
    Person* temp_person = Person::findPerson(temp_person_id);
    Vehicle* temp_vehicle = nullptr;
    try {
        temp_vehicle = Vehicle::findVehicle(tokens[2].c_str());
    }
    catch(const std::invalid_argument& e)
    {
        std::cout<<e.what()<<std::endl;
        temp_vehicle = nullptr;
    }
    if(temp_person && temp_vehicle)
    {
        temp_person->addVehicle(temp_vehicle);
        std::cout<<"Person acquired vehicle!"<<std::endl;
    }
    else
    {
        std::cout<<"Wrong input!"<<std::endl;
    }
}

void ProgramManager::command_RELEASE()
{
    unsigned int temp_person_id;
    temp_person_id = std::stoul(tokens[1]);
    Person* temp_person = Person::findPerson(temp_person_id);
    Vehicle* temp_vehicle = nullptr;
    try {
        temp_vehicle = Vehicle::findVehicle(tokens[2].c_str());
    }
    catch(const std::invalid_argument& e)
    {
        std::cout<<e.what()<<std::endl;
        temp_vehicle = nullptr;
    }
    if(temp_person && temp_vehicle)
    {
        temp_person->releaseVehicle(temp_vehicle);
        std::cout<<"Person released vehicle!"<<std::endl;
    }
    else
    {
        std::cout<<"Wrong input!"<<std::endl;
    }
}



