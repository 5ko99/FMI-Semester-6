#include "Commands.h"

bool IsValidReg(const std::string& other)
{
    if (other.size() < 7 || other.size() > 8)
    {
        return 0;
    }
    bool isValid1 = 0;
    bool isValid2 = 0;
    if (other[0] >= 'A' && other[0] <= 'Z' && other[1] >= '0' && other[1] <= '9' && other[2] >= '0' && other[2] <= '9' && other[3] >= '0' && other[3] <= '9' && other[4] >= '0' && other[4] <= '9' && other[5] >= 'A' && other[5] <= 'Z' && other[6] >= 'A' && other[6] <= 'Z')
        isValid1 = 1;
    if (other[0] >= 'A' && other[0] <= 'Z' && other[1] >= 'A' && other[1] <= 'Z' && other[2] >= '0' && other[2] <= '9' && other[3] >= '0' && other[3] <= '9' && other[4] >= '0' && other[4] <= '9' && other[5] >= '0' && other[5] <= '9' && other[6] >= 'A' && other[6] <= 'Z' && other[7] >= 'A' && other[7] < 'Z')
        isValid2 = 1;
    if ((isValid1 || isValid2) == 0)
    {
        return 0;
    }
    return 1;
}

std::string UpperToLower(std::string& command)
{
    for(int i = 0; i < command.size(); i++)
    {
        if(command.at(i) >= 'A' && command.at(i) <= 'Z')
        {
            command.at(i) = command.at(i) - 'A' + 'a';
        }
    }
    return command;
}

void CreateVehicle(std::vector<Vehicle>& arr, const std::string& descr, const Registration& registr)
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(strcmp(arr.at(i).GetReg().registr(), registr.registr()) == 0)
        {
            throw "A Vehicle with such a Registration already exists!\n";
        }
    }
    const Vehicle veh(registr, descr);
    arr.push_back(veh);
    std::cout << "Vehicle has been added successfully\n";
}

void CreatePerson(std::vector<Person>& arr, const unsigned int& id, const std::string& name)
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr.at(i).GetId() == id)
        {
            throw "A Person with such an id already exists!\n";
        }
    }
    Person person(name, id);
    arr.push_back(person);
    std::cout << "Person has been added successfully\n";
    return;
}

void ACQUIRE(const std::string& reg, const unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2)
{
    int i = 0;
    for(i; i < arr1.size(); i++)
    {
        if(arr1.at(i).GetId() == id)
        {
            break;
        }
    }
    int p = 0;
    for(p; p < arr2.size(); p++)
    {
        if(std::strcmp(arr2.at(p).GetReg().registr(), reg.c_str()) == 0)
        {
            break;
        }
    }
    if(arr2.at(p).GetPerson() != nullptr)
    {
        throw "This vehicle is already owned!\n";
    }
    if(i == arr1.size())
    {
        if(arr1.at(i - 1).GetId() != id)
        {
            throw "Id not found!\n";
        }
    }
    if(p == arr2.size())
    {
        if(std::strcmp(arr2.at(p - 1).GetReg().registr(), reg.c_str()) != 0)
        {
            throw "Registration number not found!\n";
        }
    }
    arr1.at(i).AddVehicle(arr2.at(p));
    arr2.at(p).addPerson(arr1.at(i));
    std::cout<< "Acquire was successful\n";
}

void RELEASE(const std::string& reg, unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2)
{
    int i = 0;
    for(i; i < arr1.size(); i++)
    {
        if(arr1.at(i).GetId() == id)
        {
            break;
        }
    }
    int p = 0;
    for(p; p < arr2.size(); p++)
    {
        if(std::strcmp(arr2.at(p).GetReg().registr(), reg.c_str()) == 0)
        {
            break;
        }
    }
    if(i == arr1.size())
    {
        if(arr1.at(i - 1).GetId() != id)
        {
            throw "Id not found!\n";
        }
    }
    if(p == arr2.size())
    {
        if(std::strcmp(arr2.at(p - 1).GetReg().registr(), reg.c_str()) != 0)
        {
            throw "Registration number not found!\n";
        }
    }

    arr1.at(i).RELEASE(reg);
    arr2.at(p).RemovePerson();
    std::cout << "Vehicle was released successfully!\n";
}

void REMOVEVeh(std::string reg, std::vector<Vehicle>& arr2, std::vector<Person>& arr1)
{
    int p = 0;
    for(p; p < arr2.size(); p++)
    {
        if(std::strcmp(arr2.at(p).GetReg().registr(), reg.c_str()) == 0)
        {
            if(arr2.at(p).GetPerson() == nullptr) {
                arr2.erase(arr2.begin() + p);
                std::cout<< "Vehicle successfully removed\n";
                return;
            }
            else
            {
                std::cout << "Do you really wish to delete this Vehicle, it may be the property of a person?\n";
                std::cout << "Type Yes or No\n";
                std::string command;
                std::cin >> command;
                UpperToLower(command);
                if(strcmp(command.c_str(), "yes") == 0)
                {
                    unsigned int ident = arr2.at(p).GetPerson()->GetId();
                    RELEASE(reg, ident, arr1, arr2);
                    arr2.erase(arr2.begin() + p);
                    std::cout<< "Vehicle successfully removed\n";
                }
                if(strcmp(command.c_str(), "no") == 0)
                {
                    std::cout<< "Operation stopped.\n";
                }
                return;
            }
        }
    }
    throw "No such Vehicle found\n";
}

void RemovePerson(unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2)
{
    for(int i = 0; i < arr1.size(); i++)
    {
        if(arr1.at(i).GetId() == id)
        {
            if(arr1.at(i).isEmpty()) {
                arr1.erase(arr1.begin() + i);
                return;
            }
            else {
                std::cout << "This Person owns Vehicles, do you wish to remove him?\n";
                std::cout << "Type Yes or No\n";
                std::string command;
                std::cin >> command;
                UpperToLower(command);
                if(strcmp(command.c_str(), "yes") == 0)
                {
                    for(int p = 0; p < arr1.at(i).GetSize(); p++)
                    {
                        std::string registr;
                        registr = arr1.at(i).GetVehicle(p).GetReg().registr();
                        RELEASE(registr, id, arr1, arr2);
                    }
                    arr1.erase(arr1.begin() + i);
                }
                return;
            }
        }
    }
    throw "A person with that id wasn't found!\n";
}

void SAVE(std::string path, std::vector<Person>& arr1, std::vector<Vehicle>& arr2)
{
    std:: ofstream File;
    File.open(path);
    if(!File.is_open())
    {
        std::cout<< "Not a valid path, so the file will be saved in the project's directory.\n";
        File.open("Configuration.txt");
    }
    for(int i = 0; i < arr1.size(); i++) {
        File << arr1.at(i).GetName() << std::endl << arr1.at(i).GetId() << std::endl;
        for(int p = 0; p < arr1.at(i).GetSize(); p++)
        {
            File << arr1.at(i).GetVehicle(p).GetReg().registr() << std::endl << arr1.at(i).GetVehicle(p).Getdescr() << std::endl;
        }
        File << std::endl;
    }
    File << "Not owned Vehicles:\n";
    for(int i = 0; i < arr2.size(); i++)
    {
        if(arr2.at(i).GetPerson() == nullptr)
        {
            File << arr2.at(i).GetReg().registr() << std::endl << arr2.at(i).Getdescr() << std::endl;
        }
    }
    File.close();
    std::cout << "File saved successfully.\n";
}

void SHOWPeople(std::vector<Person>& arr1)
{
    for(int i = 0; i < arr1.size(); i++)
    {
        std::cout << " `" << arr1.at(i).GetName() << "` " << arr1.at(i).GetId() << std::endl;
    }
}

void SHOWVehicles(std::vector<Vehicle>& arr2)
{
    for(int i = 0; i < arr2.size(); i++)
    {
        std::cout << " `" << arr2.at(i).GetReg().registr() << "` " << arr2.at(i).Getdescr() << std::endl;
    }

}

void SHOWVPersonWithVehicle(unsigned int id,  std::vector<Person>& arr1)
{
    for(int i = 0; i < arr1.size(); i++) {
        if (arr1.at(i).GetId() == id) {
            std::cout << " `" << arr1.at(i).GetName() << "` " << arr1.at(i).GetId() << std::endl;
            for(int p = 0; p < arr1.at(i).GetSize(); p++)
            {
                std::cout << arr1.at(i).GetVehicle(p).GetReg().registr() << "` "  << arr1.at(i).GetVehicle(p).Getdescr() << std::endl;
            }
            break;
        }
    }
}

void SHOWVehicleWithPerson(std::string reg,  std::vector<Vehicle>& arr2)
{
    for(int i = 0; i < arr2.size(); i++) {
        if (strcmp(arr2.at(i).GetReg().registr() , reg.c_str()) == 0) {
            std::cout << " `" << arr2.at(i).GetReg().registr() << "` " << arr2.at(i).Getdescr() << std::endl;
            if(arr2.at(i).GetPerson() == nullptr)
            {
                break;
            }
            std::cout << "Owner: " << " `" << arr2.at(i).GetPerson()->GetName() << "` " <<  arr2.at(i).GetPerson()->GetId() << std::endl;
            break;
        }
    }
}



void LoadFromFile(std::string path, std::vector<Person>& arr1, std::vector<Vehicle>& arr2)
{
    std::ifstream File(path);

    if(!File.is_open())
    {
        std::cout<< "Incorrect path\n";
        std::cout<< "Please enter a correct one:\n";
        std::string pathnew;
        std::cin >> pathnew;
        LoadFromFile(pathnew, arr1, arr2);
    }
    std::string thing;
    while(std::getline(File, thing)) {
        if(IsValidReg(thing))
        {
            while (IsValidReg(thing)) {
                std::string description;
                std::getline(File, description);
                Registration registr(thing);
                CreateVehicle(arr2, description, registr);
                std::getline(File, thing);
            }
            break;
        }
        else
        {
            std::string id;
            while (strcmp(thing.c_str(), "Not owned Vehicles:") != 0 && (!IsValidReg(thing))) {
                std::getline(File, id);
                unsigned int ident = 0;
                for (int i = 0; i < id.size(); i++) {
                    ident = ident + (id.at(i) - '0') * pow(10, id.size() - i - 1);
                }
                CreatePerson(arr1, ident, thing);
                std::getline(File, thing);
                while (IsValidReg(thing)) {
                    std::string description;
                    std::getline(File, description);
                    Registration registr(thing);
                    CreateVehicle(arr2, description, registr);
                    ACQUIRE(thing, ident, arr1, arr2);
                    std::getline(File, thing);
                }
                std::getline(File, thing);
            }
        }
    }
}

int RegOrId(const std::string& command)
{
    int IsReg = 1;
    int NotValid = 0;
    int IsId = 2;
    if(IsValidReg(command) == 1)
    {
        return IsReg;
    }
    for(int i = 0; i < command.size(); i++)
    {
        if(command.at(i) < '0' || command.at(i) > '9')
        {
            return NotValid;
        }
    }
    return IsId;
}
