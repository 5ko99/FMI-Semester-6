#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Solution.h"
Solution::Solution()
{
    people.reserve(100);
    vehicles.reserve(100);
}
std::string Solution::stringInQuotes(std::istream &in)
{
    std::string str;
    char c;
    while (true)
    {
        in >> std::noskipws >> c;
        if (c == '"')
            break;
        str += c;
    }
    in >> std::skipws;
    return str;
}
void Solution::vehicle(Registration &reg, std::string &desc)
{
    for (int i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].registration() == reg)
            throw std::invalid_argument("Vehicle with this registration already exist");
    }
    vehicles.push_back(Vehicle(reg, desc));
}
void Solution::person(std::string &name, unsigned int id)
{
    for (int i = 0; i < people.size(); ++i)
    {
        if (people[i].getID() == id)
            throw std::invalid_argument("Person with this id already exist");
    }
    people.push_back(Person(name, id));
}
void Solution::release(unsigned int id, Registration &reg)
{
    for (int i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].registration() == reg)
        {
            if (&vehicles[i].owner())
                vehicles[i].owner().removeVehicle(vehicles[i]);
            vehicles[i].setOwner(nullptr);
        }
    }
}
void Solution::acquire(unsigned int id, Registration &reg)
{
    Person *p;
    for (int i = 0; i < people.size(); ++i)
    {
        if (people[i].getID() == id)
        {
            p = &people[i];
            break;
        }
    }
    for (int i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].registration() == reg)
        {
            release(id, reg);
            vehicles[i].setOwner(p);
            p->addVehicle(vehicles[i]);
            break;
        }
    }
}
void Solution::remove(std::string &what)
{
    bool isNumber = true;
    for (int i = 0; i < what.size(); ++i)
    {
        if (!(what[i] >= '0' && what[i] <= '9'))
        {
            isNumber = false;
            break;
        }
    }
    if (isNumber)
    {
        unsigned int id = 0;
        for (int i = 0; i < what.size(); ++i)
        {
            id *= 10;
            id += what[i] - '0';
        }

        int pos = -1;
        for (int i = 0; i < people.size(); ++i)
        {
            if (people[i].getID() == id)
            {
                for (int j = 0; j < people[i].cntVehicles(); ++j)
                {
                    people[i][j].setOwner(nullptr);
                }
                pos = i;
                break;
            }
        }
        if (pos == -1)
            return;
        people.erase(people.begin() + pos);
        for (int i = pos; i < people.size(); ++i)
        {
            for (int j = 0; j < people[i].cntVehicles(); ++j)
            {
                people[i][j].setOwner(&people[i]);
            }
        }
    }
    else
    {
        Registration reg(what.c_str());
        int pos = -1;
        bool f = false;
        for (int i = 0; i < vehicles.size(); ++i)
        {
            if (vehicles[i].registration() == reg)
            {
                if (&vehicles[i].owner())
                    vehicles[i].owner().removeVehicle(vehicles[i]);
                pos = i;
                f = true;
            }
            else if (f)
            {
                if (&vehicles[i].owner())
                    vehicles[i].owner().removeVehicle(vehicles[i]);
            }
        }
        if (pos == -1)
            return;
        vehicles.erase(vehicles.begin() + pos);
        for (int i = pos; i < vehicles.size(); ++i)
        {
            if (&vehicles[i].owner())
            {
                vehicles[i].owner().addVehicle(vehicles[i]);
            }
        }
    }
}
void Solution::save(std::string &path)
{
    if (std::ifstream(path))
    {
        std::cout << "File exist. Do you want to continue? y/n ";
        char c;
        std::cin >> c;
        if (c == 'n')
            return;
    }
    std::fstream file(path, std::fstream::out);
    for (int i = 0; i < people.size(); ++i)
    {
        file << "person " << people[i].getName() << " " << people[i].getID() << "\n";
    }
    for (int i = 0; i < vehicles.size(); ++i)
    {
        file << "vehicle " << vehicles[i].registration() << " " << vehicles[i].description() << "\n";
    }
    for (int i = 0; i < people.size(); ++i)
    {
        for (int j = 0; j < people[i].cntVehicles(); ++j)
        {
            file << "acquire " << people[i].getID() << " " << people[i][j].registration() << "\n";
        }
    }
    file.close();
}
void Solution::show(std::string &option)
{
    if (option == "PEOPLE")
    {
        for (int i = 0; i < people.size(); ++i)
        {
            std::cout << "Person ID and name: " << people[i].getID() << " " << people[i].getName() << ". Owned vehicles: ";

            for (int j = 0; j < people[i].cntVehicles(); ++j)
            {
                std::cout << people[i][j].description() << " " << people[i][j].registration() << " ";
            }
            std::cout << "\n";
        }
    }
    else if (option == "VEHICLES")
    {

        for (int i = 0; i < vehicles.size(); ++i)
        {
            std::cout << "Vehicle registration and description: "
                      << vehicles[i].registration() << " " << vehicles[i].description() << " ";
            if (&vehicles[i].owner())
                std::cout << ". Owner ID and name: " << vehicles[i].owner().getID() << " " << vehicles[i].owner().getName();
            std::cout << "\n";
        }
    }
    else
    {
        bool isNumber = true;
        for (int i = 0; i < option.size(); ++i)
        {
            if (!(option[i] >= '0' && option[i] <= '9'))
            {
                isNumber = false;
                break;
            }
        }
        if (isNumber)
        {
            unsigned int id = 0;
            for (int i = 0; i < option.size(); ++i)
            {
                id *= 10;
                id += option[i] - '0';
            }
            for (int i = 0; i < people.size(); ++i)
            {
                if (people[i].getID() == id)
                {
                    std::cout << "Owned vehicles: ";
                    for (int j = 0; j < people[i].cntVehicles(); ++j)
                    {
                        std::cout << people[i][j].registration() << " " << people[i][j].description() << "\n";
                    }
                    break;
                }
            }
        }
        else
        {
            try
            {
                Registration reg(option.c_str());
            }
            catch (std::invalid_argument &e)
            {
                std::cout << e.what() << "\n";
                return;
            }
            Registration reg(option.c_str());
            for (int i = 0; i < vehicles.size(); ++i)
            {
                if (vehicles[i].registration() == reg)
                {
                    std::cout << "Owner ID and name: " << vehicles[i].owner().getID() << " " << vehicles[i].owner().getName() << "\n";
                }
            }
        }
    }
}
void Solution::execCommand(std::istream &in)
{
    std::string command;
    in >> command;
    for (int i = 0; i < command.size(); ++i)
    {
        if (command[i] >= 'A' && command[i] <= 'Z')
        {
            command[i] -= 'A' - 'a';
        }
    }
    if (command == "vehicle")
    {
        Registration reg;
        std::string desc;
        try
        {
            in >> reg;
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << "\n";
            in >> desc;
            return;
        }
        char c;
        in >> c;
        if (c == '"')
        {
            desc = stringInQuotes(in);
        }
        else
        {
            desc += c;
            std::string tmp;
            in >> tmp;
            desc += tmp;
        }
        try
        {
            vehicle(reg, desc);
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << "\n";
            return;
        }
    }
    else if (command == "person")
    {
        char c;
        std::string name;
        in >> c;
        if (c == '"')
        {
            name = stringInQuotes(in);
        }
        else
        {
            name += c;
            std::string tmp;
            in >> tmp;
            name += tmp;
        }

        unsigned int id;
        in >> id;
        try
        {
            person(name, id);
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << "\n";
            return;
        }
    }
    else if (command == "acquire")
    {
        unsigned int id;
        Registration reg;
        try
        {
            in >> id >> reg;
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << "\n";
            return;
        }
        acquire(id, reg);
    }
    else if (command == "release")
    {
        unsigned int id;
        Registration reg;
        try
        {
            in >> id >> reg;
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << "\n";
            return;
        }
        release(id, reg);
    }
    else if (command == "remove")
    {
        std::string what;
        in >> what;
        remove(what);
    }
    else if (command == "save")
    {
        std::string path;
        in >> path;
        save(path);
    }
    else if (command == "show")
    {
        std::string option;
        in >> option;
        show(option);
    }
    else
    {
        std::cout << "Invalid command\n";
    }
}
