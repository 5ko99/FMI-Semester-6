#include "Program.h"
#include "problemfile.h"

std::string getCommand(std::string &command)
{
    int first_quotation = -1;
    int last_quotation = -1;

    std::string str;

    if (command.at(0) == '\"')
    {
        first_quotation = 0;
        for (int i = 1; i < command.size(); ++i)
        {
            if (command.at(i) == '\"')
            {
                last_quotation = i;
            }
        }

        if (last_quotation == -1)
        {
            throw std::invalid_argument("Only one quotation mark\n");
        }

        for (++first_quotation; first_quotation < last_quotation; ++first_quotation)
        {
            str.push_back(command.at(first_quotation));
        }

        if (last_quotation == command.size() - 1 || last_quotation == command.size())
        {
            command = "";
        }
        else
        {
            command = command.substr(last_quotation + 2);
        }
    }
    else
    {
        for (int j = 0; j < command.size(); ++j)
        {
            if (command.at(j) != ' ')
            {
                str.push_back(command.at(j));
            }
            else
            {
                if (j == command.size() - 1)
                {
                    command = "";
                }
                else
                {
                    command = command.substr(j + 1);
                }

                return str;
            }
        }

        command = "";
    }

    return str;
}

void getAllArguments(std::string command, std::string &first, std::string &second, std::string &third)
{
    int pos = command.find(" ");
    first = command.substr(0, pos);
    command = command.substr(pos + 1);

    second = getCommand(command);

    if (!command.empty())
    {
        third = getCommand(command);
    }
}

size_t getEmptyRowNumber(std::string file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
    {
        throw ProblemFile();
    }

    int counter = 1;
    size_t empty_row;
    while (!file.eof())
    {
        std::string buffer;
        getline(file, buffer);
        if (buffer.empty())
        {
            empty_row = counter;
            break;
        }
        counter++;
    }
    file.close();

    return empty_row;
}

void Program::copy(const Program &other)
{
    people = other.people;
    vehicles = other.vehicles;
}

void Program::clean()
{
    people.clear();
    vehicles.clear();
}

Program::Program()
{
    people.clear();
    vehicles.clear();
}

Program::Program(const Program &other)
{
    copy(other);
}

Program &Program::operator=(const Program &other)
{
    if (this != &other)
    {
        clean();
        copy(other);
    }

    return *this;
}

Program::~Program()
{
    clean();
}

Program::Program(std::string file_name)
{
    people = Program::readPeople(file_name);
    vehicles = Program::readVehicles(file_name);
}

std::vector<Person> Program::readPeople(std::string file_name)
{
    std::ifstream file(file_name, std::ios::in);
    std::vector<Person> people;

    if (!file.is_open())
    {
        throw ProblemFile();
    }

    int line = 1;
    int c = getEmptyRowNumber(file_name);
    std::string row;
    while (getline(file, row))
    {
        if (line > c)
        {
            Person temp = readPerson(row);
            people.push_back(temp);
            std::cout << "Person is being read from file..." << std::endl;
        }
        line++;
    }
    file.close();

    return people;
}

Person Program::readPerson(std::string line)
{
    int i = 0;

    std::string temp_name;
    while (line[i] != ',')
    {
        temp_name.push_back(line[i]);
        i++;
    }
    i++;

    std::string temp_ID;
    while (line[i] != ',')
    {
        temp_ID.push_back(line[i]);
        i++;
    }

    std::vector<std::string> tempVehicles;

    while (line[i] != '\0')
    {
        i++;

        if (line[i] == '\0')
        {
            break;
        }

        std::string tempReg;
        while (line[i] != ',' && line[i] != '\0')
        {
            tempReg.push_back(line[i]);
            i++;
        }

        tempVehicles.push_back(tempReg);
    }

    Person temp_person(temp_name, stoi(temp_ID), tempVehicles);

    return temp_person;
}

std::vector<Vehicle> Program::readVehicles(std::string file_name)
{
    std::ifstream f(file_name, std::ios::in);
    std::vector<Vehicle> vehicles;

    if (!f.is_open())
    {
        throw ProblemFile();
    }

    int line = 1;
    std::string row;
    while (getline(f, row))
    {
        if (row.empty())
        {
            break;
        }
        Vehicle temp = readVehicle(row);
        vehicles.push_back(temp);
        std::cout << "A vehicle is being read..." << std::endl;

        line++;
    }
    f.close();

    return vehicles;
}

Vehicle Program::readVehicle(std::string line)
{
    int i = 0;

    std::string temp_name;
    while (line[i] != ',')
    {
        temp_name.push_back(line[i]);
        i++;
    }
    Registration tempRegistration(temp_name);
    i++;

    std::string temp_description;
    while (line[i] != ',')
    {
        temp_description.push_back(line[i]);
        i++;
    }
    i++;

    if (line[i] == '\0')
    {
        Vehicle temp_vehicle(tempRegistration, temp_description);
        return temp_vehicle;
    }

    std::string temp_owner;
    while (line[i] != '-')
    {
        temp_owner.push_back(line[i]);
        i++;
    }
    i++;

    std::string temp_ID;
    while (line[i] != '\0')
    {
        temp_ID.push_back(line[i]);
        i++;
    }

    Vehicle temp_vehicle(tempRegistration, temp_description, stoi(temp_ID));

    return temp_vehicle;
}

void Program::addVehicle(const Registration &registration, const std::string &description)
{
    Vehicle new_vehicle(registration, description);

    for (int i = 0; i < vehicles.size(); i++)
    {
        if (registration.getRegistration().compare(vehicles[i].getReg().getRegistration()) == 0)
        {
            std::cout << "This vehicle exists!" << std::endl;
            return;
        }
    }

    vehicles.push_back(new_vehicle);
}

void Program::addPerson(const std::string &name, const unsigned int id)
{
    Person new_person(name, id);

    for (int i = 0; i < people.size(); i++)
    {
        if (id == people[i].getID())
        {
            std::cout << "This person exists!" << std::endl;
            return;
        }
    }

    people.push_back(new_person);
}

bool Program::isItID(const std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str.at(i) < 48 || str.at(i) > 57)
        {
            return false;
        }
    }

    return true;
}

bool Program::isItReg(const std::string str)
{
    Registration r(str);

    return r.valid_symbol();
}

bool Program::isItWord(const std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) < 48 || str.at(i) > 57)
        {
            return true;
        }
    }

    return false;
}

void Program::release(const unsigned int id, const Registration &registration)
{
    Vehicle temp(registration, "description");

    int index = -1;
    for (int i = 0; i < people.size(); i++)
    {
        if (id == people[i].getID())
        {
            index = i;
        }
    }

    for (int i = 0; i < vehicles.size(); i++)
    {
        if (registration.getRegistration().compare(vehicles[i].getReg().getRegistration()) == 0)
        {
            temp = vehicles[i];
            vehicles[i].eraseOwner();

            people[index].eraseVehicle(temp);
        }
    }
}

void Program::acquire(const unsigned int id, const Registration &registration)
{
    Vehicle temp_vehicle(registration, "description");
    for (int i = 0; i < vehicles.size(); i++)
    {
        if (registration.getRegistration().compare(vehicles[i].getReg().getRegistration()) == 0)
        {
            temp_vehicle = vehicles[i];
        }
    }

    if (temp_vehicle.isThereAnOwner() == true)
    {
        release(temp_vehicle.getOwner(), registration);
    }

    Person temp_person("name", id);
    for (int i = 0; i < people.size(); i++)
    {
        if (id == people[i].getID())
        {
            temp_person = people[i];
            people[i].insertVehicle(temp_vehicle);
        }
    }

    for (int i = 0; i < vehicles.size(); i++)
    {
        if (registration.getRegistration().compare(vehicles[i].getReg().getRegistration()) == 0)
        {
            vehicles[i].insertOwner(temp_person);
        }
    }
}

void Program::remove(const std::string what)
{
    if (what.empty())
    {
        std::cout << "There is nothing to remove" << std::endl;
        return;
    }

    if (isItID(what))
    {
        unsigned int tempID = stoi(what);
        Person temp_person("name", tempID);
        size_t k;

        bool found = false;
        for (int i = 0; i < people.size(); i++)
        {
            if (tempID == people[i].getID())
            {
                temp_person = people[i];
                k = i;
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "Could not find that person!" << std::endl;
            return;
        }

        if (temp_person.getOwnedVehiclesCount() > 0)
        {
            std::string choice;
            std::cout << "Are you sure you want to remove this person?" << std::endl
                      << "Please, write (yes/no): ";
            std::cin >> choice;

            if (choice.compare("no") == 0)
            {
                return;
            }
            else if (choice.compare("yes") != 0)
            {
                std::cout << "Wrong input";
                return;
            }
        }

        for (int i = 0; i < temp_person.getOwnedVehiclesCount(); i++)
        {
            release(temp_person.getID(), temp_person.getElement(i));
        }

        people.erase(people.begin() + k);

        std::cout << "Person is removed!" << std::endl;
    }

    if (isItReg(what))
    {
        Registration tempReg(what);
        Vehicle tempVehicle(tempReg, "desc");
        size_t l;

        for (int i = 0; i < vehicles.size(); i++)
        {
            if (tempReg.getRegistration().compare(vehicles[i].getReg().getRegistration()) == 0)
            {
                tempVehicle = vehicles[i];
                l = i;
            }
        }

        if (tempVehicle.isThereAnOwner())
        {
            std::string choice;
            std::cout << "Are you sure you want to remove this vehicle?" << std::endl
                      << "Please, write (yes/no): ";
            std::cin >> choice;

            if (choice.compare("no") == 0)
            {
                return;
            }
            else if (choice.compare("yes") != 0)
            {
                std::cout << "Wrong input";
                return;
            }
        }

        release(tempVehicle.getOwner(), tempVehicle.getReg());
        vehicles.erase(vehicles.begin() + l);

        std::cout << "Vehicle is removed!" << std::endl;
    }
    else
    {
        std::cout << "You did not enter a valid id or registration!" << std::endl;
    }
}

void Program::show(std::string what)
{
    if (what.empty())
    {
        std::cout << "There is nothing to show" << std::endl;
        return;
    }

    std::cout << std::endl;

    if (isItID(what))
    {
        int tempId = stoi(what);
        for (int i = 0; i < people.size(); i++)
        {
            if (tempId == people[i].getID())
            {
                std::cout << "Wanted person: " << std::endl;
                std::cout << "Name: " << people[i].getName() << " ID: " << people[i].getID() << std::endl;
                for (int j = 0; j < vehicles.size(); j++)
                {
                    if (vehicles[j].getOwner() == tempId)
                    {
                        std::cout << "Owned vehicles:" << std::endl;
                        std::cout << "Registration: " << vehicles[j].getReg().getRegistration() << " Description: " << vehicles[j].getDetails() << std::endl;
                    }
                }
                std::cout << std::endl;
                break;
            }
        }
    }
    else if (isItReg(what))
    {
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i].getReg().getRegistration() == what)
            {
                std::cout << "Wanted vehicle:" << std::endl;
                std::cout << "Registration: " << vehicles[i].getReg().getRegistration() << " Description: " << vehicles[i].getDetails() << std::endl;
                for (int j = 0; j < people.size(); j++)
                {
                    if (people[i].getID() == vehicles[i].getOwner())
                    {
                        std::cout << "Owner of vehicle:" << std::endl;
                        std::cout << "Name: " << people[i].getName() << " ID: " << people[i].getID() << std::endl
                                  << std::endl;
                        break;
                    }
                }
                break;
            }
        }
    }
    else if (isItWord(what))
    {

        if (what == "people")
        {
            std::cout << "People:" << std::endl;

            for (int i = 0; i < people.size(); i++)
            {
                std::cout << people[i].getName() << " / " << people[i].getID() << " / " << people[i].getOwnedVehiclesCount() << std::endl;
            }
            std::cout << std::endl;
        }
        else if (what == "vehicles")
        {
            std::cout << "Vehicles:" << std::endl;

            for (int i = 0; i < vehicles.size(); i++)
            {
                std::cout << vehicles[i].getReg().getRegistration() << " / " << vehicles[i].getDetails() << " / " << vehicles[i].isThereAnOwner() << std::endl;
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Invalid input" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
    }
}

void Program::saveToFile(std::string fileName)
{
    std::ofstream out(fileName, std::ios::trunc);

    if (!out.is_open())
    {
        throw ProblemFile();
    }

    for (int i = 0; i < vehicles.size(); i++)
    {
        out << vehicles[i].getReg().getRegistration() << ',' << vehicles[i].getDetails() << ',';

        if (vehicles[i].isThereAnOwner())
        {
            for (int j = 0; j < people.size(); j++)
            {
                if (people[j].getID() == vehicles[i].getOwner())
                {
                    out << people[j].getName() << '-' << people[j].getID();
                }
            }
        }

        out << std::endl;
    }

    out << std::endl;

    for (int i = 0; i < people.size(); i++)
    {
        out << people[i].getName() << ',' << people[i].getID() << ',';

        for (int j = 0; j < people[i].getOwnedVehiclesCount(); j++)
        {
            out << people[i].getElement(j) << ',';
        }

        out << std::endl;
    }
}
